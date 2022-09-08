#include "glm/gtc/noise.hpp"
#include "Europa/Core.h"
#include "ChunkComponent.h"
#include "ChunkMeshComponent.h"
#include "Europa/GameObject.h"
#include "../Minecraft/Chunkmanager.h"
#include "../BlockJsonParser.h"
#include "../Minecraft/WorldGeneration.h"



ChunkComponent::ChunkComponent(glm::vec3 ChunkPosition, ChunkManager* pchunkManager, bool setActive) :
	m_ChunkPosition{ ChunkPosition }, m_pChunkManager{ pchunkManager }, m_ChunkGeneration{ ChunkPosition, chunkX, chunkY, chunkZ, pchunkManager }, m_ChunkActive{ setActive }
{

	//EU_CORE_INFO("UPDATE CHUNK AT {0}, {1}", m_ChunkPosition.x, m_ChunkPosition.z);


}

ChunkComponent::~ChunkComponent()
{
	
}

void ChunkComponent::Render() const
{
	
}
bool ChunkComponent::IsBlockSolidInChunk(int yIndex, int xIndex, int zIndex) const
{
	//Check if Index does not exceed size
	EU_CORE_ASSERT((yIndex <= (chunkY - 1) || (xIndex <= (chunkX - 1))) || (zIndex <= (chunkZ - 1)), "ACCESSING WRONG INDEX TO CHECK IF BLOCK IS SOLID");
	return IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(xIndex, yIndex, zIndex));
}
void ChunkComponent::DellaocateData()
{
	/*
	if (!m_ChunkActive) {
		GetAttachedGameObject()->RemoveComponent<ChunkMeshComponent>();
		m_pChunkMesh.reset();
	}*/
}

void ChunkComponent::Allocate()
{
	//if (m_ChunkActive && m_pChunkMesh == nullptr) {
	//	m_pChunkMesh = std::make_shared<ChunkMeshComponent>();
	//	GetAttachedGameObject()->AddComponent<ChunkMeshComponent>(m_pChunkMesh);
	//	UpdateMesh();
	//}
}

void ChunkComponent::Start()
{
	//Allocate();
	m_ChunkGeneration.GenerateChunk();
	auto comp = GetAttachedGameObject()->GetComponent<ChunkMeshComponent>();
	if (comp == nullptr) {
		m_pChunkMesh = std::make_shared<ChunkMeshComponent>();
		GetAttachedGameObject()->AddComponent<ChunkMeshComponent>(m_pChunkMesh);
	}
	m_NeedUpdate = true;

}

void ChunkComponent::Update()
{
}

void ChunkComponent::FixedUpdate()
{
}

bool ChunkComponent::Addblock(glm::vec3 posTo, const uint8_t type)
{
	glm::vec2 LocalXZ = glm::vec2{ posTo.x, posTo.z };
	LocalXZ.x -= m_ChunkPosition.x;
	LocalXZ.y -= m_ChunkPosition.z;

	glm::vec3 LocalPos = { std::abs(LocalXZ.x), posTo.y, LocalXZ.y };
	int XIndex = std::abs(glm::clamp(static_cast<int>(LocalPos.x), -15, 15));
	int YIndex = glm::clamp(static_cast<int>(LocalPos.y), 0, chunkY);
	int ZIndex = std::abs(glm::clamp(static_cast<int>(LocalPos.z), -15, 15));

	if (YIndex < (chunkY) && YIndex > 0) {
		if (m_ChunkGeneration.GetTypeAtIndex(XIndex, YIndex, ZIndex) == 0 && HasNeighbours(XIndex, YIndex, ZIndex)) {
			m_ChunkGeneration.AddBlock(type, XIndex, YIndex, ZIndex);
			//cubeArray[YIndex][XIndex][ZIndex]->SetPos({ XIndex + m_ChunkPosition.x, YIndex + (-chunkY + m_ChunkPosition.y), ZIndex + m_ChunkPosition.z });
			EU_CORE_INFO("ADD xIndex: {0}, yIndex: {1}, zIndex: {2}", XIndex, YIndex, ZIndex);

			if (m_ChunkActive)
				UpdateMesh();

			return true;
		}
		else
			return false;
	}
	else
		return false;

}

