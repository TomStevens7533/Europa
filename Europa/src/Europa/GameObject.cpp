#include "GameObject.h"
#include "mesh/Mesh.h"
#include "glm/glm.hpp"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "ResourceManager.h"

namespace Eu {
	GameObject::~GameObject() = default;

	void GameObject::SetParent(GameObject * parent)
	{
		m_Parent = parent;

		//Reshuffle root pos for all children
		ChangeRootPos((parent->GetPosFromRoot() + static_cast<int>(parent->GetChildCount())));

	}

	void GameObject::ChangeRootPos(int newRootPos)
	{
		m_PositionFromRoot = newRootPos;

		for (auto& child : m_Children)
		{
			newRootPos++;
			assert(child->GetPosFromRoot() > this->GetPosFromRoot()); //assert if circular included 
			child->ChangeRootPos(newRootPos);
			RemoveChild(child->GetPosFromRoot());

		}
	}


	int GameObject::GetPosFromRoot()
	{
		return m_PositionFromRoot;
	}

	glm::vec3 GameObject::RelativePositionToParent()
	{
		glm::vec3 currPos = GetTransform().GetPosition();

		auto parent = GetParent();
		while (parent != nullptr) {
			currPos += parent->GetTransform().GetPosition();
			parent = parent->GetParent();
		}
		return currPos;
	}

	GameObject* GameObject::GetParent() const
	{
		return m_Parent;
	}

	size_t GameObject::GetChildCount() const
	{
		return m_Children.size();
	}

	std::shared_ptr<GameObject> GameObject::GetChildAt(int Index) const
	{
		if (Index <= static_cast<int>(m_Children.size()))
			return m_Children[Index];
		else {
			return nullptr;
		}

	}

	void GameObject::RemoveChild(int index)
	{
		EU_CLIENT_INFO("Child gameobject removed at index: " + index);
		m_Children.erase(std::next(m_Children.begin(), glm::clamp(index, 0, static_cast<int>(m_Children.size() - 1))));
	}

	void GameObject::RemoveChild(std::shared_ptr<GameObject> childToRemove)
	{
		m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), childToRemove), m_Children.end());
	}

	void GameObject::AddChild(std::shared_ptr<Eu::GameObject>&go)
	{
		m_Children.push_back(go);
		go->SetParent(this);
		//go->SetScene(this->GetScene());

		//Call start on new Child
		go->Start();
	}

	void GameObject::Start()
	{
		//this component first
		m_EntityManager.Start();

		for (auto& child : m_Children)
		{
			child->Start();
		}

		m_IsInitialized = true;
	}

	void GameObject::Update()
	{
		//Update this gameobject component first
		m_Transform.Update();
		m_EntityManager.Update();

		for (auto& child : m_Children)
		{
			child->Update();
		}
	}

	void GameObject::FixedUpdate()
	{
		m_Transform.FixedUpdate();
		m_EntityManager.FixedUpdate();

		for (auto& child : m_Children)
		{
			child->FixedUpdate();
		}
	}

	void GameObject::Render() const
	{
		m_EntityManager.Render();

		for (auto& child : m_Children)
		{
			child->Render();
		}

	}

	void GameObject::SetName(std::string name)
	{
		m_GameobjectName = name;
	}

	void GameObject::SetPosition(float x, float y)
	{
		m_Transform.Translate(x, y, 0.0f);
	}

	void GameObject::SetPosition(glm::vec2 pos)
	{
		m_Transform.Translate(pos.x, pos.y);

	}

	void GameObject::SetPosition(glm::vec3 pos)
	{
		m_Transform.Translate(pos.x, pos.y, pos.z);

	}

}