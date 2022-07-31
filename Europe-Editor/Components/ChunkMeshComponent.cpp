#include "ChunkMeshComponent.h"
#include <array>
#include "Europa/Components/MeshComponent.h"
#include "Europa/GameObject.h"
#include "Europa/Components/MeshRenderComponent.h"
#include "../src/BlockJsonParser.h"
#include "../MaterialManager.h"
#include "ChunkMaterial.h"

const std::array<float, 12> xFace1{
	0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0,
};

const std::array<float, 12> xFace2{
	0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
};
const std::array<float, 12> frontFace{
	0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
};

const std::array<float, 12> backFace{
	1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0,
};

const std::array<float, 12> leftFace{
	0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
};

const std::array<float, 12> rightFace{
	1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1,
};

const std::array<float, 12> topFace{
	0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0,
};
const std::array<float, 12> bottomFace{ 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 };

ChunkMeshComponent::ChunkMeshComponent()
{

}

ChunkMeshComponent::~ChunkMeshComponent()
{
}

void ChunkMeshComponent::Start()
{
	m_pChunkMesh = std::make_shared<Eu::MeshComponent>();

	GetAttachedGameObject()->AddComponent<Eu::MeshComponent>(m_pChunkMesh);
	m_pChunkMeshRenderer = std::make_shared<Eu::MeshRenderComponent>();

	GetAttachedGameObject()->AddComponent<Eu::MeshRenderComponent>(m_pChunkMeshRenderer);
	m_CurrMat = Eu::MaterialManager::GetInstance()->CreateMaterial<ChunkMaterial>();
	m_pChunkMeshRenderer->SetMaterial(m_CurrMat);

}

void ChunkMeshComponent::Update()
{

}

void ChunkMeshComponent::FixedUpdate()
{

}

void ChunkMeshComponent::Render() const
{

}

