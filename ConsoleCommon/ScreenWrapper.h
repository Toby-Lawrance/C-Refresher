#pragma once

#define OOF_IMPL
#include "oof.h"
#include <tuple>
#include <memory>
#include <vector>
#include "Vector2D.h"

class DrawableObject;

class ScreenWrapper
{
public:
	ScreenWrapper();
	ScreenWrapper(Vector2D<int> dims);

	int width, height;

	std::unique_ptr<oof::pixel_screen> ps;

	static auto GetScreenCellDimensions() -> Vector2D<int>;
	static auto GetCursorPosXY() -> Vector2D<int>;

	[[nodiscard]] auto ConvertToScreenSpace(Vector2D<double> worldSpace) const -> Vector2D<int>;
	auto ConvertToWorldSpace(Vector2D<int> screenSpace) const -> Vector2D<double>;

	auto GetScreenResolution() const -> Vector2D<double>;

	auto SetPixel(Vector2D<double> pos, oof::color c) const -> void;
	auto GetPixel(Vector2D<double> pos) const -> oof::color&;
	auto setPixel(Vector2D<int> pos, oof::color c) const -> void;
	auto getPixel(Vector2D<int> pos) const -> oof::color&;

	auto Draw() -> void;
	auto Update() const -> void;

	auto AddDrawObject(std::string id, std::shared_ptr<DrawableObject> obj) -> void;
	std::shared_ptr<DrawableObject> GetDrawObject(std::string id);

	//std::vector<std::unique_ptr<DrawableObject>> screenObjects;

private:
	std::unordered_map<std::string, std::shared_ptr<DrawableObject>> screenObjects;

	template <typename char_type>
	auto FastPrint(const std::basic_string<char_type>& sss) -> void;
};
