#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Game.h"
#include "Fire.h"

CSimon::CSimon(CMorningstar* morningStar)
{
	this->morningStar = morningStar;
	isAttact = 0;
	coType = SIMON_TYPE;
	listCollisionType.push_back(BRICK_TYPE);
	listCollisionType.push_back(ITEM_TYPE);
	
	subWeapon = 0;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// reset attact timer 
	if (GetTickCount() - attactTime >= ATTACT_FRAME_LASTED * 3) {
		attactTime = 0;
		isAttact = 0;
	}

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bi t to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		/*for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj))
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			}
		}*/

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CItems*>(e->obj)){
				CItems* item = dynamic_cast<CItems*>(e->obj);
				if (item->getItemType() == STAR_ITEM_TYPE && this->morningStar->getLevel() < 3) {
					int nextMorningStarLevel = this->morningStar->getLevel() + 1;
					this->morningStar->setLevel(nextMorningStarLevel);
				}
				else {
					if (item->getItemType() == DARTS_ITEM_TYPE)
						this->subWeapon->itemType = DARTS_SUB_WEAPON;
				}
				item->SetState(STATE_DIE);
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) {
		delete coEvents[i];
	}	
}

void CSimon::Render(float &x_cam, float &y_cam)
{
	int ani;

	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else {
		if (vx == 0)
			(nx > 0) ? ani = SIMON_ANI_IDLE_RIGHT : ani = SIMON_ANI_IDLE_LEFT;
		else 
			(vx > 0) ? ani = SIMON_AN_WALKING_RIGHT : ani = SIMON_ANI_WALKING_LEFT;
		
		if (vy < 0) {//jump
			
			(nx > 0) ? ani = SIMON_ANI_SIT_LEFT : ani = SIMON_ANI_SIT_RIGHT;
		}
		
		if (state == SIMON_STATE_SITDOWN)
			(nx > 0) ? ani = SIMON_ANI_SIT_LEFT : ani = SIMON_ANI_SIT_RIGHT;

		if (isAttact){
			dx = 0;			//don't jump
			vx = 0;			//don't moving
				//int ani = (nx > 0) ? SIMON_ANI_SIT_ATTACT_RIGHT : SIMON_ANI_SIT_ATTACT_LEFT;
	
			ani = (nx > 0) ? SIMON_ANI_ATTACT_RIGHT : SIMON_ANI_ATTACT_LEFT;
			
			if (this->state != SIMON_STATE_ATTACT_SUBWEAPON) {
				
				morningStar->setAttact(nx);
				morningStar->Render(x_cam, y_cam, animations[ani]->getCurrentFrame(), animations[ani]->getLastFrame());
			}
		}		
	}
	
	animations[ani]->Render(x - x_cam, y - y_cam, 255);

	RenderBoundingBox(x_cam, y_cam);
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
		case SIMON_STATE_WALKING_RIGHT:
			if (!isAttact) {
				vx = SIMON_WALKING_SPEED;
				nx = 1;
			}
			break;
		case SIMON_STATE_WALKING_LEFT:
			if (!isAttact) {
				vx = -SIMON_WALKING_SPEED;
				nx = -1;
			}
			break;
		case SIMON_STATE_JUMP:
			if (y > 110) {
				vx = 0;
				vy = -SIMON_JUMP_SPEED_Y;
			}
			break;
		case SIMON_STATE_IDLE:
			vx = 0;
			break;
		case SIMON_STATE_DIE:
			vy = -SIMON_DIE_DEFLECT_SPEED;
			break;
		case SIMON_STATE_SITDOWN:
			//don't move when sitdown
			vx = 0;
			//don't jump when sitdown
			vy += dt * SIMON_GRAVITY * 1000;
			break;
	}
}

void CSimon::StartAttact()
{
	if (!isAttact) {
		isAttact = 1; 
		attactTime = GetTickCount();

		int ani;
		/*if (isSitDown) {
			ani = (nx > 0) ? SIMON_ANI_SIT_ATTACT_RIGHT : SIMON_ANI_SIT_ATTACT_LEFT;
		}
		else {*/
		ani = (nx > 0) ? SIMON_ANI_ATTACT_RIGHT : SIMON_ANI_ATTACT_LEFT;
		//}

		if (this->state != SIMON_STATE_ATTACT_SUBWEAPON) {
			animations[ani]->currentFrame = -1;
			this->morningStar->attactTime = attactTime;
			this->morningStar->SetPosition(x, y);
		}
		
	}
		 
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 10;
	top = y;
	right = left + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
	
}