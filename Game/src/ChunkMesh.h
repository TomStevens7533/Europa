#pragma once
#include <array>
#include "Europa/mesh/Mesh.h"
#include <Europa/Renderer/VertexArray.h>
#include "Europa/Renderer/Program.h"
#include "Block.h"


class ChunkMesh
{
public:



public:
	ChunkMesh();
	~ChunkMesh() {};
	bool AddFace(glm::vec3 ChunPos, glm::vec3 BlockPos, Faces dir, BlockTypes blockType);
	void BufferMesh();
	void Render() const;
private: //Chunk
	std::shared_ptr<Eu::Mesh> m_pChunkMesh;
	std::shared_ptr<Eu::VertexArray> m_ChunkVertexArray;

	BlockInfromation BlockInfo;
	const std::shared_ptr<Eu::BaseProgram>* m_pRenderingProgram = nullptr;
	int m_VertextIndexIndex = 0;

};

