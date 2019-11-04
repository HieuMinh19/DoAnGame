#include "Fire.h"

CFire::CFire(CItems *item)
{
	coType = FIRE_TYPE;
	this->item = item;
}

void CFire::Render(float &x_cam, float &y_cam)
{
	int ani = FIRE_ANI_ACTIVE;
	/*if (state == FIRE_STATE_DIE) {
		ani = FIRE_ANI_DIE;
	}*/
	//DebugOut(L"x_item: %f\n", x-x_cam);
	
	animations[ani]->Render(x-x_cam, y-y_cam);
	if(this->state != STATE_DIE)
		GetPosition(this->item->x, this->item->y);
	RenderBoundingBox(x_cam, y_cam);
}

void CFire::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + FIRE_BBOX_WIDTH;
	b = y + FIRE_BBOX_HEIGHT;
}

void CFire::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case FIRE_STATE_DIE:
			SetState(STATE_DIE);
			break;
		case FIRE_STATE_ACTIVE:
			break;
		case STATE_DIE:

			break;
	}
}

void CFire::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	float yItem = y - 12;
	if (state == STATE_DIE) {	
		this->item->setActive(true);
		this->item->canUpdate = true;
		this->canUpdate = false;
		x -= 1000;
	}
}