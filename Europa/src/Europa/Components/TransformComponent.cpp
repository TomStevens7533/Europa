#include "TransformComponent.h"
#include "glm/gtx/rotate_vector.hpp"

namespace Eu {
	TransformComponent::TransformComponent() :
		m_Position{ 0, 0, 0 },
		m_WorldPosition{ 0, 0, 0 },
		m_Scale{ 1, 1, 1 },
		m_WorldScale{ 1, 1, 1 },
		m_Forward{ 0, 0, 1 },
		m_Up{ 0, 1, 0 },
		m_Right{ 1, 0, 0 },
		m_Rotation{ 0, 0, 0, 1 },
		m_WorldRotation{ 0, 0, 0, 1 }
	{}

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

	void TransformComponent::UpdateTransforms()
	{
		//Calculate World Matrix
		//**********************
		auto rot = glm::rotate(glm::mat4(1.f), m_Rotation.x, glm::vec3(1, 0, 0));
		rot = glm::rotate(rot, m_Rotation.y, glm::vec3(0, 1, 0));
		rot = glm::rotate(rot, m_Rotation.z, glm::vec3(0, 0, 1));
		//
		//auto world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z) *
		//	XMMatrixRotationQuaternion(rot) *
		//	XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		//if (const auto pParent = m_pGameObject->GetParent())
		//{
		//	const auto parentWorld = XMLoadFloat4x4(&pParent->GetTransform()->m_World);
		//	world *= parentWorld;
		//}

		//XMStoreFloat4x4(&m_World, world);

		////Get World Transform
		//XMVECTOR pos, scale;
		//if (XMMatrixDecompose(&scale, &rot, &pos, world))
		//{
		//	XMStoreFloat3(&m_WorldPosition, pos);
		//	XMStoreFloat3(&m_WorldScale, scale);
		//	XMStoreFloat4(&m_WorldRotation, rot);
		//}

		//const auto rotMat = XMMatrixRotationQuaternion(rot);
		//const auto forward = XMVector3TransformCoord(XMVectorSet(0, 0, 1, 0), rotMat);
		//const auto right = XMVector3TransformCoord(XMVectorSet(1, 0, 0, 0), rotMat);
		//const auto up = XMVector3Cross(forward, right);

		//XMStoreFloat3(&m_Forward, forward);
		//XMStoreFloat3(&m_Right, right);
		//XMStoreFloat3(&m_Up, up);

		//m_IsTransformChanged = TransformChanged::NONE;
	}


}
