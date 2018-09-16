#include "time.hpp"
#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include <ctime>

WatchTime::WatchTime(const TimeRep& initTime)
{
	time = initTime;
	minInterval = 0;
	secondsAdj = 0;
	std::time(&lastTime);
}

std::string WatchTime::getTime()
{
	std::ostringstream hours, minutes;
	hours << ((time.hours % 12) + 1);
	minutes << time.minutes;
	std::string retStr = hours.str() + ":" + minutes.str();
	if(time.hours >= 12) {
		retStr.append("PM");
	} else {
		retStr.append("AM");
	}
	return retStr;
}

void WatchTime::tick()
{
	unsigned seconds = (((std::clock() / CLOCKS_PER_SEC) + secondsAdj) % 86400);
	time.minutes = seconds / 60;
	time.hours = seconds / 3600;
}
