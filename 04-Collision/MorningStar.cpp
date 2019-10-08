#include "Morningstar.h"
int a = 1;
CMorningstar::CMorningstar()
{
	level = 1;
	isActiveLeft = 0;
}


void CMorningstar::Render(float &x_cam, float &y_cam)
{

	int ani;
	if (isActiveLeft) {
		if (isActiveLeft == -1) {
			ani = WEAPON_ANI_ATTACT_LEFT;
			//DebugOut(L"[INFO] test: %d\n", ++a);
			if(a <= 5)
				animations[ani]->Render(x - x_cam + 20, y - y_cam);
			else
					animations[ani]->Render(x - x_cam, y - y_cam - 10);
			
		}
		else {
			ani = WEAPON_ANI_ATTACT_RIGHT;
			animations[ani]->Render(x - x_cam, y - y_cam);
		}
		
	}
}

void CMorningstar::Render(float xSimon, float ySimon, float xCam, float yCam)
{
	int ani;
	if (isActiveLeft) {
		(isActiveLeft == -1) ? ani = WEAPON_ANI_ATTACT_LEFT : ani = WEAPON_ANI_ATTACT_RIGHT;
		
		animations[ani]->Render(xSimon - xCam, ySimon - yCam);
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


	
	/*if (isActiveLeft == -1) {
		
		if (animations[WEAPON_ANI_ATTACT_LEFT]->getCurrentFrame() == 0) {
			x += 20;
			
		}
		else
			if (animations[WEAPON_ANI_ATTACT_LEFT]->getCurrentFrame() == 1 || animations[WEAPON_ANI_ATTACT_LEFT]->getCurrentFrame() == 2)
				y += 20;
	}
	else
		if (isActiveLeft == 1) {
			if (GetTickCount() - attactTime <= ATTACT_FRAME_LASTED) {
				x -= 10;
			}
			else
				if (GetTickCount() - attactTime <= ATTACT_FRAME_LASTED * 3)
					y += 20;
		}*/

	if (GetTickCount() - attactTime > ATTACT_FRAME_LASTED * 3)		//100 is time to live of frame
	{
		attactTime = 0;
		isActiveLeft = 0;
	}


}

CMorningstar::~CMorningstar()
{
}
