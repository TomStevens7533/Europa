#include "WorldGeneration.h"
#include "glm/gtc/noise.hpp"
#include <iostream>
#include "Chunkmanager.h"

ChunkGeneration::ChunkGeneration(const glm::vec3& chunkPos, int xSize, int YSize, int Zsize, ChunkManager* pMAnager) 
	: m_XLength{ xSize }, m_ZLength{ Zsize }, m_YLength{ YSize }, m_pChunkManager{ pMAnager }, m_ChunkPos{chunkPos}
{
	for (int z = 0; z < m_ZLength; z++)
	{
		for (int x = 0; x < m_XLength; x++) {
			int voxelxPos = x + chunkPos.x;
			int voxedzPos = z + chunkPos.z;

			float value = glm::simplex(glm::vec2{ voxelxPos / 64.f, voxedzPos / 64.f });
			float value2 = glm::simplex(glm::vec2{ voxelxPos / 128.f, voxedzPos / 128.f });
			float value3 = glm::simplex(glm::vec2{ voxelxPos / 1000.f, voxedzPos / 1000.f });
			//make between 0 and 1.0
			float totalValue = (value * value2 * value3 * value3 - 0.f) / (1.f - 0.f);
			totalValue = (totalValue + 1) / 2;

			float mappedValue = glm::mix(0, 150, totalValue);
			 
			heightMap[z * 16 + x] = static_cast<int>(mappedValue);
		}

	}
}

void ChunkGeneration::GenerateChunk()
{
	for (size_t xIndex = 0; xIndex < m_XLength; xIndex++)
	{
		for (size_t zIndex = 0; zIndex < m_ZLength; zIndex++)
		{

			for (size_t yIndex = 0; yIndex < m_YLength; yIndex++)
			{
				if(GetTypeAtIndex(xIndex,yIndex,zIndex) == BlockTypes::AIR)
					cubeArray[yIndex][xIndex][zIndex] = GetBlockType(xIndex, yIndex, zIndex);
				//cubeArray[yIndex][xIndex][zIndex]->SetPos({ cubePosition.x + xIndex, cubePosition.y + yIndex, cubePosition.z + zIndex });
			}

		}


	}

}

BlockTypes ChunkGeneration::GetTypeAtIndex(int x, int y, int z) const
{
	return cubeArray[y][x][z];
}

BlockTypes ChunkGeneration::GetBlockType(int x, int y, int z)
{
	int maxHeight = heightMap[z * 16 + x];

	//flora Check
	{
		if (y == maxHeight + 1 && y > 60) {
			int maxValue = 100;
			//flowers
			if (((rand() % 1000) / 10.f) <= m_FlowerChance) {
				int randFlower = rand() % 4;
				switch (randFlower)
				{
				case 0:
					break;
					return BlockTypes::ROSE;
				case 1:
					return BlockTypes::AZURE;
					break;
				case 2:
					return BlockTypes::TULIP;
					break;
				default:
					return BlockTypes::ROSE;
					break;
				}
			}
			//trees
			if (((rand() % 1000) / 10.f) <= m_TreeChance) {
				BuildTree(x, y + 1, z);
				return BlockTypes::OAKLOG;
			}
		}

	}

	if (y > maxHeight && y > 60)
		return BlockTypes::AIR;
	if (y > maxHeight)
		return BlockTypes::WATER;



	if(y == maxHeight)
		return BlockTypes::GRASS;

	int dirtDeviationLength = rand() % m_MaxDirtLength;
	if (y >= maxHeight - dirtDeviationLength)
		return BlockTypes::DIRT;
	

	return BlockTypes::STONE;
}

void ChunkGeneration::BuildTree(int x, int y, int z)
{
	//build log
	int legth = (m_MinTreeLength - 1) + m_ExtaTreeLength  +(1 + (rand() % m_ExtaTreeLength));
	for (size_t i = 0; i < legth; i++)
	{
   		AddBlock(BlockTypes::OAKLOG, x, y + i, z);
	}
	//Leaves
	int leaveLength = legth;
	AddBlock(BlockTypes::LEAVES, x, y + legth, z);
	int currentMaxLeafHeight = (leaveLength + m_MinLeafHeight + (rand() % (m_MaxLeafHeight - m_MinLeafHeight)));
	for (int YIndex = leaveLength; YIndex <= currentMaxLeafHeight; YIndex++)
	{

		int LeafDifference = 1 + (YIndex % (leaveLength / 4));
		int XLeafDifference = LeafDifference;
		for (int xIndex = -XLeafDifference; xIndex <= LeafDifference; xIndex++)
		{
			int ZLeafDifference =  XLeafDifference + m_MinLeafWidth;

			for (int zIndex = -ZLeafDifference; zIndex <= LeafDifference; zIndex++)
			{
				if (IsIndexInBounds((x + xIndex), y + leaveLength - (currentMaxLeafHeight - YIndex), (z + zIndex))) {
					//Fill inn this chunk
					AddBlock(BlockTypes::LEAVES, (x + xIndex), y + leaveLength - (currentMaxLeafHeight - YIndex), (z + zIndex));
				}
				else {
					//fill in in neighbouring chunk 
					m_pChunkManager->AddBlockAtPos({ m_ChunkPos.x + (x + xIndex), m_ChunkPos.y +
						(y + leaveLength - (currentMaxLeafHeight - YIndex)) ,  m_ChunkPos.z + (z + zIndex) }, BlockTypes::LEAVES);
				}
			}

		}

	}
}
 
bool ChunkGeneration::IsIndexInBounds(int x, int y, int z) const
{
	if (x < 0 || x > (m_XLength - 1))
		return false;
	if (y < 0 || y > (m_YLength - 1))
		return false;
	if (z < 0 || z > (m_ZLength - 1))
		return false;

	return true;
}

void ChunkGeneration::AddBlock(BlockTypes type, int x, int y, int z)
{

	cubeArray[y][x][z] = type;
	
}

