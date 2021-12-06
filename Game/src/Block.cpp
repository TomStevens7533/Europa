#include "Block.h"
#include "Europa/ResourceManager.h"
        


BlockInfromation::BlockInfromation()
{
	BaseEntity* block = new Dirt;
	m_UVMAP.insert({ BlockTypes::DIRT, block });
	block = new Grass;
	m_UVMAP.insert({ BlockTypes::GRASS, block });
	block = new Stone;
	m_UVMAP.insert({ BlockTypes::STONE, block });
	block = new Water;
	m_UVMAP.insert({ BlockTypes::WATER, block });
	block = new OakLog;
	m_UVMAP.insert({ BlockTypes::OAKLOG, block });
	block = new Rose;
	m_UVMAP.insert({ BlockTypes::ROSE, block });
	block = new Azure;
	m_UVMAP.insert({ BlockTypes::AZURE, block });
	block = new Tulip;
	m_UVMAP.insert({ BlockTypes::TULIP, block });
	block = new Leaves;
	m_UVMAP.insert({ BlockTypes::LEAVES, block });
	block = new Leaves;
	m_UVMAP.insert({ BlockTypes::LEAVES, block });




}

BlockInfromation::~BlockInfromation()
{
	for (auto& blockInfo : m_UVMAP)
	{
		delete (blockInfo.second);
		blockInfo.second = nullptr;
	}
}

glm::vec2* BlockInfromation::GetUVFaceInformation(BlockTypes blockType, Faces faceDir) const
{
	return (m_UVMAP.at(blockType)->GetUV(faceDir));

}

bool BlockInfromation::IsBlockCube(BlockTypes blockType) const
{
	return m_UVMAP.at(blockType)->isCube();
}

bool BlockInfromation::IsBlockSolid(BlockTypes blockType) const
{
	if (blockType != BlockTypes::AIR) {
		return m_UVMAP.at(blockType)->isSolid();
	}
	else
		return false;

}

