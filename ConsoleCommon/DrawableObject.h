#pragma once

#include "oof.h"
#include <memory>
#include <chrono>

#include "ScreenWrapper.h"
#include "Vector2D.h"

class DrawableObject
{
public:
	std::string ID;

	virtual ~DrawableObject() = default;
	virtual void Draw(ScreenWrapper& sw);
	virtual void Update(std::chrono::duration<std::chrono::microseconds> deltaTime);
	Vector2D<double> pos;
};

