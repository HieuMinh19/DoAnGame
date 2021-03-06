#pragma once
#include "GameObject.h"

#define BG_BBOX_WIDTH  770
#define BG_BBOX_HEIGHT 185

class CBackGround : public CGameObject
{
public:
	CBackGround() { coType = BACKGROUND_TYPE; }
	virtual void Render(float &x_cam, float &y_cam);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
