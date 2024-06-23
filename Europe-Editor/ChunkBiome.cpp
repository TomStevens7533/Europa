#include "ChunkBiome.h"

#define MAP_SIZE_X 100
#define MAP_SIZE_Y 100

void ChunkBiome::GenerateMap()
{
	heightMap.resize(100 * 100);
}

BiomeType ChunkBiome::SampleBiome(int x, int y)
{
	return BiomeType::Grass;
}

