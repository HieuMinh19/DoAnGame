#include "Morningstar.h"
bool a = true;


void CMorningstar::isCollision(vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>& coEventsResult)
{
	//left, top right, bottom object
	float Lob, Rob, Tob, Bob;
	float l, t, r, b;		//left, right, top, bottom morningstar
	GetBoundingBox(l, t, r, b);
	
	for (UINT i = 0; i < coObjects->size(); i++) {			
		coObjects->at(i)->GetBoundingBox(Lob, Tob, Rob, Bob);

		if (l < Lob && Lob < r) {
			if (t < Tob && Tob < b) {
				coEventsResult.push_back(coObjects->at(i));
			}
			
			if (Tob < t && t < Bob)
				coEventsResult.push_back(coObjects->at(i));
		}

		if (l < Rob && Rob < r) {
			if (Tob < b && b < Bob)
				coEventsResult.push_back(coObjects->at(i));

			if (Tob < t && t < Bob)
				coEventsResult.push_back(coObjects->at(i));
		}
	}
}
CMorningstar::CMorningstar()
{
	level = 3;
	isActiveLeft = 0;
	attactTime = GetTickCount();
	isLastFram = false;
	coType = MORNING_STAIR_TYPE;
	listCollisionType.push_back(FIRE_TYPE);
}


void CMorningstar::Render(float &x_cam, float &y_cam)
{
	
}

void CMorningstar::Render(float& x_cam, float& y_cam, int curentFrame, int lastFram)
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
						if (level == 2) {
							animations[WEAPON_ANI_ATTACT_LEFT2_LV2]->Render(x - x_cam - 10, y - y_cam - 10);
						}
						else {
							animations[WEAPON_ANI_ATTACT_LEFT2_LV3]->Render(x - x_cam + 10, y - y_cam - 10);

						}
				}
				else {
					if (level == 1)
						animations[WEAPON_ANI_ATTACT_LEFT3_LV1]->Render(x - x_cam + 10, y - y_cam + 15);
					else
						if (level == 2)
							animations[WEAPON_ANI_ATTACT_LEFT3_LV2]->Render(x - x_cam - 30, y - y_cam + 10);
						else {
							if (lastFram != curentFrame) {
								x = x - x_cam - 40;
								y = y - y_cam;
							}
							animations[WEAPON_ANI_ATTACT_LEFT3_LV3]->Render(x, y);
							RenderBoundingBox(x, y);
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
						if (level == 2) {
							animations[WEAPON_ANI_ATTACT_RIGHT3_LV2]->Render(x - x_cam + 15, y - y_cam);
						}
						else {
						
							if (lastFram == curentFrame - 1) {
								DebugOut(L"co vao %d\n", x);
								x = x - x_cam + 10;
								y = y - y_cam;
							}														
							animations[WEAPON_ANI_ATTACT_RIGHT3_LV3]->Render(x, y);
							this->isLastFram = true;
							RenderBoundingBox(x, y);
						}
				}
		}
	}
	
}


void CMorningstar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	if (level == 1) {
		right = x + BBOX_WIDTH_LV1;
	}
	else {
		(level == 2) ? right = x + BBOX_WIDTH_LV2 : right = x + BBOX_WIDTH_LV3;
	}
	bottom = y + BB_HEIGHT;	
}

void CMorningstar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (isLastFram) {
		vector<LPGAMEOBJECT> collisionObjects;
		isCollision(coObjects, collisionObjects);

		//collision with fire
		for (UINT i = 0; i < collisionObjects.size(); i++) {
			if (collisionObjects[i]->GetType() == FIRE_TYPE) {
				collisionObjects[i]->SetState(STATE_DIE);
			}
		}
	}
		

	if (GetTickCount() - attactTime > ATTACT_FRAME_LASTED * 3) {	
		attactTime = 0;
		isActiveLeft = 0;
		isLastFram = false;
	}	
}

CMorningstar::~CMorningstar()
{
}
