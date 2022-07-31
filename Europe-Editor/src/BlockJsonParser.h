#pragma once
#include <DirectXMath.h>
#include <vector>
#include <string>
#include "Minecraft/BlockStruct.h"
#include <map>
#include <glm/glm.hpp>


class ParserException : public std::runtime_error
{
public:
	~ParserException() {}
	ParserException(const std::string msg)
		: std::runtime_error(msg)
	{}
};

struct BlockInformation {
	std::string name;
	bool IsSolid;
	bool IsCube;
	std::map< Faces, std::vector<glm::vec2>> uvCoords;
};
class BaseTexture;
class BlockJsonParser 
{
public:
	BlockJsonParser() = default;
	BlockJsonParser(std::wstring path) { ParseFile(path); }
	const std::map< Faces, std::vector<glm::vec2>>* GetUVOfType(uint8_t id) const;
	bool IsSolid(uint8_t id) const;
	bool IsCube(uint8_t id) const;
	std::string GetName(uint8_t id);

	void ParseFile(std::wstring path);
private:
	std::shared_ptr<Eu::BaseTexture>  m_pTextureAtlas;
	std::map<uint8_t, BlockInformation> m_BlockMap;=
};