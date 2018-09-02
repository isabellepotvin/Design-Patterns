#pragma once

#ifndef TIMER_Mgr
#define TIMER_Mgr

#include <vector>
#include "Timer.h"
#include "Player.h"

class TimerMgr
{
public:
	static TimerMgr* GetInstance(); //constructor

	void createTimer(int milliseconds, function<void(Player* player1, Player* player2, vector<NPC*>* gems)> fn, Player* player1, Player* player2, vector<NPC*>* gems);
	void tickTimers();

	std::vector<Timer*> m_timers; //variable

private:
	TimerMgr(); //constructor

	static TimerMgr* m_TimerMgr; //variable
};

#endif
