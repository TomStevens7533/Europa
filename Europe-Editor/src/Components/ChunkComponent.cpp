#include "glm/gtc/noise.hpp"
#include "Europa/Core.h"
#include "ChunkComponent.h"
#include "ChunkMeshComponent.h"
#include "Europa/GameObject.h"
#include "../BlockJsonParser.h"
#include "Europa/ResourceManager.h"
#include "ChunkManager.h"


ChunkComponent::ChunkComponent(int xSize, int ySize, int zSize, const std::shared_ptr < ChunkManager> ptr, int scale /*= 1*/) : m_Scale{scale}
, m_XSize{ xSize }, m_YSize{ ySize }, m_ZSize{ zSize }, m_AxisSize{ xSize, ySize, xSize }, m_pManager{ ptr }
{
	
	

	m_ChunkArray = new uint8_t[m_XSize * m_YSize * m_ZSize]{0};


}

ChunkComponent::~ChunkComponent()
{
	delete[] m_ChunkArray;
}

void ChunkComponent::Start()
{
	//Allocate();
	auto comp = GetAttachedGameObject()->GetComponent<ChunkMeshComponent>();
	if (comp == nullptr) {
		m_pChunkMesh = std::make_shared<ChunkMeshComponent>();
		GetAttachedGameObject()->AddComponent<ChunkMeshComponent>(m_pChunkMesh);
	}
	m_NeedUpdate = true;

	//Create noise map
	glm::ivec2 chunkPos{ GetAttachedGameObject()->GetTransform().GetPosition().x,
			GetAttachedGameObject()->GetTransform().GetPosition().z };
	std::array<int, 16 * 16 > heightMap;

	for (int z = 0; z < m_ZSize; z++)
	{
		for (int x = 0; x < m_XSize; x++) {
			int voxelxPos = x + chunkPos.x;
			int voxedzPos = z + chunkPos.y;

			float value = glm::simplex(glm::vec2{ voxelxPos / 64.f, voxedzPos / 64.f });
			float value2 = glm::simplex(glm::vec2{ voxelxPos / 128.f, voxedzPos / 128.f });
			float value3 = glm::simplex(glm::vec2{ voxelxPos / 250.f, voxedzPos / 400.f });


			//make between 0 and 1.0
			float totalValue = (value * value2 * value3) / (1.f - 0.f);
			totalValue = (totalValue + 1) / 2;

			float mappedValue = glm::mix(0, m_YSize, totalValue);

			heightMap[z * 16 + x] = static_cast<int>(mappedValue);
		}

	}

	//Generate block types
	for (int i = 0; i < m_AxisSize.x; i++) {
		for (int j = 0; j < m_AxisSize.y; j++) {

			for (int k = 0; k < m_AxisSize.z; k++) {

				// Assign values to the
				// memory blocks created
				//* (m_ChunkArray + i * m_AxisSize.y * m_AxisSize.z + j * m_AxisSize.z + k) = ((i % 2 == 0) ? 0 : 1);

				*(m_ChunkArray + i * m_AxisSize.y * m_AxisSize.z + j * m_AxisSize.z + k) = GetBlockType(i, j, k, &heightMap);
			}
		}
	}

}
uint8_t ChunkComponent::GetBlockType(int x, int y, int z, std::array<int, 16 * 16 >* heightmap)
{
	int maxHeight = (*heightmap)[z * 16 + x];
	if (y < maxHeight)
		return 1;
	else
		return 0;
}


void ChunkComponent::Render() const
{
	
}

void ChunkComponent::CreateMesh()
{
	if (m_NeedUpdate) {

		m_pChunkMesh->ResetMesh();


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

						const bool IsCurrOpqaue = currentBlock != 0;
						const bool IsCompareOpqaue = compareBlock != 0;

						if (IsCurrOpqaue == IsCompareOpqaue) { //if equals no face 
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

		m_NeedUpdate = false;
		m_pChunkMesh->BufferMesh();
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
		break;
	default:
		break;
	}
}


void ChunkComponent::Update()
{
	if (m_NeedUpdate)
		CreateMesh();
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
	*(m_ChunkArray + x * m_AxisSize.y * m_AxisSize.z + y * m_AxisSize.z + z) = id;
}

uint8_t ChunkComponent::GetBlock(int x, int y, int z)
{
	//TODO CHECK OTHER CHUNKS
	if (x >= m_AxisSize.x || y >= m_AxisSize.y || z >= m_AxisSize.z || x < 0 || y < 0 || z < 0)
		return 0;

	//return 0;
	//if (y >= m_AxisSize.y || y < 0)
	//	return 0;
	//
	//if (x < 0 || x >= (m_XSize))
	//{
	//	return 0;
	//	glm::ivec2 pos{ GetAttachedGameObject()->GetTransform().GetPosition().x,
	//		GetAttachedGameObject()->GetTransform().GetPosition().z };
	//
	//	return m_pManager->GetBlockIDNeighbour(pos, x, y, z);
	//
	//}
	//return 1;

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
