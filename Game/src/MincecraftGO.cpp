#include "MincecraftGO.h"


Chunk::Chunk()
{	
	glm::vec3 cubePosition = { 0,0,0 };

	for (size_t yIndex = 0; yIndex < 64; yIndex++) //256
	{
		cubePosition.x = 0;
		for (size_t xIndex = 0; xIndex < 16; xIndex++)
		{
			cubePosition.z = 0;
			for (size_t zIndex = 0; zIndex < 16; zIndex++)
			{
				Eu::gameObject* newCube = new Eu::gameObject;
				newCube->AddMesh("Resources/minecraft/minecraftcube.obj");
				newCube->AddTexture("Resources/minecraft/mcdirt.png", Eu::TextureTypes::TEXTURE2D);
				newCube->SetPos(cubePosition);
				cubeArray[zIndex][xIndex][yIndex] = newCube;
				cubePosition.z += 1;

			}
			cubePosition.x += 1;
		}
		cubePosition.y += 1;

	}


}

Chunk::~Chunk()
{
	for (size_t yIndex = 0; yIndex < 64; yIndex++) //256
	{
		for (size_t xIndex = 0; xIndex < 16; xIndex++)
		{
			for (size_t zIndex = 0; zIndex < 16; zIndex++)
			{
				delete cubeArray[zIndex][xIndex][yIndex];

			}
		}

	}

}

void Chunk::Update()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Chunk::Render() const
{
	for (size_t yIndex = 0; yIndex < 64; yIndex++) //256
	{
		for (size_t xIndex = 0; xIndex < 16; xIndex++)
		{
			for (size_t zIndex = 0; zIndex < 16; zIndex++)
			{
				cubeArray[zIndex][xIndex][yIndex]->Render();

			}
		}

	}
}

void Chunk::SetPos(glm::vec3 position)
{
	throw std::logic_error("The method or operation is not implemented.");
}

