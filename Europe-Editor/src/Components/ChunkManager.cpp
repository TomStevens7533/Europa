#include "ChunkManager.h"
#include "Europa/GameObject.h"
#include "ChunkComponent.h"

ChunkManager::ChunkManager(const int xSize, int ySize, int zSize, const int chunkWidthAmount, const int chunkDepthAmount, float scale)
	: m_ChunkxSize{ static_cast<double>(xSize) }, m_ChunkySize{ static_cast<double>(ySize) }, m_ChunkzSize{ static_cast<double>(zSize) }, m_ChunkWidthAmount{ chunkWidthAmount }, m_ChunkDepthAmount{chunkDepthAmount}
	, m_IsUpdatingAroundCamera{false}, m_Scale{ scale }
{

}

ChunkManager::ChunkManager(const int xSize, int ySize, int zSize, Eu::PerspectiveCameraControllerComponent* cam, float scale /*= 1*/)
	: m_ChunkxSize{ static_cast<double>(xSize) }, m_ChunkySize{ static_cast<double>(ySize) }, m_ChunkzSize{ static_cast<double>(zSize) }, m_Scale{scale}, m_Camera{cam}, m_IsUpdatingAroundCamera{true}
{
	
}

ChunkManager::~ChunkManager()
{

}

void ChunkManager::Start()
{
	if (m_IsUpdatingAroundCamera == false) {
		//Create chunks based on width and depth around origin gameobject
		const glm::dvec2 originPos = glm::dvec2{ (GetAttachedGameObject()->GetTransform().GetPosition().x), glm::round(GetAttachedGameObject()->GetTransform().GetPosition().z) };
		const double ChunkTotalWidth = m_ChunkWidthAmount * (m_ChunkxSize * m_Scale);
		const double ChunkTotalDepth = m_ChunkDepthAmount * (m_ChunkzSize * m_Scale);
		double chunkSizeZ = (m_ChunkzSize * m_Scale);
		double chunkSizeY = (m_ChunkySize * m_Scale);
		double chunkSizex = (m_ChunkxSize * m_Scale);


		for (double x = (originPos.x - ChunkTotalWidth); x < (originPos.x + ChunkTotalWidth); x += chunkSizex)
		{
			for (double z = (originPos.y - ChunkTotalDepth); z < (originPos.y + ChunkTotalDepth); z += chunkSizeZ)
			{
				//Create chunk
				CreateChunk(glm::dvec2{ x,z });
			} 
		}
		
	}
}
void ChunkManager::CreateChunk(glm::dvec2 position)
{
	ChunkID id = GetChunkID(position);
	EU_CORE_INFO("Creating Chunk at POS: {0},{1}; Idx: {2}, {3}", position.x, position.y, id.x, id.y);
	auto chunkComp = std::make_shared<ChunkComponent>(m_ChunkxSize, m_ChunkySize, m_ChunkzSize, shared_from_this(), m_Scale);
	m_ChunkIDMap.insert(std::make_pair(id, chunkComp));
	auto go = std::make_shared<Eu::GameObject>();
	go->SetPosition(glm::vec3{  position.x  , 0, position.y });
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

uint8_t ChunkManager::GetBlockIDNeighbour(glm::dvec2 position, int x, int y, int z)
{
	
	ChunkID id = GetChunkID(position);
	if (x < 0) {
		id.x += 1;
		if (m_ChunkIDMap.count(id) > 0) {
			return  m_ChunkIDMap[id]->GetBlock(m_ChunkxSize, y, z);
		}
	}
	if (x >= (m_ChunkxSize)) {
		id.x -= 1;
		if (m_ChunkIDMap.count(id) > 0) {
			return  m_ChunkIDMap[id]->GetBlock(0, y, z);
		}
	}
	if (z >= m_ChunkzSize) {
		id.y += 1;
		if (m_ChunkIDMap.count(id) > 0) {
			return  m_ChunkIDMap[id]->GetBlock(x, y, 0);
		}
	}
	if (z < 0) {
		id.y -= 1;
		if (m_ChunkIDMap.count(id) > 0) {
			return  m_ChunkIDMap[id]->GetBlock(x, y, m_ChunkzSize);
		}
	}
	return 0;
	
}

void ChunkManager::UpdateNeightbours(glm::ivec2 posiotn)
{
	//std::pair<int, int> id = GetChunkID(posiotn);
	//if (m_ChunkIDMap.count({ id.first - 1 , id.second }) > 0)
	//	m_ChunkIDMap[{id.first - 1, id.second}]->SetDirty();
	//if (m_ChunkIDMap.count({ id.first + 1 , id.second }) > 0)
	//	m_ChunkIDMap[{id.first + 1, id.second }]->SetDirty();
	//if (m_ChunkIDMap.count({ id.first , id.second - 1 }) > 0)
	//	m_ChunkIDMap[{id.first , id.second - 1}]->SetDirty();
	//if (m_ChunkIDMap.count({ id.first  , id.second  + 1}) > 0)
	//	m_ChunkIDMap[{id.first , id.second + 1}]->SetDirty();
}  //

ChunkID ChunkManager::GetChunkID(glm::dvec2 position)
{
	ChunkID id;
	id.x = (position.x) / (m_ChunkxSize * m_Scale);
	id.y = (position.y) / (m_ChunkzSize * m_Scale);
	return id;

}

