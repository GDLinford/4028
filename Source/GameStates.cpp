#include <stdafx.h>
#include "GameStates.h"
#include "GameStateManager.h"

GameState::GameState() : m_name(nullptr), m_fTimeInState(0.f), m_isActive(false)
{
	//set the current process function pointer to point to initialise
	process = &GameState::Initialise;
}

GameState::~GameState()
{
	if (m_name != nullptr)
	{
		delete[] m_name;
		m_name = nullptr;
	}
}

//set the name of the state
void GameState::SetStateName(const char* a_pStateName)
{
	if (m_name == nullptr)
	{
		u64 l = (u64)strlen(a_pStateName);
		//allocate 1+1 as null terminator is required
		m_name = new char[l + 1];
 		strcpy(m_name, a_pStateName);

		
	}
}

//get the name of the state
const char* GameState::GetStateName()
{
	return m_name;
}

void GameState::SetManager(GameStateManager* a_pManager)
{
	m_pManager = a_pManager;
}

//empty draw function
void GameState::Draw()
{

}