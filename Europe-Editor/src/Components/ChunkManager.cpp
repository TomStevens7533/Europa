#include "ChunkManager.h"
#include "Europa/GameObject.h"
#include "ChunkComponent.h"
#include <mutex>

ChunkManager::ChunkManager(const int xSize, int ySize, int zSize, const int chunkWidthAmount, const int chunkDepthAmount, glm::vec3 scale)
	: m_ChunkxSize{ static_cast<double>(xSize) }, m_ChunkySize{ static_cast<double>(ySize) }, m_ChunkzSize{ static_cast<double>(zSize) }, m_ChunkWidthAmount{ chunkWidthAmount }, m_ChunkDepthAmount{chunkDepthAmount}
	, m_IsUpdatingAroundCamera{false}, m_Scale{ scale }
{
}

ChunkManager::ChunkManager(const int xSize, int ySize, int zSize, Eu::PerspectiveCameraControllerComponent* cam, glm::vec3 scale)
	: m_ChunkxSize{ static_cast<double>(xSize) }, m_ChunkySize{ static_cast<double>(ySize) }, m_ChunkzSize{ static_cast<double>(zSize) }, m_Scale{ scale }, m_Camera{ cam }, m_IsUpdatingAroundCamera{ true }
{
	
}

ChunkManager::~ChunkManager()
{
	m_KillThread = true;

	for (size_t i = 0; i < m_ThreadVector.size(); i++)
	{
		m_ThreadVector[i].join();
	}
}

void ChunkManager::Start()
{
	if (m_IsUpdatingAroundCamera == false) {
		//Create chunks based on width and depth around origin gameobject
		const glm::dvec2 originPos = glm::dvec2{ (GetAttachedGameObject()->GetTransform().GetPosition().x), glm::round(GetAttachedGameObject()->GetTransform().GetPosition().z) };
		const double ChunkTotalWidth = m_ChunkWidthAmount * (m_ChunkxSize * m_Scale.x);
		const double ChunkTotalDepth = m_ChunkDepthAmount * (m_ChunkzSize * m_Scale.z);
		double chunkSizeZ = (m_ChunkzSize * m_Scale.z);
		double chunkSizeY = (m_ChunkySize * m_Scale.y);
		double chunkSizex = (m_ChunkxSize * m_Scale.x);


		for (double x = (originPos.x - ChunkTotalWidth); x <= (originPos.x + ChunkTotalWidth); x += chunkSizex)
		{
			for (double z = (originPos.y - ChunkTotalDepth); z <= (originPos.y + ChunkTotalDepth); z += chunkSizeZ)
			{
				//Create chunk
				CreateChunk(glm::dvec2{ x,z });
			} 
		}
		
	}

	std::vector<std::vector<ChunkComponent*>> chunkThreadVector;
	int index{0};
	auto it = m_ChunkIDMap.begin();
	//Create threads
	while (it != m_ChunkIDMap.end()) {
		std::vector<ChunkComponent*> ChunkToWorkOn;
		for (int i = 0; i < 50 && it != m_ChunkIDMap.end(); ++i, ++it) {
			ChunkToWorkOn.push_back(it->second.get());
		}
		chunkThreadVector.push_back(ChunkToWorkOn);
	}
	
	for (size_t i = 0; i < chunkThreadVector.size(); i++)
	{
		m_FutureVector.push_back(InitizalizeChunks(chunkThreadVector[i]));

	}

	

}
void ChunkManager::CreateChunk(glm::dvec2 position)
{
	ChunkID id = GetChunkID(position);
	//EU_CORE_INFO("Creating Chunk at POS: {0},{1}; Idx: {2}, {3}", position.x, position.y, id.x, id.y);
	auto chunkComp = std::make_shared<ChunkComponent>(id, m_ChunkxSize, m_ChunkySize, m_ChunkzSize, this);
	m_ChunkIDMap.insert(std::make_pair(id, chunkComp));
	auto go = std::make_shared<Eu::GameObject>();
	go->SetPosition(glm::vec3{  position.x  , 0, position.y });
	go->GetTransform().Scale(glm::vec3{ m_Scale.x, m_Scale.y, m_Scale.z });
	go->AddComponent<ChunkComponent>(chunkComp);
	GetAttachedGameObject()->AddChild(go);
}

