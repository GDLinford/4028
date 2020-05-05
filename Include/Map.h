#ifndef MAP_H
#define MAP_H

#include<stdafx.h>

class Player;

class Map 
{
public:

	Map();
	~Map();

	void GetSize(u32& a_w, u32& a_h);
	u8 GetGridValue(u32 a_x, u32 a_y);

	bool LoadMap(const char* a_filename);

	void draw(const Player* a_player);

private:
	u32 m_width;
	u32 m_height;

	u8* m_map;
};


#endif // !Map_H

