#include "glm/gtc/noise.hpp"
#include "Europa/Core.h"
#include "ChunkComponent.h"
#include "ChunkMeshComponent.h"
#include "Europa/GameObject.h"
#include "../BlockJsonParser.h"
#include "Europa/ResourceManager.h"
#include "ChunkManager.h"
#include "PerlinNosie.h"


ChunkComponent::ChunkComponent(ChunkID iD, int xSize, int ySize, int zSize, ChunkManager* ptr) : m_XSize{ xSize }, m_YSize{ ySize }, m_ZSize{ zSize }, m_AxisSize{ xSize, ySize, zSize }, m_pManager{ ptr }, m_ChunkID{ iD }
{

}

ChunkComponent::~ChunkComponent()
{
}
void ChunkComponent::DestroyChunk()
{
	delete[] m_ChunkArray;
}
bool ChunkComponent::InitializeChunk()
{
	m_ChunkArray = new uint8_t[m_XSize * m_YSize * m_ZSize]{ 0 };


	heightMap.resize(m_XSize * m_ZSize);
	//Create noise map
	glm::vec2 chunkPos{ GetAttachedGameObject()->GetTransform().GetPosition().x,
			GetAttachedGameObject()->GetTransform().GetPosition().z };
	glm::vec3 chunkScaling = GetAttachedGameObject()->GetTransform().GetScale();

	const siv::PerlinNoise perlin{ 1 };

	for (int z = 0; z < m_AxisSize.z; z++)
	{
		for (int x = 0; x < m_AxisSize.x; x++) {



			float worldxpos = (chunkPos.x) + (x * chunkScaling.x);
			float worldzpos = (chunkPos.y) + (z * chunkScaling.z);


			float value = static_cast<float>((perlin.octave2D_01((worldxpos) / 550.f, (worldzpos) / 550.f, 8)));
			float value2 = static_cast<float>((perlin.octave2D_01((worldxpos) / 700.f, (worldzpos) / 700.f, 8)));
			float value3 = static_cast<float>((perlin.octave2D_01((worldxpos) / 1024.f, (worldzpos) / 650.f, 8)));

			float totalValue = static_cast<float>((value * value2 * value3 * value3 - 0) / (1 - 0));
			totalValue = (totalValue + 1) / 2;

			float mappedValue = static_cast<int>(glm::mix(0, m_YSize, value));

			heightMap[z * m_XSize + x] = mappedValue;
		}
	}

	for (int z = 0; z < m_AxisSize.z; z++)
	{
		for (int x = 0; x < m_AxisSize.x; x++)
		{

			for (int y = 0; y < m_AxisSize.y; y++) {

				if (y < (m_AxisSize.y - 10)) {
					uint8_t blockID = GetBlockType(x, y, z, (heightMap)[z * m_XSize + x]);

					//Flip x to correct space
					x = (m_AxisSize.x - 1) - x;
					*(m_ChunkArray + x * m_AxisSize.y * m_AxisSize.x + y * m_AxisSize.z + z) = blockID;
				}

			}

		}

	}
	m_Initialized = true;
	return m_Initialized;

}

void ChunkComponent::Start()
{
	//Allocate();
	auto comp = GetAttachedGameObject()->GetComponent<ChunkMeshComponent>();
	if (comp == nullptr) {
		m_pChunkMesh = std::make_shared<ChunkMeshComponent>();
		GetAttachedGameObject()->AddComponent<ChunkMeshComponent>(m_pChunkMesh);
	}
}
uint8_t ChunkComponent::GetBlockType(int x, int y, int z, int maxHeight)
{
	int dirtAmount = rand() % 2;
	int leafchance = rand() % 20;
	if (y > maxHeight + dirtAmount)
		return 0;

	else //in height mapped scope
	{
		if (y >= (maxHeight - dirtAmount))
			return 1;
		else
			return 2;
	}
	return 0;

}


