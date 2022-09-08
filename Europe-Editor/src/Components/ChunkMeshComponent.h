#pragma once
#include "Europa/Components/BaseComponent.h"
#include <glm/glm.hpp>
#include <memory>
#include "../Minecraft/BlockStruct.h"
namespace Eu {
	class MeshComponent;
	class MeshRenderComponent;

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
	bool AddFace(glm::vec3 BlockPos, Faces dir, uint8_t blockType);
	void BufferMesh();

private:
	std::shared_ptr < Eu::MeshComponent> m_pChunkMesh{};
	std::shared_ptr<Eu::MeshRenderComponent> m_pChunkMeshRenderer{};
	int m_VertextIndexIndex = 0;
	std::shared_ptr<ChunkMaterial> m_CurrMat;



};

