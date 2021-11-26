#include "BlockDatabase.h"
//------------GETUV-------------

glm::vec2* BaseBlock::GetUV(Faces face)
{
	switch (face)
	{
	case Faces::TOP:
		return &(TOP[0]);
		break;
	case Faces::BOT:
		return &(BOT[0]);
		break;
	case Faces::LEFT:
		return &(LEFT[0]);
		break;
	case Faces::RIGHT:
		return &(RIGHT[0]);
		break;
	case Faces::FRONT:
		return &(FRONT[0]);
		break;
	case Faces::BACK:
		return &(LEFT[0]);
		break;
	default:
		break;
	}
}


//BLOCK TYPES
Dirt::Dirt()
{
	TOP =	{ glm::vec2{0.25f, 0.f},  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.5f, 0.25f },  glm::vec2{ 0.5f, 0.0f } };
	BOT =	{ glm::vec2{0.25f, 0.f},  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.5f, 0.25f },  glm::vec2{ 0.5f, 0.0f } };
	BACK =	{ glm::vec2{0.25f, 0.f},  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.5f, 0.25f },  glm::vec2{ 0.5f, 0.0f } };
	FRONT =	{ glm::vec2{0.25f, 0.f},  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.5f, 0.25f },  glm::vec2{ 0.5f, 0.0f } };
	LEFT =	{ glm::vec2{0.25f, 0.f},  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.5f, 0.25f },  glm::vec2{ 0.5f, 0.0f } };
	RIGHT =	{ glm::vec2{0.25f, 0.f},  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.5f, 0.25f },  glm::vec2{ 0.5f, 0.0f } };

	m_MeshType = MeshType::Solid;
	m_MeshStyle = MeshStyle::Block;
	m_State = State::Solid;

}



Grass::Grass()
{
	TOP =	{ glm::vec2{0.5f, 0.f},  glm::vec2{ 0.5f, 0.25f },  glm::vec2{ 0.75f, 0.25f },  glm::vec2{ 0.75f, 0.0f } };
	BOT =	{ glm::vec2{0.25f, 0.f},  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.5f, 0.25f },  glm::vec2{ 0.5f, 0.0f } };
	BACK =	{ glm::vec2{ 0.75f, 0.25f },   glm::vec2{ 1.f, 0.25f },  glm::vec2{1.f, 0.f},   glm::vec2{ 0.75f, 0.f } };
	FRONT = { glm::vec2{ 0.75f, 0.25f },   glm::vec2{ 1.f, 0.25f },  glm::vec2{1.f, 0.f},   glm::vec2{ 0.75f, 0.f } };
	LEFT =	{ glm::vec2{ 0.75f, 0.25f },   glm::vec2{ 1.f, 0.25f },  glm::vec2{1.f, 0.f},   glm::vec2{ 0.75f, 0.f } };
	RIGHT =	{ glm::vec2{ 0.75f, 0.25f },   glm::vec2{ 1.f, 0.25f },  glm::vec2{1.f, 0.f},   glm::vec2{ 0.75f, 0.f } };

	m_MeshType = MeshType::Solid;
	m_MeshStyle = MeshStyle::Block;
	m_State = State::Solid;
}
OakLog::OakLog()
{
	TOP =	{ glm::vec2{0.75f, 0.75f},  glm::vec2{ 0.75f, 1.f },  glm::vec2{ 1.f, 1.f },  glm::vec2{ 1.f, 0.75f } };
	BOT =	{ glm::vec2{0.75f, 0.75f},  glm::vec2{ 0.75f, 1.f },  glm::vec2{ 1.f, 1.f },  glm::vec2{ 1.f, 0.75f } };
	BACK =	{ glm::vec2{0.5f, 0.75f},  glm::vec2{ 0.5f, 1.f },  glm::vec2{ 0.75f, 1.f },  glm::vec2{ 0.75f, 0.75f } };
	FRONT = { glm::vec2{0.5f, 0.75f},  glm::vec2{ 0.5f, 1.f },  glm::vec2{ 0.75f, 1.f },  glm::vec2{ 0.75f, 0.75f } };
	LEFT =	{ glm::vec2{0.5f, 0.75f},  glm::vec2{ 0.5f, 1.f },  glm::vec2{ 0.75f, 1.f },  glm::vec2{ 0.75f, 0.75f } };
	RIGHT = { glm::vec2{0.5f, 0.75f},  glm::vec2{ 0.5f, 1.f },  glm::vec2{ 0.75f, 1.f },  glm::vec2{ 0.75f, 0.75f } };

	m_MeshType = MeshType::Solid;
	m_MeshStyle = MeshStyle::Block;
	m_State = State::Solid;
}

