#pragma once
#include "NPC.h"

class Topaz : public NPC
{

public:
	Topaz(int x, int y) {
		m_name = "Topaz";
		m_type = NPCTypes::Topaz;
		m_colour = 14;
		m_ascii = 234;
		m_X = x;
		m_Y = y;
	}
};