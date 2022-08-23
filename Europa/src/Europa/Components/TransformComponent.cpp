#include "TransformComponent.h"
#include "glm/glm.hpp"
#include <corecrt_math_defines.h>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtx/quaternion.hpp>

namespace Eu {
	TransformComponent::TransformComponent() :
		m_Position{ 0, 0, 0 },
		m_WorldPosition{ 0, 0, 0 },
		m_Scale{ 1, 1, 1 },
		m_WorldScale{ 1, 1, 1 },
		m_Forward{ 0, 0, -1 },
		m_Up{ 0, 1, 0 },
		m_Right{ 1, 0, 0 },
		m_Rotation{ 0, 0, 0, 1 },
		m_WorldRotation{ 0, 0, 0, 1 }
	{
		UpdateTransforms();
	}


	void TransformComponent::Translate(float x, float y, float z)
	{
		m_Position = glm::vec3(x, y, z);
		m_IsDirty = true;
	}

	void TransformComponent::Translate(const glm::vec3& position)
	{
		m_Position = position;
		m_IsDirty = true;

	}

	void TransformComponent::Translate(float x, float y)
	{
		m_Position = glm::vec3(x, y, m_Position.z);
		m_IsDirty = true;
	}

	void TransformComponent::Rotate(float x, float y, float z, bool degrees /*= true*/)
	{
		if (degrees) {
			glm::vec3 euler = glm::vec3(x * (180.f / M_PI),y * (180.f / M_PI), z * (180.f / M_PI));
			m_Rotation = glm::quat(glm::radians(euler));
		}
		else {
			glm::vec3 euler = glm::vec3(x, y, z);
			m_Rotation = glm::quat(euler);
		}
		m_IsDirty = true;

	}

	void TransformComponent::Rotate(const glm::vec3& rotation, bool degrees /*= true*/)
	{
		if(degrees) {
			glm::vec3 euler = glm::vec3( glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
			m_Rotation = glm::quat(euler);
		}
		else {
			m_Rotation = glm::quat(rotation);
		}
		m_IsDirty = true;

	}

	void TransformComponent::Scale(float x, float y, float z)
	{
		m_Scale = glm::vec3(x, y, z);
		m_IsDirty = true;


	}

	void TransformComponent::Scale(float s)
	{
		m_Scale = glm::vec3(s, s, s);
		m_IsDirty = true;

	}

	void TransformComponent::Scale(const glm::vec3& scale)
	{
		m_Scale = scale;
		m_IsDirty = true;

	}

	bool TransformComponent::CheckIfDirty()
	{
		//If Parent is dirty == update required (spatial relation)

		return m_IsDirty;
	}
	void TransformComponent::Start()
	{
		UpdateTransforms();
	}

	void TransformComponent::Update()
	{
		m_IsDirty = CheckIfDirty();

		if (m_IsDirty)
			UpdateTransforms();
	}

	void TransformComponent::FixedUpdate()
	{

	}

	void TransformComponent::Render() const
	{

	}

	void TransformComponent::UpdateTransforms()
	{
		//Calculate World Matrix
		//**********************
		//rot
		auto rot = glm::toMat4(m_Rotation);
		//trans
		auto trans = glm::translate(glm::mat4(1), m_Position);
		//Scale
		auto scale = glm::scale(glm::mat4(1), m_Scale);
		m_World = trans * rot  * scale;
	
		//decompose 
		glm::vec3 skew;
		glm::quat decompRot;
		glm::vec4 perspective;
		glm::decompose(m_World, m_WorldScale, decompRot, m_WorldPosition, skew, perspective);

		//convert conjugate to worldrot
		m_WorldRotation = glm::conjugate(decompRot);
		
		m_Forward = (glm::vec4(0, 0, -1, 0) * rot);
		m_Right =   (glm::vec4(1, 0, 0, 0) * rot);
		m_Up =   glm::normalize(glm::cross(m_Forward, m_Right));

		m_IsDirty = false;

	}


}
     