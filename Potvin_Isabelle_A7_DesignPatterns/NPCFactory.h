#pragma once

#include "NPC.h"
#include "Tanzanite.h"
#include "Topaz.h"
#include "Musgravite.h"
#include "RedBeryl.h"
#include "Diamond.h"
#include "Jade.h"


class NPCFactory
{
public:
	static NPCFactory* GetInstance();
	NPC* createNPC(NPCTypes type, int x, int y);

private:
	NPCFactory(); //constructor
	static NPCFactory* m_NPCFactory; //variable


};