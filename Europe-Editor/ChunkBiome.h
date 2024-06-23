#pragma once
#include "src/Minecraft/BlockStruct.h"
#include <vector>

class ChunkBiome
{
public:
	void GenerateMap();
	BiomeType SampleBiome(int x, int y);
private:
	std::vector<int> heightMap;
};