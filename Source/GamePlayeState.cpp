#include <stdafx.h>
#include "GamePlayState.h"
#include "GameStateManager.h"
#include "rc_ImageLoader.h"
#include "Renderer.h"
#include "Player.h"
#include "Map.h"

GamePlayState::GamePlayState() : GameState(), m_pMap(nullptr), m_pPlayer(nullptr) 
{

}

GamePlayState::~GamePlayState() 
{
	if (m_pMap) 
	{
		delete m_pMap;
		delete m_pPlayer;
	}
}

void GamePlayState::Initialise(float a_fDT) 
{
	UNREFERENCED_PARAMETER(a_fDT);
	m_pMap = new Map();
	if (m_pMap->LoadMap("../resources/Map/Map.map")) 
	{
		m_pPlayer = new Player();

		m_isActive = true;
		process = &GameState::Update;
	}
}

void GamePlayState::Update(float a_fDT) 
{
	UNREFERENCED_PARAMETER(a_fDT);
	//process player movement
	m_pPlayer->Update(a_fDT);
}

void GamePlayState::Draw() 
{
	//get renderer pointer
	Renderer* renderer = Renderer::GetInstance();

	//draw background
	unsigned int ceilingColour = 0x00505050;
	unsigned int floorColour = 0x00B2B2B2;
	renderer->FillRenderBuffer(0, 0, 640, 320, ceilingColour);
	renderer->FillRenderBuffer(0, 320, 640, 320, floorColour);

	//draw Map
	m_pMap->draw(m_pPlayer);
}

void GamePlayState::Leave(float a_fDT) 
{
	UNREFERENCED_PARAMETER(a_fDT);
	//if we are leaving the state inform the gameStateManager to remove us
	GetManager()->RemoveState(this);
}