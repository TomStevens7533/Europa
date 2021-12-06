#pragma once
#include "Europa/GameObject.h"
#include <vector>
#include "Chunk.h"
#include "BlockDatabase.h"
#include "BlockStruct.h"
#include "BlockDatabase.h"



class BlockInfromation
{
public:
	BlockInfromation();
	~BlockInfromation();
	glm::vec2* GetUVFaceInformation(BlockTypes blockType, Faces faceDir) const;
	bool IsBlockCube(BlockTypes blockType) const;
	bool IsBlockSolid(BlockTypes blockType) const;


private:
	std::map<BlockTypes, BaseEntity*> m_UVMAP;
};

