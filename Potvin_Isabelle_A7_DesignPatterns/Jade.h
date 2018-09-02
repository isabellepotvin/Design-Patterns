#pragma once
#include "NPC.h"

class Jade : public NPC
{

public:
	Jade(int x, int y) {
		m_name = "Jade";
		m_type = NPCTypes::Jade;
		m_colour = 10;
		m_ascii = 232;
		m_X = x;
		m_Y = y;
	}
};