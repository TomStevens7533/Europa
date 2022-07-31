#include "MeshRenderComponent.h"
#include "MeshComponent.h"
#include "../GameObject.h"
#include "../ResourceManager.h"
#include "../Renderer/Renderer.h"
#include "../BaseMaterial.h"
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
}

void Eu::MeshRenderComponent::Update()
{
	m_pMaterial->UpdateMaterialVariables();
}

void Eu::MeshRenderComponent::FixedUpdate()
{
}

void Eu::MeshRenderComponent::Render() const
{
	auto comp = (m_pMeshComp->GetVertexBuffer());
	if (comp != nullptr) {
		Renderer::Submit(m_pMeshComp->GetVertexBuffer(), m_pMaterial, GetAttachedGameObject()->GetTransform().GetWorld());

	}
}

void MeshRenderComponent::SetMaterial(std::shared_ptr<Eu::BaseMaterial> mat)
{
	m_pMaterial = mat;
}
