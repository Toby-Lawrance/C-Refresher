#include "Circle.h"

#include "../ConsoleCommon/ScreenWrapper.h"

void Circle::Draw(ScreenWrapper& sw)
{
	DrawableObject::Draw(sw);

	const auto currentResolution = sw.GetScreenResolution();

	const auto boundingBoxTop = pos.y + radius;
	const auto boundingBoxBottom = pos.y - radius;
	const auto boundingBoxLeft = pos.x - radius;
	const auto boundingBoxRight = pos.x + radius;

	for(double i = boundingBoxLeft; i <= boundingBoxRight; i += currentResolution.x)
	{
		for(double j = boundingBoxBottom; j <= boundingBoxTop; j += currentResolution.y)
		{
			auto sp = sw.ConvertToScreenSpace(Vector2D(i, j));
			if (!sw.ps->is_in(sp.x,sp.y))
			{
				continue;
			}
			if((i - pos.x)*(i - pos.x) + (j - pos.y)*(j - pos.y) <= radius * radius)
			{
				sw.SetPixel(Vector2D(i,j),color);
			}
		}
	}
}
