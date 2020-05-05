#include <stdafx.h>
#include "Map.h"
#include "Renderer.h"
#include "Player.h"

Map::Map() : m_width(0), m_height(0), m_map(nullptr) 
{

}

Map::~Map() 
{

}

bool Map::LoadMap(const char* a_filename) 
{
	//Load a level if the map is not null then we
	
	if (m_map != nullptr) 
	{
		delete[] m_map;
		m_map = nullptr;
	}
	std::fstream file;
	file.open(a_filename, std::ios_base::in | std::ios_base::binary);
	//test to see if the file has opened correctly
	if (file.is_open()) 
	{
		//success file has been opened, verify contents of file
		file.ignore(std::numeric_limits<std::streamsize>::max());
		std::streamsize fileSize = file.gcount();
		file.clear();
		file.seekg(0, std::ios_base::beg);
		if (fileSize == 0) 
		{
			file.close();
			return false;
		}
		//read in the width and height of the level map
		file >> m_width >> m_height;
		file.ignore(1); //ignore end of line marker
		//allocate memory to hold all the map data
		m_map = new u8[m_width * m_height];
		u32 index = 0;
		//read line of the the file to get one row worth of map data
		//use getline to read in each line of the file
		for (std::string currentMapLine; std::getline(file, currentMapLine); ) 
		{
			//cpnert string from getline into stringstream and use comma seperator to break into chunks and store values in map
			std::istringstream ss{ currentMapLine };
			int val = 0;
			while (ss >> val) // whilt we still have number data to read
			{
				//when parsing store as int value temporarily then static cast to u8 otherwise we read values as char, char value of 0 is 48
				m_map[index] = (u8)(val);
				++index;
				if ((ss >> std::ws).peek() == ',') //std::ws ignore white space is the next char is a comma ignore it too
				{
					ss.ignore();
				}


			}
		}

		//file close
		file.close();
		return true;
	}

	return false;
}

//the level knows how to draw itself
void Map::draw(const Player* a_player) 
{
	//get the instance of the renderer to get the dimensions of the render window
	Renderer* renderer = Renderer::GetInstance();
	u32 windowWidth = 0, windowHeight = 0;
	renderer->GetWindowSize(windowWidth, windowHeight);

	//from the passed in pointer to the player get the current position and firection of the player
	float playerPosX = 0.f, playerPosY = 0.f;
	a_player->GetPosition(playerPosX, playerPosY);
	float playerDirX = 0.f, playerDirY = 0.f;
	a_player->GetRotation(playerDirX, playerDirY);
	float nearPlaneLength = a_player->GetNearPlaneLength();

	//camera plane is perpendicular to player direction
	//swap components and negate y
	//multiply by near plane length to get vector to right length
	float camPlaneX = -playerDirY * nearPlaneLength;
	float camPlaneY = playerDirX * nearPlaneLength;

	for (u32 c = 0; c < windowWidth; c++) //c represents which screen column we are examining
	{
		//get the x position as a value between -1 & 1
		float cameraX = ((2.f * c) / (float)windowWidth) - 1.f;
		float rayDirX = playerDirX + (camPlaneX * cameraX);
		float rayDirY = playerDirY + (camPlaneY * cameraX);
		//length of ray from one X/Y side to nex X/Y side
		float deltaDistX = (rayDirX != 0.f) ? std::abs(1.f / rayDirX) : 0;
		float deltaDistY = (rayDirY != 0.f) ? std::abs(1.f / rayDirY) : 0;

		//player curren grid position
		int mapX = (int)(playerPosX);
		int mapY = (int)(playerPosY);

		//length of ray from current position to next X/Y side
		float sideDistX = 0.f;
		float sideDistY = 0.f;

		float perpWallDist = 0.f;

		//direction to step in x/y +-1
		int stepX = 0;
		int stepY = 0;

		//available to store collision
		int collision = 0;
		//based on the direction of the ray where do we start testing the wall collision
		if (rayDirX < 0) 
		{
			stepX = -1;
			sideDistX = (playerPosX - mapX) * deltaDistX;
		}
		else 
		{
			stepX = 1;
			sideDistX = (mapX + 1.f - playerPosX) * deltaDistX;
		}
		//do the same for y direction of the ray
		if (rayDirY < 0) 
		{
			stepY = -1;
			sideDistY = (playerPosY - mapY) * deltaDistY;
		}
		else 
		{
			stepY = 1;
			sideDistY = (mapY + 1.f - playerPosY) * deltaDistY;
		}
		//value to track whether we have hit a north/south wall or an east/west wall
		int yIntersection = 0;
		//loop through our ray case incrementing along the ray by an interval and test to see if a collision with a non blank tile
		while (collision == 0) 
		{
			//jump to next map square in x or y direction
			if (sideDistX < sideDistY) 
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				yIntersection = 0;
			}
			else 
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				yIntersection = 1;
			}
			//test current map location for a collision (tile value that are non zero indicate a wall or non empty tile)
			collision = m_map[(mapX + (mapY * m_width))];
		}
		//we have collided our raycast with a wall
		perpWallDist = (!yIntersection) ?
			(mapX - playerPosX + (1 - stepX) / 2.f) / rayDirX :
			(mapY - playerPosY + (1 - stepY) / 2.f) / rayDirY;

		//Calculate height of line to draw
		s32 lineHeight = (int)(windowHeight / perpWallDist);
		//calculate upper and lower points to draw
		s32 yPos = (windowHeight >> 1) - (lineHeight >> 1);
		yPos = (yPos < 0) ? 0 : yPos;
		renderer->FillRenderBuffer(c, yPos, 1, lineHeight, (!yIntersection) ? 0x00FF0FF0 : 0x00880880);
	}
}
void Map::GetSize(u32& a_w, u32& a_h) 
{
	a_w = m_width;
	a_h = m_height;
}

u8 Map::GetGridValue(u32 a_x, u32 a_y) 
{
	u32 index = a_x + (a_y * m_width);
	if (index < (m_width * m_height)) 
	{
		return m_map[index];
	}
	return 255; //values of 255 will indicate a map out of bounds error
}