#pragma once
#include "BaseComponent.h"
#include <string>
#include <vector>
#include "../Renderer/VertexArray.h"


namespace Eu {


	struct OBJ {
		std::vector<Vertex_Input> m_VertexBuffer;
		std::vector<uint32_t> m_IndexBuffer;
	};
	class MeshComponent : public BaseComponent
	{
	public:
		MeshComponent(const std::string& path);
		MeshComponent() {};
		~MeshComponent();
		void Start() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		const std::shared_ptr<Eu::VertexArray> GetVertexBuffer() const;

		void AddFaceToMesh(std::vector<Vertex_Input>& NewFaces, std::vector<int> newIndices);
		void Clear();

	protected:
		void OBJParser(const std::string& path);
	private:
		void BufferMesh();
	private:
		std::shared_ptr<Eu::VertexArray> m_ChunkVertexArray;
		OBJ m_OBJ;
		bool m_IsParsed{ false };
	};
};
