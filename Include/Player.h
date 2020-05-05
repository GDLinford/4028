#include <stdafx.h>

#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player 
{
public:
	Player();
	~Player();

	void Update(float a_fDT);

	void SetPosition(float a_px, float a_py);
	void GetPosition(float& a_gpx, float& a_gpy) const;
	void SetRotation(float a_rdegrees);
	void GetRotation(float& a_rx, float& a_ry) const;

	float GetNearPlaneLength() const { return m_nearPlaneLength; }

private:
	float m_posX;
	float m_posY;
	float m_dirX;
	float m_dirY;

	float m_nearPlaneLength;

};



#endif // !_PLAYER_H_
