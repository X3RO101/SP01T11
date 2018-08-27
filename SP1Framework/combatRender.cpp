#include "combatRender.h"

string continueRender;
int ansPasser; // for the answer checker
bool bArray[18]; // bool array for random mob gen so that it doesnt print twice
int mobAnsvvers[18] = { 2, 1, 3, 2, 3, 1, 2, 1, 3, 2, 1, 2, 3, 1, 2, 3, 1, 2 }; // all the answers for the mobs
int cAns; // the correct ans is copied into here
int playerinput; // the input for the ans
int h = 0;
int g = 0; // a and h used as the conditions for the text picker
double totalTime = 0;
double timeForCOrW = 0;
int CORW = 0;

Text mob1;
Text mob2;
Text mob3;
Text mob4;
Text mob5;
Text mob6;
Text mob7;
Text mob8;
Text mob9;
Text mob10;
Text mob11;
Text mob12;
Text mob13;
Text mob14;
Text mob15;
Text mob16;
Text mob17;
Text mob18;

void initMobText(Text * mobNo, ifstream* mobFile)
{
	getline(*mobFile, mobNo->monsterQn); // stores the mob text into the mob object 
}

void COMBAT() // runs when gamestate is in combat
{

	if (h == g)
	{
		textPicker(); // ansPasser is for the array for answers
	}
	spamPrint(); // continuously prints the same line of text for the duration of combat
}

void combatlogic()
{
	inputAns();
	checkAns();
	ansWrong();
}

void spamPrint()
{
	const WORD colors[] = {
		0x1F, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	COORD textCoord;
	textCoord.X = 0;
	textCoord.Y = 35;


	g_Console.writeToBuffer(textCoord, continueRender, colors[0]);
}

void duration(EGAMESTATES * gameState, double dt) // timer for the combat
{
	totalTime += dt;
	if (totalTime > 10.0)
	{
		CORW = 2;
		h = 0;
		isdead = true;
		moveAllow = true;
		*gameState = S_COMBATAFTERMATH;
	}
}

void inputAns()
{
	if (g_abKeyPressed[K_1])
	{
		playerinput = 1;
	}
	if (g_abKeyPressed[K_2])
	{
		playerinput = 2;
	}
	if (g_abKeyPressed[K_3])
	{
		playerinput = 3;
	}
}

void checkAns()
{
	cAns = mobAnsvvers[ansPasser - 1];
	if (playerinput == cAns)
	{
		h = 0;
		playerinput = 0;
		cAns = 0;
		CORW = 1;
		ansPasser = 0;
		moveAllow = true;
		g_eGameState = S_COMBATAFTERMATH;
	}
}

void printCOrW()
{
	string incorrect = "Wrong!";
	string correct = "Correct!";
	const WORD colors[] = {
		0x1F, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	COORD corwCoords;
	corwCoords.X = 0;
	corwCoords.Y = 35;
	// 1 be correct 2 be wrong
	if (CORW == 1)
	{
		g_Console.writeToBuffer(corwCoords, correct, colors[0]);
	}
	if (CORW == 2)
	{
		g_Console.writeToBuffer(corwCoords, incorrect, colors[0]);
	}
}

void stopPrintingCOrW(double dt)
{
	timeForCOrW += dt;
	if (timeForCOrW > 1.0)
	{

		CORW = 0;
		moveAllow = true;
		g_eGameState = S_GAME;
	}
}

void ansWrong()
{
	if (playerinput == 1 || playerinput == 2 || playerinput == 3)
	{
		if (playerinput != cAns)
		{
			h = 0;
			isdead = true;
			playerinput = 0;
			CORW = 2;
			moveAllow = true;
			g_eGameState = S_COMBATAFTERMATH;
		}
	}
}

void textPicker() // randomly picks a mob text to print
{
	srand(time(nullptr));
	ansPasser = rand() % 18 + 1;
	if (bArray[ansPasser - 1])
	{
		switch (ansPasser)
		{
		case 1:
			continueRender = mob1.monsterQn;
			h++;
			break;
		case 2:
			continueRender = mob2.monsterQn;
			h++;
			break;
		case 3:
			continueRender = mob3.monsterQn;
			h++;
			break;
		case 4:
			continueRender = mob4.monsterQn;
			h++;
			break;
		case 5:
			continueRender = mob5.monsterQn;
			h++;
			break;
		case 6:
			continueRender = mob6.monsterQn;
			h++;
			break;
		case 7:
			continueRender = mob7.monsterQn;
			h++;
			break;
		case 8:
			continueRender = mob8.monsterQn;
			h++;
			break;
		case 9:
			continueRender = mob9.monsterQn;
			h++;
			break;
		case 10:
			continueRender = mob10.monsterQn;
			h++;
			break;
		case 11:
			continueRender = mob11.monsterQn;
			h++;
			break;
		case 12:
			continueRender = mob12.monsterQn;
			h++;
			break;
		case 13:
			continueRender = mob13.monsterQn;
			h++;
			break;
		case 14:
			continueRender = mob14.monsterQn;
			h++;
			break;
		case 15:
			continueRender = mob15.monsterQn;
			h++;
			break;
		case 16:
			continueRender = mob16.monsterQn;
			h++;
			break;
		case 17:
			continueRender = mob17.monsterQn;
			h++;
			break;
		case 18:
			continueRender = mob18.monsterQn;
			h++;
			break;
		default:
			continueRender = "test";
			break;
		}
		bArray[ansPasser - 1] = false;
	}
}

