#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"
namespace Eu {

	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent();
		~TransformComponent();
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;


		void Translate(float x, float y, float z);
		void Translate(const glm::vec3& position);

		void Rotate(float x, float y, float z, bool degrees = true);
		void Rotate(const glm::vec3& rotation, bool degrees = true);

		void Scale(float x, float y, float z);
		void Scale(float s);
		void Scale(const  glm::vec3& scale);

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
		const glm::vec3& GetScale() const { return m_Scale; }
		const glm::vec3& GetWorldScale() const { return m_WorldScale; }
		const glm::vec4& GetRotation() const { return m_Rotation; }
		const glm::vec4& GetWorldRotation() const { return m_WorldRotation; }
		const glm::mat4& GetWorld() const { return m_World; }

		const glm::vec3& GetForward() const { return m_Forward; }
		const glm::vec3& GetUp() const { return m_Up; }
		const glm::vec3& GetRight() const { return m_Right; }

		bool IsDirty() const { return m_IsDirty; }


		//Basecomp functions
		void Start() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

	protected:

		void UpdateTransforms();
		bool CheckConstraints() const;

		bool CheckIfDirty();
		bool m_IsDirty{};

	private:

		glm::vec3 m_Position{}, m_WorldPosition{};
		glm::vec3 m_Scale{}, m_WorldScale{};
		glm::vec3 m_Forward{}, m_Up{}, m_Right{};
		glm::vec4 m_Rotation{}, m_WorldRotation{};
		glm::mat4 m_World{};
		bool m_IsTransformChanged{};
		bool m_IsIntialized{false};
	};
}
