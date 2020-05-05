#include <stdafx.h>
#include "rc_ImageLoader.h"
#include "rc_PCXLoader.h"
#include <fstream>

void* ImageLoader::LoadFromFile(const char* a_filename, u32 a_imageType, u32& a_width, u32& a_height, u8& a_bpp, void*& a_paletteData) 
{
	//get an fstream to read in the file data
	std::fstream file;
	file.open(a_filename, std::ios_base::in | std::ios_base::binary);
	//test to see i the file has opened in correctlty
	if (file.is_open()) 
	{
		//success file has been opened, verify contents of file -- ie check that file is not Zero length
		file.ignore(std::numeric_limits<std::streamsize>::max());   //attempt to read the highest number of bytes from the file
		std::streamsize filesize = file.gcount();
		file.clear();
		file.seekg(0, std::ios_base::beg);
		if (filesize == 0) 
		{
			file.close();
			return nullptr;
		}
		void* imageData = nullptr;
		//switch statement to choose which custom image loader to call
		switch (a_imageType) 
		{
		case(IM_BITMAP):{//todo
			break;
		}
		case(IM_PCX): {
			imageData = PCXLoader::LoadFromFiles(&file, a_width, a_height, a_bpp, a_paletteData);
			if (a_bpp != 32) 
			{
				imageData = PCXLoader::ConvertTo32bpp(imageData, a_paletteData, a_width, a_height, a_bpp);
			}
			break;
		}
		case(IM_PPM): {



			break;
		}
		default:
			break;
		}
		file.close();
		return imageData;
	}
	return nullptr; // file has failed to open return nullptr
}