#include "glm/gtc/noise.hpp"
#include "Europa/Core.h"
#include "ChunkComponent.h"
#include "ChunkMeshComponent.h"
#include "Europa/GameObject.h"
#include "../Minecraft/Chunkmanager.h"
#include "../BlockJsonParser.h"
#include "../Minecraft/WorldGeneration.h"



ChunkComponent::ChunkComponent(glm::vec3 ChunkPosition, ChunkManager* pchunkManager, std::pair<int, int>chunkIndex, bool setActive) :
	m_ChunkPosition{ ChunkPosition }, m_pChunkManager{ pchunkManager }, m_ChunkIndex{ chunkIndex }, m_ChunkGeneration{ ChunkPosition, chunkX, chunkY, chunkZ, pchunkManager }, m_ChunkActive{ setActive }
{



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
	Allocate();
	m_ChunkGeneration.GenerateChunk();
	auto comp = GetAttachedGameObject()->GetComponent<ChunkMeshComponent>();
	if (comp == nullptr) {
		m_pChunkMesh = std::make_shared<ChunkMeshComponent>();
		GetAttachedGameObject()->AddComponent<ChunkMeshComponent>(m_pChunkMesh);
	}
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
			//EU_CORE_INFO("ADD xIndex: {0}, yIndex: {1}, zIndex: {2}", XIndex, YIndex, ZIndex);

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
			//EU_CORE_INFO("DELETED xIndex: {0}, yIndex: {1}, zIndex: {2}", XIndex, YIndex, ZIndex);
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
	//if (m_ChunkMesh != nullptr) {


	bool IsSideSoldid[6] = { false, false, false, false, false, false };

	int isYallSolid = 0;
	for (int yIndex = 0; yIndex < chunkY; yIndex++)
	{


		for (int xIndex = 0; xIndex < chunkX; xIndex++)
		{


			isYallSolid = 0;
			for (int zIndex = 0; zIndex < chunkZ; zIndex++)
			{
				uint8_t currentLookUpType = m_ChunkGeneration.GetTypeAtIndex(xIndex, yIndex, zIndex);
				if (currentLookUpType != 0) { //if AIR/Seetrouh skip no faces need to be added
					//YSolidCheck

					if (yIndex != chunkY - 1) {
						if (yIndex != 0) { //Bottom Block Check
							int botIndex = yIndex - 1;
							if (IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(xIndex, botIndex, zIndex)) == false) {
								//if solid
								if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::BOT, currentLookUpType))
									continue;
							}
						}



						int TopIndex = yIndex + 1;
						if (IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(xIndex, TopIndex, zIndex)) == false)
						{
							if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::TOP, currentLookUpType))
								continue;

						}
					}
					if (yIndex == 0) //No face rendering at bottom of chunk
						IsSideSoldid[1] = true;
					if (yIndex >= chunkY - 1) //render faces at top of chunk
						if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::TOP, currentLookUpType))
							continue;


					//check left/right
					if (xIndex != 0) { //left check
						int leftIndex = xIndex - 1;
						if (IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(leftIndex, yIndex, zIndex)) == false)
							if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::LEFT, currentLookUpType))
								continue;
					}
					if (xIndex == 0) { //left boundary check
						if (m_pChunkManager->IsBlockSolidInChunk({ m_ChunkIndex.first - 1, m_ChunkIndex.second }, (chunkX - 1) - xIndex, yIndex, zIndex) == false) //if not solid render face
							if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::LEFT, currentLookUpType))
								continue;

					}

					if (xIndex != chunkX - 1) { // right check
						int rightIndex = xIndex + 1;
						if (IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(rightIndex, yIndex, zIndex)) == false)
							if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::RIGHT, currentLookUpType))
								continue;

					}
					if (xIndex == chunkX - 1) { //right boundary check
						if (m_pChunkManager->IsBlockSolidInChunk({ m_ChunkIndex.first + 1, m_ChunkIndex.second }, (chunkX - 1) - xIndex, yIndex, zIndex) == false)
							if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::RIGHT, currentLookUpType))
								continue;


					}

					//ZCheckingaa
					if (zIndex != 0) { //z is -1 is back +1 is front in opengl rasterization
						int backIndex = zIndex - 1;
						if (IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(xIndex, yIndex, backIndex)) == false)
							if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::BACK, currentLookUpType))
								continue;

					}
					if (zIndex == 0) { //back boundary check
						if (m_pChunkManager->IsBlockSolidInChunk({ m_ChunkIndex.first, m_ChunkIndex.second - 1 }, xIndex, yIndex, (chunkZ - 1) - zIndex) == false)
							if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::BACK, currentLookUpType))
								continue;
					}

					if (zIndex != chunkZ - 1) { //front check
						int frontIndex = zIndex + 1;
						if (IsBlockSolid(m_ChunkGeneration.GetTypeAtIndex(xIndex, yIndex, frontIndex)) == false)
							if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::FRONT, currentLookUpType))
								continue;

					}
					if (zIndex == chunkZ - 1) { //front chunk bounday check
						if (m_pChunkManager->IsBlockSolidInChunk({ m_ChunkIndex.first, m_ChunkIndex.second + 1 }, xIndex, yIndex, (chunkZ - 1) - zIndex) == false)
							if (m_pChunkMesh->AddFace(m_ChunkPosition, glm::vec3{ static_cast<float>(xIndex), static_cast<float>(yIndex), static_cast<float>(zIndex) }, Faces::FRONT, currentLookUpType))
								continue;

					}



				}



			}


		}
	}
	m_pChunkMesh->BufferMesh();
	//}

}

bool ChunkComponent::IsBlockSolid(uint8_t blockType) const
{
	return BlockJsonParser::GetInstance()->IsSolid(blockType);
}
