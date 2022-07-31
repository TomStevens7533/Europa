#pragma once
#include <array>
#include "Europa/mesh/Mesh.h"
#include <Europa/Renderer/VertexArray.h>
#include "BlockStruct.h"

class BlockInfromation;
namespace Eu { 
	class MeshComponent;
}


class ChunkMesh
{
public:



public:
	ChunkMesh(const BlockInfromation* blockInfo);
	~ChunkMesh() {};
	bool AddFace(glm::vec3 ChunPos, glm::vec3 BlockPos, Faces dir, BlockTypes blockType);
	void BufferMesh();
	void Render() const;
private:
private: //Chunk
	Eu::MeshComponent* m_pChunkMesh;
	std::shared_ptr<Eu::VertexArray> m_ChunkVertexArray;

	const std::shared_ptr<Eu::BaseProgram>* m_pRenderingProgram = nullptr;
	int m_VertextIndexIndex = 0;

	const BlockInfromation* BlockInfo = nullptr;
};

