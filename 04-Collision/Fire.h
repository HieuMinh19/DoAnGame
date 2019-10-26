#pragma once
#include "GameObject.h"
#include "Items.h"
#include "debug.h"

#define FIRE_BBOX_WIDTH  16
#define FIRE_BBOX_HEIGHT 31
#define FIRE_GRAVITY	0.02f

#define FIRE_BBOX_HEIGHT_DIE 9

#define FIRE_STATE_ACTIVE	100
#define FIRE_STATE_DIE		200

#define FIRE_ANI_ACTIVE 0

class CFire : public CGameObject
{
	CItems* item;
public:
	CFire(CItems *item);
	virtual void Render(float &x_cam, float &y_cam);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void SetState(int state);
};