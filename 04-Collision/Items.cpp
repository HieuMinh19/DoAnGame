#include "Items.h"

CItems::CItems()
{
	coType = ITEM_TYPE;
	isActive = false;
}

void CItems::Render(float& x_cam, float& y_cam)
{
	int ani = HEALTH_ANI_ITEM;
	//DebugOut(L"x_cam: %f\n", x_cam);
	/*if (state == FIRE_STATE_DIE) {
		ani = FIRE_ANI_DIE;
	}*/
	if(isActive)
		animations[ani]->Render(x - x_cam, y - y_cam);
	//RenderBoundingBox();
}

void CItems::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + HEATH_BBOX_WIDTH;
	b = y + HEATH_BBOX_HEIGHT;
}

void CItems::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += ITEM_GRAVITY;
	DebugOut(L"dt: %f\n", vy);
}

void CItems::SetState(int state)
{
	CGameObject::SetState(state);
}
