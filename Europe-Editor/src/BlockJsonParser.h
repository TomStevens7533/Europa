#pragma once
#include <DirectXMath.h>
#include <vector>
#include <string>
#include "Minecraft/BlockStruct.h"
#include <map>
#include <glm/glm.hpp>
#include <memory>
#include <exception>
namespace Eu { class BaseTexture; }


class ParserException : public std::exception
{
public:
	~ParserException() {}
	ParserException(const std::string msg)
		: std::exception(msg.c_str())
	{}
};

struct BlockInformation {
	std::string name;
	bool IsSolid;
	bool IsCube;
	std::map< Faces, std::vector<glm::vec2>> uvCoords;
};
class BlockJsonParser 
{
public:
	BlockJsonParser(const BlockJsonParser& other) = delete;
	BlockJsonParser(BlockJsonParser&& other) noexcept = delete;
	BlockJsonParser& operator=(const BlockJsonParser& other) = delete;
	BlockJsonParser& operator=(BlockJsonParser&& other) noexcept = delete;
public:
	static std::shared_ptr<BlockJsonParser> GetInstance();
	BlockJsonParser(std::wstring path) { ParseFile(path); }
	const std::vector<glm::vec2>* GetUVOfType(uint8_t id, Faces face) const;
	bool IsSolid(uint8_t id) const;
	bool IsCube(uint8_t id) const;
	std::string GetName(uint8_t id);

	void ParseFile(std::wstring path);
private:
	std::shared_ptr<Eu::BaseTexture>  m_pTextureAtlas;
	std::map<uint8_t, BlockInformation> m_BlockMap;
	static std::shared_ptr<BlockJsonParser> m_BlockResources;
};