#pragma once
#include "GameObject.h"
#include "debug.h"

#define DARTS_WEAPON		24
#define DARTS_BBOX_WIDHT	16
#define DARTS_BOBX_HEIGHT	8
#define DARTS_ANI_FLY_LEFT	0
#define DARTS_ANI_FLY_RIGHT	1
#define DARTS_SPEED			0.1f

class CSubWeapon : public CGameObject
{
	DWORD timeLive;
public:
	int weaponType;
	CSubWeapon();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render(float& x, float& y_cam);
	virtual void SetState(int state);
};

