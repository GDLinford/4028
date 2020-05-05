#include<stdafx.h>
#include "InputManager.h"
#include "Player.h"

Player::Player() : m_dirX(1.f), m_dirY(0.f), m_posX(2.f), m_posY(3.f) 
{
	float nearPlaneDistance = 1.f;
	m_nearPlaneLength = tanf(HALF_FOV * (float)(PI / 180.f)) * nearPlaneDistance;
}

Player::~Player() 
{

}

void Player::SetPosition(float a_px, float a_py) 
{
	m_posX = a_px; 
	m_posY = a_py;
}

void Player::GetPosition(float& a_gpx, float& a_gpy) const 
{
	a_gpx = m_posX; 
	a_gpy = m_posY;
}

void Player::SetRotation(float a_degrees) 
{
	float radians = a_degrees * (float)(PI / 180.f);
	m_dirX = 1.f * cosf(radians);
	m_dirY = 1.f * sin(radians);
}

void Player::GetRotation(float& a_rx, float& a_ry) const 
{
	a_rx = m_dirX; 
	a_ry = m_dirY;
}

void Player::Update(float a_fDT) 
{
	//Process player movement
	if (InputManager::GetInstance()->GetKeyDown('W')) 
	{
		m_posX += 2.f * m_dirX * a_fDT;
		m_posY += 2.f * m_dirY * a_fDT;
	}
	if (InputManager::GetInstance()->GetKeyDown('S')) 
	{
		m_posX -= 2.f * m_dirX * a_fDT;
		m_posY -= 2.f * m_dirY * a_fDT;
	}
	//player rotation
	if (InputManager::GetInstance()->GetKeyDown('A')) 
	{
		//both camera direction and plane must be rotated
		float playerRotSpeed = -0.4f * a_fDT;
		float oldDirX = m_dirX;
		m_dirX = oldDirX * cosf(playerRotSpeed) - m_dirY * sin(playerRotSpeed);
		m_dirY = oldDirX * sin(playerRotSpeed) + m_dirY * cos(playerRotSpeed);
	}
	if (InputManager::GetInstance()->GetKeyDown('D')) 
	{
		//both camera direction and camera plane must be rotated
		float playerRotSpeed = 0.4f * a_fDT;
		float oldDirX = m_dirX;
		m_dirX = oldDirX * cosf(playerRotSpeed) - m_dirY * sin(playerRotSpeed);
		m_dirY = oldDirX * sin(playerRotSpeed) + m_dirY * cos(playerRotSpeed);
	}
}