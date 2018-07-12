#ifndef ETCFUNC_H
#define ETCFUNC_H

#include<ctime>
#include<cstdlib>
#include<iostream>
#include<random>

class Clock
{
protected:
	
	int total;
	
	bool passed();
	void clockinit();
	
};

class Random
{
public:
	
	static short s_pickInRadius(short pick, int seed);
	static int seed;
	
protected:
	
	std::mt19937 m_randEngine;
	int pickInRadius(int pick);
	int intInRange(int pick, int index);
	
};

#endif // ETCFUNC_H
