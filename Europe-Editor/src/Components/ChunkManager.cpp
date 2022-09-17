#include "ChunkManager.h"
#include "Europa/GameObject.h"
#include "ChunkComponent.h"

ChunkManager::ChunkManager(const int xSize, int ySize, int zSize, const int chunkWidthAmount, const int chunkDepthAmount, float scale)
	: m_ChunkxSize{ xSize }, m_ChunkySize{ ySize }, m_ChunkzSize{ zSize }, m_ChunkWidthAmount{ chunkWidthAmount }, m_ChunkDepthAmount{chunkDepthAmount}
	, m_IsUpdatingAroundCamera{false}, m_Scale{ scale }
{

}

ChunkManager::ChunkManager(const int xSize, int ySize, int zSize, Eu::PerspectiveCameraControllerComponent* cam, float scale /*= 1*/)
	: m_ChunkxSize{ xSize }, m_ChunkySize{ ySize }, m_ChunkzSize{ zSize }, m_Scale{scale}, m_Camera{cam}, m_IsUpdatingAroundCamera{true}
{
	
}

ChunkManager::~ChunkManager()
{

}

void ChunkManager::Start()
{
	if (m_IsUpdatingAroundCamera == false) {
		//Create chunks based on width and depth around origin gameobject
		const glm::ivec2 originPos = glm::ivec2{ glm::round(GetAttachedGameObject()->GetTransform().GetPosition().x), glm::round(GetAttachedGameObject()->GetTransform().GetPosition().z) };
		const int ChunkTotalWidth = m_ChunkWidthAmount  * glm::floor(m_ChunkxSize * m_Scale);
		const int ChunkTotalDepth = m_ChunkDepthAmount  * glm::floor(m_ChunkzSize * m_Scale);



		for (int x = (originPos.x - ChunkTotalWidth); x < (originPos.x + ChunkTotalWidth); x += glm::floor(m_ChunkxSize * m_Scale))
		{
			for (int z = (originPos.y - ChunkTotalDepth); z < (originPos.y + ChunkTotalDepth); z += glm::floor(m_ChunkzSize * m_Scale))
			{
				//Create chunk
				
				CreateChunk(glm::ivec2{ x,z });
			}
		}
		
	}
}
void ChunkManager::CreateChunk(glm::ivec2 position)
{
	EU_CORE_INFO("Creating Chunk at ID: {0},{1}", position.x , position.y );
	std::pair<int, int> id = GetChunkID(position);
	auto chunkComp = std::make_shared<ChunkComponent>(m_ChunkxSize, m_ChunkySize, m_ChunkzSize, shared_from_this(), m_Scale);
	m_ChunkIDMap.insert(std::make_pair(id, chunkComp));
	auto go = std::make_shared<Eu::GameObject>();
	go->SetPosition(glm::vec3{ position.x  , 0, position.y });
	go->GetTransform().Scale(glm::vec3{ m_Scale, m_Scale, m_Scale });
	go->AddComponent<ChunkComponent>(chunkComp);
	GetAttachedGameObject()->AddChild(go);
}

void ChunkManager::Update()
{
}

void ChunkManager::FixedUpdate()
{
}

void ChunkManager::Render() const
{
}

uint8_t ChunkManager::GetBlockIDNeighbour(glm::ivec2 position, int x, int y, int z)
{
	std::pair<int, int> id = GetChunkID(position);
	if (x < 0) {
		id.first += 1;
		if (m_ChunkIDMap.count(id) > 0) {
			return  m_ChunkIDMap[id]->GetBlock(m_ChunkxSize, y, z);
		}
	}
	if (x >= (m_ChunkxSize)) {
		id.first -= 1;
		if (m_ChunkIDMap.count(id) > 0) {
			return  m_ChunkIDMap[id]->GetBlock(0, y, z);
		}
	}
	if (z >= m_ChunkzSize) {
		id.second += 1;
		if (m_ChunkIDMap.count(id) > 0) {
			return  m_ChunkIDMap[id]->GetBlock(x, y, m_ChunkzSize);
		}
	}
	if (z < 0) {
		id.second -= 1;
		if (m_ChunkIDMap.count(id) > 0) {
			return  m_ChunkIDMap[id]->GetBlock(x, y, 0);
		}
	}
	return 0;

}

void ChunkManager::UpdateNeightbours(glm::ivec2 posiotn)
{
	std::pair<int, int> id = GetChunkID(posiotn);
	if (m_ChunkIDMap.count({ id.first - 1 , id.second }) > 0)
		m_ChunkIDMap[{id.first - 1, id.second}]->SetDirty();
	if (m_ChunkIDMap.count({ id.first + 1 , id.second }) > 0)
		m_ChunkIDMap[{id.first + 1, id.second }]->SetDirty();
	if (m_ChunkIDMap.count({ id.first , id.second - 1 }) > 0)
		m_ChunkIDMap[{id.first , id.second - 1}]->SetDirty();
	if (m_ChunkIDMap.count({ id.first  , id.second  + 1}) > 0)
		m_ChunkIDMap[{id.first , id.second + 1}]->SetDirty();
}

std::pair<int,int> ChunkManager::GetChunkID(glm::ivec2 position)
{
	std::pair<int, int> id;
	id.first = glm::floor((position.x) / m_ChunkxSize);
	id.second = glm::floor((position.y ) / m_ChunkzSize);
	return id;

}

