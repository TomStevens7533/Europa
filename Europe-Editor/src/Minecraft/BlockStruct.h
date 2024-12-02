#pragma once
#include "glm/ext/scalar_uint_sized.hpp"
enum class Faces
{
	TOP, BOT, LEFT, RIGHT, FRONT, BACK

};

struct ChunkID
{
	int x;
	int y;
};

enum class BiomeType
{
	Grass,
	Ice
};

enum class BlockType : uint8_t {
	AIR,
	GRASS,
	DIRT,
	STONE,
	WOOD,
	LEAVES
};
