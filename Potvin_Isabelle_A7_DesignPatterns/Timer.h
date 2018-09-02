#pragma once

#ifndef TIMER
#define TIMER

#include <functional>
#include <time.h>
#include "Player.h"
#include "NPC.h"

using std::function;

class Timer
{
public:
	Timer(int milliseconds, unsigned int currentTime, function<void(Player* player1, Player* player2, vector<NPC*>* gems)> fn, Player* player1, Player* player2, vector<NPC*>* gems); //constructor
	bool tick(unsigned int currentTime);

	//variables
	Player* m_player1;
	Player* m_player2;
	vector<NPC*>* m_gems;

private:

	//variables
	std::function<void(Player* player1, Player* player2, vector<NPC*>* gems)> m_callback;
	unsigned int m_startTime;
	unsigned int m_interval;
};

#endif
