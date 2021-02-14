#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<MMsystem.h>
#include "waitForDefinition.c"

typedef struct
{
	int hr, min, sec;
} TIMER_TIME;

void timerMessage(TIMER_TIME);
TIMER_TIME convertTime(int);
int convertIntoSec(TIMER_TIME);

void main()
{
	int startingSec, sec;
	TIMER_TIME convertedTime, remainingTime, userTime;
	
	while(1)
	{
		// clearing the screen
		system("cls");
		
		// taking user input
		printf("Enter time in the following format:\nHOUR(S) MINUTE(S) SECONDS(S)\n");
		fflush(stdin);
		scanf("%d %d %d", &userTime.hr, &userTime.min, &userTime.sec);
		
		sec = convertIntoSec(userTime);
		
		convertedTime = convertTime(sec);
		
		for(startingSec=sec; startingSec > 0; startingSec--)
		{
			// clearing the screen
			system("cls");
			
			// displaying messages
			timerMessage(convertedTime);
			remainingTime = convertTime(startingSec);
			printf("%d : %d : %d", remainingTime.hr, remainingTime.min, remainingTime.sec);
			
			// waiting for one second...
			waitFor(1000.0);
		}
		
		// playing the time out audio
		PlaySound(TEXT("time_out.wav"), NULL, SND_ASYNC);
		
		// clearing the screen
		system("cls");
		
		//displaying messages
		timerMessage(convertedTime);
		printf("Time is Up!\n");
		printf("Press any key to continue...");
		
		getch();
		PlaySound(NULL, NULL, SND_ASYNC);
	}
}

// function to display the timer message
void timerMessage(TIMER_TIME timerTime)
{
	printf("Timer set for: %d HOUR(S) %d MINUTE(S) %d SECOND(S)\n", timerTime.hr, timerTime.min, timerTime.sec);
}

TIMER_TIME convertTime(int sec)
{
	int finalSec, min, finalMin, hr;
	
	min = sec / 60;
	finalSec = sec % 60;
	hr = min / 60;
	finalMin = min % 60;
	
	TIMER_TIME convertedTime = {hr, finalMin, finalSec};
	
	return convertedTime;
}

int convertIntoSec(TIMER_TIME timerTime)
{
	int sec = (timerTime.hr * 3600) + (timerTime.min * 60) + timerTime.sec;
	
	return sec;
}
