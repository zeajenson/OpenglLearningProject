#pragma once
#include <ctime>


class OutputTimer
{
public:
	OutputTimer();
	~OutputTimer();
	void startTimer();
	double getElapsedTime();
	void resetTimer();
private:
	double startTime;
};

