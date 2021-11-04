#include "Eupch.h"
#include "Mesh.h"
#include <iostream>
#include <fstream>

namespace Eu {

	Mesh::Mesh(const std::string& path)
	{
		OBJParser(path);
	}

	Mesh::~Mesh()
	{
		EU_CORE_INFO("Removing mesh data on cpu");
		m_OBJ.m_VertexBuffer.clear();
		m_OBJ.m_IndexBuffer.clear();
	}

	void Mesh::OBJParser(const std::string& path)
	{
		std::ifstream input;
		std::vector<glm::vec3> vertexVector;
		std::vector<glm::vec2> UVvector;
		std::vector<glm::vec3> normalVector;
		std::vector<glm::vec3> FaceVector;

		input.open(path, std::ios::in);
		std::string strX;
		std::string strY;
		std::string strZ;



		if (input.is_open())
		{
			std::string newLine;
			while (!input.eof())
			{
				std::getline(input, newLine, ' ');

				if (newLine == "#") {
					std::getline(input, newLine, '\n');
					//std::getline(input, newLine, ' ');
				}
				else if (newLine == "f" || newLine.find("f") != std::string::npos) {

					for (size_t i = 0; i < 3; i++)
					{
						//vertex
						std::getline(input, strX, '/');
						std::getline(input, strY, '/');
						std::getline(input, strZ, ' ');

						Vertex_Input vertex{ vertexVector[std::stoi(strX) - 1], glm::vec3{1,1,1}, UVvector[std::stoi(strY) - 1], normalVector[std::stoi(strZ) - 1] };

						auto vetexIt = std::find(m_OBJ.m_VertexBuffer.begin(), m_OBJ.m_VertexBuffer.end(), vertex);



						if (vetexIt != m_OBJ.m_VertexBuffer.end()) {

							m_OBJ.m_IndexBuffer.push_back(static_cast<uint32_t>(std::distance(m_OBJ.m_VertexBuffer.begin(), vetexIt)));

						}
						else {
							m_OBJ.m_VertexBuffer.push_back(vertex);
							m_OBJ.m_IndexBuffer.push_back(int(m_OBJ.m_VertexBuffer.size()) - 1);
						}



					}
					std::getline(input, newLine);//get rest of line

				}
				else if (newLine == "vt" || newLine.find("vt") != std::string::npos) {
					//GetUVCoordinates
					std::getline(input, strX, ' ');
					std::getline(input, strY, ' ');
					std::getline(input, strZ, '\n');
					UVvector.push_back(glm::vec2{ std::stof(strX) , 1 - std::stof(strY) });

				}
				else if (newLine == "vn" || newLine.find("vn") != std::string::npos) {
					//GetNormals
					std::getline(input, strX, ' ');
					std::getline(input, strY, ' ');
					std::getline(input, strZ, '\n');
					normalVector.push_back(glm::vec3{ std::stof(strX) ,std::stof(strY) ,std::stof(strZ) });

				}
				else if (newLine == "v" || newLine.find("v") != std::string::npos) {
					//space
					std::getline(input, newLine, ' ');
					//vertex
					std::getline(input, strX, ' ');
					std::getline(input, strY, ' ');
					std::getline(input, strZ, '\n');
					vertexVector.push_back(glm::vec3(std::stof(strX), std::stof(strY), std::stof(strZ)));

				}
				else {

					std::getline(input, newLine, '\n');
				}



			}
			EU_CORE_TRACE("OBJ file successfully loaded in\n path: {0}\n Vertex amount : {1}",path , m_OBJ.m_VertexBuffer.size());

		}
		else 
			EU_CORE_WARN("PATH NOT FOUND: {0}", path)
	}


}

