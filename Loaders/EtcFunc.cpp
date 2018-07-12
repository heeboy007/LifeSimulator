#include"EtcFunc.h"

bool Clock::passed()
{
	if(total == time(0))
	{
		return false;
	}
	else
	{
		total = time(0);
		return true;
	}
}

void Clock::clockinit()
{
	total = time(0);
	std::cout << "Clock::clockinit() Called" << std::endl;
}

int Random::seed = 0;

int Random::pickInRadius(int pick)
{
	//srand(2);
	return rand() % pick;
}

int Random::intInRange(int pick, int index)
{
	if(Random::seed >= 2147483000)
		Random::seed = 0;
	Random::seed++;
	srand(time(0) + index);
	//srand(time(0));
	m_randEngine = std::mt19937(time(0) - Random::seed);
	//m_randEngine = std::mt19937(time(0));
	std::uniform_int_distribution<int> dist(0, pick);
	return (dist(m_randEngine) + rand()) % pick;
}

short Random::s_pickInRadius(short pick, int seed)
{
	srand(time(0));
	return rand() % pick + 1;
}
