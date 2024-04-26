#pragma once
#include "Europa/Components/BaseComponent.h"
#include <unordered_map>
#include "glm/glm.hpp"
#include "../Minecraft/BlockStruct.h"
#include <thread>
#include <mutex>
#include <future>

class ChunkComponent;
namespace Eu {
	class PerspectiveCameraControllerComponent;
}

// Define the hash function for the struct
struct MyStructHash {
	std::size_t operator()(const ChunkID& s) const {
		std::size_t h1 = std::hash<int>()(s.x);
		std::size_t h2 = std::hash<int>()(s.y);
		// Combine the hashes of x and y using a simple bitwise xor operation
		return h1 ^ (h2 << 1);
	}
};

// Define the equality operator for the struct
struct MyStructEqual {
	bool operator()(const ChunkID& s1, const ChunkID& s2) const {
		return s1.x == s2.x && s1.y == s2.y;
	}
};

class ChunkManager : public Eu::BaseComponent, public std::enable_shared_from_this<ChunkManager>
{
public:
	ChunkManager(const int xSize, int ySize, int zSize, Eu::PerspectiveCameraControllerComponent* cam, glm::vec3 scale);
	ChunkManager(const int xSize, int ySize, int zSize, const int chunkWidthAmount, const int chunkDepthAmount, glm::vec3 scale);
	~ChunkManager();


	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;
	uint8_t GetBlockIDNeighbour(ChunkID position, int x, int y, int z) const;
	void UpdateNeightbours(glm::ivec2 posiotn);
private:
	void CreateChunk(glm::dvec2 position);
	ChunkID GetChunkID(glm::dvec2 position);
	
	//Thread function
	void UpdateChunks(std::vector<ChunkComponent*> localThreads);
	std::future<bool> InitizalizeChunks(std::vector<ChunkComponent*> localThreads);
private:
	bool m_IsUpdatingAroundCamera{ false };
	std::atomic<bool> m_KillThread{ false };
	std::mutex m_KillMutex;
	std::condition_variable m_Cond;
	double m_ChunkxSize{};
	double m_ChunkySize{};
	double m_ChunkzSize{};
	const int m_ChunkWidthAmount{};
	const int m_ChunkDepthAmount{};
	const glm::vec3 m_Scale{};
	Eu::PerspectiveCameraControllerComponent* m_Camera{};
	std::unordered_map < ChunkID, std::shared_ptr<ChunkComponent>, MyStructHash, MyStructEqual> m_ChunkIDMap;
	std::thread m_MeshingThread;

	//Threads
	bool m_IsValid = true;
	std::vector<std::thread> m_ThreadVector;
	std::vector<std::future<bool>> m_FutureVector;
	std::vector<std::promise<bool>> m_PromiseVector;




};


