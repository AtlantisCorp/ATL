//  ========================================================================  //
//
//  File    : Linux/Platform.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 27/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  /
#ifndef PlatformLinuxHpp
#define PlatformLinuxHpp

#include <ATL/StdIncludes.hpp>

namespace atl 
{
	////////////////////////////////////////////////////////////
	/// \brief Defines some basic implementation for Linux platforms.
	///
	////////////////////////////////////////////////////////////
	class Platform : public Singleton < Platform >
	{
	public:
		
		////////////////////////////////////////////////////////////
		Platform();
	
		////////////////////////////////////////////////////////////
		~Platform();
		
		////////////////////////////////////////////////////////////
		/// \brief Actually does nothing but return true.
		///
		////////////////////////////////////////////////////////////
		bool Init();
		
		////////////////////////////////////////////////////////////
		/// \brief Return linux's platform name by using 'gethostname'.
		///
		////////////////////////////////////////////////////////////
		String GetName() const ;
		
		////////////////////////////////////////////////////////////
		/// \brief Returns the default surfacer library that has to be 
		/// used on linux's platform. 
		/// 
		/// As the default Window's manager is always X11, default surfacer 
		/// is always 'X11Surfacer.so'. This library can be changed in the
		/// main configuration file.
		///
		////////////////////////////////////////////////////////////
		String GetDefaultSurfacer() const ;
		
		////////////////////////////////////////////////////////////
		/// \brief Returns the default driver library to be used on this 
		/// platform.
		///
		/// On linux's platform, only OpenGL/Mesa drivers are available.
		/// 'Gl3Driver' is so always returned. This library can be changed
		/// in the main configuration file.
		///
		////////////////////////////////////////////////////////////
		String GetDefaultDriver() const ;
		
		////////////////////////////////////////////////////////////
		/// \brief Returns the default plugin's directory path on this
		/// platform.
		///
		/// It returns always './Plugins/' but this directory can be changed
		/// in the main configuration file. This directory is automatically
		/// loaded at application's startup.
		///
		////////////////////////////////////////////////////////////
		String GetDefaultAutoload() const ;
	};
}

#endif // PlatformLinuxHpp
