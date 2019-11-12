#include "CSubWeapon.h"

CSubWeapon::CSubWeapon()
{
	this->AddAnimation(80041);
	this->AddAnimation(8004);
	canUpdate = false;
	listCollisionType.push_back(FIRE_TYPE);
	weaponType = DARTS_WEAPON;
	vx = DARTS_SPEED;
}

void CSubWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DARTS_BBOX_WIDHT;
	bottom = y + DARTS_BOBX_HEIGHT;
}

void CSubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	

	x += dx;
	//x += 0.001;
	//y = 50;

	DebugOut(L"x: %f\n", x);
}

void CSubWeapon::Render(float& xCam, float& yCam)
{
	int ani;
	ani = (nx > 0) ? DARTS_ANI_FLY_LEFT : DARTS_ANI_FLY_RIGHT;

	if(canUpdate)
		animations[ani]->Render(x-xCam, y-yCam);
}

void CSubWeapon::Render(float& xStart, float& yStart, int nx)
{
	/*int ani;
	ani = (nx > 0) ? DARTS_ANI_FLY_LEFT : DARTS_ANI_FLY_RIGHT;

	animations[ani]->Render(x, y);*/
}

void CSubWeapon::SetState(int state)
{
	CGameObject::SetState(state);
}
