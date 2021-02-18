#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<MMsystem.h>
#include<stdlib.h>
#include "waitForDefinition.c"

typedef struct TimerTime
{
	int hr, min, sec;
} TIMER_TIME;

// global variables
char selected_alarm_tone[25]="assets/alarm_tone_1.wav";
FILE *alarm_fp;

// functions declaration(s)
void timerMessage(TIMER_TIME);
TIMER_TIME convertTime(int);
int convertIntoSec(TIMER_TIME);
void clearScreen(void);
// UI functions
void startMenu(void);
void alarmMenu(void);

void main()
{
	int startingSec, sec;
	TIMER_TIME convertedTime, remainingTime, userTime;
	
	alarm_fp = fopen("alarm_tone.data", "r");
	if(alarm_fp == NULL)
		puts("Something went wrong while loading data!");
	else
	{
		fscanf(alarm_fp, "%s", &selected_alarm_tone);
		fclose(alarm_fp);
	}
	
	startMenu();
	
	while(1)
	{
		while(1)
		{
			// clearing the screen
			clearScreen();
			
			// taking user input
			printf("Enter time in the following format:\nHOUR(S) MINUTE(S) SECONDS(S)\nFor Start Menu, enter -1 -1 -1\n");
			fflush(stdin);
			scanf("%d %d %d", &userTime.hr, &userTime.min, &userTime.sec);
			
			if(userTime.hr < 0 || userTime.min < 0 || userTime.sec < 0)
			{
				startMenu();
				continue;
			}
			else
				break;
		}
		sec = convertIntoSec(userTime);
		
		convertedTime = convertTime(sec);
		
		for(startingSec=sec; startingSec>0; startingSec--)
		{
			// clearing the screen
			clearScreen();
			
			// displaying messages
			timerMessage(convertedTime);
			remainingTime = convertTime(startingSec);
			printf("%d : %d : %d", remainingTime.hr, remainingTime.min, remainingTime.sec);
			
			// waiting for one second...
			waitFor(1000.0);
		}
		
		// playing the time out audio
		PlaySound(TEXT(selected_alarm_tone), NULL, SND_ASYNC);
		
		// clearing the screen
		clearScreen();
		
		//displaying messages
		timerMessage(convertedTime);
		printf("Time is Up!\n");
		printf("Press any key to continue...");
		
		getch();
		PlaySound(NULL, NULL, SND_ASYNC);
	}
}

// start menu function
void startMenu()
{
	short int userInput;
	
	while(1)
	{
		// clearing the screen
		clearScreen();
		
		// taking user input
		printf("Hey there! Welcome to Countdown Timer!\nPlease type an option number and press Enter\n");
		printf("1) Set Timer\n2) Change Tone\n3) Quit\n");
		scanf("%d", &userInput);
		
		if(userInput == 1)
		{
			return;
		}
		else if(userInput == 2)
		{
			alarmMenu();
		}
		else if(userInput == 3)
		{
			exit(0);
		}
		else
		{
			puts("Invalid Option! Please choose an option between 1 and 3 (inclusive). Press any key to continue...");
			getch();
		}
		
	}
}

// alarm tone UI function
void alarmMenu()
{
	short int userInput;
	
	while(1)
	{
		// clearing the screen
		clearScreen();
		
		// taking user input
		printf("Please select an alarm tone (Choose 4 to go BACK)\n");
		printf("1) Alarm Tone 1\n2) Alarm Tone 2\n3) Alarm Tone 3\n");
		scanf("%d", &userInput);
		
		if(userInput == 1)
		{
			strcpy(selected_alarm_tone, "assets/alarm_tone_1.wav");
		}
		else if(userInput == 2)
		{
			strcpy(selected_alarm_tone, "assets/alarm_tone_2.wav");
		}
		else if(userInput == 3)
		{
			strcpy(selected_alarm_tone, "assets/alarm_tone_3.wav");
		}
		else if(userInput == 4)
		{
			return;
		}
		else
		{
			puts("Invalid Option! Please choose an option between 1 and 3 (inclusive). Press any key to continue...");
			getch();
			continue;
		}
		
		printf("Saving..");
		
		alarm_fp = fopen("alarm_tone.data", "w");
		if(alarm_fp == NULL)
			puts("Something went wrong while saving data!");
		else
		{
			fprintf(alarm_fp, "%s", selected_alarm_tone);
			fclose(alarm_fp);
		}
		
		clearScreen();
		
		puts("Alarm tone successfully set! Press any key to continue...");
		getch();
		return;
		
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

void clearScreen()
{
	system("cls");
}
