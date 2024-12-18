#pragma once
#include <glm/glm.hpp>
#include <utility>
#include "Europa/Components/BaseComponent.h"
#include <atomic>
#include <array>
#include "../Minecraft/BlockStruct.h"


class ChunkMeshComponent;
class BlockInfromation;
class ChunkManager;
class ChunkComponent final : public Eu::BaseComponent
{
public:

	ChunkComponent(ChunkID iD, int xSize, int ySize, int zSize, ChunkManager* ptr);
	~ChunkComponent();

	void DestroyChunk();
	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const;

	void BuildTrees();
	void SetDirty() { m_Initialized = true; };
	bool GetDirtyFlag() { return m_Initialized; }
	BlockType GetBlock(int x, int y, int z);

	BlockType GetBlockType(int x, int y, int z, int max);
	bool IsBlockSolid(int x, int y, int z) const;

	//Threaded
	bool InitializeChunk();
	void ReplaceBlock(int x, int y, int z, BlockType id);
	void CreateMesh();
	bool GetInitstate() const { return m_Initialized; }

private:
	struct BlockMask
	{
		int id;
		int normal;
	};

private:
	bool IsBlockSolid(uint8_t blockType) const;
	bool CompareMask(BlockMask mask1, BlockMask mask2);
	void CreateQuad(BlockMask mask, glm::ivec3 axisMask, glm::ivec3 v1, glm::ivec3 v2, glm::ivec3 v3, glm::ivec3 v4, int widht, int height);
	int GetTextureIndex(BlockType block, glm::vec3 normal);
private:
	std::shared_ptr<ChunkMeshComponent> m_pChunkMesh;
	std::atomic<bool> m_Initialized{ false };
	std::atomic<bool> m_NeedMeshing{ true };
	std::vector<int> heightMap;
	mutable std::mutex m_ChunkIDMapMutex;

	ChunkManager* m_pManager;
private:
	const int m_XSize{};
	const int m_YSize{};
	const int m_ZSize{};
	const ChunkID m_ChunkID{};
	const glm::ivec3 m_AxisSize{};
	std::condition_variable cv;

	uint8_t* m_ChunkArray{nullptr};
};

