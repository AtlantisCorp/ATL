//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3Program.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 11/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/ErrorCenter.hpp>
#include <ATL/VertexComponent.hpp>
#include <Gl3Driver/Gl3Program.h>
#include <Gl3Driver/Gl3Shader.h>
#include <Gl3Driver/Gl3Context.h>
#include <ATL/Root.hpp>

#ifdef GL3DRIVER_CATCHGLERROR

////////////////////////////////////////////////////////////
void CatchGlError( const char* func )
{
    static GLenum err = GL_NO_ERROR ;
    err = glGetError();
    
    if ( err != GL_NO_ERROR )
    {
        ErrorCenter::CatchError( Error::PluginError , "OpenGL (%i): '%s()' failed." , (int)err , func );
    }
}

#else

////////////////////////////////////////////////////////////
#define CatchGlError( ... ) (void)

#endif

////////////////////////////////////////////////////////////
uint32_t GlTypeToComponent( GLenum gltype )
{
#define RET( a , b ) if ( gltype == a ) return b ;
    
    RET( GL_FLOAT ,              VertexComponent::R32Float )
    RET( GL_FLOAT_VEC2 ,         VertexComponent::R32G32Float )
    RET( GL_FLOAT_VEC3 ,         VertexComponent::R32G32B32Float )
    RET( GL_FLOAT_VEC4 ,         VertexComponent::R32G32B32A32Float )
    RET( GL_INT ,                VertexComponent::R32Sint )
    RET( GL_INT_VEC2 ,           VertexComponent::R32G32Sint )
    RET( GL_INT_VEC3 ,           VertexComponent::R32G32B32Sint )
    RET( GL_INT_VEC4 ,           VertexComponent::R32G32B32A32Sint )
    RET( GL_UNSIGNED_INT ,       VertexComponent::R32Uint )
    RET( GL_UNSIGNED_INT_VEC2 ,  VertexComponent::R32G32Uint )
    RET( GL_UNSIGNED_INT_VEC3 ,  VertexComponent::R32G32B32Uint )
    RET( GL_UNSIGNED_INT_VEC4 ,  VertexComponent::R32G32B32A32Uint )
    
#undef RET
    
    return VertexComponent::Unknown ;
};

////////////////////////////////////////////////////////////
bool GlIsSampler( GLenum gltype )
{
    return gltype == GL_SAMPLER_1D || gltype == GL_SAMPLER_2D || gltype == GL_SAMPLER_3D ||
           gltype == GL_SAMPLER_CUBE ;
}

////////////////////////////////////////////////////////////
Gl3Program::Gl3Program( const SharedVector < Shader >& shaders , const Weak < Gl3Context >& context )
: Program( shaders ) , m_glid( 0 ) , m_countunit( 0 ) , m_context( context )
{
    assert( !context.expired() && "'context' has expired." );
    
    GLuint glid = glCreateProgram();
    CatchGlError( "glCreateProgram" );
    
    for ( auto const& shader : shaders )
    {
        if ( !shader )
            continue ;
        
        const Shared < Gl3Shader > glshader = std::static_pointer_cast < Gl3Shader >( shader );
        glAttachShader( glid , glshader->GetGlId() );
        CatchGlError( "glAttachShader" );
    }
    
    glLinkProgram( glid );
    CatchGlError( "glLinkProgram" );
    
    GLint compiled ;
    glGetProgramiv( glid , GL_LINK_STATUS , &compiled );
    if ( compiled != GL_TRUE )
    {
        GLsizei log_length = 0 ;
        GLchar message [1024];
        glGetProgramInfoLog( glid , 1024 , &log_length , message );
        throw Gl3Exception( Gl3Error::GlLinkProgram , "Linker error: %s" , message );
    }
    
    m_glid.store( glid );
    
    glUseProgram( glid );
    {
        GlMakeLayout( glid );
        GlMakeParameters( glid );
    }
    glUseProgram( 0 );
}

////////////////////////////////////////////////////////////
Gl3Program::~Gl3Program()
{
    if ( !m_context.expired() )
    {
        auto context = m_context.lock();
        context->SetActive( true );
        
        GLuint glid = m_glid.load();
        
        if ( glid ) {
            glDeleteProgram( glid );
        }
        
        context->SetActive( false );
    }
}

////////////////////////////////////////////////////////////
void Gl3Program::Prepare( const RenderTarget& target ) const
{
    GLuint glid = m_glid.load();
    glUseProgram( glid );
}

