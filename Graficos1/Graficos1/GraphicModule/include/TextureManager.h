//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#ifndef TextureManager_H
#define TextureManager_H

#include <windows.h>
#ifdef openGL
#include <gl/gl.h>
#endif
#include "FreeImage.h"
#include "Textura.h"
#include <map>
#include "flags.h"
namespace GraphicsModule {
	class TextureManager
	{
	public:
		static TextureManager* Inst();
		virtual ~TextureManager();

		//load a texture an make it the current texture
		//if texID is already in use, it will be unloaded and replaced with this texture
		bool LoadTexture(const char* filename,int inverted, Textura*tex, SRV_DIMENSION d);

		//free the memory for a texture
		bool UnloadTexture(const unsigned int texID);

		//set the current texture
		bool BindTexture(const unsigned int texID);

		//free all texture memory
		void UnloadAllTextures();

	protected:
		TextureManager();
		TextureManager(const TextureManager& tm);
		TextureManager& operator=(const TextureManager& tm);

		static TextureManager* m_inst;
	public:
#ifdef openGL
		std::map<unsigned int, GLuint> m_texID;
#endif
	};
}


#endif