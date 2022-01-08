#include "pch.h"
#include "ScreenWrapper.h"

#include "framework.h"
#include "Windows.h"
#define OOF_IMPL
#include "oof.h"
#include <tuple>


std::tuple<int, int> ScreenWrapper::GetScreenCellDimensions()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return std::make_tuple(csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

std::tuple<int, int> ScreenWrapper::GetCursorPosXY() {
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);
	return std::make_tuple(
		cbsi.dwCursorPosition.X + 0,
		cbsi.dwCursorPosition.Y - 1 // This is correct, this function is weird
	);
}

void ScreenWrapper::Draw()
{
}

template <typename char_type>
void ScreenWrapper::FastPrint(const std::basic_string<char_type>& sss)
{
	HANDLE const output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	const auto char_count = static_cast<DWORD>(sss.length());
	if constexpr (std::is_same_v<char_type, char>)
	{
		WriteConsoleA(output_handle, sss.c_str(), char_count, nullptr, nullptr);
	}
	else
	{
		WriteConsoleW(output_handle, sss.c_str(), char_count, nullptr, nullptr);
	}
}
