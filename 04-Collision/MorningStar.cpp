#include "Morningstar.h"

CMorningstar::CMorningstar()
{
	level = 1;
	isActiveLeft = 0;
}


void CMorningstar::Render(float &x_cam, float &y_cam)
{
	int ani;
	if(isActiveLeft)
	{
		(isActiveLeft == -1) ? ani = WEAPON_ANI_ATTACT_LEFT : ani = WEAPON_ANI_ATTACT_RIGHT;
		animations[ani]->Render(x - x_cam, y - y_cam);
	}
		
}

void CMorningstar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BBOX_WIDTH_LV1;
	bottom = y + BB_HEIGHT;
}

void CMorningstar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

CMorningstar::~CMorningstar()
{
}