bool ChunkComponent::DestroyBlock(glm::vec3 posTolook)
{
	glm::vec2 LocalXZ = glm::vec2{ posTolook.x, posTolook.z };
	int xIdnex = std::abs(static_cast<int>(std::abs(posTolook.x) - std::abs(m_ChunkPosition.x)) % 16);
	int zIdnex = std::abs(static_cast<int>(std::abs(posTolook.z) - std::abs(m_ChunkPosition.z)) % 16);


	glm::vec3 LocalPos = { std::abs(LocalXZ.x), posTolook.y, LocalXZ.y };
	int XIndex = xIdnex;
	int YIndex = glm::clamp(static_cast<int>(LocalPos.y), 0, chunkY);
	int ZIndex = zIdnex;




	if (YIndex < (chunkY) && YIndex > 0) {
		if (m_ChunkGeneration.GetTypeAtIndex(XIndex, YIndex, ZIndex) != 0) {
			m_ChunkGeneration.AddBlock(0, XIndex, YIndex, ZIndex);
			//cubeArray[YIndex][XIndex][ZIndex] = nullptr;
			EU_CORE_INFO("DELETED xIndex: {0}, yIndex: {1}, zIndex: {2}", XIndex, YIndex, ZIndex);
			UpdateMesh();
			return true;
		}
		else
			return false;
	}
	else
		return false;


}

bool ChunkComponent::HasNeighbours(int xIndex, int yIndex, int zIndex)
{
	bool HasNeighbour = false;
	if (yIndex != 0) {
		int botIndex = yIndex - 1;
		HasNeighbour = !(IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(xIndex, botIndex, zIndex)) == false);
		if (HasNeighbour)
			return HasNeighbour;
	}
	if (yIndex != chunkY) {
		int topIndex = yIndex + 1;
		HasNeighbour = !(IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(xIndex, topIndex, zIndex)) == false);
		if (HasNeighbour)
			return HasNeighbour;
	}
	if (xIndex != 0) {
		int leftIndex = xIndex - 1;
		HasNeighbour = !(IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(leftIndex, yIndex, zIndex)) == false);
		if (HasNeighbour)
			return HasNeighbour;
	}
	if (xIndex != chunkX) {
		int rightIndex = xIndex + 1;
		HasNeighbour = !(IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(rightIndex, yIndex, zIndex)) == false);
		if (HasNeighbour)
			return HasNeighbour;
	}
	if (zIndex != 0) {
		int frontIndex = zIndex - 1;
		HasNeighbour = !(IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(xIndex, yIndex, frontIndex)) == false);
		if (HasNeighbour)
			return HasNeighbour;
	}
	if (zIndex != chunkZ) {
		int backIndex = zIndex + 1;
		HasNeighbour = !(IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(xIndex, yIndex, backIndex)) == false);
		if (HasNeighbour)
			return HasNeighbour;
	}
	return false;
}

