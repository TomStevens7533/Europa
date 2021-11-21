#pragma once
#include "Europa/GameObject.h"
#include <vector>
#include "Chunk.h"
#include "../BlockDatabase.h"



class BlockInfromation
{
public:
	BlockInfromation();
	~BlockInfromation();
	glm::vec2* GetUVFaceInformation(BlockTypes blockType, Faces faceDir);
	bool IsBlockCube(BlockTypes blockType);

private:
	std::map<BlockTypes, BaseEntity*> m_UVMAP;
};

