#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Game.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	// reset untouchable timer if untouchable time has passed
	/*if ( GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}*/

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
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) {
		delete coEvents[i];
	}


	//770 la kich thuoc  map, den 730 phai dung lai
	if (vx > 0 && x > 730)
		x = 730;
	if (vx < 0 && x < 0) x = 0;
	
}

void CSimon::Render(float &x_cam, float &y_cam)
{
	int ani;
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	if (state == SIMON_STATE_ATTACT) 
		if (nx > 0) { 
			ani = SIMON_ANI_ATTACT_LEFT; 
		}
		else {
			ani = SIMON_ANI_ATTACT_RIGHT;
		}
	else {
		if (vx == 0)
		{
			if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
			else ani = SIMON_ANI_IDLE_LEFT;
		}
		else if (vx > 0)
			ani = SIMON_AN_WALKING_RIGHT;
		else
		{
			ani = SIMON_ANI_WALKING_LEFT;
		}
		if (vy < 0) {
			if (nx > 0) ani = SIMON_ANI_SIT_LEFT;
			else ani = SIMON_ANI_SIT_RIGHT;
		}
		if (state == SIMON_STATE_SITDOWN)
		{
			if (nx > 0) ani = SIMON_ANI_SIT_LEFT;
			else ani = SIMON_ANI_SIT_RIGHT;
		}
	}
	//mau bouding box
	//return mau binh thuong sau thoi gian khong va cham 
	int alpha = 255;
	//if (untouchable) alpha = 128;
	float x_temp = x - x_cam;
	float y_temp = y - y_cam;
	animations[ani]->Render(x-x_cam, y-y_cam, alpha);
	
	RenderBoundingBox(x_temp,y_temp);
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		if (state == SIMON_STATE_SITDOWN)
			state = SIMON_STATE_JUMP;
		vy = -SIMON_JUMP_SPEED_Y;
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
	case SIMON_STATE_ATTACT:
		vx = 0;
		/*attact_start = GetTickCount();*/
		break;
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
}

void CSimon::StartAttact() {

}