#ifndef _TIME_HPP
#define _TIME_HPP

#include <string>

// Expected to be military time
struct TimeRep
{
	unsigned hours, minutes;
};

class WatchTime
{
	TimeRep time;
	unsigned secondsAdj; // second adjust for time after 0:00
	unsigned short minInterval;
	time_t newTime;
	time_t lastTime;
public:
	WatchTime(const TimeRep& initTime);
	std::string getTime();
	void tick();
};

#endif // _TIME_HPP