void ChunkComponent::Render() const
{
	
}
void ChunkComponent::BuildTrees()
{
	int treeAmount = 1;
	while (treeAmount != 0)
	{
		int x = rand() % m_XSize;
		int z = rand() % m_ZSize;
		int y = (heightMap)[z * m_XSize + x];

		if (GetBlock(x, y, z) == 1)
		{
			// Create tree
			// Trunk height
			int trunkHeight = 5 + (rand() % 4);
			// Trunk
			for (int i = 0; i < trunkHeight; i++)
			{
				ReplaceBlock(x, y + i, z, 4);
			}
			// Leaves
			for (int i = -2; i <= 2; i++)
			{
				for (int j = -2; j <= 2; j++)
				{
					for (int j = -2; j <= 2; j++)
					{
						for (int k = trunkHeight - 2; k <= trunkHeight + 2; k++)
						{
							// Only place leaves if block is within a certain distance from the trunk

							ReplaceBlock(x + i, y + k, z + j, 3);
						}
					}
				}
			}
		}
		treeAmount--;
	}
}
void ChunkComponent::CreateMesh()
{
	if (m_NeedMeshing) {

		for (size_t axis = 0; axis < 3; ++axis) //Go over all axises
		{
			//Go over slice in certain direction: ie slice towards x are all planes in YZ
			const int Axis1 = (axis + 1) % 3;
			const int Axis2 = (axis + 2) % 3;

			const int currentAxisLimit = m_AxisSize[axis];
			const int axis1Limit = m_AxisSize[Axis1];
			const int axis2Limit = m_AxisSize[Axis2];

			auto deltaAxis1 = glm::ivec3{ 0 };
			auto deltaAxis2 = glm::ivec3{ 0 };

			auto chunkIterator = glm::ivec3{ 0 };
			auto axisMask = glm::ivec3{ 0 };

			axisMask[axis] = 1;

			std::vector<BlockMask> maskVector;
			maskVector.resize(axis1Limit * axis2Limit);

			//Check elke slice
			for (chunkIterator[axis] = -1; chunkIterator[axis] < currentAxisLimit;)
			{
				int n = 0; // Represents mask index

				for (chunkIterator[Axis2] = 0; chunkIterator[Axis2] < axis2Limit; ++chunkIterator[Axis2])
				{
					for (chunkIterator[Axis1] = 0; chunkIterator[Axis1] < axis1Limit; ++chunkIterator[Axis1])
					{
						//Get current block
						const uint8_t currentBlock = GetBlock(chunkIterator.x, chunkIterator.y, chunkIterator.z);
						//Get neigbourhing block
						const uint8_t compareBlock = GetBlock(chunkIterator.x + axisMask.x, chunkIterator.y + axisMask.y, chunkIterator.z + axisMask.z);

						//verschil maken met air en transparant 3 opties
						const bool IsCurrOpqaue = IsBlockSolid(currentBlock);
						const bool IsCompareOpqaue = IsBlockSolid(compareBlock);

						if (currentBlock == 3 && !IsCompareOpqaue)
						{
							maskVector[n++] = BlockMask{ currentBlock, 1}; //towards direction of compareblock
							//draw other block aswell
						}
						else if (compareBlock == 3 && !IsCurrOpqaue)
						{
							maskVector[n++] = BlockMask{ compareBlock, -1 }; //towards direction of compareblock
							//draw other block aswell
						}
						else if (IsCurrOpqaue == IsCompareOpqaue) { //if equals no face 
							maskVector[n++] = BlockMask{ 0, 0 };
						}
						else if (IsCurrOpqaue) {
							maskVector[n++] = BlockMask{ currentBlock, 1 }; //towards direction of compareblock
						}
						else {
							maskVector[n++] = BlockMask{ compareBlock, -1 }; //towards direction of currentBlock
						}
					}
				}
				++chunkIterator[axis];
				n = 0;
				//Generate mesh based on mask information;
				for (size_t j = 0; j < axis2Limit; ++j)
				{
					for (size_t i = 0; i < axis1Limit;)
					{
						if (maskVector[n].normal != 0) //If not transparant
						{
							const auto currentMask = maskVector[n];
							chunkIterator[Axis1] = i;
							chunkIterator[Axis2] = j;

							int width;
							for (width = 1; (((i + width) < axis1Limit) && (CompareMask(maskVector[n + width], currentMask))); ++width)
							{
								//Merge mask together
							}

							int height;
							bool isDone{ false };
							for (height = 1; (j + height) < axis2Limit; ++height)
							{	
								//Merge mask together height
								for (size_t k = 0; k < width; ++k)
								{	//check entire width to merge height on all
									if (CompareMask(maskVector[n + k + height * axis1Limit], currentMask)) {
										continue;
									}
									isDone = true;
									break;
								}
								if(isDone)
									break;

							}
							deltaAxis1[Axis1] = width;
							deltaAxis2[Axis2] = height;

							CreateQuad(currentMask, axisMask
								, chunkIterator
								, chunkIterator + deltaAxis1 //width
								, chunkIterator + deltaAxis2 //height
								, chunkIterator + deltaAxis1 + deltaAxis2 //width + height
								, width, height);

							//reset
							deltaAxis1 = glm::ivec3{ 0 };
							deltaAxis2 = glm::ivec3{ 0 };

							//Reset all mask values
							for (int l = 0; l < height; l++)
							{
								for (int k = 0; k < width; k++)
								{
									maskVector[n + k + l * axis1Limit] = BlockMask{ 0, 0 };
								}
							}

							i += width;
							n += width;
						}
						else {
							i++;
							n++;
						}
					}
				}
			}

		}

		m_NeedMeshing = false;
		m_pChunkMesh->ResetMesh();
	}
}
void ChunkComponent::CreateQuad(BlockMask mask, glm::ivec3 axisMask, glm::ivec3 v1, glm::ivec3 v2, glm::ivec3 v3, glm::ivec3 v4, int widht, int height)
{

	const auto normal = glm::vec3(axisMask * mask.normal);
	std::vector<glm::vec3> maskVertices;
	maskVertices.push_back(v1);
	maskVertices.push_back(v2);
	maskVertices.push_back(v3);
	maskVertices.push_back(v4);
	m_pChunkMesh->AddVertices(maskVertices, normal, mask.normal, widht, height, GetTextureIndex(mask.id, normal));

}

