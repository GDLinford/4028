#include <stdafx.h>
#include "rc_TextureManager.h"
#include "rc_Texture.h"

TextureManager::TextureManager() : m_pTextureMap() 
{

}

TextureManager::~TextureManager()
{
	//need to iterate through the texturemap and
	//remove and references to images and unload
	m_pTextureMap.clear();
}

//Load Texture
//Uses and std map as a texture dictionairy to track loaded texture
//attempts to load a texture already memory will increment 
//a ref count for that texture

Texture* TextureManager::LoadTexture(const char* a_fileName, u32 a_format) 
{
	Texture* pTexture = nullptr;
	if (a_fileName != nullptr) 
	{
		std::map<std::string, TextureRef>::iterator dictionaryIter =
			m_pTextureMap.find(a_fileName);
		if (dictionaryIter != m_pTextureMap.end())
			//if iterator is not at end then texture was located
		{
			TextureRef& texRef = (TextureRef&)(dictionaryIter->second);
			//get reference to texture ref struct
			pTexture = texRef.pTexture;
			++texRef.refCount;
		}
		else
		{
			//better load the texture in as its not in the texture map yet
			pTexture = new Texture();
			if (pTexture->Load(a_fileName, a_format)) 
			{
				//load successful place into texRef structure 
				//and insert into dictionairy
				TextureRef texRef = { pTexture, 1 };
				m_pTextureMap[a_fileName] = texRef;
			}
			else { delete pTexture; pTexture = nullptr; }
		}
	}
	return pTexture;
}

//Remove a texture from memory 
//this will either unload the texture or simply decrement
//its reference count until this reaches 0 and then unload
void TextureManager::ReleaseTexture(Texture* a_pTexture) 
{
	for (auto dictionaryIter = m_pTextureMap.begin();
		dictionaryIter != m_pTextureMap.end(); ++dictionaryIter) 
	{
		TextureRef& texRef = (TextureRef&)(dictionaryIter->second);
		if (a_pTexture == texRef.pTexture) // found the texture to remove 
		{
			//pre decrement will be evaluated before call to <=
			//-- it's safe code could be seperated into two line if you want to
			if (--texRef.refCount == 0) 
			{
				delete texRef.pTexture;
				texRef.pTexture = nullptr;
				m_pTextureMap.erase(dictionaryIter);
				break;//escape the for loop to return
			}
		}
	}
}

bool TextureManager::TextureExist(const char* a_filename) 
{
	auto dictionairyIter = m_pTextureMap.find(a_filename);
	if (dictionairyIter != m_pTextureMap.end()) 
	//if iterator is not at end then texture was located
	{
		return true;
	}

	return false;
}

//return a pointer to the texture and incremements the reference count
Texture* TextureManager::GetTexture(const char* a_filename) 
{
	Texture* pTexture = nullptr;
	auto dictionaryIter = m_pTextureMap.find(a_filename);
	if (dictionaryIter != m_pTextureMap.end())
		//if iterator is not at end then texture was located
	{
		TextureRef& texRef = (TextureRef&)(dictionaryIter->second);
		//get reference to texture ref struct
		texRef.refCount++;
		pTexture = texRef.pTexture;
	}
	return pTexture;
}