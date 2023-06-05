#pragma once
#include "Europa/Components/BaseComponent.h"
#include <map>
#include "glm/glm.hpp"

class ChunkComponent;
namespace Eu {
	class PerspectiveCameraControllerComponent;
}
struct ChunkID
{
	float x;
	float y;

	// Overloading the < operator
	bool operator<(const ChunkID& other) const {
		return (x - y) > ((fabs(x) < fabs(y) ? fabs(y) : fabs(x)) * DBL_EPSILON);
	}
	bool operator>(const ChunkID& other) const {
		return (y - x) > ((fabs(x) < fabs(y) ? fabs(y) : fabs(x)) * DBL_EPSILON);
	}
	bool operator==(const ChunkID& other) const {
		return fabs(x - y) <= ((fabs(x) > fabs(y) ? fabs(y) : fabs(x)) * DBL_EPSILON);
	}
};

struct safe_double_less {
	bool operator()(ChunkID left, ChunkID right) const {
		bool leftXNaN = std::isnan(left.x);
		bool rightXNaN = std::isnan(right.x);

		bool leftYNaN = std::isnan(left.y);
		bool righYXNaN = std::isnan(right.x);

		//if isnan(1) pass if
		if (leftXNaN || leftYNaN || rightXNaN || righYXNaN)
			return true; //Define default behaviour for if NAN numbers are found; if any we consider the greater

		if (left.x < right.x) {
			return true;
		}
		else if (left.x > right.x) {
			return false;
		}
		else {
			// First elements are equal, compare the second elements
			if (left.y < right.y) {
				return true;
			}
			else if (left.y > right.y) {
				return false;
			}
			else {
				// Both elements are equal
				return false;
			}
		}
	}
};
class ChunkManager : public Eu::BaseComponent, public std::enable_shared_from_this<ChunkManager>
{
public:
	ChunkManager(const int xSize, int ySize, int zSize, Eu::PerspectiveCameraControllerComponent* cam, float scale = 1);
	ChunkManager(const int xSize, int ySize, int zSize, const int chunkWidthAmount, const int chunkDepthAmount, float scale = 1);
	~ChunkManager();


	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;
	uint8_t GetBlockIDNeighbour(glm::ivec2 position, int x, int y, int z);
	void UpdateNeightbours(glm::ivec2 posiotn);
private:
	void CreateChunk(glm::dvec2 position);
	ChunkID GetChunkID(glm::dvec2 position);
private:
	bool m_IsUpdatingAroundCamera{ false };

	double m_ChunkxSize{};
	double m_ChunkySize{};
	double m_ChunkzSize{};
	const int m_ChunkWidthAmount{};
	const int m_ChunkDepthAmount{};
	const float m_Scale{};
	Eu::PerspectiveCameraControllerComponent* m_Camera{};
	std::map < ChunkID, std::shared_ptr<ChunkComponent>, safe_double_less> m_ChunkIDMap;



};


