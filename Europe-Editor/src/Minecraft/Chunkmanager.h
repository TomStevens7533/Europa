#pragma once
#include <vector>
#include "Chunk.h"
#include "Europa/Core/TimeStep.h"
#include "Europa/camera/CameraController.h"
#include <map>
#include <utility>
#include "Block.h"


class ChunkManager
{
public:
	ChunkManager(Eu::PerspectiveCameraController& CameraController);
	~ChunkManager();
	void Update(Eu::TimeStep ts, Eu::PerspectiveCameraController& CameraController);
	bool IsBlockSolidInChunk(std::pair<int, int> chunkInex, int xIndex, int yIndex, int zIndex) const ;
	void Render();
	bool DeleteBlockAtPos(glm::vec3 posToLook);
	bool AddBlockAtPos(glm::vec3 posToLook, BlockTypes type);

private:
	void UpdateLoadedChunks(Eu::PerspectiveCameraController& CameraController);
	void ReloadNeighbouringChunks(std::pair<int, int> chunkIndex);
private:
	std::map<std::pair<int, int>, Chunk*> m_ChunkVec;
	BlockInfromation BlockInfo;


	int m_Xdiff = 16;
	int m_Zdiff = 16;
	int m_ChunkLoadDistance = 128;
	bool isUpdating;

	int m_XCameraQuadrant;
	int m_YCameraQuadrant;


};
