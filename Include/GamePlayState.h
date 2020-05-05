#include <stdafx.h>
#include "GameStates.h"
#pragma once

#ifndef __GAMEPLAY_STATE_H__
#define __GAMEPLAY_STATE_H__

class Player;
class Map;

class GamePlayState : public GameState 
{
public:
	GamePlayState();
	virtual ~GamePlayState();

	//define the virtual parent methods and implement them in the source file
	virtual void Initialise(float a_fDT);
	virtual void Update(float a_fDT);
	virtual void Leave(float a_fDT);

	void DrawBackGround();
	virtual void Draw();

private:

	Map* m_pMap;
	Player* m_pPlayer;



};


#endif // !__GAMEPLAY_STATE_H__

