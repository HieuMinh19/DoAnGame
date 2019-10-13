#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Global.h"

#define BBOX_WIDTH_LV1	30
#define BB_HEIGHT		10

#define WEAPON_STATE_ATTACT 10

//#define WEAPON_ANI_ATTACT_LEFT	0
//#define WEAPON_ANI_ATTACT_RIGHT	1
#define WEAPON_ANI_ATTACT_LEFT1	0
#define WEAPON_ANI_ATTACT_LEFT2	1
#define WEAPON_ANI_ATTACT_LEFT3	2

#define WEAPON_ANI_ATTACT_RIGHT1	3
#define WEAPON_ANI_ATTACT_RIGHT2	4
#define WEAPON_ANI_ATTACT_RIGHT3	5



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
	DWORD attactTime;
	bool flagUpdatePos = true;
public:
	int getLevel() { return this->level; }
	int getAttact() { return this->isActiveLeft; }
	void setAttact(int status) { this->isActiveLeft = status; }
	void setLevel(int lv) { this->level = lv; }
	void Render(float &x_cam, float &y_cam);
	void Render(float& x_cam, float& y_cam, int currentFram);
	//void Render(float xSimon, float ySimon, float xCam, float yCam);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	CMorningstar();
	~CMorningstar();
};

