#pragma once
#include "NPC.h"

class Tanzanite : public NPC
{

public:
	Tanzanite(int x, int y) {
		m_name = "Tanzanite";
		m_type = NPCTypes::Tanzanite;
		m_colour = 9;
		m_ascii = 234;
		m_X = x;
		m_Y = y;
	}
};