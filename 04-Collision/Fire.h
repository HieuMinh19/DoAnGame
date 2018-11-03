#pragma once
#include "GameObject.h"

#define FIRE_BBOX_WIDTH  16
#define FIRE_BBOX_HEIGHT 16
#define FIRE_GRAVITY	0.02f

#define FIRE_BBOX_HEIGHT_DIE 9

#define FIRE_STATE_ACTIVE 100
#define FIRE_STATE_DIE 200

#define FIRE_ANI_ACTIVE 0

class CFire : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void SetState(int state);
};