bool ChunkMeshComponent::AddFace(glm::vec3 ChunPos, glm::vec3 BlockPos, Faces dir, uint8_t blockType)
{
	const std::array<float, 12>* blockFace;

	std::vector<Eu::Vertex_Input> m_vertices;
	std::vector<int> m_Indices;


	bool isCube = BlockJsonParser::GetInstance()->IsCube(blockType);
	float LightLevel = 1.f;

	auto uvInformation = BlockJsonParser::GetInstance()->GetUVOfType(blockType, dir);

	if (isCube) { //cube form
		switch (dir)
		{
		case Faces::TOP:
			LightLevel = 1.0f;
			blockFace = &topFace;
			break;
		case Faces::BOT:
			LightLevel = 0.4f;
			blockFace = &bottomFace;
			break;
		case Faces::LEFT:
			LightLevel = 0.8f;
			blockFace = &leftFace;
			break;
		case Faces::RIGHT:
			LightLevel = 0.8f;
			blockFace = &rightFace;
			break;
		case Faces::FRONT:
			LightLevel = 0.6f;
			blockFace = &frontFace;
			break;
		case Faces::BACK:
			LightLevel = 0.6f;
			blockFace = &backFace;
			break;
		default:
			break;
		}


		glm::vec3 Vertex1Pos = glm::vec3{ (*blockFace)[0] + ChunPos.x + BlockPos.x, (*blockFace)[1] + (ChunPos.y + BlockPos.y), (*blockFace)[2] + ChunPos.z + BlockPos.z };
		m_vertices.push_back(Eu::Vertex_Input{ Vertex1Pos,
			glm::vec3{ 1,1,1 }, (*uvInformation)[0], glm::vec3{LightLevel,LightLevel,LightLevel}});
		//std::cout << Vertex1Pos.x << "  " << Vertex1Pos.y << " " << Vertex1Pos.z << std::endl;


		glm::vec3 Vertex2Pos = glm::vec3{ (*blockFace)[3] + ChunPos.x + BlockPos.x, (*blockFace)[4] + (ChunPos.y + BlockPos.y), (*blockFace)[5] + ChunPos.z + BlockPos.z };
		m_vertices.push_back(Eu::Vertex_Input{ Vertex2Pos,
			glm::vec3{ 1,1,1 },  (*uvInformation)[1], glm::vec3{ LightLevel,LightLevel,LightLevel} });


		glm::vec3 Vertex3Pos = glm::vec3{ (*blockFace)[6] + ChunPos.x + BlockPos.x, (*blockFace)[7] + (ChunPos.y + BlockPos.y), (*blockFace)[8] + ChunPos.z + BlockPos.z };
		m_vertices.push_back(Eu::Vertex_Input{ Vertex3Pos,
			glm::vec3{ 1,1,1 }, (*uvInformation)[2], glm::vec3{ LightLevel,LightLevel,LightLevel } });

		glm::vec3 Vertex4Pos = glm::vec3{ (*blockFace)[9] + ChunPos.x + BlockPos.x, (*blockFace)[10] + (ChunPos.y + BlockPos.y), (*blockFace)[11] + ChunPos.z + BlockPos.z };
		m_vertices.push_back(Eu::Vertex_Input{ Vertex4Pos,
			glm::vec3{ 1,1,1 }, (*uvInformation)[3], glm::vec3{ LightLevel ,LightLevel,LightLevel } });

		m_Indices = { m_VertextIndexIndex, m_VertextIndexIndex + 1, m_VertextIndexIndex + 2, m_VertextIndexIndex + 2, m_VertextIndexIndex + 3, m_VertextIndexIndex };
		m_VertextIndexIndex += 4;



		m_pChunkMesh->AddFaceToMesh(m_vertices, m_Indices);

		return false;
	}
	else {
		blockFace = &xFace2;
		for (size_t i = 0; i < 2; i++)
		{
			glm::vec3 Vertex1Pos = glm::vec3{ (*blockFace)[0] + ChunPos.x + BlockPos.x, (*blockFace)[1] + (ChunPos.y + BlockPos.y), (*blockFace)[2] + ChunPos.z + BlockPos.z };
			m_vertices.push_back(Eu::Vertex_Input{ Vertex1Pos,
				glm::vec3{ 1,1,1 }, (*uvInformation)[0], glm::vec3{ LightLevel,LightLevel,LightLevel } });
			//std::cout << Vertex1Pos.x << "  " << Vertex1Pos.y << " " << Vertex1Pos.z << std::endl;


			glm::vec3 Vertex2Pos = glm::vec3{ (*blockFace)[3] + ChunPos.x + BlockPos.x, (*blockFace)[4] + (ChunPos.y + BlockPos.y), (*blockFace)[5] + ChunPos.z + BlockPos.z };
			m_vertices.push_back(Eu::Vertex_Input{ Vertex2Pos,
				glm::vec3{ 1,1,1 }, (*uvInformation)[1], glm::vec3{ LightLevel,LightLevel,LightLevel} });


			glm::vec3 Vertex3Pos = glm::vec3{ (*blockFace)[6] + ChunPos.x + BlockPos.x, (*blockFace)[7] + (ChunPos.y + BlockPos.y), (*blockFace)[8] + ChunPos.z + BlockPos.z };
			m_vertices.push_back(Eu::Vertex_Input{ Vertex3Pos,
				glm::vec3{ 1,1,1 },(*uvInformation)[2], glm::vec3{ LightLevel,LightLevel,LightLevel } });

			glm::vec3 Vertex4Pos = glm::vec3{ (*blockFace)[9] + ChunPos.x + BlockPos.x, (*blockFace)[10] + (ChunPos.y + BlockPos.y), (*blockFace)[11] + ChunPos.z + BlockPos.z };
			m_vertices.push_back(Eu::Vertex_Input{ Vertex4Pos,
				glm::vec3{ 1,1,1 },(*uvInformation)[3], glm::vec3{ LightLevel ,LightLevel,LightLevel } });

			blockFace = &xFace1;
		}
		m_Indices = { m_VertextIndexIndex, m_VertextIndexIndex + 1, m_VertextIndexIndex + 2, m_VertextIndexIndex + 2, m_VertextIndexIndex + 3, m_VertextIndexIndex,
			m_VertextIndexIndex + 4, m_VertextIndexIndex + 5, m_VertextIndexIndex + 6, m_VertextIndexIndex + 6, m_VertextIndexIndex + 7, m_VertextIndexIndex + 4 };

		m_VertextIndexIndex += 8;
		m_pChunkMesh->AddFaceToMesh(m_vertices, m_Indices);
		return true;
	}
}

void ChunkMeshComponent::BufferMesh()
{
	m_pChunkMesh->BufferMesh();
}

