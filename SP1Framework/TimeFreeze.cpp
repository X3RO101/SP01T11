#include "TimeFreeze.h"

bool timeFreeze( Text * Mob /*, int * HP  */) // run infinitely until timer runs out
{
	CStopWatch time; // this makes a stopwatch
	time.startTimer(); //start stopwatch
	double durationPassed = time.getElapsedTime(); // gets the time that has passed
	durationPassed += time.getElapsedTime(); // keeps updating the time passed
	if ( durationPassed > 10.0)
	{
		//*HP--;
		//x = false;
	}
    if (/*userInput == */ Mob->correctAns) // when player gets it correct
	{
		//x = false;
		//change gamestate back
	}
	else if (/*userInput != */ Mob->correctAns) //when they input wrong answer
	{
		//*HP--;
	}
	//return x;
	return true;
}