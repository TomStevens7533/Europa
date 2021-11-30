#include "ChunkMesh.h"
#include "Europa/structs.h"
#include "Europa/ResourceManager.h"
#include "Europa/Renderer/Renderer.h"

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


ChunkMesh::ChunkMesh()
{
	if (m_pRenderingProgram == nullptr) //default to 2D texture program
		m_pRenderingProgram = &Eu::ResourceManager::GetInstance()->GetProgram(Eu::ShaderType::TEXTURE2D_WORLDSPACE_SHADER);
	m_pChunkMesh = std::make_shared<Eu::Mesh>();
}

bool ChunkMesh::AddFace(glm::vec3 ChunPos, glm::vec3 BlockPos, Faces dir, BlockTypes blockType)
{
	const std::array<float, 12>* blockFace;

	std::vector<Eu::Vertex_Input> m_vertices;
	std::vector<int> m_Indices;

	glm::vec2* uvInformation = BlockInfo.GetUVFaceInformation(blockType, dir);
	bool isCube = BlockInfo.IsBlockCube(blockType);
	float LightLevel = 1.f;


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
			glm::vec3{ 1,1,1 }, *uvInformation, glm::vec3{ LightLevel,LightLevel,LightLevel } });
		//std::cout << Vertex1Pos.x << "  " << Vertex1Pos.y << " " << Vertex1Pos.z << std::endl;


		glm::vec3 Vertex2Pos = glm::vec3{ (*blockFace)[3] + ChunPos.x + BlockPos.x, (*blockFace)[4] + (ChunPos.y + BlockPos.y), (*blockFace)[5] + ChunPos.z + BlockPos.z };
		m_vertices.push_back(Eu::Vertex_Input{ Vertex2Pos,
			glm::vec3{ 1,1,1 }, *(uvInformation + 1), glm::vec3{ LightLevel,LightLevel,LightLevel} });


		glm::vec3 Vertex3Pos = glm::vec3{ (*blockFace)[6] + ChunPos.x + BlockPos.x, (*blockFace)[7] + (ChunPos.y + BlockPos.y), (*blockFace)[8] + ChunPos.z + BlockPos.z };
		m_vertices.push_back(Eu::Vertex_Input{ Vertex3Pos,
			glm::vec3{ 1,1,1 },*(uvInformation + 2), glm::vec3{ LightLevel,LightLevel,LightLevel } });

		glm::vec3 Vertex4Pos = glm::vec3{ (*blockFace)[9] + ChunPos.x + BlockPos.x, (*blockFace)[10] + (ChunPos.y + BlockPos.y), (*blockFace)[11] + ChunPos.z + BlockPos.z };
		m_vertices.push_back(Eu::Vertex_Input{ Vertex4Pos,
			glm::vec3{ 1,1,1 },*(uvInformation + 3), glm::vec3{ LightLevel ,LightLevel,LightLevel } });

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
				glm::vec3{ 1,1,1 }, *uvInformation, glm::vec3{ LightLevel,LightLevel,LightLevel } });
			//std::cout << Vertex1Pos.x << "  " << Vertex1Pos.y << " " << Vertex1Pos.z << std::endl;


			glm::vec3 Vertex2Pos = glm::vec3{ (*blockFace)[3] + ChunPos.x + BlockPos.x, (*blockFace)[4] + (ChunPos.y + BlockPos.y), (*blockFace)[5] + ChunPos.z + BlockPos.z };
			m_vertices.push_back(Eu::Vertex_Input{ Vertex2Pos,
				glm::vec3{ 1,1,1 }, *(uvInformation + 1), glm::vec3{ LightLevel,LightLevel,LightLevel} });


			glm::vec3 Vertex3Pos = glm::vec3{ (*blockFace)[6] + ChunPos.x + BlockPos.x, (*blockFace)[7] + (ChunPos.y + BlockPos.y), (*blockFace)[8] + ChunPos.z + BlockPos.z };
			m_vertices.push_back(Eu::Vertex_Input{ Vertex3Pos,
				glm::vec3{ 1,1,1 },*(uvInformation + 2), glm::vec3{ LightLevel,LightLevel,LightLevel } });

			glm::vec3 Vertex4Pos = glm::vec3{ (*blockFace)[9] + ChunPos.x + BlockPos.x, (*blockFace)[10] + (ChunPos.y + BlockPos.y), (*blockFace)[11] + ChunPos.z + BlockPos.z };
			m_vertices.push_back(Eu::Vertex_Input{ Vertex4Pos,
				glm::vec3{ 1,1,1 },*(uvInformation + 3), glm::vec3{ LightLevel ,LightLevel,LightLevel } });

			blockFace = &xFace1;
		}
		m_Indices = { m_VertextIndexIndex, m_VertextIndexIndex + 1, m_VertextIndexIndex + 2, m_VertextIndexIndex + 2, m_VertextIndexIndex + 3, m_VertextIndexIndex,
			m_VertextIndexIndex + 4, m_VertextIndexIndex + 5, m_VertextIndexIndex + 6, m_VertextIndexIndex + 6, m_VertextIndexIndex + 7, m_VertextIndexIndex + 4 };

		m_VertextIndexIndex += 8;
		m_pChunkMesh->AddFaceToMesh(m_vertices, m_Indices);
		return true;
	}


}

void ChunkMesh::BufferMesh()
{
	//NON transparant Data
	{
		m_ChunkVertexArray.reset(Eu::VertexArray::Create());

		auto Vertices = m_pChunkMesh->GetVertexBuffer();
		auto Indices = m_pChunkMesh->GetIndexBuffer();

		Eu::BufferLayout layout = {
			{Eu::ShaderDataType::Float3, "a_Position"},
			{Eu::ShaderDataType::Float3, "a_Color"},
			{Eu::ShaderDataType::Float2, "a_Uv"},
			{Eu::ShaderDataType::Float3, "a_Normal"},
		};

		std::shared_ptr<Eu::VertexBuffer> pVertexBuffer;
		pVertexBuffer.reset(Eu::VertexBuffer::Create(Vertices.data(), Vertices.size()));
		pVertexBuffer->SetLayout(layout);
		m_ChunkVertexArray->AddVertexBuffer(pVertexBuffer);

		//indexbuffer
		std::shared_ptr<Eu::IndexBuffer> pIndexBuffer;
		pIndexBuffer.reset(Eu::IndexBuffer::Create(Indices.data(), Indices.size()));
		m_ChunkVertexArray->AddIndexBuffer(pIndexBuffer);

		(*m_pRenderingProgram)->SetUniformInt(0, "u_Texture", Eu::BaseProgram::ShaderTypes::T_PixelShader);

		m_pChunkMesh->Clear();
		m_VertextIndexIndex = 0;
	}



	


}
 
void ChunkMesh::Render() const
{
	m_ChunkVertexArray->Bind();
	Eu::Renderer::Submit(m_ChunkVertexArray, *m_pRenderingProgram);
}

