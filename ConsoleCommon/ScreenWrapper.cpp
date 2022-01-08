#include "pch.h"
#include "ScreenWrapper.h"
#include "DrawableObject.h"
#include "framework.h"
#include "Windows.h"
#define OOF_IMPL
#include "oof.h"
#include <tuple>


ScreenWrapper::ScreenWrapper()
{
	const auto size = ScreenWrapper::GetScreenCellDimensions();
	width = size.x;
	height = size.y;
	ps = std::make_unique<oof::pixel_screen>(width,height);
}

ScreenWrapper::ScreenWrapper(Vector2D<int> dims)
{
	width = dims.x;
	height = dims.y;
	ps = std::make_unique<oof::pixel_screen>(width, height);
}

auto ScreenWrapper::GetScreenCellDimensions() -> Vector2D<int>
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return {csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1};
}

auto ScreenWrapper::GetCursorPosXY() -> Vector2D<int>
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);
	return {
		cbsi.dwCursorPosition.X,
		cbsi.dwCursorPosition.Y - 1 // This is correct, this function is weird
	};
}

Vector2D<int> ScreenWrapper::ConvertToScreenSpace(Vector2D<double> worldSpace) const
{
	worldSpace.x = max(min(100.0, worldSpace.x), 0.0);
	worldSpace.y = max(min(100.0, worldSpace.y), 0.0);
	return { static_cast<int>(round(ps->get_width() * (worldSpace.x / 100.0))),static_cast<int>(round(ps->get_halfline_height() * (worldSpace.y / 100.0))) };
}

Vector2D<double> ScreenWrapper::ConvertToWorldSpace(Vector2D<int> screenSpace) const
{
	screenSpace.x = max(min(ps->get_width(), screenSpace.x), 0);
	screenSpace.y = max(min(ps->get_halfline_height(), screenSpace.y), 0);
	return { static_cast<double>(screenSpace.x) / static_cast<double>(ps->get_width()),static_cast<double>(screenSpace.y) / static_cast<double>(ps->get_halfline_height()) };
}

auto ScreenWrapper::GetScreenResolution() const -> Vector2D<double>
{
	return { 100.0 / ps->get_width(),100.0 / ps->get_halfline_height() };
}

auto ScreenWrapper::SetPixel(Vector2D<double> pos, oof::color c) -> void
{
	setPixel(ConvertToScreenSpace(pos), c);
}

auto ScreenWrapper::GetPixel(Vector2D<double> pos) -> oof::color&
{
	return getPixel(ConvertToScreenSpace(pos));
}

auto ScreenWrapper::setPixel(Vector2D<int> pos, oof::color c) -> void
{
	if(!ps->is_in(pos.x,pos.y))
	{
		return;
	}

	auto& col = ps->get_color(pos.x, pos.y);
	col = c;
}

auto ScreenWrapper::getPixel(Vector2D<int> pos) -> oof::color&
{
	return ps->get_color(pos.x, pos.y);
}

auto ScreenWrapper::Draw() -> void
{
	const auto CurrentDimensions = GetScreenCellDimensions();
	if(ps->get_width() != CurrentDimensions.x || ps->get_halfline_height() != CurrentDimensions.y)
	{
		ps = std::make_unique<oof::pixel_screen>(CurrentDimensions.x, CurrentDimensions.y);
	}

	ps->clear();

	for (const auto& object : screenObjects)
	{
		object.second->Draw(*this);
	}

	FastPrint(ps->get_string());
}

auto ScreenWrapper::Update() const -> void
{
	static std::chrono::time_point<std::chrono::steady_clock> lastUpdate = std::chrono::steady_clock::now();
	const std::chrono::duration<std::chrono::microseconds> delta(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastUpdate));
	for(const auto& object : screenObjects)
	{
		object.second->Update(delta);
	}
	lastUpdate = std::chrono::steady_clock::now();
}

auto ScreenWrapper::AddDrawObject(std::string id, std::shared_ptr<DrawableObject> obj) -> void
{
	if(obj == nullptr)
	{
		return;
	}

	screenObjects[id] = obj;
}

std::shared_ptr<DrawableObject> ScreenWrapper::GetDrawObject(std::string id)
{
	if (screenObjects.contains(id))
	{
		return screenObjects[id];
	}

	return nullptr;
}

template <typename char_type>
auto ScreenWrapper::FastPrint(const std::basic_string<char_type>& sss) -> void
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
