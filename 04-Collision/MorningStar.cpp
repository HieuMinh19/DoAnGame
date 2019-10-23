#include "Morningstar.h"
CMorningstar::CMorningstar()
{
	level = 3;
	isActiveLeft = 0;
	attactTime = GetTickCount();
	coType = MORNING_STAIR_TYPE;
	listCollisionType.push_back(FIRE_TYPE);

}


void CMorningstar::Render(float &x_cam, float &y_cam)
{
	
}

void CMorningstar::Render(float& x_cam, float& y_cam, int curentFrame)
{
	int ani;
	if (isActiveLeft) {
		if (isActiveLeft == -1) {
			if (curentFrame == 0) {
				if (level == 1)
					animations[WEAPON_ANI_ATTACT_LEFT1_LV1]->Render(x - x_cam + 20, y - y_cam);
				else
					(level == 2) ?
						animations[WEAPON_ANI_ATTACT_LEFT1_LV2]->Render(x - x_cam + 20, y - y_cam) :
						animations[WEAPON_ANI_ATTACT_LEFT1_LV3]->Render(x - x_cam + 20, y - y_cam);
			}
			else
				if (curentFrame == 1) {
					if (level == 1)
						animations[WEAPON_ANI_ATTACT_LEFT2_LV1]->Render(x - x_cam + 10, y - y_cam + 25);
					else
						(level == 2) ?
							animations[WEAPON_ANI_ATTACT_LEFT2_LV2]->Render(x - x_cam - 10, y - y_cam - 10) :
							animations[WEAPON_ANI_ATTACT_LEFT2_LV3]->Render(x - x_cam + 10, y - y_cam - 10);
				}
					
				else {
					if (level == 1)
						animations[WEAPON_ANI_ATTACT_LEFT3_LV1]->Render(x - x_cam + 10, y - y_cam + 15);
					else
						if (level == 2)
							animations[WEAPON_ANI_ATTACT_LEFT3_LV2]->Render(x - x_cam - 30, y - y_cam + 10);
						else {
							float xBBox = x - x_cam - 40;
							float yBBox = y - y_cam;
							animations[WEAPON_ANI_ATTACT_LEFT3_LV3]->Render(x - x_cam - 40, y - y_cam);
							RenderBoundingBox(xBBox, yBBox);
						}
				}	
		}
		else {
			if (curentFrame == 0) {
				if (level == 1)
					animations[WEAPON_ANI_ATTACT_RIGHT1_LV1]->Render(x - x_cam - 10, y - y_cam);
				else
				if (level == 2)
						animations[WEAPON_ANI_ATTACT_RIGHT1_LV2]->Render(x - x_cam - 10, y - y_cam + 10);
					else
						animations[WEAPON_ANI_ATTACT_RIGHT1_LV3]->Render(x - x_cam - 15, y - y_cam + 10);
			}
			else
				if(curentFrame == 1){
					if (level == 1)
						animations[WEAPON_ANI_ATTACT_RIGHT2_LV1]->Render(x - x_cam + 20, y - y_cam + 5);
					else
						if (level == 2)
							animations[WEAPON_ANI_ATTACT_RIGHT2_LV2]->Render(x - x_cam, y - y_cam - 10);
						else
							animations[WEAPON_ANI_ATTACT_RIGHT2_LV3]->Render(x - x_cam, y - y_cam - 10);
				}
				else {
					if (level == 1)
						animations[WEAPON_ANI_ATTACT_RIGHT3_LV1]->Render(x - x_cam + 50, y - y_cam + 20);
					else
						if (level == 2)
							animations[WEAPON_ANI_ATTACT_RIGHT3_LV2]->Render(x - x_cam + 15, y - y_cam);
						else {
							
							animations[WEAPON_ANI_ATTACT_RIGHT3_LV3]->Render(x - x_cam + 10, y - y_cam);
							/*x = x - x_cam + 10;
							y = y - y_cam;*/
							RenderBoundingBox(x, y);
						}
				}
		}
	}
	
}


void CMorningstar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - 50;
	top = y;
	right = x + BBOX_WIDTH_LV1 + 10;
	bottom = y + BB_HEIGHT;
}

void CMorningstar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	float min_tx, min_ty, nx = 0, ny;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	// block 
	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bi t to avoid overlapping next frame
	y += min_ty * dy + ny * 0.4f;

	//collision logic with fire
	for (UINT i = 0; i < coEventsResult.size(); i++) {
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<CFire*>(e->obj))
		{
			DebugOut(L"[INFO] Fire: %d\n", i);
			CFire* fire = dynamic_cast<CFire*>(e->obj);
			fire->SetState(STATE_DIE);
		}
	}


	
	if (GetTickCount() - attactTime < ATTACT_FRAME_LASTED) {
		y -= 15;
		x += 22;
	}
	else
		if (GetTickCount() - attactTime < ATTACT_FRAME_LASTED * 2) {
			y += 20;
		}else
			if (GetTickCount() - attactTime < ATTACT_FRAME_LASTED * 3) {
				x -= 15;
				y += 20;
			}
	
	if (isActiveLeft == 1) {
		if (GetTickCount() - attactTime <= ATTACT_FRAME_LASTED) {
			x -= 10;
		}
		else
			if (GetTickCount() - attactTime <= ATTACT_FRAME_LASTED * 3)
				y += 20;
	}

	if (GetTickCount() - attactTime > ATTACT_FRAME_LASTED * 3) {		//100 is time to live of frame
		attactTime = 0;
		isActiveLeft = 0;
	}	
}

CMorningstar::~CMorningstar()
{
}
