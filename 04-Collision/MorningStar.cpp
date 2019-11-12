#include "Morningstar.h"
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
	level = 1;
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
					animations[WEAPON_ANI_ATTACT_LEFT1_LV1]->Render(x - x_cam + 15, y - y_cam + 5);
				else {
					(level == 2) ?
						animations[WEAPON_ANI_ATTACT_LEFT1_LV2]->Render(x - x_cam + 20, y - y_cam + 10) :
						animations[WEAPON_ANI_ATTACT_LEFT1_LV3]->Render(x - x_cam + 20, y - y_cam);
				}	
			}
			else
				if (curentFrame == 1) {
					if (level == 1)
						animations[WEAPON_ANI_ATTACT_LEFT2_LV1]->Render(x - x_cam + 40, y - y_cam + 35);
					else
						if (level == 2) {
							animations[WEAPON_ANI_ATTACT_LEFT2_LV2]->Render(x - x_cam + 15, y - y_cam);
						}
						else {
							animations[WEAPON_ANI_ATTACT_LEFT2_LV3]->Render(x - x_cam + 20, y - y_cam + 10);
						}
				}
				else {
					if (level == 1) {
						if (lastFram == curentFrame - 1) {
						
							x -= 25;
							y += 10;
						}
						this->isLastFram = true;
						animations[WEAPON_ANI_ATTACT_LEFT3_LV1]->Render(x - x_cam + 35, y - y_cam + 10);
					}
					else {
						if (level == 2) {
							if (lastFram == curentFrame - 1) {
								x -= 30;
								y += 10;
							}
							this->isLastFram = true;
							animations[WEAPON_ANI_ATTACT_LEFT3_LV2]->Render(x - x_cam, y - y_cam);
						}
							
						else {
							if (lastFram == curentFrame - 1) {
								x -= 40;
								y += 5;
							}
							this->isLastFram = true;
							animations[WEAPON_ANI_ATTACT_LEFT3_LV3]->Render(x - x_cam, y - y_cam);
						}
					}
				}	
		}
		else {
			if (curentFrame == 0) {
				if (level == 1)
					animations[WEAPON_ANI_ATTACT_RIGHT1_LV1]->Render(x - x_cam - 5, y - y_cam + 5);
				else
				if (level == 2)
						animations[WEAPON_ANI_ATTACT_RIGHT1_LV2]->Render(x - x_cam - 10, y - y_cam + 10);
					else
						animations[WEAPON_ANI_ATTACT_RIGHT1_LV3]->Render(x - x_cam - 15, y - y_cam + 10);
			}
			else
				if(curentFrame == 1){
					if (level == 1)
						animations[WEAPON_ANI_ATTACT_RIGHT2_LV1]->Render(x - x_cam - 10, y - y_cam + 10);
					else
						if (level == 2)
							animations[WEAPON_ANI_ATTACT_RIGHT2_LV2]->Render(x - x_cam - 15, y - y_cam + 10);
						else
							animations[WEAPON_ANI_ATTACT_RIGHT2_LV3]->Render(x - x_cam - 10, y - y_cam);
				}
				else {
					if (level == 1) {
						if (lastFram == curentFrame - 1) {
							x += 25;
							y += 5;
						}
						animations[WEAPON_ANI_ATTACT_RIGHT3_LV1]->Render(x - x_cam + 25, y - y_cam + 15);
						this->isLastFram = true;	
					}
					else
						if (level == 2) {
							if (lastFram == curentFrame - 1) {
								x += 25;
								y += 10;
							}
							animations[WEAPON_ANI_ATTACT_RIGHT3_LV2]->Render(x - x_cam, y - y_cam - 5);
							this->isLastFram = true;
						}
						else {
							if (lastFram == curentFrame - 1) {
								x += 10;
							}														
							animations[WEAPON_ANI_ATTACT_RIGHT3_LV3]->Render(x - x_cam, y - y_cam);
							this->isLastFram = true;
						}
				}
		}
	}
	RenderBoundingBox(x_cam, y_cam);
}


void CMorningstar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;

	if (level == 1) {
		right = left + BBOX_WIDTH_LV1;
	}
	else {
		right = (level == 2) ? left + BBOX_WIDTH_LV2 : left + BBOX_WIDTH_LV3;
	}
	bottom = top + BB_HEIGHT;	
}

void CMorningstar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (GetTickCount() - attactTime > ATTACT_FRAME_LASTED * 3) {
		attactTime = 0;
		isActiveLeft = 0;
		isLastFram = false;
	}

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
}

CMorningstar::~CMorningstar()
{
}
