#include "OutputTimer.h"


OutputTimer::OutputTimer()
{
	this->startTime = 0;
}


OutputTimer::~OutputTimer()
{
}

void OutputTimer::startTimer() {
	this->startTime = (double)clock();
}

double OutputTimer::getElapsedTime() {
	double outputTime = ((double)clock() - this->startTime);
	return outputTime;
}

void OutputTimer::resetTimer() {
	this->startTime = (double)clock();
}