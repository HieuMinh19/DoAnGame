#pragma once
#include "GameObject.h"
#include "Global.h"
#include "debug.h"

#define HEALTH_ANI_ITEM 0
#define HEATH_BBOX_WIDTH 23
#define HEATH_BBOX_HEIGHT 19

#define ITEM_GRAVITY	0.002f

class CItems: public CGameObject
{
	bool isActive;
public:
	CItems();
	virtual void Render(float& x, float& y_cam);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void setActive(bool active) { this->isActive = active; };
};

