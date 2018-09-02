#pragma once
#include "NPC.h"

class Musgravite : public NPC
{

public:
	Musgravite(int x, int y) {
		m_name = "Musgravite";
		m_type = NPCTypes::Musgravite;
		m_colour = 5;
		m_ascii = 232;
		m_X = x;
		m_Y = y;
	}
};