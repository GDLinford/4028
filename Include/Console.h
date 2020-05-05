#pragma once
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdafx.h>

class Console
{
public:
	//default constructor/destructor to allow for allocation of memory and initialisation of member vars
	Console();
	~Console();
	//initialise function to allow for setting up console window and console screen buffer (permissible to fail during
	//initialisation and return false, cannot return false from constructor so constructors do as little as possible
	bool Initialise(const char* a_windowTitle, const unsigned short a_xPos = 0, const unsigned short a_yPos = 0,
		const unsigned short a_width = 0, const unsigned short a_height = 0);


	unsigned int WriteToLocation(wchar_t* a_data, short a_dataLength, short a_xPos, short a_yPos);

	HWND GetConsoleWindowHandle() { return m_consoleWindow; }


private:
	unsigned short m_xPos;
	unsigned short m_yPos;
	unsigned short m_consoleWidth;
	unsigned short m_consoleHeight;

	HANDLE m_consoleHandle;
	HWND m_consoleWindow;

};




#endif // !__CONSOLE_H__

