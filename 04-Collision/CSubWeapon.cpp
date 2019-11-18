#include "CSubWeapon.h"

CSubWeapon::CSubWeapon(int weaponType)
{
	if (weaponType == DARTS_ITEM_TYPE) {
		this->AddAnimation(80041);
		this->AddAnimation(8004);
	}
	
	canUpdate = false;
	listCollisionType.push_back(FIRE_TYPE);
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
	
	if (this->state == STATE_DIE)
		this->x = -1000;

	x += dx;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bi t to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CFire*>(e->obj)) {
				CFire* fire = dynamic_cast<CFire*>(e->obj);
				fire->SetState(STATE_DIE);
				this->SetState(STATE_DIE);
			}
		}
	}
}

void CSubWeapon::Render(float& xCam, float& yCam)
{
	int ani;
	ani = (nx > 0) ? DARTS_ANI_FLY_LEFT : DARTS_ANI_FLY_RIGHT;

	if(canUpdate)
		animations[ani]->Render(x-xCam, y-yCam);
}

void CSubWeapon::SetState(int state)
{
	CGameObject::SetState(state);
}
