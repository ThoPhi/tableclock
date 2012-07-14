/*//////////////////////////////////*/
//
//
//
//
//
//
/*/////////////////////////////////*/
#ifndef _RACE_H_
#define _RACE_H_

#define MAX_PLAYER		20
#define STORAGE_BYTE	3
#define MAX_ROUND		3
//define status
#define START			0
#define BEGIN			1
#define COUNT_DOWN		2
#define FINISH			10
#define FINISH1			11
#define FINISH2			12
#define TIMEOUT			13

#define READY			20
#define STOP			21
#define	RUNNING			30
#define LAP1			31
#define	LAP2			32
#define LAP3			33
#define LAP4			34


//declare variable
extern volatile unsigned char RaceStatus;
extern volatile unsigned int DelayTime;
extern volatile unsigned char Lap;

extern unsigned char StorageResult[MAX_PLAYER][STORAGE_BYTE] ;

extern unsigned char Player;
//declare function
void init_race();
void racing();
#endif
