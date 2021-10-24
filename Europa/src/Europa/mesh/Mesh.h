#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "../structs.h"


namespace Eu {
	struct OBJ {
		std::vector<Vertex_Input> m_VertexBuffer;
		std::vector<uint32_t> m_IndexBuffer;
	};




	class Mesh
	{
	public:
		Mesh(const std::string& path);
		~Mesh();

		inline std::vector<Vertex_Input>& GetVertexBuffer() { return m_OBJ.m_VertexBuffer; }
		inline std::vector<uint32_t>& GetIndexBuffer() { return m_OBJ.m_IndexBuffer; }




	private:


	private:
		void OBJParser(const std::string& path);
		OBJ m_OBJ;
	};

}


