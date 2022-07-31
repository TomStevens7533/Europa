#pragma once
#include "Europa/Components/BaseComponent.h"
#include <glm/glm.hpp>
#include "../src/Minecraft/BlockStruct.h"

namespace Eu {
	class MeshComponent;
	class MeshRenderComponent;

}
class ChunkMeshComponent final : public Eu::BaseComponent
{
public:
	ChunkMeshComponent();
	~ChunkMeshComponent();

	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;
	bool AddFace(glm::vec3 ChunPos, glm::vec3 BlockPos, Faces dir, BlockTypes blockType);
	void BufferMesh();

private:
	Eu::MeshComponent* m_pChunkMesh;
	Eu::MeshRenderComponent* m_pChunkMeshRenderer;
	int m_VertextIndexIndex = 0;



};

