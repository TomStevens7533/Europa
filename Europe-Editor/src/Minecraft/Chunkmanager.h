#pragma once
#include <vector>
#include "Chunk.h"
#include "Europa/Core/TimeStep.h"
#include "Europa/camera/CameraController.h"
#include <map>
#include <utility>
#include <memory>
#include "Europa/Components/BaseComponent.h"


class ChunkComponent;
class ChunkManager final : public Eu::BaseComponent
{
public:
	ChunkManager(Eu::PerspectiveCameraControllerComponent& CameraController);
	~ChunkManager();



	bool IsBlockSolidInChunk(std::pair<int, int> chunkInex, int xIndex, int yIndex, int zIndex) const;
	void Render();

	void Render() const override {};
	void Start() override;
	void Update() override;

	void FixedUpdate() override {};
	bool DeleteBlockAtPos(glm::vec3 posToLook);
	bool AddBlockAtPos(glm::vec3 posToLook, uint8_t type);

private:
	void UpdateLoadedChunks(Eu::PerspectiveCameraControllerComponent& CameraController);
	void ReloadNeighbouringChunks(std::pair<int, int> chunkIndex);



private:
	std::map<std::pair<int, int>, std::shared_ptr<ChunkComponent>> m_ChunkVec;
	Eu::PerspectiveCameraControllerComponent* m_pCamera;

	int m_Xdiff = 16;
	int m_Zdiff = 16;
	int m_ChunkLoadDistance = 10;
	bool isUpdating;

	int m_XCameraQuadrant;
	int m_YCameraQuadrant;


};
