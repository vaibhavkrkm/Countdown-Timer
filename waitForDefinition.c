#include<time.h>

void waitFor(float timer)
{
	clock_t initialTime;
	
	initialTime = clock();
	
	while(clock() - initialTime < timer);
}
