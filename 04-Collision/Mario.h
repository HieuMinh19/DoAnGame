#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.1f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define SIMON_STATE_ATTACT_LEFT		500
#define SIMON_STATE_ATTACT_RIGHT	600

#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1

#define MARIO_ANI_BIG_WALKING_RIGHT		2
#define MARIO_ANI_BIG_WALKING_LEFT		3
#define MARIO_ANI_ATTACT_LEFT			4
#define SIMON_ANI_ATTACT_RIGHT			5

#define MARIO_ANI_DIE				8

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_UNTOUCHABLE_TIME 5000


class CMario : public CGameObject
{
	
	int untouchable;
	DWORD untouchable_start;
public: 
	CMario() : CGameObject()
	{
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};