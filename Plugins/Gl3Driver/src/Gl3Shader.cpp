//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3Shader.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 06/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3Shader.h>

////////////////////////////////////////////////////////////
Gl3Shader::Gl3Shader( const String& file , const MimeType& mime , Stage stage , GLenum glstage , va_list& args )
: Shader( stage , file , mime ) , m_glid( 0 )
{
    auto filecontent = atl::LoadFileContent( file );
    
    if ( filecontent.empty() )
    {
        throw Gl3Exception( Gl3Error::EmptyFile , "File is empty: %s " , file.data() );
    }
    
    iGl3Shader( filecontent , glstage , args );
}

////////////////////////////////////////////////////////////
Gl3Shader::Gl3Shader( std::istream& is , const MimeType& mime , Stage stage , GLenum glstage , va_list& args )
: Shader( stage , "istream" , mime ) , m_glid( 0 )
{
    is.seekg( 0 , is.end );
    size_t size = is.tellg();
    is.seekg( 0 , is.beg );
    
    if ( !size )
    {
        throw Gl3Exception( Gl3Error::EmptyStream , "Stream is empty." );
    }
    
    char* buffer = new char [size+1];
    assert( buffer && "Invalid allocation of buffer. (memory not sufficient)" );
    memset( buffer , 0 , size+1 );
    is.read( buffer , size );
    
    String source( buffer );
    delete[] buffer ;
    
    assert( source.size() && "Invalid input stream." );
    iGl3Shader( source , glstage , args );
}

////////////////////////////////////////////////////////////
Gl3Shader::~Gl3Shader()
{
    GLuint glid = m_glid.load();
    
    if ( glid )
    {
        glDeleteShader( glid );
    }
}

////////////////////////////////////////////////////////////
GLuint Gl3Shader::GetGlId() const
{
    return m_glid.load();
}

////////////////////////////////////////////////////////////
void Gl3Shader::iGl3Shader( const String& source , GLenum glstage , va_list& args )
{
    GLuint shaderid = glCreateShader( glstage );
    
    if ( shaderid )
    {
        GLint size = source.size();
        const GLchar* data = source.data();
        
        glShaderSource( shaderid , 1 , &data , &size );
        glCompileShader( shaderid );
        
        GLint compiled ;
        glGetShaderiv( shaderid , GL_COMPILE_STATUS , &compiled );
        if ( compiled != GL_TRUE )
        {
            GLsizei log_length = 0 ;
            GLchar message [1024] ;
            glGetShaderInfoLog( shaderid , 1024 , &log_length , message );
            throw Gl3Exception( Gl3Error::GlCompileShader , "Compiler error (%s): %s" , GetFile().data() , message );
        }
        
        m_glid.store( shaderid );
        return ;
    }
    
    throw Gl3Exception( Gl3Error::GlCreateShader , "'glCreateShader' failed." );
}
