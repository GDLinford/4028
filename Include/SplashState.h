#include <stdafx.h>
#include "GameStates.h"

#ifndef __SPLASH_STATE__
#define __SPLASH_STATE__

class SplashState : public GameState 
{
public:
	SplashState();
	virtual ~SplashState();

	//define the virtual parent methods and implement them in the source file
	virtual void Initialise(float a_fDT);
	virtual void Update(float a_fDT);
	virtual void Leave(float a_fDT);

	virtual void Draw();

private:
	void* m_backgroundImageData;
	u32 m_bgWidth;
	u32 m_bgHeight;

};


#endif // !__SPLASH_STATE__
