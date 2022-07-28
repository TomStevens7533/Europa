#include "MeshRenderComponent.h"
#include "MeshComponent.h"
#include "../GameObject.h"
#include "../ResourceManager.h"
#include "../Renderer/Renderer.h"
using namespace Eu;

Eu::MeshRenderComponent::MeshRenderComponent()
{

}

Eu::MeshRenderComponent::~MeshRenderComponent()
{

}

void Eu::MeshRenderComponent::Start()
{
	m_pMeshComp = GetAttachedGameObject()->GetComponent<MeshComponent>();
	m_pModelProgram = ResourceManager::GetInstance()->GetProgram(ShaderType::TEXTURE2D_WORLDSPACE_SHADER);
}

void Eu::MeshRenderComponent::Update()
{
}

void Eu::MeshRenderComponent::FixedUpdate()
{
}

void Eu::MeshRenderComponent::Render() const
{
	Renderer::Submit(m_pMeshComp->GetVertexBuffer(), m_pModelProgram, GetAttachedGameObject()->GetTransform().GetWorld());
}
