//  ========================================================================  //
//
//  File    : ATL/Shader.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 04/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Shader_hpp
#define Shader_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Resource.hpp>
#include <ATL/Stage.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Describe a Shader interface unit.
    ///
    /// A Shader object represents the actual program for the designated
    /// stage. You can load a shader directly by creating a new Program
    /// and giving the shaders' files, or you can load the corresponding
    /// metaclass from given file (by using 'MimeDatabase::FindForFile()'
    /// to get the MIME type of the file). You can also load a Shader from
    /// different other things, see the constructors.
    ///
    /// A Shader is generally held by the Program but this behaviour is
    /// not guaranteed (as D3D needs actually one shader per stage object,
    /// but OpenGL needs only the program object, different owning behaviour
    /// might happen because OpenGL does not need the shader objects once
    /// the program is linked).
    ///
    ////////////////////////////////////////////////////////////
    class Shader : public Resource
    {
        ////////////////////////////////////////////////////////////
        Atomic < Stage > m_stage ; ///< Stage used for this Shader.
        
    protected:
        
        ////////////////////////////////////////////////////////////
        /// \brief Constructs the Shader structure by giving Resource
        /// and Shader's parameters.
        ///
        ////////////////////////////////////////////////////////////
        Shader( Stage stage , const String& file , const MimeType& mime );
        
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Constructs a Shader by loading the given file.
        ///
        /// \param file File to load.
        /// \param args Other arguments following the pattern :
        ///         - ( Weak < Context > ) the context where you wish the
        ///           the shader will be loaded (generally given by RenderWindow).
        ///         - ( ShaderParams ) A structure holding some informations
        ///           that may or may not be used depending on implementation.
        ///
        /// \notes For the implementator: All arguments are passed as pointers.
        ///
        ////////////////////////////////////////////////////////////
        Shader( const String& file , va_list& args );
        
        ////////////////////////////////////////////////////////////
        virtual ~Shader();
        
        ////////////////////////////////////////////////////////////
        virtual Stage GetStage() const ;
    };
}

#endif /* Shader_hpp */
