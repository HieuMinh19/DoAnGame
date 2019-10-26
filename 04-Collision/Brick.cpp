#include "Brick.h"

CBrick::CBrick()
{ 
	coType = BRICK_TYPE;
}

void CBrick::Render(float &x_cam, float &y_cam)
{
	animations[0]->Render(x-x_cam, y-x_cam);
	RenderBoundingBox(x_cam, y_cam);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}