#include "Morningstar.h"
int a = 1;
CMorningstar::CMorningstar()
{
	level = 1;
	isActiveLeft = 0;
	attactTime = GetTickCount();
}


void CMorningstar::Render(float &x_cam, float &y_cam)
{
	int ani;
	if (isActiveLeft) {
		if (isActiveLeft == -1) {
			
			animations[WEAPON_ANI_ATTACT_LEFT1]->Render(x - x_cam, y - y_cam);
			flagUpdatePos = false;
		}
		else {
			ani = WEAPON_ANI_ATTACT_RIGHT1;
			animations[ani]->Render(x - x_cam, y - y_cam);
		}
		
	}
}

void CMorningstar::Render(float& x_cam, float& y_cam, int curentFrame)
{
	int ani;
	if (isActiveLeft) {
		if (isActiveLeft == -1) {
			if(curentFrame == 0)
				animations[WEAPON_ANI_ATTACT_LEFT1]->Render(x - x_cam + 20, y - y_cam);
			else
				if(curentFrame == 1)
					animations[WEAPON_ANI_ATTACT_LEFT2]->Render(x - x_cam + 10, y - y_cam + 25);
				else
					animations[WEAPON_ANI_ATTACT_LEFT3]->Render(x - x_cam + 10, y - y_cam + 15);
		}
		else {
			if(curentFrame == 0)
				animations[WEAPON_ANI_ATTACT_RIGHT1]->Render(x - x_cam - 10, y - y_cam);
			else
				if(curentFrame == 1)
					animations[WEAPON_ANI_ATTACT_RIGHT2]->Render(x - x_cam + 20, y - y_cam  + 5);
				else
					animations[WEAPON_ANI_ATTACT_RIGHT3]->Render(x - x_cam + 50 , y - y_cam + 20);
		}

	}
}

//void CMorningstar::Render(float xSimon, float ySimon, float xCam, float yCam)
//{
//	int ani;
//	if (isActiveLeft) {
//		(isActiveLeft == -1) ? ani = WEAPON_ANI_ATTACT_LEFT : ani = WEAPON_ANI_ATTACT_RIGHT;
//		
//		animations[ani]->Render(xSimon - xCam, ySimon - yCam);
//	}
//}

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
	
	if (isActiveLeft == -1 && flagUpdatePos) {
		DebugOut(L"[INFO] count 1: %d\n", GetTickCount() - attactTime);
		if (GetTickCount() - attactTime < ATTACT_FRAME_LASTED) {
			y -= 15;
			x += 22;
			DebugOut(L"[INFO] fram 1: %d\n", x);
		}
		else
			if (GetTickCount() - attactTime < ATTACT_FRAME_LASTED * 2) {
				y += 20;
				DebugOut(L"[INFO] fram 2: %d\n", x);
			}else
				if (GetTickCount() - attactTime < ATTACT_FRAME_LASTED * 3) {
					x -= 15;
					y += 20;
					DebugOut(L"[INFO] frame 3: %d\n", x);
				}
	
		
		
	}
	else
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
		flagUpdatePos = true;
	}	
}

CMorningstar::~CMorningstar()
{
}
