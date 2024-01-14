#include "ChunkMeshComponent.h"
#include <array>
#include "Europa/Components/MeshComponent.h"
#include "Europa/GameObject.h"
#include "Europa/Components/MeshRenderComponent.h"
#include "ChunkMaterial.h"
#include "Europa/Renderer/Renderer.h"
#include "Europa/Material/MaterialManager.h"
#include "../BlockJsonParser.h"
#include "Europa/Log.h"

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
	m_CurrMat = Eu::MaterialManager::GetInstance()->CreateMaterial<ChunkMaterial>();
}

ChunkMeshComponent::~ChunkMeshComponent()
{
}

void ChunkMeshComponent::Start()
{


}

void ChunkMeshComponent::Update()
{
	if (m_ResetMesh == true)
		BufferMesh();
}

void ChunkMeshComponent::FixedUpdate()
{

}

void ChunkMeshComponent::Render() const
{
	if (m_IsBuffered) {
		//EU_CORE_INFO("RENDER POS: {0}, {1}", GetAttachedGameObject()->GetTransform().GetWorldPosition().x, GetAttachedGameObject()->GetTransform().GetWorldPosition().z);
		Eu::Renderer::Submit(m_ChunkVertexArray, m_CurrMat, GetAttachedGameObject()->GetTransform().GetWorld());

	}
}

