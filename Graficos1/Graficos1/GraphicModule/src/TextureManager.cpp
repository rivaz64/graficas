//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#include "TextureManager.h"
#include "Textura.h"
#include <windows.h>
#include"test.h"
#include "flags.h"
namespace GraphicsModule {
	TextureManager* TextureManager::m_inst(0);

	TextureManager* TextureManager::Inst()
	{
		if (!m_inst)
			m_inst = new TextureManager();

		return m_inst;
	}

	TextureManager::TextureManager()
	{
		// call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
#endif
	}

	//these should never be called
	//TextureManager::TextureManager(const TextureManager& tm){}
	//TextureManager& TextureManager::operator=(const TextureManager& tm){}

	TextureManager::~TextureManager()
	{
		// call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
#endif

		UnloadAllTextures();
		m_inst = 0;
	}

	bool TextureManager::LoadTexture(const char* filename,
		int inverted, Textura* tex)
	{
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image,  once loaded
		FIBITMAP* dib(0);
		//pointer to the image data
		BYTE* bits(0);
		//image width and height
		unsigned int width(0), height(0);
		//OpenGL's image ID to map to



		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(filename, 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return false;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif)) {
			dib = FreeImage_Load(fif, filename);

			dib = FreeImage_ConvertTo32Bits(dib);

		}

		//if the image failed to load, return failure
		if (!dib)
			return false;

		//retrieve the image data
		bits = FreeImage_GetBits(dib);
		//get the image width and height
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		//if this somehow one of these failed (they shouldn't), return failure
		if ((bits == 0) || (width == 0) || (height == 0))
			return false;
#ifdef openGL


		//if this texture ID is in use, unload the current texture
		/*if (m_texID.find(texID) != m_texID.end())
			glDeleteTextures(1, &(m_texID[texID]));*/

			//generate an OpenGL texture ID for this texture
		glGenTextures(1, &tex->get);
		//store the texture ID mapping
		//m_texID[texID] = gl_texID;
		//bind to the new texture ID
		glBindTexture(GL_TEXTURE_2D, tex->get);
		//store the texture data for OpenGL use
		GLenum formats[5] = { GL_BGRA,GL_RGBA,GL_RED,GL_GREEN };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, formats[inverted], GL_UNSIGNED_BYTE, bits);
		/*f (!inverted)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);*/

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);
		//Free FreeImage's copy of the data
		FreeImage_Unload(dib);
#endif
#ifdef directX

		ZeroMemory(&tex->des, sizeof(tex->des));
		tex->des.Width = width;
		tex->des.Height = height;
		tex->des.MipLevels = 1;
		tex->des.ArraySize = 1;
		DXGI_FORMAT formats[4] = { DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM,DXGI_FORMAT_R16G16_UNORM,DXGI_FORMAT_R10G10B10A2_UNORM };
		tex->des.Format = formats[inverted];
		

		//tex->des.Format = DXGI_FORMAT_R32_FLOAT;
		/*if (Flags & MODEL_LOAD_FORMAT_RGBA)
			texD.Format = FORMAT_R8G8B8A8_UNORM;
		else if (Flags & MODEL_LOAD_FORMAT_BGRA)
			texD.Format = FORMAT_B8G8R8A8_UNORM;*/
		tex->des.SampleDesc.Count = 1;
		tex->des.SampleDesc.Quality = 0;
		tex->des.Usage = (D3D11_USAGE)GraphicsModule::USAGE::DEFAULT;
		tex->des.BindFlags = (UINT)GraphicsModule::BIND_FLAG::SHADER_RESOURCE;
		tex->des.CPUAccessFlags = 0;
		tex->des.MiscFlags = 0;

		/*if (FAILED(getmanager()->getDevice()->CreateTexture2D(*tex)))
		{
			return false;
		}/*/
		GraphicsModule::getmanager()->getDevice()->CreateTexture2D(*tex);
		unsigned int esta = FreeImage_GetPitch(dib);
		GraphicsModule::getmanager()->getConext()->get()->UpdateSubresource(tex->get, 0, NULL, bits, FreeImage_GetPitch(dib), 0);
		CD3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));
		/*if (Flags & MODEL_LOAD_FORMAT_RGBA)
			srvd.Format = FORMAT_R8G8B8A8_UNORM;
		else if (Flags & MODEL_LOAD_FORMAT_BGRA)
			srvd.Format = FORMAT_B8G8R8A8_UNORM;//*/
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MipLevels = 1; // same as orig texture
		GraphicsModule::getmanager()->getDevice()->get()->CreateShaderResourceView(tex->get, &srvd, &tex->srv);//*/

#endif
		//return success
		return true;
	}

	bool TextureManager::UnloadTexture(const unsigned int texID)
	{
#ifdef openGL
		bool result(true);
		//if this texture ID mapped, unload it's texture, and remove it from the map
		if (m_texID.find(texID) != m_texID.end())
		{
			glDeleteTextures(1, &(m_texID[texID]));
			m_texID.erase(texID);
		}
		else
		{
			result = false;
		}
		return result;
#endif
		return false;
	}

	bool TextureManager::BindTexture(const unsigned int texID)
	{
#ifdef openGL
		bool result(true);
		//if this texture ID mapped, bind it's texture as current
		if (m_texID.find(texID) != m_texID.end())
			glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
		//otherwise, binding failed
		else
			result = false;

		return result;
#endif
		return false;
	}

	void TextureManager::UnloadAllTextures()
	{
		//start at the begginning of the texture map
#ifdef openGL
		std::map<unsigned int, GLuint>::iterator i = m_texID.begin();

		//Unload the textures untill the end of the texture map is found
		while (i != m_texID.end())
			UnloadTexture(i->first);

		//clear the texture map
		m_texID.clear();
#endif
	}
}