void ChunkManager::Update()
{
	
	if (m_IsValid)
	{	
		bool valid = true;
		for (size_t i = 0; i < m_FutureVector.size(); i++)
		{
			auto status = m_FutureVector[i].wait_for(std::chrono::milliseconds(0));
			if (status == std::future_status::ready) {
				valid &= true;
			}
			else
				valid &= false;
		}

		if (valid)
		{

			//All Chunks have been initialized
			for (std::promise<bool>& f : m_PromiseVector)
			{
				f.set_value(true);
			}
			m_IsValid = false;
		}

	}
}

void ChunkManager::FixedUpdate()
{

}

void ChunkManager::Render() const
{
}

//Can only be exectutes if chunkID map is up to date
uint8_t ChunkManager::GetBlockIDNeighbour(ChunkID lookupID, int x, int y, int z)  const
{
	try
	{
		if (x < 0) {
			lookupID.x += 1;
			if (m_ChunkIDMap.count(lookupID) > 0) {
				return  m_ChunkIDMap.at(lookupID)->GetBlock(m_ChunkxSize, y, z);
			}
		}
		if (x >= (m_ChunkxSize)) {
			lookupID.x -= 1;
			if (m_ChunkIDMap.count(lookupID) > 0) {
				return  m_ChunkIDMap.at(lookupID)->GetBlock(0, y, z);
			}
		}
		if (z >= m_ChunkzSize) {
			lookupID.y += 1;
			if (m_ChunkIDMap.count(lookupID) > 0) {
				return  m_ChunkIDMap.at(lookupID)->GetBlock(x, y, 0);
			}
		}
		if (z < 0) {
			lookupID.y -= 1;
			if (m_ChunkIDMap.count(lookupID) > 0) {
				return  m_ChunkIDMap.at(lookupID)->GetBlock(x, y, m_ChunkzSize);
			}
		}
	}
	catch (const std::exception&)
	{
		EU_CORE_INFO("Chunk idx not found: {0}, {1}", lookupID.x, lookupID.y);
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
	id.x = int(1000.f * position.x) / int(1000.f * float(m_ChunkxSize * m_Scale.x));
	id.y = int(1000.f * position.y) / int(1000.f * float(m_ChunkzSize * m_Scale.z));

	return id;

}

void ChunkManager::UpdateChunks(std::vector<ChunkComponent*> localThreads)
{
	while (true)
	{
		if (m_KillThread == true)
			return;

		for (auto& it : localThreads) {
			// Mesh chunks
			it->CreateMesh();
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

//because it goes out of scope the future is set
std::future<bool> ChunkManager::InitizalizeChunks(std::vector<ChunkComponent*> localThreads)
{
	// Create a promise to store the result
	std::promise<bool> promise;

	//Create promise to main thread
	std::promise<bool>& notificationPromise = m_PromiseVector.emplace_back();
	std::future<bool> notificationFuture = notificationPromise.get_future();

	// Get the future associated with the promise
	std::future<bool> future = promise.get_future();

	// Start a new thread to compute the square and fulfill the promise
	 std::thread([localThreads, p = std::move(promise), f = std::move(notificationFuture)]() mutable {
		bool isDone = true;
		// Compute the square

		for (size_t i = 0; i < localThreads.size(); i++)
		{
				isDone &= localThreads[i]->InitializeChunk();
				std::this_thread::sleep_for(std::chrono::nanoseconds(5));

		}

		// Fulfill the promise with the result
		p.set_value(isDone);

		//bool created = false;
		while (true)
		{
			auto status = f.wait_for(std::chrono::milliseconds(0));
			if (status == std::future_status::ready) {
				// Worker future is ready, get the value
				while (true)
				{
					for (size_t i = 0; i < localThreads.size(); i++)
					{
						localThreads[i]->CreateMesh();
						std::this_thread::sleep_for(std::chrono::nanoseconds(5));

					}
					EU_CORE_INFO("Done");
					return;
		
				}
			}
			std::this_thread::sleep_for(std::chrono::seconds(5));
		
		}

		}).detach(); // Detach the thread, as we are not joining it

	// Return the future associated with the promise
	return future;
}

