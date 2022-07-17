#include "TransformComponent.h"

using namespace Eu;

//Base functio ss
void TransformComponent::Start()
{
	UpdateTransforms();
}

void TransformComponent::Update()
{
}

void TransformComponent::FixedUpdate()
{
	m_IsDirty = CheckIfDirty();

	if (m_IsDirty)
		UpdateTransforms();
}

Eu::TransformComponent::TransformComponent()
{

}

void Eu::TransformComponent::Translate(float x, float y, float z)
{

}

void Eu::TransformComponent::Rotate(float x, float y, float z, bool degrees /*= true*/)
{

}

void Eu::TransformComponent::Scale(float x, float y, float z)
{

}

void Eu::TransformComponent::Start()
{

}

void Eu::TransformComponent::Update()
{

}

void Eu::TransformComponent::FixedUpdate()
{

}

void Eu::TransformComponent::Render() const
{

}

void Eu::TransformComponent::UpdateTransforms()
{

}

bool Eu::TransformComponent::CheckConstraints() const
{

}

bool Eu::TransformComponent::CheckIfDirty()
{

}
void Eu::TransformComponent::Scale(const glm::vec3& scale)
{

}

void Eu::TransformComponent::Scale(float s)
{

}

void Eu::TransformComponent::Rotate(const glm::vec3& rotation, bool isQuaternion /*= true*/)
{

}

void Eu::TransformComponent::Translate(const glm::vec3& position)
{

}

Eu::TransformComponent::~TransformComponent()
{

}

