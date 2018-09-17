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
	tick();
	std::ostringstream hours, minutes;
	if(time.hours % 12 == 0) {
		hours << 12;
	}
	else {
		hours << (time.hours % 12);
	}
	minutes << time.minutes;
	std::string retStr;
	if((time.hours % 12 > 0) && (time.hours % 12 < 10)) {
		retStr.append(" " + hours.str() + ":");
	}
	else {
		retStr.append(hours.str() + ":");
	}
	if(time.minutes < 10) {
		retStr.append("0" + minutes.str());
	}
	else {
		retStr.append(minutes.str());
	}
	if(time.hours >= 12) {
		retStr.append("PM");
	} else {
		retStr.append("AM");
	}
	return retStr;
}

void WatchTime::tick()
{
	unsigned seconds = (((std::clock() / CLOCKS_PER_SEC * 500) + secondsAdj) % 86400);
	//unsigned seconds = (((std::clock() / CLOCKS_PER_SEC) + secondsAdj) % 86400);
	time.minutes = seconds / 60 % 60;
	time.hours = seconds / 3600 % 24;
}
