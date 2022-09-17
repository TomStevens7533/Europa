#pragma once
#include "Europa/Components/BaseComponent.h"
#include <map>
#include "glm/glm.hpp"

class ChunkComponent;
namespace Eu {
	class PerspectiveCameraControllerComponent;
}
class ChunkManager : public Eu::BaseComponent, public std::enable_shared_from_this<ChunkManager>
{
public:
	ChunkManager(const int xSize, int ySize, int zSize, Eu::PerspectiveCameraControllerComponent* cam, float scale = 1);
	ChunkManager(const int xSize, int ySize, int zSize, const int chunkWidthAmount, const int chunkDepthAmount, float scale = 1);
	~ChunkManager();


	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;
	uint8_t GetBlockIDNeighbour(glm::ivec2 position, int x, int y, int z);
	void UpdateNeightbours(glm::ivec2 posiotn);
private:
	void CreateChunk(glm::ivec2 position);
	std::pair<int, int> GetChunkID(glm::ivec2 position);
private:
	bool m_IsUpdatingAroundCamera{ false };

	const int m_ChunkxSize{};
	const int m_ChunkySize{};
	const int m_ChunkzSize{};
	const int m_ChunkWidthAmount{};
	const int m_ChunkDepthAmount{};
	const float m_Scale{};
	Eu::PerspectiveCameraControllerComponent* m_Camera{};
	std::map < std::pair<int, int>, std::shared_ptr<ChunkComponent>> m_ChunkIDMap;



};


