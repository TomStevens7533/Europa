#include "GameObject.h"
#include "mesh/Mesh.h"
#include "glm/gtx/transform.hpp"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "ResourceManager.h"

namespace Eu {

	//base
	void BaseGameObject::AddRotation(glm::vec3 newRotation)
	{
		//we use radians
		m_RotationVec += newRotation;




		//clamp between 2PI TODO: fix negative
		m_RotationVec.x = fmod(m_RotationVec.x, 2.0f * glm::pi<float>());
		m_RotationVec.y = fmod(m_RotationVec.y, 2.0f * glm::pi<float>());
		m_RotationVec.z = fmod(m_RotationVec.z, 2.0f * glm::pi<float>());


		m_RotationMatrix = glm::rotate(glm::mat4(1.f), m_RotationVec.x, glm::vec3(1, 0, 0));
		m_RotationMatrix = glm::rotate(m_RotationMatrix, m_RotationVec.y, glm::vec3(0, 1, 0));
		m_RotationMatrix = glm::rotate(m_RotationMatrix, m_RotationVec.z, glm::vec3(0, 0, 1));

	}



	void BaseGameObject::AddScale(glm::vec3 scale)
	{
		m_ScaleMatrix = glm::scale(scale);
	}

	gameObject::gameObject()
	{
		//Create program attach shaders
		m_ResourceManager = ResourceManager::GetInstance();
		if(m_pRenderingProgram) //default to 2D texture program
			m_pRenderingProgram = &m_ResourceManager->GetProgram(TextureTypes::TEXTURE2D);

	}

	void gameObject::AddMesh(const std::string& path)
	{		
		m_VertexArray = m_ResourceManager->GetModel(path);
	}

	void gameObject::AddTexture(const std::string& path, const TextureTypes textureType)
	{
		m_ptexture = m_ResourceManager->GetTexture(path, textureType);
		m_pRenderingProgram = &m_ResourceManager->GetProgram(textureType);
		(*m_pRenderingProgram)->SetUniformInt(0, "u_Texture", BaseProgram::ShaderTypes::T_PixelShader);

		//set sampler2D


	}

	void gameObject::SetPos(glm::vec3 position)
	{
		m_ToWorldMatrix = glm::translate(glm::mat4(1), position);
		//send worldMatrix to GPU

	}

	

	void gameObject::Update()
	{
		//Do update stuff to member variables


	}

	void gameObject::Render() const
	{
		//Bind current texture before rendering calll
		m_ptexture->Bind();
		auto TRSmatrix =  m_ToWorldMatrix * m_RotationMatrix * m_ScaleMatrix ;
		Renderer::Submit(m_VertexArray, *m_pRenderingProgram, TRSmatrix);


	}
	/// <SKYBOX>
	/// SKYBOX
	/// </SKYBOX>

	SkyBox::SkyBox()
	{
		m_ResourceManager = ResourceManager::GetInstance();
		m_pRenderingProgram = &m_ResourceManager->GetProgram(TextureTypes::CUBETEXTURE);
		AddMesh("Resources/kubus.obj");
	}

	void SkyBox::AddTexture(const std::string& path)
	{
		m_ptexture = m_ResourceManager->GetTexture(path, TextureTypes::CUBETEXTURE);
		(*m_pRenderingProgram)->SetUniformInt(0, "u_Texture", BaseProgram::ShaderTypes::T_PixelShader);
	}

	void SkyBox::SetPos(glm::vec3 position)
	{
		EU_CORE_ERROR("Translating skybox has no effect!");
	}

	void SkyBox::Update()
	{
		
	}

	void SkyBox::Render() const
	{
		//Bind current texture before rendering calll
		m_ptexture->Bind();
		Renderer::SubmitNoDepth(m_VertexArray, *m_pRenderingProgram, m_RotationMatrix, true);
	}

	void SkyBox::AddMesh(const std::string& path)
	{
		m_VertexArray = m_ResourceManager->GetModel(path);

	}

	}