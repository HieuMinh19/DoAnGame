#pragma once
#include "GameObject.h"
#include "debug.h"

#define BBOX_WIDTH_LV1	30
#define BB_HEIGHT		10

#define WEAPON_STATE_ATTACT 10

#define WEAPON_ANI_ATTACT_LEFT	0
#define	WEAPON_ANI_ATTACT_RIGHT 1

class CMorningstar : public CGameObject
{
	int level;
	/*
	varriable check attact
	default 0
	return 1 =>		attact left
	return -1 =>	attact right
	return 0 =>		don't attact
	*/
	int isActiveLeft;		
public:
	int getLevel() { return this->level; }
	int getAttact() { return this->isActiveLeft; }
	void setAttact(int status) { this->isActiveLeft = status; }
	void setLevel(int lv) { this->level = lv; }
	void Render(float &x_cam, float &y_cam);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	CMorningstar();
	~CMorningstar();
};

