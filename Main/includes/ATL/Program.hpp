//  ========================================================================  //
//
//  File    : ATL/Program.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Program_hpp
#define Program_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/IDGenerator.hpp>
#include <ATL/ConstantParameter.hpp>
#include <ATL/Alias.hpp>
#include <ATL/VertexLayout.hpp>
#include <ATL/Shader.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class RenderTarget ;
    class ParameterValue ;
    class VaryingParameter ;
    
    ////////////////////////////////////////////////////////////
    /// \brief A unique program ID generated by IDGenerator.
    ///
    ////////////////////////////////////////////////////////////
    typedef unsigned long long ProgramId ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines an interface to manipulate program (a set
    /// of shaders in a particular order).
    ///
    /// A Layout is a set of Vertex attributes that are linked to
    /// Attribute's aliases. Those Aliases are then bindable by any
    /// user to input data to the program. A VertexAttrib represents
    /// an attribute (or a slot) in a program.
    /// It is similar to a Parameter excepted the data is streamed
    /// from a buffer.
    ///
    /// A Parameter is a constant value passed to a program (or a shader
    /// stage) that is linked with an Alias. This Alias is bindable by any
    /// user to pass custom parameter values.
    ///
    ////////////////////////////////////////////////////////////
    class Program
    {
        ////////////////////////////////////////////////////////////
        static IDGenerator < ProgramId > s_generator ; ///< Static generator used to create a new identifier.
        
        ////////////////////////////////////////////////////////////
        Atomic < ProgramId >               m_id ;         ///< ID used to uniquely identifiate the program in a session.
        Map < Alias , ConstantParameter* > m_aliases ;    ///< Aliases associated to given parameter.
        Vector < ConstantParameter >       m_parameters ; ///< Parameters for input for this program.
        Shared < VertexLayout >            m_layout ;     ///< Layout used in this program.
        mutable Mutex                      m_mutex ;      ///< Acces to data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        Program();
        
        ////////////////////////////////////////////////////////////
        /// \brief Constructs a program from its shaders.
        ///
        /// While Program object claim it own the passed shaders, it does
        /// not guaranty you might be able to retrieve those objects.
        /// Please keep trace of those shared pointers if you wish to use
        /// them later.
        ///
        ////////////////////////////////////////////////////////////
        Program( const SharedVector < Shader >& shaders );
        
        ////////////////////////////////////////////////////////////
        virtual ~Program();
        
        ////////////////////////////////////////////////////////////
        virtual ProgramId GetId() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Prepares the program for uses in rendering.
        ///
        /// \param target RenderTarget that called this function. It is
        ///               given by reference to avoid Weaked locking or
        ///               Shared copying. It is not guaranteed the target
        ///               is not used by another thread while this function
        ///               is executed.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Prepare( const RenderTarget& target ) const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds an alias for a given parameter.
        ///
        /// If the parameter's name is not findable, it does nothing but
        /// return false.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool AddAlias( Alias alias , const String& name );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds an alias for given parameter's index.
        ///
        /// If the parameter's index is invalid, it returns false.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool AddAlias( Alias alias , int32_t index );
        
        ////////////////////////////////////////////////////////////
        /// \brief Removes the alias from the program.
        ///
        ////////////////////////////////////////////////////////////
        virtual void RemoveAlias( Alias alias );
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the name of the parameter associated with
        /// given alias.
        ///
        ////////////////////////////////////////////////////////////
        virtual String GetAliasName( Alias alias ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the index of the parameter associated with
        /// given alias, or -1.
        ///
        ////////////////////////////////////////////////////////////
        virtual int32_t GetAliasIndex( Alias alias ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Clears all aliases association.
        ///
        ////////////////////////////////////////////////////////////
        virtual void ResetAliases();
        
        ////////////////////////////////////////////////////////////
        /// \brief Retrieve the parameter with a three-step selection
        /// (alias/name/index) and binds its value.
        ///
        /// \param parameter ConstantParameter to bind. This parameter
        ///                  should not be modified while binding it.
        ///                  Generally, ParameterGroup returns a copy of
        ///                  its constant parameters to the RenderQueue
        ///                  and thus they are different objects.
        ///
        ////////////////////////////////////////////////////////////
        virtual void BindConstantParameter( const ConstantParameter& parameter ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Retrieve the parameter with a three-step selection
        /// (alias/name/index) and binds its value.
        ///
        /// \param parameter VaryingParameter to bind. This parameter
        ///                  is shared among RenderQueues and RenderCommands,
        ///                  and locking is most likely to happen when getting
        ///                  parameter's data.
        ///
        ////////////////////////////////////////////////////////////
        virtual void BindVaryingParameter( const Shared < VaryingParameter >& parameter ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Binds the parameter designated with name, with
        /// the given value.
        ///
        ////////////////////////////////////////////////////////////
        virtual void BindName( const String& name , const ParameterValue& value ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Binds the parameter designated by index, to the
        /// given value.
        ///
        ////////////////////////////////////////////////////////////
        virtual void BindIndex( int32_t idx , const ParameterValue& value ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Binds the parameter designated by alias, to the given
        /// value.
        ///
        ////////////////////////////////////////////////////////////
        virtual void BindAlias( Alias alias , const ParameterValue& value ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Finds the parameter with given name or return null.
        ///
        ////////////////////////////////////////////////////////////
        virtual ConstantParameter* GetParameterByName( const String& name );
        
        ////////////////////////////////////////////////////////////
        /// \brief Finds the parameter with given index or return null.
        ///
        ////////////////////////////////////////////////////////////
        virtual ConstantParameter* GetParameterByIndex( int32_t index );
        
        ////////////////////////////////////////////////////////////
        /// \brief Finds the parameter with given alias or return null.
        ///
        ////////////////////////////////////////////////////////////
        virtual ConstantParameter* GetParameterByAlias( Alias alias );
        
        ////////////////////////////////////////////////////////////
        /// \brief Finds the parameter with given name or return null.
        ///
        ////////////////////////////////////////////////////////////
        virtual const ConstantParameter* GetParameterByName( const String& name ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Finds the parameter with given index or return null.
        ///
        ////////////////////////////////////////////////////////////
        virtual const ConstantParameter* GetParameterByIndex( int32_t index ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Finds the parameter with given alias or return null.
        ///
        ////////////////////////////////////////////////////////////
        virtual const ConstantParameter* GetParameterByAlias( Alias alias ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Binds multiple parameters in one command.
        ///
        ////////////////////////////////////////////////////////////
        virtual void BindConstantParameters( const Vector < ConstantParameter >& params ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Binds multiple parameters in one command.
        ///
        ////////////////////////////////////////////////////////////
        virtual void BindVaryingParameters( const SharedVector < VaryingParameter >& params ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the parameter for given stage and with given
        /// name.
        ///
        /// An external API may or may not return the correct stage value.
        /// As example, OpenGl stages are not stored as parameters are bound
        /// for the whole program.
        ///
        ////////////////////////////////////////////////////////////
        virtual const ConstantParameter* GetParameterByStage( Stage stage , const String& name ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the parameter for given stage and with given
        /// name.
        ///
        /// An external API may or may not return the correct stage value.
        /// As example, OpenGl stages are not stored as parameters are bound
        /// for the whole program.
        ///
        /// \param index Index representing the parameter. On different APIs,
        /// the index may be global in the program (OpenGL) or local for each
        /// shader stage (D3D).
        ///
        ////////////////////////////////////////////////////////////
        virtual const ConstantParameter* GetParameterByStage( Stage stage , int32_t index ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the generated VertexLayout currently bound
        /// to this program.
        ///
        /// On OpenGL drivers, the VertexLayout does not represent anything
        /// but informations upon future glVertexAttrib* functions. On D3D,
        /// it represents the full ID3D11InputLayout object. This object should
        /// be generated by the program itself to conform the shader's signature,
        /// but the user can give an alternate VertexLayout to change this behaviour.
        /// However, an alternate VertexLayout may not be accepted or have the correct
        /// behaviour for the different shader stages.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < VertexLayout > GetVertexLayout() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Submits a VertexLayout to the program.
        ///
        /// This VertexLayout is not checked as matching the real program's
        /// input layout but is used to bind attributes to the program.
        /// Texture management and parameters management is not relied to
        /// this class.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetVertexLayout( const Shared < VertexLayout >& layout );
        
    protected:
        
        ////////////////////////////////////////////////////////////
        /// \brief Interface to bind a given parameter to given value.
        ///
        ////////////////////////////////////////////////////////////
        virtual void BindParameter( const ConstantParameter* parameter , const ParameterValue& value ) const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Called by derived class to modify the parameters
        /// in this program.
        ///
        /// When constructing the program object, the derived class must
        /// discover arguments in shader's files and report them in the
        /// parent class as ConstantParameters.
        ///
        /// ( OGL ): On OpenGL, all arguments are shared for the whole
        /// program so the 'stage' field will always remain 'Stage::Vertex'
        /// or 'Stage::None'.
        /// ( D3D ): On DirectX, arguments are specific for each stage.
        /// 'stage' field is relevant and a parameter that does not exist
        /// for the given stage must not be bound for another stage.
        ///
        /// \note Reset the Alias parameter map. This function should be
        /// called once by the derived class when loading the program's
        /// shaders and discovering the parameters (usually in the constructor,
        /// as Metaclass construction support exception error handling).
        ///
        /// \note As the parameter discovery is done by the program object
        /// (and not the shader object), Metaclass is not envolved in the
        /// program creation and thus, automatic exception handling is not
        /// done for you. You should use a try/catch block when creating a
        /// program to catch exception throwed by the Program object when
        /// constructing it.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetParameters( const Vector < ConstantParameter >& params );
    };
}

#endif /* Program_h */