int ChunkComponent::GetTextureIndex(uint8_t block, glm::vec3 normal)
{
	switch (block)
	{
	case 1: //grass
		if (normal == glm::vec3{ 0,1,0 })
			return 2;
		if (normal == glm::vec3{ 0,-1,0 })
			return 0;
		else
			return 1;
		break;
	case 2:
		return 3;
	case 3:
		return 4;
	case 4:
		return 5;
	default:
		break;
	}
}


void ChunkComponent::Update()
{
	/*if (m_NeedUpdate)
		CreateMesh();*/
}

void ChunkComponent::FixedUpdate()
{

}
bool ChunkComponent::IsBlockSolid(uint8_t blockType) const
{
	return BlockJsonParser::GetInstance()->IsSolid(blockType);
}

bool ChunkComponent::IsBlockSolid(int x, int y, int z) const
{
	if (x >= m_AxisSize.x || y >= m_AxisSize.y || z >= m_AxisSize.z || x < 0 || y < 0 || z < 0)
		return true;

	uint8_t resultBlock = *(m_ChunkArray + x * m_AxisSize.y * m_AxisSize.z + y * m_AxisSize.z + z);
	return resultBlock != 0 ? true : false;
}

void ChunkComponent::ReplaceBlock(int x, int y, int z, uint8_t id)
{
	//std::lock_guard<std::mutex> lock(m_ChunkIDMapMutex);

	if (x < 0 || x >= (m_XSize) || z < 0 || z >= (m_ZSize))
	{

		glm::dvec2 pos{ GetAttachedGameObject()->GetTransform().GetPosition().x,
		GetAttachedGameObject()->GetTransform().GetPosition().z };

		m_pManager->ReplaceBlock(m_ChunkID, id, x, y, z);
		return;

	}

	*(m_ChunkArray + x * m_AxisSize.y * m_AxisSize.z + y * m_AxisSize.z + z) = id;
}

uint8_t ChunkComponent::GetBlock(int x, int y, int z)
{
	if (y < 0 || y >= (m_YSize))
		return 0;

	if (x < 0 || x >= (m_XSize) || z < 0 || z >= (m_ZSize))
	{
		glm::dvec2 pos{ GetAttachedGameObject()->GetTransform().GetPosition().x,
			GetAttachedGameObject()->GetTransform().GetPosition().z };
	
		return m_pManager->GetBlockIDNeighbour(m_ChunkID, x, y, z);
	
	}

	uint8_t resultBlock = *(m_ChunkArray + x * m_AxisSize.y * m_AxisSize.z + y * m_AxisSize.z + z);
	return resultBlock;
}

bool ChunkComponent::CompareMask(BlockMask mask1, BlockMask mask2)
{
	return mask1.id == mask2.id && mask1.normal == mask2.normal;
	
}


//bool ChunkComponent::IsBlockSolid(int x, int y, int z) const
//{
//	return BlockJsonParser::GetInstance()->IsSolid((m_ChunkGeneration.GetTypeAtIndex(x, y, z)));
//}
