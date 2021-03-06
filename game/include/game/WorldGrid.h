#pragma once

#include <concepts>

#include <array>
#include <cstdint>

#include <wglm/glm.hpp>

#include <serial/Serializer.h>

#include <mem/Index.h>

#include <misc/Misc.h>

#include "Game.h"

constexpr auto WORLD_SIZE = 70;

namespace game
{
	struct WeakObject;
	struct QualifiedObject;
	struct Everything;

	glm::ivec2 getDirectionFromIndex(std::integral auto index);
	uint8_t getIndexFromDirection(glm::ivec2 vec);

	struct Directions
	{
		std::array<uint8_t, 16> data;

		glm::ivec2 getDirection(int32_t index) const;
		void setDirection(int32_t index, uint8_t direction);
		void setDirection(int32_t index, glm::ivec2 direction);

		bool hasDirection(int32_t index);
	};

	struct WorldGrid
	{
		struct Trace
		{
			std::vector<UniqueObject> data;

			[[nodiscard]]
			UniqueObject release(WeakObject const& obj);

			void add(WeakObject const& obj);
			void add(UniqueObject&& obj);

			void clear();
		};

		std::array<std::array<Trace, WORLD_SIZE>, WORLD_SIZE> grid;
		std::array<std::array<int32_t, WORLD_SIZE>, WORLD_SIZE> group;
		std::array<std::array<Directions, WORLD_SIZE>, WORLD_SIZE> directions;

		bool hasDirection(glm::ivec2 p, int32_t index);
		void setDirection(glm::ivec2 p, int32_t index, uint8_t direction);
		void setDirection(glm::ivec2 p, int32_t index, glm::ivec2 direction);
		glm::ivec2 getDirection(glm::ivec2 p, int32_t index);

		void replaceGroup(glm::ivec2 p, int32_t replace, int32_t with);

		bool isGrouped(glm::ivec2 pos);
		void setGroup(glm::ivec2 pos, int32_t g);
		int32_t getGroup(glm::ivec2 pos) const;

		std::optional<WeakObject> get(int32_t x, int32_t y);
		std::optional<WeakObject> get(glm::ivec2 pos);

		void place(Index<Everything> index, int32_t x, int32_t y);
		void place(Index<Everything> index, glm::ivec2 pos);

		void remove(int32_t x, int32_t y);
		void remove(glm::ivec2 pos);

		bool occupied(int32_t x, int32_t y);
		bool occupied(glm::ivec2 pos);
		bool empty(glm::ivec2 pos);

		WorldGrid() = default;
		~WorldGrid() = default;

		NO_COPY_MOVE(WorldGrid);
	};

	glm::ivec2 getDirectionFromIndex(std::integral auto index) {
		assert(index >= 0);
		switch (index) {
			case 0:
				return glm::ivec2(1, 1);
				break;
			case 1:
				return glm::ivec2(1, 0);
				break;
			case 2:
				return glm::ivec2(1, -1);
				break;
			case 3:
				return glm::ivec2(0, -1);
				break;
			case 4:
				return glm::ivec2(-1, -1);
				break;
			case 5:
				return glm::ivec2(-1, 0);
				break;
			case 6:
				return glm::ivec2(-1, 1);
				break;
			case 7:
				return glm::ivec2(0, 1);
				break;
			default:
				assert(0);
				return glm::ivec2(0, 0);
				break;
		}
	}

}

template<>
struct serial::Serializable<game::WorldGrid::Trace>
{
	inline static const std::string_view typeName = "Trace";

	ALL_DEF(game::WorldGrid::Trace) {
		return serializer.runAll<Selector>(
			ALL(data)
			);
	}
};

template<>
struct serial::Serializable<game::WorldGrid>
{
	inline static const auto typeName = "WorldGrid";

	ALL_DEF(game::WorldGrid) {
		return serializer.runAll<Selector>(
			ALL(grid),
			ALL(group),
			ALL(directions)
			);
	};
};

template<>
struct serial::Serializable<game::Directions>
{
	inline static const auto typeName = "Directions";

	ALL_DEF(game::Directions) {
		return serializer.runAll<Selector>(
			ALL(data)
			);
	};
};

