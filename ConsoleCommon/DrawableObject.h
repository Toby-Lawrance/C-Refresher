#pragma once

#include "oof.h"
#include <memory>

#include "ScreenWrapper.h"
#include "Vector2D.h"

class DrawableObject
{
public:
	std::string ID;

	virtual ~DrawableObject() = default;
	virtual void Draw(ScreenWrapper& sw);
	Vector2D<double> pos;
};

