#pragma once
#include "Europa/GameObject.h"

class Chunk : public Eu::BaseGameObject
{
public:

	Chunk();
	virtual ~Chunk() override;

	virtual void Update() override;
	virtual void Render() const override;
	virtual void SetPos(glm::vec3 position) override;

private:
	Eu::gameObject* cubeArray[16][16][64];
	const uint32_t x = 16;
	const uint32_t z = 16;
	const uint32_t y = 16;


};