Stone::Stone()
{
	TOP = { glm::vec2{0.0f, 0.f},  glm::vec2{ 0.0f, 0.25f },  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.25f, 0.0f } };
	BOT = { glm::vec2{0.0f, 0.f},  glm::vec2{ 0.0f, 0.25f },  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.25f, 0.0f } };
	BACK = { glm::vec2{0.0f, 0.f},  glm::vec2{ 0.0f, 0.25f },  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.25f, 0.0f } };
	FRONT = { glm::vec2{0.0f, 0.f},  glm::vec2{ 0.0f, 0.25f },  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.25f, 0.0f } };
	LEFT = { glm::vec2{0.0f, 0.f},  glm::vec2{ 0.0f, 0.25f },  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.25f, 0.0f } };
	RIGHT = { glm::vec2{0.0f, 0.f},  glm::vec2{ 0.0f, 0.25f },  glm::vec2{ 0.25f, 0.25f },  glm::vec2{ 0.25f, 0.0f } };

	m_MeshType = MeshType::Solid;
	m_MeshStyle = MeshStyle::Block;
	m_State = State::Solid;
}

Water::Water()
{
	TOP =	{ glm::vec2{0.25f, 0.25f},  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.5f, 0.5f },  glm::vec2{ 0.5f, 0.25f } };
	BOT =	{ glm::vec2{0.25f, 0.25f},  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.5f, 0.5f },  glm::vec2{ 0.5f, 0.25f } };
	BACK =	{ glm::vec2{0.25f, 0.25f},  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.5f, 0.5f },  glm::vec2{ 0.5f, 0.25f } };
	FRONT = { glm::vec2{0.25f, 0.25f},  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.5f, 0.5f },  glm::vec2{ 0.5f, 0.25f } };
	LEFT =	{ glm::vec2{0.25f, 0.25f},  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.5f, 0.5f },  glm::vec2{ 0.5f, 0.25f } };
	RIGHT = { glm::vec2{0.25f, 0.25f},  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.5f, 0.5f },  glm::vec2{ 0.5f, 0.25f } };


	m_MeshType = MeshType::Solid;
	m_MeshStyle = MeshStyle::Block;
	m_State = State::Solid;
}

Rose::Rose()
{
	m_UV = { glm::vec2{0.25f, 0.75f},  glm::vec2{ 0.5f, 0.75f },  glm::vec2{ 0.5f, 0.5f },  glm::vec2{ 0.25f, 0.5f } };

	m_MeshType = MeshType::Flora;
	m_MeshStyle = MeshStyle::XStyle;
	m_State = State::Solid;
}

glm::vec2* NonBlock::GetUV(Faces face)
{
	return &(m_UV[0]);
}

Tulip::Tulip()
{
	m_UV = { glm::vec2{0.5f, 0.75f},  glm::vec2{ 0.75f, 0.75f },  glm::vec2{ 0.75f, 0.5f },  glm::vec2{ 0.5f, 0.5f } };

	m_MeshType = MeshType::Flora;
	m_MeshStyle = MeshStyle::XStyle;
	m_State = State::Solid;
}

Azure::Azure()
{
	m_UV = { glm::vec2{0.75f, 0.75f},  glm::vec2{ 1.f, 0.75f },  glm::vec2{ 1.f, 0.5f },  glm::vec2{ 0.75f, 0.5f } };

	m_MeshType = MeshType::Flora;
	m_MeshStyle = MeshStyle::XStyle;
	m_State = State::Solid;
}

Leaves::Leaves()
{
	TOP =	 { glm::vec2{0.0f, 0.25f},  glm::vec2{ 0.0f, 0.5f },  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.25f, 0.25f } };
	BOT =	 { glm::vec2{0.0f, 0.25f},  glm::vec2{ 0.0f, 0.5f },  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.25f, 0.25f } };
	BACK =	 { glm::vec2{0.0f, 0.25f},  glm::vec2{ 0.0f, 0.5f },  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.25f, 0.25f } };
	FRONT =	 { glm::vec2{0.0f, 0.25f},  glm::vec2{ 0.0f, 0.5f },  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.25f, 0.25f } };
	LEFT =	 { glm::vec2{0.0f, 0.25f},  glm::vec2{ 0.0f, 0.5f },  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.25f, 0.25f } };
	RIGHT =  { glm::vec2{0.0f, 0.25f},  glm::vec2{ 0.0f, 0.5f },  glm::vec2{ 0.25f, 0.5f },  glm::vec2{ 0.25f, 0.25f } };

	m_MeshType = MeshType::Flora;
	m_MeshStyle = MeshStyle::Block;
	m_State = State::Solid;
}
