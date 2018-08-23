// This is the main file for the game logic and function
//
//
#include "game.h"


bool bArray[18];

void textRender();

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>




double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;

string texty;
//string whichText(string *output, bool *boolArray);
bool disablemovement(EGAMESTATES g_eGameState)
{
	if (g_eGameState == S_COMBAT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

EGAMESTATES g_eGameState = S_SPLASHSCREEN;


double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(87, 30, "SP1 Framework");
//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// *output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point *output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = 5;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(16, 0, L"Consolas");

	for (int i = 0; i < sizeof(bArray); i++)  // for the mobs' text
	{
		bArray[i] = true;
	}
	

	for (int i = 0; i < sizeof(bArray); i++)  // initialise all the memory to be true for the mobs' text
	{
		bArray[i] = true;
	}


}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// *output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// *output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_1]      = isKeyPressed(0x31);
	g_abKeyPressed[K_2]      = isKeyPressed(0x32);
	g_abKeyPressed[K_3]      = isKeyPressed(0x33);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// *output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
		case S_COMBAT:// combat(g_eGameState, dt);
			break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// *output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_GAME: renderGame();
            break;
		case S_COMBAT:// renderCombat(&bArray[18] , g_Console);
			break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
    processUserInput();// checks if you should change states or do something else with the game, e.g. pause, exit
	if (g_eGameState == S_GAME)
	{
		moveCharacter();    // moves the character, collision detection, physics, etc
	}                   // sound can be played here too.
}

void moveCharacter()
{
	COORD c;

	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if ((g_abKeyPressed[K_UP] ) && (collision(map, (g_sChar.m_cLocation.Y - 1) , g_sChar.m_cLocation.X) != true) && (disablemovement (g_eGameState) != true))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;
		if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//change gamestate to combat
			//run text for monster
		}
		else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			c.Y = g_sChar.m_cLocation.Y;
			c.X = g_sChar.m_cLocation.X;
			keycounter++;
			map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
		}
        bSomethingHappened = true;
		
    }
   if ((g_abKeyPressed[K_LEFT]) && (collision(map, g_sChar.m_cLocation.Y, (g_sChar.m_cLocation.X - 1)) != true) && (disablemovement (g_eGameState) != true))//performs movement if keystroke is pressed and if there is no wall in the direction of travel
    {
       // Beep(1440, 30);
        g_sChar.m_cLocation.X--;
		if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			g_eGameState = S_COMBAT;
		}
		else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			c.Y = g_sChar.m_cLocation.Y;
			c.X = g_sChar.m_cLocation.X;
			keycounter++;
			map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
		}
        bSomethingHappened = true;
    }
    if ((g_abKeyPressed[K_DOWN] ) && (collision(map, (g_sChar.m_cLocation.Y + 1) , g_sChar.m_cLocation.X) != true) && (disablemovement (g_eGameState) != true))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;
		if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for monster
		}
		else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			c.Y = g_sChar.m_cLocation.Y;
			c.X = g_sChar.m_cLocation.X;
			keycounter++;
			map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';

		
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for end door password, if correct, do lvlcleared++ to change lvl on next render, reset pos of player
			lvlcleared++;
			g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_sChar.m_cLocation.Y = 5;
		}
        bSomethingHappened = true;
    }
    if ((g_abKeyPressed[K_RIGHT] ) && (collision(map, g_sChar.m_cLocation.Y, (g_sChar.m_cLocation.X + 1)) != true) && (disablemovement (g_eGameState) != true))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;
		if (touchmonster(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			//run text for monster
		}
		else if (touchkey(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			c.Y = g_sChar.m_cLocation.Y;
			c.X = g_sChar.m_cLocation.X;
			keycounter++;
			map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		}
		else if (touchend(map, g_sChar.m_cLocation.Y, g_sChar.m_cLocation.X) == true)
		{
			if (keycounter == keysneeded)
			{
				keysneeded = 0;
				lvlcleared++;
				g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
				g_sChar.m_cLocation.Y = 5;
			}
		}
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
        bSomethingHappened = true;
    }

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.015; // 125ms should be enough
    }
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "Labyrinthos Libertas", 0x03); //Title of the game here
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);//color to change to if space bar is pressed
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);//quit
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
    //Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1F, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };
    COORD c;
	colour(colors[0]);

	string rows;
	string cols;
	string keys;
	string filename;
	int y;
	int x;

	if (lvlcleared == 0)
	{
		filename += "lvl1.txt";
	}
	else if (lvlcleared == 1)
	{
		filename += "lvl2.txt";
	}
	else if (lvlcleared == 2)
	{
		filename += "lvl3.txt";
	}
	else if (lvlcleared == 3)
	{
		filename += "lvl4.txt";
	}
	else if (lvlcleared == 4)
	{
		filename += "lvl5.txt";
	}


	if (lvlcleared == changeinlvl)
	{
		ifstream currentlvl;
		currentlvl.open(filename);
		getline(currentlvl, cols);
		getline(currentlvl, rows);
		getline(currentlvl, keys);

		y = stoi(rows);
		x = stoi(cols);
		keysneeded = stoi(keys);
		
		for (int i = 0; i < y - 1; ++i)
		{
			string currentrow;
			char currentchar;
			getline(currentlvl, currentrow);
			for (int j = 0; j < x - 1; ++j)
			{
				currentchar = currentrow[j];

				c.X = j;
				c.Y = i;

				switch (currentchar)
				{
				case'#':
					map[i][j] = (char)219;
					break;
				case'k':
					map[i][j] = 'k';
					break;
				case'o':
					map[i][j] = 'o';
					break;
				case'm':
					map[i][j] = 'm';
					break;
				case ' ':
					map[i][j] = ' ';
					break;
				default:
					break;
				}
			}
		}
		changeinlvl++;
		currentlvl.close();
	}
	else
	{
		for (int i = 0; i < 15; ++i)
		{
			for (int j = 0; j < 87; ++j)
			{
				c.X = j;
				c.Y = i;
				g_Console.writeToBuffer(c, map[i][j], colors[0]);
			}
		}
	}
}

void textRender()
{
	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	COORD Text;
	Text.X = 0;
	Text.Y = 18;
	//g_Console.writeToBuffer(Text, whichText(&texty, &bArray[18]), colors[0]);
}


void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;//default color of character
    if (g_sChar.m_bActive)//if spacebar is pressed, change the color of character
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);//send character printing details to the buffer
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}


string ansChecker(Text * Mob)
{
	bool g_abKeyPressed[K_COUNT];
	if (g_abKeyPressed[K_1] == Mob->correctAns)
	{
		//print congrats
	}
	else if (g_abKeyPressed[K_2] == Mob->correctAns)
	{
		//print congrats
	}
	else if (g_abKeyPressed[K_3] == Mob->correctAns)
	{
		//print congrats
	}
	return 0;
}

/*
what happens when the player runs into an entity?
the game checks which entity they ran into and render the corresponding text
eg: run into mob1
check that player run into mob1
access text relating to mob1
render text of mob1
after finish clean textbox
*/