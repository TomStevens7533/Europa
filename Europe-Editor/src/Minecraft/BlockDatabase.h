#pragma once
#include <glm/glm.hpp>
#include "BlockStruct.h"
#include <array>

enum class MeshType
{
	Solid = 0,
	Flora = 1,
	Liquid = 2,
};

enum class MeshStyle
{
	Block = 0,
	XStyle = 1
};

enum class State
{
	Solid = 0,
	Liquid = 1,
	Gas = 2
};
class BaseEntity {
public:
	virtual glm::vec2* GetUV(Faces face) = 0;
	bool isCube() const { return m_MeshStyle == MeshStyle::Block; }
	bool isSolid() const { return m_MeshType == MeshType::Solid; }
protected:
	MeshType m_MeshType;
	MeshStyle m_MeshStyle;
	State m_State;
};
//---------------------BLOCKS-----------------------------
class BaseBlock : public BaseEntity
{
	virtual glm::vec2* GetUV(Faces face) override;

protected:
	std::array<glm::vec2, 4> TOP;
	std::array<glm::vec2, 4> BOT;
	std::array<glm::vec2, 4> BACK;
	std::array<glm::vec2, 4> FRONT;
	std::array<glm::vec2, 4> LEFT;
	std::array<glm::vec2, 4> RIGHT;
};

class Dirt : public BaseBlock
{
public:
	Dirt();
};
class Grass : public BaseBlock
{
public:
	Grass();
};
class Stone : public BaseBlock
{
public:
	Stone();
};
class OakLog : public BaseBlock
{
public:
	OakLog();
};
class Water : public BaseBlock
{
public:
	Water();
};
class Leaves : public BaseBlock
{
public:
	Leaves();
};
//--------------------NONBLOCKS---------------------------
class NonBlock : public BaseEntity
{
public:
	virtual glm::vec2* GetUV(Faces face) override;

protected:
	std::array<glm::vec2, 4> m_UV;
};

class Rose : public NonBlock
{
public:
	Rose();
};


class Tulip : public NonBlock
{
public:
	Tulip();
};


class Azure : public NonBlock
{
public:
	Azure();
};

