#include <stdafx.h>
#pragma once
#ifndef __PCX_LOADER_H__
#define __PCX_LOADER_H__

#define PCX_VALID_HEADER 10
#define PCX_RLE_ENCODING 1
#define PCX_VGA_PALETTE_OFFSET -769
#define PCX_RLE_MASK 0xC0 //1100 0000
#define PCX_RLE_FREQ_MASK 0x3F //0011 1111
/*****************************************

* PCX Image version 3 did not contain a palette and instead utilised a default
* EGA palette which is provided here.

***************************************/

const u8 PCX_defaultPalette[48] = {
	0x00, 0x00, 0x00,    0x00, 0x00, 0x80,	  0x00, 0x80, 0x00,
	0x00, 0x80, 0x80,    0x80, 0x00, 0x00,	  0x80, 0x80, 0x80,
	0x80, 0x80, 0x00,    0x80, 0x80, 0x80,	  0xc0, 0xc0, 0xc0,
	0x00, 0x00, 0xff,    0x00, 0xff, 0x00,	  0x00, 0xff, 0xff,
	0xff, 0x00, 0x00,    0xff, 0x00, 0xff,	  0xff, 0xff, 0x00,
	0xff, 0xff, 0xff
};


//brief PCX File header format - 128 bytes in size

struct PCXHeader 
{
	u8			identifier;				/** <PCX ID Number (always 0x0A) */
	u8			version;				//version number
	u8			encoding;				//Enoding (always 1, no other value used)
	u8			bitsPerPixel;			// bits per pixel (1, 2, 4, 8
	struct PCXDimensions { u16 left; u16 top; u16 right; u16 bottom; }
	dimensions;							//image dimensions struct (left, Top, Right, Bottom
	u16			hRes;					//Horizontal Resolution
	u16			vRes;					//Verical Resolution

	struct PCXPaletteColour { u8 R; u8 G; u8 B; }
	colourpalette[16];					//16 colour EGA palette struct(u8 R, u8 G, u8 B)
	u8			reservedByte;			//Reserved byte (always 0)
	u8			numColourPlanes;		//number of colour planes(1,3,4)
	u16			bytesPerScanline;		//bytes per scanline
	u16			paletteinfo;			//Palette Type
	u16			hScreenRes;				//Horizontal Screen Size
	u16			vScreenRes;				//Vertical Screen Size
	u8			Padding[54];			//Reserved (always 0)

};
class PCXLoader
{
public:
	PCXLoader() {};
	~PCXLoader() {};

	static void* LoadFromFiles(std::fstream* a_stream, u32& a_w, u32& a_h, u8& a_bpp, void*& a_palette);
	static void* ConvertTo32bpp(void* a_imageData, void* palette, u32& a_w, u32& a_h, u8& a_bpp);
};


#endif // !__PCX_LOADER_H__
