#include "Timer.h"

//constructor
Timer::Timer(int milliseconds, unsigned int currentTime, function<void(Player* player1, Player* player2, vector<NPC*>* gems)> fn, Player* player1, Player* player2, vector<NPC*>* gems)
{
	m_interval = milliseconds;
	m_callback = fn;
	m_startTime = currentTime;
	m_player1 = player1;
	m_player2 = player2;
	m_gems = gems;
}

bool Timer::tick(unsigned int currentTime)
{
	if (currentTime - m_startTime >= m_interval) //if the timer is done
	{
		m_callback(m_player1, m_player2, m_gems);
		return true;
	}
	return false; //if the timer is not done
}
