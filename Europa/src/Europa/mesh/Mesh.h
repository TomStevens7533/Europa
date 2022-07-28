#pragma once
#include <string>
#include <glm/glm.hpp>


namespace Eu {
	




	class Mesh
	{
	public:
		Mesh(const std::string& path);
		Mesh() = default; //Create Empty mesh object
		~Mesh();

		inline std::vector<Vertex_Input>& GetVertexBuffer() { return m_OBJ.m_VertexBuffer; }
		inline std::vector<uint32_t>& GetIndexBuffer() { return m_OBJ.m_IndexBuffer; }

		void AddFaceToMesh(std::vector<Vertex_Input>& NewFaces, std::vector<int> newIndices);
		void Clear();

	private:


	private:
		void OBJParser(const std::string& path);
		OBJ m_OBJ;
	};

}


