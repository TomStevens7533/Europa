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
		BaseGameObject() = default;
		virtual ~BaseGameObject() = default;
		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void SetPos(glm::vec3 position) = 0;
		virtual void AddPos(glm::vec3 position) = 0;
		virtual void SetUVBounds(int wIndex, int HIndex, int colSize, int rowSize) = 0;
		void AddRotation(glm::vec3 newRotation);
		void AddScale(glm::vec3 scale);

	protected:
		//matrices
		glm::vec3 m_RotationVec = { 0,0,0 };
		glm::vec3 m_Position;


	};


	class gameObject : public BaseGameObject
	{
	public:
		//We can create empty gameobject
		gameObject();
		virtual ~gameObject() override {};

		void AddMesh(const std::string& path);
		void AddTexture(const std::string& path, const TextureTypes textureType);
		virtual void SetUVBounds(int wIndex, int HIndex, int colSize, int rowSize) override;
		virtual void AddPos(glm::vec3 position) override;


		virtual void SetPos(glm::vec3 position) override;
		virtual void Update() override;
		virtual void Render() const override;
	private:
		bool isBoundingUVs = false;
		glm::vec2 uBounds;
		glm::vec2 vBounds;

		static std::shared_ptr<BaseTexture>* m_ptexture;
		static std::shared_ptr<VertexArray>* m_VertexArray;
		const static std::shared_ptr<BaseProgram>* m_pRenderingProgram;

	};

	class SkyBox : public BaseGameObject {
	public:
		//We can create empty gameobject
		SkyBox();
		virtual ~SkyBox() override {  };

		void AddTexture(const std::string& path);
		virtual void SetUVBounds(int wIndex, int HIndex, int colSize, int rowSize) override;
		virtual void SetPos(glm::vec3 position) override;
		virtual void AddPos(glm::vec3 position) override;

		virtual void Update() override;
		virtual void Render() const override;

	private:
		void AddMesh(const std::string& path);

		static std::shared_ptr<BaseTexture>* m_ptexture;
		static std::shared_ptr<VertexArray>* m_VertexArray;
		const static std::shared_ptr<BaseProgram>* m_pRenderingProgram;
		glm::mat4 m_TRSMatrix = glm::mat4(1.f);

	};

	

}

