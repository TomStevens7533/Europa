#pragma once
#include "Europa/Components/BaseComponent.h"
#include <glm/glm.hpp>
#include <memory>
#include "../Minecraft/BlockStruct.h"
#include <Europa/structs.h>
#include <atomic>
namespace Eu {
	class MeshComponent;
	class MeshRenderComponent;
	class VertexArray;

}
class ChunkMaterial;
class ChunkMeshComponent final : public Eu::BaseComponent
{
public:
	ChunkMeshComponent();
	~ChunkMeshComponent();

	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;
	void AddFace(glm::vec3 BlockPos, Faces dir, uint8_t blockType);

	void AddVertices(std::vector<glm::vec3> vertex, glm::vec3 normal, int normalll, int width, int height, uint8_t texturedID);

	void BufferMesh();
	void ResetMesh() { m_IsBuffered = false; };
private:
	std::atomic<bool> m_IsBuffered{ false };
	int m_VertextIndexIndex = 0;
private:
	static std::shared_ptr<ChunkMaterial> m_CurrMat;
	std::shared_ptr<Eu::VertexArray> m_ChunkVertexArray;
	std::vector<Eu::ChunkVertexInput> m_VertexBuffer;
	std::vector<uint32_t> m_IndexBuffer;




};

