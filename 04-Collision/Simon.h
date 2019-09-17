#pragma once
#include "GameObject.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 220

#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACT			500
#define SIMON_STATE_SITDOWN			600

//define index of animation
#define SIMON_ANI_IDLE_RIGHT			0
#define SIMON_ANI_IDLE_LEFT				1
#define SIMON_AN_WALKING_RIGHT			2
#define SIMON_ANI_WALKING_LEFT			3
#define SIMON_ANI_SIT_LEFT				4
#define SIMON_ANI_SIT_RIGHT				5
#define SIMON_ANI_ATTACT_LEFT			6
#define SIMON_ANI_ATTACT_RIGHT			7
#define SIMON_ANI_DIE					8

#define SIMON_BBOX_WIDTH  15
#define SIMON_BBOX_HEIGHT 27
#define SIMON_SIT_BBOX_HEIGHT  22

#define SIMON_UNTOUCHABLE_TIME 5000
#define SIMON_ATTACT_TIME	1000

class CSimon : public CGameObject
{
	int isAttact;
	DWORD attactTime;

public: 
	CSimon() : CGameObject()
	{
		isAttact = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render(float &x_cam, float &y_cam);
	void SetState(int state);
	
	void StartAttact() { isAttact = 1; attactTime = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};