void ChunkComponent::UpdateMesh()
{
	if (m_NeedUpdate == false)
		return;

	bool IsOnSurface = false;
	EU_CORE_INFO("UPDATE CHUNK AT {0}, {1}", m_ChunkPosition.x, m_ChunkPosition.z);

	for (int yIndex = 0; yIndex < ChunkSizeY; yIndex++)
	{
		bool IsYlevelClear = true;
		for (int xIndex = 0; xIndex < ChunkSizeX; xIndex++)
		{
			for (int zIndex = 0; zIndex < ChunkSizeZ; zIndex++)
			{
				uint8_t currentLookUpType = m_ChunkGeneration.GetTypeAtIndex(xIndex, yIndex, zIndex);
				if (currentLookUpType != 0) { //if AIR/Seetrouh skip no faces need to be added
					bool isCube = IsBlockSolid(currentLookUpType);
					//EU_CORE_INFO("UPDATE BLOCK AT {0}, {1}, {2}", xIndex, yIndex, zIndex);

					//Check if block under or above is solid
					if (yIndex != ChunkSizeY - 1) {
						if (yIndex != 0) { //Bottom Block Check
							int botIndex = yIndex - 1;
							if (!IsBlockSolid(xIndex, botIndex, zIndex)) {
								//is solid
								if (m_pChunkMesh->AddFace(glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::BOT, currentLookUpType)) {
									IsYlevelClear = false;
									continue;
								}
							}
						}
						int TopIndex = yIndex + 1;
						if (!IsBlockSolid(xIndex, TopIndex, zIndex))
						{
							if (m_pChunkMesh->AddFace( glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::TOP, currentLookUpType)) {
								IsYlevelClear = false;
								continue;
							}

						}
					}
					if (yIndex == (ChunkSizeY - 1)) //Always render faces at top of chunk
					{
						if (!IsBlockSolid(xIndex, yIndex, zIndex)) {
							if (m_pChunkMesh->AddFace(glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::TOP, currentLookUpType)) {
								IsYlevelClear = false;
								continue;
							}


						}

					}

					//WE DONT RENDER BOTTOM OF CHUNK

					//check left/right X
					if (xIndex != (ChunkSizeX)) { //left check
						int leftIndex = xIndex > 0 ? xIndex - 1 : 0;
						if (!IsBlockSolid(leftIndex, yIndex, zIndex))
							if (m_pChunkMesh->AddFace(glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::LEFT, currentLookUpType)) {
								IsYlevelClear = false;
								continue;
							}

						// right check
						int rightIndex = xIndex < (ChunkSizeX - 1) ? xIndex + 1 : (ChunkSizeX - 1);
						if (!IsBlockSolid(rightIndex, yIndex, zIndex))
							if (m_pChunkMesh->AddFace(glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::RIGHT, currentLookUpType)) {
								IsYlevelClear = false;
								continue;
							}
					}
					//Check neighbouring chunks for now render it
					if (xIndex == 0) {
						if (!m_pChunkManager->IsBlockSolidInChunk(std::make_pair(static_cast<int>(m_ChunkPosition.x) - ChunkSizeX, static_cast<int>(m_ChunkPosition.z)), (ChunkSizeX - 1) - xIndex, yIndex, zIndex)) {
							if (m_pChunkMesh->AddFace( glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::LEFT, currentLookUpType)) {
								IsYlevelClear = false;
								continue;
							}
						}

					}
					if (xIndex == (ChunkSizeX - 1)) {
						if (!m_pChunkManager->IsBlockSolidInChunk(std::make_pair(static_cast<int>(m_ChunkPosition.x) + ChunkSizeX, static_cast<int>(m_ChunkPosition.z)), 0, yIndex, zIndex)) {
							if (m_pChunkMesh->AddFace( glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::RIGHT, currentLookUpType)) {
								IsYlevelClear = false;
								continue;
							}
						}

					}
					//ZCheck
					if (zIndex != (ChunkSizeZ)) { //z is -1 is back +1 is front in directx rasterization
						//Render in chunk
						int backIndex = zIndex > 0 ? zIndex - 1 : 0;
						if (!IsBlockSolid(xIndex, yIndex, backIndex))
							if (m_pChunkMesh->AddFace(glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::BACK, currentLookUpType)) {
								IsYlevelClear = false;
								continue;
							}

						//front check
						int frontIndex = zIndex < (ChunkSizeZ - 1) ? zIndex + 1 : (ChunkSizeZ - 1);
						if (!IsBlockSolid(xIndex, yIndex, frontIndex))
							if (m_pChunkMesh->AddFace(glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::FRONT, currentLookUpType)) {
								IsYlevelClear = false;
								continue;
							}

					}
					//Check neighbouring chunks for now render it
					if (zIndex == 0) {
						if (!m_pChunkManager->IsBlockSolidInChunk(std::make_pair(static_cast<int>(m_ChunkPosition.x), static_cast<int>(m_ChunkPosition.z) - ChunkSizeZ), xIndex, yIndex, (ChunkSizeZ - 1))) {
							if (m_pChunkMesh->AddFace(glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::BACK, currentLookUpType)) {
								IsYlevelClear = false;
								continue;
							}
						}
					}
					if (zIndex == (ChunkSizeZ - 1)) {
						if (!m_pChunkManager->IsBlockSolidInChunk(std::make_pair(static_cast<int>(m_ChunkPosition.x), static_cast<int>(m_ChunkPosition.z) + ChunkSizeZ), xIndex, yIndex, 0)) {
							if (m_pChunkMesh->AddFace(glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::FRONT, currentLookUpType)) {
								IsYlevelClear = false;
								continue;
							}
						}

					}
				}



			}


		}
		if (IsYlevelClear == false && IsOnSurface == false) {
			IsOnSurface = true;
			continue;
		}
		else if (IsYlevelClear == false && IsOnSurface == true) {
			goto ENDCREATELOOP;
		}

	}
ENDCREATELOOP:

	m_pChunkMesh->BufferMesh();
	m_NeedUpdate = false;

}

bool ChunkComponent::IsBlockSolid(uint8_t blockType) const
{
	return BlockJsonParser::GetInstance()->IsSolid(blockType);
}

bool ChunkComponent::IsBlockSolid(int x, int y, int z) const
{
	return BlockJsonParser::GetInstance()->IsSolid((m_ChunkGeneration.GetTypeAtIndex(x, y, z)));
}
