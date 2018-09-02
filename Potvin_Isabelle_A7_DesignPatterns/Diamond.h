#pragma once
#include "NPC.h"

class Diamond : public NPC
{

public:
	Diamond(int x, int y) {
		m_name = "Diamond";
		m_type = NPCTypes::Diamond;
		m_colour = 15;
		m_ascii = 235;
		m_X = x;
		m_Y = y;
	}
};