void ChunkMeshComponent::AddFace(glm::vec3 BlockPos, Faces dir, uint8_t blockType)
{
	//const std::array<float, 12>* blockFace;
	//
	//std::vector<Eu::Vertex_Input> m_vertices;
	//std::vector<int> m_Indices;
	//
	//bool isCube = BlockJsonParser::GetInstance()->IsCube(blockType);
	//float LightLevel = 1.f;
	//
	//auto uvInformation = BlockJsonParser::GetInstance()->GetUVOfType(blockType, dir);
	//
	//if (isCube) { //cube form
	//	switch (dir)
	//	{
	//	case Faces::TOP:
	//		LightLevel = 1.0f;
	//		blockFace = &topFace;
	//		break;
	//	case Faces::BOT:
	//		LightLevel = 0.4f;
	//		blockFace = &bottomFace;
	//		break;
	//	case Faces::LEFT:
	//		LightLevel = 0.8f;
	//		blockFace = &leftFace;
	//		break;
	//	case Faces::RIGHT:
	//		LightLevel = 0.8f;
	//		blockFace = &rightFace;
	//		break;
	//	case Faces::FRONT:
	//		LightLevel = 0.6f;
	//		blockFace = &frontFace;
	//		break;
	//	case Faces::BACK:
	//		LightLevel = 0.6f;
	//		blockFace = &backFace;
	//		break;
	//	default:
	//		break;
	//	}
	//
	//
	//	glm::vec3 Vertex1Pos = glm::vec3{ (*blockFace)[0] + BlockPos.x, (*blockFace)[1] + ( BlockPos.y), (*blockFace)[2] + BlockPos.z };
	//	m_vertices.push_back(Eu::Vertex_Input{ Vertex1Pos,
	//		glm::vec3{ 1,1,1 }, (*uvInformation)[0], glm::vec3{LightLevel,LightLevel,LightLevel}});
	//	//std::cout << Vertex1Pos.x << "  " << Vertex1Pos.y << " " << Vertex1Pos.z << std::endl;
	//
	//
	//	glm::vec3 Vertex2Pos = glm::vec3{ (*blockFace)[3]  + BlockPos.x, (*blockFace)[4] + ( BlockPos.y), (*blockFace)[5] + BlockPos.z };
	//	m_vertices.push_back(Eu::Vertex_Input{ Vertex2Pos,
	//		glm::vec3{ 1,1,1 },  (*uvInformation)[1], glm::vec3{ LightLevel,LightLevel,LightLevel} });
	//
	//
	//	glm::vec3 Vertex3Pos = glm::vec3{ (*blockFace)[6] + BlockPos.x, (*blockFace)[7] +  BlockPos.y, (*blockFace)[8] + BlockPos.z };
	//	m_vertices.push_back(Eu::Vertex_Input{ Vertex3Pos,
	//		glm::vec3{ 1,1,1 }, (*uvInformation)[2], glm::vec3{ LightLevel,LightLevel,LightLevel } });
	//
	//	glm::vec3 Vertex4Pos = glm::vec3{ (*blockFace)[9]+ BlockPos.x, (*blockFace)[10] + (BlockPos.y), (*blockFace)[11] + + BlockPos.z };
	//	m_vertices.push_back(Eu::Vertex_Input{ Vertex4Pos,
	//		glm::vec3{ 1,1,1 }, (*uvInformation)[3], glm::vec3{ LightLevel ,LightLevel,LightLevel } });
	//
	//	m_Indices = { m_VertextIndexIndex, m_VertextIndexIndex + 1, m_VertextIndexIndex + 2, m_VertextIndexIndex + 2, m_VertextIndexIndex + 3, m_VertextIndexIndex };
	//	m_VertextIndexIndex += 4;
	//}
	//else {
	//	blockFace = &xFace2;
	//	for (size_t i = 0; i < 2; i++)
	//	{
	//		glm::vec3 Vertex1Pos = glm::vec3{ (*blockFace)[0] + BlockPos.x, (*blockFace)[1] + ( BlockPos.y), (*blockFace)[2] + BlockPos.z };
	//		m_vertices.push_back(Eu::Vertex_Input{ Vertex1Pos,
	//			glm::vec3{ 1,1,1 }, (*uvInformation)[0], glm::vec3{ LightLevel,LightLevel,LightLevel } });
	//		//std::cout << Vertex1Pos.x << "  " << Vertex1Pos.y << " " << Vertex1Pos.z << std::endl;
	//
	//
	//		glm::vec3 Vertex2Pos = glm::vec3{ (*blockFace)[3] + BlockPos.x, (*blockFace)[4] + ( BlockPos.y), (*blockFace)[5] + BlockPos.z };
	//		m_vertices.push_back(Eu::Vertex_Input{ Vertex2Pos,
	//			glm::vec3{ 1,1,1 }, (*uvInformation)[1], glm::vec3{ LightLevel,LightLevel,LightLevel} });
	//
	//
	//		glm::vec3 Vertex3Pos = glm::vec3{ (*blockFace)[6] + BlockPos.x, (*blockFace)[7] + ( BlockPos.y), (*blockFace)[8] + BlockPos.z };
	//		m_vertices.push_back(Eu::Vertex_Input{ Vertex3Pos,
	//			glm::vec3{ 1,1,1 },(*uvInformation)[2], glm::vec3{ LightLevel,LightLevel,LightLevel } });
	//
	//		glm::vec3 Vertex4Pos = glm::vec3{ (*blockFace)[9]  + BlockPos.x, (*blockFace)[10] + ( BlockPos.y), (*blockFace)[11]  + BlockPos.z };
	//		m_vertices.push_back(Eu::Vertex_Input{ Vertex4Pos,
	//			glm::vec3{ 1,1,1 },(*uvInformation)[3], glm::vec3{ LightLevel ,LightLevel,LightLevel } });
	//
	//		blockFace = &xFace1;
	//	}
	//	m_Indices = { m_VertextIndexIndex, m_VertextIndexIndex + 1, m_VertextIndexIndex + 2, m_VertextIndexIndex + 2, m_VertextIndexIndex + 3, m_VertextIndexIndex,
	//		m_VertextIndexIndex + 4, m_VertextIndexIndex + 5, m_VertextIndexIndex + 6, m_VertextIndexIndex + 6, m_VertextIndexIndex + 7, m_VertextIndexIndex + 4 };
	//
	//	m_VertextIndexIndex += 8;
	//}
	//
	//m_ChunkMeshData.m_VertexBuffer.insert(m_ChunkMeshData.m_VertexBuffer.end(), m_vertices.begin(), m_vertices.end());
	//m_ChunkMeshData.m_IndexBuffer.insert(m_ChunkMeshData.m_IndexBuffer.end(), m_Indices.begin(), m_Indices.end());
}

