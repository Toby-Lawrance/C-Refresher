#pragma once

#define OOF_IMPL
#include "oof.h"
#include <tuple>

class ScreenWrapper
{
public:
	static std::tuple<int, int> GetScreenCellDimensions();
	static std::tuple<int, int> GetCursorPosXY();

	void Draw();

private:
	template <typename char_type>
	void FastPrint(const std::basic_string<char_type>& sss);
};