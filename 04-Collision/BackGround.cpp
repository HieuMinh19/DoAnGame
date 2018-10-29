#include "BackGround.h"

void CBackGround::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CBackGround::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BACKGROUND_BBOX_WIDTH;
	b = y + BACKGROUND_BBOX_HEIGHT;
}