void ChunkMeshComponent::AddVertices(std::vector<glm::vec3> vertex, glm::vec3 normal, int normalll, int width, int height, uint8_t texturedID)
{
	//TODO: scale uv coordinates with with and height

	std::vector<int> indicesVec;
	std::vector<Eu::ChunkVertexInput> vertices;
	std::vector<glm::vec2> uvCoords;
	if (normal.x == 1 || normal.x == -1)
		uvCoords = std::vector<glm::vec2>{ glm::vec2{height,width},  glm::vec2{height,0},  glm::vec2{0,width},  glm::vec2{0,0} };
	else
		uvCoords = std::vector<glm::vec2>{ glm::vec2{width,height}, glm::vec2{0,height},  glm::vec2{width,0},  glm::vec2{0,0} };

	//Get light level
	int lightLevel{};
	lightLevel = 90;
	if (normal.y < 0)
		lightLevel = 40;
	else if (normal.x != 0)
		lightLevel = 60;
	else if (normal.z != 0)
		lightLevel = 80;


	auto uvInformation = BlockJsonParser::GetInstance()->GetUVOfType(1, Faces::FRONT);
	for (size_t i = 0; i < vertex.size(); i++)
	{
		Eu::ChunkVertexInput input;
		input.Position = vertex[i];
		//input.TextureIdxAnNormal = texturedID;
		input.tex = static_cast<int>(texturedID);

		//Pack Normal
		uint8_t packedNormalValue{0};
		if (normal.x != 0) {
			packedNormalValue |= 0x80;  // Set the 8th bit to 1
			if (normal.x < 0)
				packedNormalValue |= 0x10;
		}
		if (normal.y != 0) {
			packedNormalValue |= 0x40;  // Set the 7th bit to 1
			if (normal.y < 0)
				packedNormalValue |= 0x08;
		}
		if (normal.z != 0) {
			packedNormalValue |= 0x20;  // Set the 6th bit to 1
			if (normal.z < 0)
				packedNormalValue |= 0x04;
		}
		input.tex = (input.tex << 8) | packedNormalValue;
		input.tex = (input.tex << 8) | lightLevel;


		//Pack UV
		unsigned int packedUV;
		short packedWidth = static_cast<short>(uvCoords[i].x); 
		short packedHeight = static_cast<short>(uvCoords[i].y);
		packedUV = (packedWidth << 16 | packedHeight);
		input.UV = packedUV;
		vertices.push_back(input);
	}
	indicesVec = { m_VertextIndexIndex, m_VertextIndexIndex + 2 + normalll, m_VertextIndexIndex + 2 - normalll, m_VertextIndexIndex + 3, m_VertextIndexIndex + 1 - normalll, m_VertextIndexIndex + 1 + normalll };
	m_VertextIndexIndex += 4;
	m_IndexBuffer.insert(m_IndexBuffer.end(), indicesVec.begin(), indicesVec.end());
	m_VertexBuffer.insert(m_VertexBuffer.end(), vertices.begin(), vertices.end());


}

void ChunkMeshComponent::BufferMesh()
{
	m_ChunkVertexArray.reset(Eu::VertexArray::Create());

	Eu::BufferLayout layout = {
		{Eu::ShaderDataType::Float3, "a_Position"},
		{Eu::ShaderDataType::Int, "a_NormalTextureIDX", true},
		{Eu::ShaderDataType::Int, "a_UV", true},

	};

	std::shared_ptr<Eu::VertexBuffer> pVertexBuffer;
	pVertexBuffer.reset(Eu::VertexBuffer::Create(m_VertexBuffer.data(), static_cast<uint32_t>(m_VertexBuffer.size()) * sizeof(Eu::ChunkVertexInput)));
	pVertexBuffer->SetLayout(layout);
	m_ChunkVertexArray->AddVertexBuffer(pVertexBuffer);

	//indexbuffer
	std::shared_ptr<Eu::IndexBuffer> pIndexBuffer;
	pIndexBuffer.reset(Eu::IndexBuffer::Create(m_IndexBuffer.data(), static_cast<uint32_t>(m_IndexBuffer.size())));
	m_ChunkVertexArray->AddIndexBuffer(pIndexBuffer);
	m_IsBuffered = true;
	m_IndexBuffer.clear();
	m_IndexBuffer.shrink_to_fit();
	m_VertexBuffer.clear();
	m_VertexBuffer.shrink_to_fit();

	m_VertextIndexIndex = 0;
	m_ResetMesh = false;
	//EU_CORE_INFO("BUFFF");

}

