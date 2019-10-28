#pragma once
#include "GameObject.h"
#include "Global.h"
#include "debug.h"
#include "Brick.h"

#define HEALTH_ANI_ITEM			0
#define STAR_ANI_ITEM			1

#define HEALTH_BBOX_WIDTH 16
#define HEALTH_BBOX_HEIGHT 16

#define HEALTH_ITEM_TYPE		20
#define STAR_ITEM_TYPE			23

#define ITEM_GRAVITY	0.05f

class CItems: public CGameObject
{
	int itemType;
	bool isActive;
public:
	CItems();
	virtual void Render(float& x, float& y_cam);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void setActive(bool active) { this->isActive = active; };
	int getItemType() { return this->itemType; }
};
