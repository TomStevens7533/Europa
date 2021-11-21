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
	}

	void BaseGameObject::AddScale(glm::vec3 scale)
	{
	}

	gameObject::gameObject()
	{
		//Create program attach shaders 
		if(m_pRenderingProgram) //default to 2D texture program
			m_pRenderingProgram = &ResourceManager::GetInstance()->GetProgram(TextureTypes::TEXTURE2D);


	}

	void gameObject::AddMesh(const std::string& path)
	{		

		m_VertexArray = &ResourceManager::GetInstance()->GetModel(path);

	}

	void gameObject::AddTexture(const std::string& path, const TextureTypes textureType)
	{
		if (m_ptexture == nullptr)
			m_ptexture = &ResourceManager::GetInstance()->GetTexture(path, textureType);

		if (m_pRenderingProgram == nullptr)
			m_pRenderingProgram = &ResourceManager::GetInstance()->GetProgram(textureType);

			//(*m_pRenderingProgram)->SetUniformInt(0, "u_Texture", BaseProgram::ShaderTypes::T_PixelShader); //this gives opengl error


		//set sampler2D


	}

	void gameObject::SetUVBounds(int wIndex, int HIndex, int colSize, int rowSize)
	{
		if (m_ptexture) {
			glm::vec2 texWidthAndHeight = glm::vec2{ (*m_ptexture)->GetWidth(), (*m_ptexture)->GetHeigh() };
			float texWidth = texWidthAndHeight.x / static_cast<float>(colSize);
			float texHeight = texWidthAndHeight.y / static_cast<float>(rowSize);
			
			 uBounds = { (texWidth * (wIndex)) / texWidthAndHeight.x, ((texWidth * wIndex) + texWidth)/ texWidthAndHeight.x };
			 vBounds = { (texHeight * (HIndex)) / texWidthAndHeight.y, ((texHeight * HIndex) + texHeight) / texWidthAndHeight.y };

			 //(*m_pRenderingProgram)->SetUniformInt(1, "isBoundingUV", BaseProgram::ShaderTypes::T_PixelShader);

			 //isBoundingUVs = true;
		}

		

	}

	void gameObject::AddPos(glm::vec3 position)
	{
		m_Position += position;

	}

	void gameObject::SetPos(glm::vec3 position)
	{
		m_Position = position;

		//send worldMatrix to GPU

	}

	

	void gameObject::Update()
	{
		//Do update stuff to member variablesddd


	}

	void gameObject::Render() const
	{

		glm::mat4 rotMat;
		rotMat = glm::rotate(glm::mat4(1.f), m_RotationVec.x, glm::vec3(1, 0, 0));
		rotMat = glm::rotate(rotMat, m_RotationVec.y, glm::vec3(0, 1, 0));
		rotMat = glm::rotate(rotMat, m_RotationVec.z, glm::vec3(0, 0, 1));

		//Bind current texture before rendering calll
		if (m_ptexture != nullptr) {
			//(*m_ptexture)->Bind();

			if (isBoundingUVs) {
				(*m_pRenderingProgram)->SetUniformVec2(uBounds, "BoundingU", BaseProgram::ShaderTypes::T_VertexShader);
				(*m_pRenderingProgram)->SetUniformVec2(vBounds, "BoundingV", BaseProgram::ShaderTypes::T_VertexShader);
			}
			else {
				(*m_pRenderingProgram)->SetUniformInt(0, "isBoundingUV", BaseProgram::ShaderTypes::T_PixelShader);

			}
		
		}

		if (m_VertexArray != nullptr && m_pRenderingProgram != nullptr)
			Renderer::Submit(*m_VertexArray, *m_pRenderingProgram, glm::translate(glm::mat4(1), m_Position) * rotMat);


	}


	std::shared_ptr<Eu::BaseTexture>* gameObject::m_ptexture = nullptr;

	std::shared_ptr<Eu::VertexArray>* gameObject::m_VertexArray = nullptr;

	const std::shared_ptr<Eu::BaseProgram>* gameObject::m_pRenderingProgram = nullptr;

	/// <SKYBOX>
	/// SKYBOX
	/// </SKYBOX>

	SkyBox::SkyBox()
	{
		m_pRenderingProgram = &ResourceManager::GetInstance()->GetProgram(TextureTypes::CUBETEXTURE);
		AddMesh("Resources/kubus.obj");
	}

	void SkyBox::AddTexture(const std::string& path)
	{
		if(m_ptexture == nullptr)
			m_ptexture = &ResourceManager::GetInstance()->GetTexture(path, TextureTypes::CUBETEXTURE);
		//if (m_pRenderingProgram != nullptr)
			//(*m_pRenderingProgram)->SetUniformInt(0, "u_Texture", BaseProgram::ShaderTypes::T_PixelShader);
	}

	void SkyBox::SetUVBounds(int wIndex, int HIndex, int colSize, int rowSize)
	{

	}

	void SkyBox::SetPos(glm::vec3 position)
	{
		EU_CORE_ERROR("Translating skybox has no effect!");
	}

	void SkyBox::AddPos(glm::vec3 position)
	{

	}

	void SkyBox::Update()
	{
		
	}

	void SkyBox::Render() const
	{
		//Bind current texture before rendering calll
		if (m_ptexture != nullptr)
			(*m_ptexture)->Bind();

		if (m_VertexArray != nullptr && m_pRenderingProgram != nullptr)
			Renderer::SubmitNoDepth(*m_VertexArray, *m_pRenderingProgram, m_TRSMatrix, true);
	}

	void SkyBox::AddMesh(const std::string& path)
	{
		m_VertexArray = &ResourceManager::GetInstance()->GetModel(path);

	}

	std::shared_ptr<Eu::BaseTexture>* SkyBox::m_ptexture = nullptr;

	std::shared_ptr<Eu::VertexArray>* SkyBox::m_VertexArray = nullptr;

	const std::shared_ptr<Eu::BaseProgram>* SkyBox::m_pRenderingProgram = nullptr;

	}