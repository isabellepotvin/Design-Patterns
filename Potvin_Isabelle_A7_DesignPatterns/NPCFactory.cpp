#include "NPCFactory.h"

NPCFactory* NPCFactory::m_NPCFactory = 0;

NPCFactory* NPCFactory::GetInstance()
{
	if (m_NPCFactory == 0)
		m_NPCFactory = new NPCFactory();
	return m_NPCFactory;
}

NPCFactory::NPCFactory(){} //constructor

NPC* NPCFactory::createNPC(NPCTypes type, int x, int y)
{
	switch (type)
	{
	case NPCTypes::Tanzanite:
		return new Tanzanite(x, y);
		break;
	case NPCTypes::Topaz:
		return new Topaz(x, y);
		break;
	case NPCTypes::Musgravite:
		return new Musgravite(x, y);
		break;
	case NPCTypes::RedBeryl:
		return new RedBeryl(x, y);
		break;
	case NPCTypes::Diamond:
		return new Diamond(x, y);
		break;
	case NPCTypes::Jade:
		return new Jade(x, y);
		break;
	default:
		break;
	}
}