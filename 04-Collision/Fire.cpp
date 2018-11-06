#include "Fire.h"

void CFire::Render(float &x_cam, float &y_cam)
{
	int ani = FIRE_ANI_ACTIVE;
	/*if (state == FIRE_STATE_DIE) {
		ani = FIRE_ANI_DIE;
	}*/
	animations[ani]->Render(x-x_cam,y-y_cam);
	//RenderBoundingBox();
}

void CFire::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + FIRE_BBOX_WIDTH;
	b = y + FIRE_BBOX_HEIGHT;
}
//void CFire::SetState(int state)
//{
//	CGameObject::SetState(state);
//	switch (state)
//	{
//	case FIRE_STATE_DIE:
//		break;
//	case FIRE_STATE_ACTIVE:
//		break;
//	}
//}
//void CFire::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
//{
//	CGameObject::Update(dt, coObjects);
//
//	//
//	// TO-DO: make sure Goomba can interact with the world and to each of them too!
//	// 
//}