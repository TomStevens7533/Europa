#pragma once
#include "BaseComponent.h"
#include <memory>

namespace Eu {
	class MeshComponent;
	class BaseProgram;
	class MeshRenderComponent : public BaseComponent
	{
	public:
		MeshRenderComponent();
		~MeshRenderComponent();


		void Start() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

	private:
		MeshComponent* m_pMeshComp;
		std::shared_ptr<Eu::BaseProgram> m_pModelProgram{};
	};

}

