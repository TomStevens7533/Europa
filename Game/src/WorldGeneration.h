#pragma once
#include "BlockStruct.h"
#include <array>
#include <glm/glm.hpp>

class ChunkManager;
class ChunkGeneration {
public:
	ChunkGeneration(const glm::vec3& chunkPos, int xSize, int YSize, int Zsize, ChunkManager* pMAnager);
	
	void GenerateChunk();
	BlockTypes GetTypeAtIndex(int x, int y, int z) const;
	void AddBlock(BlockTypes type, int x, int y, int z);
private:
	BlockTypes GetBlockType(int x, int y, int z);
	void BuildTree(int x, int y, int z);
	bool IsIndexInBounds(int x, int y, int z) const;
private:
	std::array<int, 16* 16 > heightMap;
	int m_MaxDirtLength = 5;
	//tree
	int m_MinTreeLength = 3;
	int m_ExtaTreeLength = 4;
	int m_ExtaLeafLength = 3;
	int m_MinLeafHeight = 5;
	int m_MaxLeafHeight = 8;
	int m_MinLeafWidth = 2;
	int m_MaxLeafWith = 4;

	float m_FlowerChance = 15.f; //10 percent;
	float m_TreeChance = 0.3f; //20 percent;

	int m_XLength;
	int m_YLength;
	int m_ZLength;

	ChunkManager* m_pChunkManager;
	glm::vec3 m_ChunkPos;
	BlockTypes cubeArray[256][16][16]{BlockTypes::AIR};

};
