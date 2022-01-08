#pragma once
#include "../ConsoleCommon/DrawableObject.h"

class Circle : public DrawableObject
{
public:
	double radius = 5;
	oof::color color;

	void Draw(ScreenWrapper& sw) override;
};

