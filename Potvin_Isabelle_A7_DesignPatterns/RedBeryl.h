#pragma once
#include "NPC.h"

class RedBeryl : public NPC
{

public:
	RedBeryl(int x, int y) {
		m_name = "RedBeryl";
		m_type = NPCTypes::RedBeryl;
		m_colour = 12;
		m_ascii = 235;
		m_X = x;
		m_Y = y;
	}
};