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
	DebugOut(L"item: %f\n", this->item->x);
	//RenderBoundingBox();
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
	//DebugOut(L"x: %f\n", x);
	float yItem = y - 12;
	if (state == STATE_DIE) {	
		//DebugOut(L"xItem: %f\n", xItem);
		this->item->setActive(true);
		this->item->Render(x, yItem);
		item->SetSpeed(0, 0);

		x -= 1000;
		//DebugOut(L"x x: %f\n", x);
		//this->item->Render(x, y);
	}
		

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
}