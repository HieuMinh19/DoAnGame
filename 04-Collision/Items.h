#pragma once
#include "GameObject.h"
#include "Global.h"
#include "debug.h"
#include "Brick.h"

#define TIME_LIVE_ITEM			2000

#define HEALTH_ANI_ITEM			0
#define STAR_ANI_ITEM			1
#define DARTS_ANI_ITEM			2

#define HEALTH_BBOX_WIDTH		16
#define HEALTH_BBOX_HEIGHT		16

#define ITEM_GRAVITY			0.05f
#define ITEM_SPEED				0.05f;

class CItems: public CGameObject
{
	
public:
	int itemType;
	DWORD timeLive;
	bool isActive;

	CItems();
	CItems(float x, float y, int type);
	virtual void Render(float& x, float& y_cam);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void setActive(bool active) { this->isActive = active; this->timeLive = GetTickCount(); };
	int getItemType() { return this->itemType; }
};
