#include "TimerMgr.h"

TimerMgr* TimerMgr::m_TimerMgr = 0;

TimerMgr* TimerMgr::GetInstance()
{
	if (m_TimerMgr == 0) //if a timer manager does not already exist
		m_TimerMgr = new TimerMgr();
	return m_TimerMgr; //if it does exist
}

TimerMgr::TimerMgr()
{

}

void TimerMgr::createTimer(int milliseconds, function<void(Player* player1, Player* player2, vector<NPC*>* gems)> fn, Player* player1, Player* player2, vector<NPC*>* gems)
{
	Timer *timer = new Timer(milliseconds, clock(), fn, player1, player2, gems);
	m_timers.push_back(timer);
}

void TimerMgr::tickTimers()
{
	for (int i = 0; i < m_timers.size(); i++)
	{
		if (m_timers[i]->tick(clock())) //if the timer is done
		{
			delete m_timers[i];
			m_timers.erase(m_timers.begin() + i);
			i--;
		}
	}
}