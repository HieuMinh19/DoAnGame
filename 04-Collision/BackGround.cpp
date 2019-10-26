#include "Background.h"

void CBackGround::Render(float &x_cam, float &y_cam)
{
	animations[0]->Render(x-x_cam, y-y_cam);
	//RenderBoundingBox();
}

void CBackGround::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BG_BBOX_WIDTH;
	b = y + BG_BBOX_HEIGHT;
}
