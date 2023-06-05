#pragma once
#include <glm/glm.hpp>
#include <utility>
#include "Europa/Components/BaseComponent.h"
#include <atomic>
#include <array>



class ChunkMeshComponent;
class BlockInfromation;
class ChunkManager;
class ChunkComponent final : public Eu::BaseComponent
{
public:

	ChunkComponent(int xSize, int ySize, int zSize, const std::shared_ptr < ChunkManager> ptr, int scale = 1);
	~ChunkComponent();

	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const;

	void SetDirty() { m_NeedUpdate = true; };
	bool GetDirtyFlag() { return m_NeedUpdate; }
	void CreateMesh();
	uint8_t GetBlock(int x, int y, int z);
	uint8_t GetBlockType(int x, int y, int z, std::array<int, 16 * 16 >* heightmap);
	bool IsBlockSolid(int x, int y, int z) const;

private:
	struct BlockMask
	{
		uint8_t id;
		int normal;
	};

private:
	bool IsBlockSolid(uint8_t blockType) const;
	void ReplaceBlock(int x, int y, int z, uint8_t id);
	bool CompareMask(BlockMask mask1, BlockMask mask2);
	void CreateQuad(BlockMask mask, glm::ivec3 axisMask, glm::ivec3 v1, glm::ivec3 v2, glm::ivec3 v3, glm::ivec3 v4, int widht, int height);
	int GetTextureIndex(uint8_t block, glm::vec3 normal);
private:
	std::shared_ptr<ChunkMeshComponent> m_pChunkMesh;
	std::atomic<bool> m_NeedUpdate{ false };
	const std::shared_ptr<ChunkManager> m_pManager;
private:
	const int m_Scale{};
	const int m_XSize{};
	const int m_YSize{};
	const int m_ZSize{};
	const glm::ivec3 m_AxisSize{};

	uint8_t* m_ChunkArray{nullptr};
};

