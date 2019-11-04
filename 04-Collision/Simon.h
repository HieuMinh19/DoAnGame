#pragma once
#include "GameObject.h"
#include "Global.h"
#include "MorningStar.h"
#include "Brick.h"
#include "Items.h"


#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.2f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.0005f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACT			500
#define SIMON_STATE_SITDOWN			600
#define SIMON_STATE_SIT_ATTACT		700
#define SIMON_STATE_ATTACT_SUBWEAPON		800

//define index of animation
#define SIMON_ANI_IDLE_RIGHT			0
#define SIMON_ANI_IDLE_LEFT				1
#define SIMON_AN_WALKING_RIGHT			2
#define SIMON_ANI_WALKING_LEFT			3
#define SIMON_ANI_SIT_LEFT				4
#define SIMON_ANI_SIT_RIGHT				5
#define SIMON_ANI_ATTACT_LEFT			6
#define SIMON_ANI_ATTACT_RIGHT			7
#define SIMON_ANI_SIT_ATTACT_LEFT		8
#define SIMON_ANI_SIT_ATTACT_RIGHT		9
#define SIMON_ANI_DIE					10

#define SIMON_BBOX_WIDTH		15
#define SIMON_BBOX_HEIGHT		32
#define SIMON_SIT_BBOX_HEIGHT	22

#define DARTS_SUB_WEAPON		1004

class CSimon : public CGameObject
{
	DWORD attactTime;
	CMorningstar* morningStar;	
	int subWeaponType;
	CItems* subWeapon;
public:
	int isAttact;
	CSimon(CMorningstar* morningStar);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render(float &x_cam, float &y_cam);
	void SetState(int state);
	void StartAttact();
	CMorningstar* getMorningStar() { return this->morningStar; }
	void SetSubWeapon(CItems* subWeapon) { this->subWeapon = subWeapon; }
	
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};