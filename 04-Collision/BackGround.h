#pragma once
#include "GameObject.h"

#define BACKGROUND_BBOX_WIDTH  770
#define BACKGROUND_BBOX_HEIGHT 185

class CBackGround : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};