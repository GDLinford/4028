#include <stdafx.h>
#pragma once

#ifndef __IMAGE_LOADER_H__
#define __IMAGE_LOADER_H__

typedef enum ImageType 
{
	IM_BITMAP,
	IM_PCX,
	IM_PPM,

	IM_MAX
}ImageType;

class ImageLoader
{
public:
	ImageLoader() {}; //default constructor - no real functionality
	~ImageLoader() {}; //default destructor - no additional functionality

	//A static function to load an image from a provided file
	//both the returned image pixel data and the palette data will need to be freed by the caller with a delete[] operator
	/*!
		\param a_filename The filename and path of the image to load
		\param a_width a reference that will be used to store the width in pixels of the image
		\param a_height a reference that will be used to store the height of the images in pixels
		\param a_bpp a reference to store the number of bits per pixels for the image
		\param a_paletteData a reference pointer to the palette data that may be loader with the image,
			for the non-palettised images pass in nullptr
		\return returns a void pointer to image pixel data that has been extracted from the file
	*/

	static void* LoadFromFile(const char* a_filename, u32 a_imageType, u32& a_width, u32& a_height, u8& a_bpp, void*& a_paletteData);


private:

};


#endif // !__IMAGE_LOADER_H__
