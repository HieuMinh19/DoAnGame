#include "Items.h"

CItems::CItems()
{
	//random items
	srand((unsigned)time(0));
	itemType = rand() % (5) + 20;

	coType = ITEM_TYPE;
	isActive = false;
	vy = ITEM_GRAVITY;
	listCollisionType.push_back(BRICK_TYPE);
	canUpdate = false;
	//timeLive = GetTickCount();
}

CItems::CItems(float x, float y, int type)
{
	this->x = x;
	this->y = y;
	this->itemType = type;

	coType = ITEM_TYPE;
	isActive = false;
	vy = ITEM_GRAVITY;
	listCollisionType.push_back(BRICK_TYPE);
	canUpdate = false;
	timeLive = 0;
}

void CItems::Render(float& x_cam, float& y_cam)
{
	int ani;
	switch (itemType)
	{
	case 20:
	case 21:
		ani = HEALTH_ANI_ITEM;
		itemType = HEALTH_ITEM_TYPE;
		break;
	case 22:
	case 23:
		ani = STAR_ANI_ITEM;
		itemType = STAR_ITEM_TYPE;
		break;
	case 24: 
		ani = DARTS_ANI_ITEM;
		itemType = DARTS_ITEM_TYPE;
		break;
	default:
		ani = HEALTH_ANI_ITEM;
		break;
	}
	
	if(isActive)
		animations[ani]->Render(x - x_cam, y - y_cam);

	RenderBoundingBox(x_cam, y_cam);
}

void CItems::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + HEALTH_BBOX_WIDTH;
	b = y + HEALTH_BBOX_HEIGHT;
}

void CItems::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (isActive) {
		CalcPotentialCollisions(coObjects, coEvents);
	}
	else {
		timeLive = 0;
	}
		
	

	if (GetTickCount() - timeLive > TIME_LIVE_ITEM) {
		this->state = STATE_DIE;
		this->isActive = false;
	}
		
	// No collision occured, proceed normally
	if (coEvents.size() == 0){
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) {
		delete coEvents[i];
	}

	if (this->state == STATE_DIE) {
		x -= 1000;
	}
		

}

void CItems::SetState(int state)
{
	CGameObject::SetState(state);
}
