#pragma once
#include "Eupch.h"
#include <glm/glm.hpp>
#include "Texture.h"

namespace Eu {
	class VertexArray;
	class BaseTexture;
	class BaseProgram;
	class ResourceManager;

	class BaseGameObject {
	public:
		virtual ~BaseGameObject() = default;
		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void SetPos(glm::vec3 position) = 0;
		void AddRotation(glm::vec3 newRotation);
		void AddScale(glm::vec3 scale);

	protected:
		//matrices
		glm::mat4 m_ToWorldMatrix = glm::mat4(1.f);
		glm::mat4 m_RotationMatrix = glm::mat4(1.f);
		glm::mat4 m_ScaleMatrix = glm::mat4(1.f);

		glm::vec3 m_RotationVec = { 0,0,0 };
		uint32_t m_GoIndex;


		ResourceManager* m_ResourceManager;
		const std::shared_ptr<BaseProgram>* m_pRenderingProgram;


	};


	class gameObject : public BaseGameObject
	{
	public:
		//We can create empty gameobject
		gameObject();
		virtual ~gameObject() override {};

		void AddMesh(const std::string& path);
		void AddTexture(const std::string& path, const TextureTypes textureType);

		virtual void SetPos(glm::vec3 position) override;
		virtual void Update() override;
		virtual void Render() const override;

	private: //attributes
		std::shared_ptr<BaseTexture> m_ptexture;
		std::shared_ptr<VertexArray> m_VertexArray;
	};

	class SkyBox : public BaseGameObject {
	public:
		//We can create empty gameobject
		SkyBox();
		virtual ~SkyBox() override {};

		void AddTexture(const std::string& path);

		virtual void SetPos(glm::vec3 position) override;
		virtual void Update() override;
		virtual void Render() const override;

	private:
		void AddMesh(const std::string& path);
	private: //attributes
		std::shared_ptr<BaseTexture> m_ptexture;
		std::shared_ptr<VertexArray> m_VertexArray;
	};

	

}

