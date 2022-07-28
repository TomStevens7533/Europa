#pragma once
#include "BaseComponent.h"
#include <string>
#include <vector>
#include "../structs.h"

namespace Eu {
	class MeshComponent : public BaseComponent
	{
	public:
		MeshComponent(const std::string& path);
		~MeshComponent();
		void Start() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		inline std::vector<Vertex_Input>& GetVertexBuffer() { return m_OBJ.m_VertexBuffer; }
		inline std::vector<uint32_t>& GetIndexBuffer() { return m_OBJ.m_IndexBuffer; }

		void AddFaceToMesh(std::vector<Vertex_Input>& NewFaces, std::vector<int> newIndices);
		void Clear();

	protected:
		void OBJParser(const std::string& path);
	private:
		OBJ m_OBJ;
		bool m_IsParsed{ false };
	};
};