////////////////////////////////////////////////////////////
void Gl3Program::BindParameter( const ConstantParameter* parameter , const ParameterValue& value ) const
{
    assert( parameter && "'parameter' is null." );
    GLuint uniform = parameter->GetIndex();
    
    if ( value.GetType() == ParameterType::Texture )
    {
        auto texture = value.GetTexture().lock();
        if ( !texture )
        {
            ErrorCenter::CatchError( Error::InvalidWeak , "OpenGL: Parameter '%s' was given invalid texture." , parameter->GetName().data() );
            return ;
        }
        
        auto it = m_texunits.find( parameter->GetIndex() );
        if ( it == m_texunits.end() )
        {
            ErrorCenter::CatchError( Error::ParameterBinding , "OpenGL: Parameter '%s' is not a texture." , parameter->GetName().data() );
        }
        
        else
        {
            glActiveTexture( GL_TEXTURE0 + (it->second) );
            texture->Bind();
        }
    }
    
    else if ( value.GetType() == ParameterType::Float1 ) {
        glUniform1f( uniform , value.GetFloat1() );
    }
    
    else if ( value.GetType() == ParameterType::Float2 ) {
        glUniform2fv( uniform , 1 , glm::value_ptr(value.GetFloat2()) );
    }
    
    else if ( value.GetType() == ParameterType::Float3 ) {
        glUniform3fv( uniform , 1 , glm::value_ptr(value.GetFloat3()) );
    }
    
    else if ( value.GetType() == ParameterType::Float4 ) {
        glUniform4fv( uniform , 1 , glm::value_ptr(value.GetFloat4()) );
    }
}

////////////////////////////////////////////////////////////
void Gl3Program::GlMakeLayout( GLuint glid )
{
    GLint attribs , maxattriblength ;
    glGetProgramiv( glid , GL_ACTIVE_ATTRIBUTES , &attribs );
    glGetProgramiv( glid , GL_ACTIVE_ATTRIBUTE_MAX_LENGTH , &maxattriblength );
    CatchGlError( "glGetProgramiv" );
    
    auto layout = std::make_shared < VertexLayout >();
    Logger log = Root::Get().GetLogger();
    
    for ( GLint attrib = 0 ; attrib < attribs ; ++attrib )
    {
        GLsizei attrib_length ;
        GLchar  attrib_name [maxattriblength+1];
        memset( attrib_name , 0 , maxattriblength+1 );
        GLint   attrib_size ;
        GLenum  attrib_type ;
        glGetActiveAttrib( glid , attrib , maxattriblength , &attrib_length , &attrib_size , &attrib_type , attrib_name );
        CatchGlError( "glGetActiveAttrib" );
        
        log.info( "Discovered attribute '" , String( attrib_name , attrib_length ) , "': " );
        log.info( "  .slot   = " , attrib );
        log.info( "  .size   = " , attrib_size );
        log.info( "  .length = " , attrib_length );
        log.info( "  .type   = " , (unsigned int) attrib_type );
        
        VertexAttrib newattrib( attrib , String( attrib_name , attrib_length ) , GlTypeToComponent( attrib_type ) );
        layout -> AddVertexAttrib( newattrib );
    }
    
    SetVertexLayout( layout );
}

////////////////////////////////////////////////////////////
void Gl3Program::GlMakeParameters( GLuint glid )
{
    GLint uniforms , maxuniformlength ;
    glGetProgramiv( glid , GL_ACTIVE_UNIFORMS , &uniforms );
    glGetProgramiv( glid , GL_ACTIVE_UNIFORM_MAX_LENGTH , &maxuniformlength );
    CatchGlError( "glGetProgramiv" );
    
    Vector < ConstantParameter > params ;
    Logger log = Root::Get().GetLogger();
    
    for ( GLint uniform = 0 ; uniform < uniforms ; ++uniform )
    {
        GLsizei uni_length ;
        GLint   uni_size ;
        GLenum  uni_type ;
        GLchar  uni_name [maxuniformlength+1];
        memset( uni_name , 0 , maxuniformlength+1 );
        glGetActiveUniform( glid , uniform , maxuniformlength , &uni_length , &uni_size , &uni_type , uni_name );
        CatchGlError( "glGetActiveUniform" );
        
        log.info( "Discovered uniform '" , String( uni_name , uni_length ) , "':" );
        log.info( "  .index  = " , uniform );
        log.info( "  .length = " , uni_length );
        log.info( "  .size   = " , uni_size );
        log.info( "  .type   = " , (int) uni_type );
        
        if ( GlIsSampler( uni_type ) )
        {
            GLint nextunit = m_countunit.fetch_add( 1 );
            glUniform1i( uniform , nextunit );
            m_texunits[uniform] = nextunit ;
            log.info( "  .unit   = " , (int) nextunit );
        }
        
        ConstantParameter param ;
        param.SetName( String( uni_name , uni_length ) );
        param.SetIndex( uniform );
        param.SetStage( Stage::Unknown );
        params.push_back( param );
    }
    
    SetParameters( params );
}
