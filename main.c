#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<MMsystem.h>
#include "waitForDefinition.c"

void timerMessage(int);

void main()
{
	int startingSec, sec;
	while(1)
	{
		system("cls");
		printf("Enter the number of seconds for the timer: ");
		scanf("%d", &sec);
		fflush(stdin);
		
		for(startingSec=sec; startingSec > 0; startingSec--)
		{
			// clearing the screen
			system("cls");
			
			// displaying messages
			timerMessage(sec);
			printf("SECONDS REMAINING: %d", startingSec);
			
			// waiting for one second...
			waitFor(1000.0);
		}
		
		// playing the time out audio
		PlaySound(TEXT("time_out.wav"), NULL, SND_ASYNC);
		
		// clearing the screen
		system("cls");
		
		//displaying messages
		timerMessage(sec);
		printf("Time is Up!\n");
		printf("Press any key to continue...");
		
		getch();
		PlaySound(NULL, NULL, SND_ASYNC);
	}
}

// function to display the timer message
void timerMessage(int sec)
{
	printf("Timer set for: %d seconds\n", sec);
}
