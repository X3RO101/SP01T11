#include "tilemanager.h"
#include "game.h"

char **map;

void arraymaker(string levelgen())
{
	char **mapptr = new char*[30];//2d array declared with pointers
	for (int i = 0; i < 30; ++i)
	{
		mapptr[i] = new char[101];
	}
	
	

	int rowcounter = 0;
	int colcounter = 0;
	int entercounter = 0;
	int totaldimen = 3000;

	while (rowcounter < 30)
	{
		while (colcounter < 101)
		{
			while (int i = 0 != totaldimen)
			{
				mapptr[rowcounter][colcounter] = levelgen()[i];
				i++;
				colcounter++;
			}
			rowcounter++;
			colcounter = 0;
		}
	}
	map = mapptr;
	
}

char** getarray(void)
{
	return map;
}


bool collision(char array[30][101], int playerycoord, int playerxcoord) //checks if player encounters a wall
{
	if (array[playerycoord][playerxcoord] == (char)219)//up
	{
		return true;
	}
	else
	{
		return false;
	}
}	


bool touchmonster(struct SGameChar g_sChar, struct monstatus monster[])//checks if player encounters a monster
{
	bool montouched = false;
	if (g_sChar.m_cLocation.X == monster[0].location.X && g_sChar.m_cLocation.Y == monster[0].location.Y)
	{
		if (monster[0].alive == true)
		{
			montouched = true;
		}
	}
	else if (g_sChar.m_cLocation.X == monster[1].location.X && g_sChar.m_cLocation.Y == monster[1].location.Y)
	{
		if (monster[1].alive == true)
		{
			montouched = true;
		}
	}
	else if (g_sChar.m_cLocation.X == monster[2].location.X && g_sChar.m_cLocation.Y == monster[2].location.Y)
	{
		if (monster[2].alive == true)
		{
			montouched = true;
		}
	}
	else if (g_sChar.m_cLocation.X == monster[3].location.X && g_sChar.m_cLocation.Y == monster[3].location.Y)
	{
		if (monster[3].alive == true)
		{
			montouched = true;
		}
	}
	else if (g_sChar.m_cLocation.X == monster[4].location.X && g_sChar.m_cLocation.Y == monster[4].location.Y)
	{
		if (monster[4].alive == true)
		{
			montouched = true;
		}
	}
	else if (g_sChar.m_cLocation.X == monster[5].location.X && g_sChar.m_cLocation.Y == monster[5].location.Y)
	{
		if (monster[5].alive == true)
		{
			montouched = true;
		}
	}
	else
	{
		montouched = false;
	}

	return montouched;
}


bool monstercollides(int i, struct monstatus monster[])
{
	/*
	bool monsterhit = false;
	for (int a = 0; i < 6; i++)
	{
		if (a != i)
		{
			if (monster[6].location.X == monster[a].location.X && monster[6].location.Y == monster[a].location.Y)
			{
				monsterhit = true;
			}
			else
			{
				continue;
			}
		}
	}

	return monsterhit;
	*/
	bool monsterhit = false;

	if (i == 0)
	{
		if (monster[6].location.X == monster[1].location.X && monster[6].location.Y == monster[1].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[2].location.X && monster[6].location.Y == monster[2].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[3].location.X && monster[6].location.Y == monster[3].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[4].location.X && monster[6].location.Y == monster[4].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[5].location.X && monster[6].location.Y == monster[5].location.Y)
		{
			monsterhit = true;
		}
	}
	else if (i == 1)
	{
		if (monster[6].location.X == monster[0].location.X && monster[6].location.Y == monster[0].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[2].location.X && monster[6].location.Y == monster[2].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[3].location.X && monster[6].location.Y == monster[3].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[4].location.X && monster[6].location.Y == monster[4].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[5].location.X && monster[6].location.Y == monster[5].location.Y)
		{
			monsterhit = true;
		}
	}
	else if (i == 2)
	{
		if (monster[6].location.X == monster[0].location.X && monster[6].location.Y == monster[0].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[1].location.X && monster[6].location.Y == monster[1].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[3].location.X && monster[6].location.Y == monster[3].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[4].location.X && monster[6].location.Y == monster[4].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[5].location.X && monster[6].location.Y == monster[5].location.Y)
		{
			monsterhit = true;
		}
	}
	else if (i == 3)
	{
		if (monster[6].location.X == monster[0].location.X && monster[6].location.Y == monster[0].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[1].location.X && monster[6].location.Y == monster[1].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[2].location.X && monster[6].location.Y == monster[2].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[4].location.X && monster[6].location.Y == monster[4].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[5].location.X && monster[6].location.Y == monster[5].location.Y)
		{
			monsterhit = true;
		}
	}
	else if (i == 4)
	{
		if (monster[6].location.X == monster[0].location.X && monster[6].location.Y == monster[0].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[1].location.X && monster[6].location.Y == monster[1].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[2].location.X && monster[6].location.Y == monster[2].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[3].location.X && monster[6].location.Y == monster[3].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[5].location.X && monster[6].location.Y == monster[5].location.Y)
		{
			monsterhit = true;
		}
	}
	else if (i == 5)
	{
		if (monster[6].location.X == monster[0].location.X && monster[6].location.Y == monster[0].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[1].location.X && monster[6].location.Y == monster[1].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[2].location.X && monster[6].location.Y == monster[2].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[3].location.X && monster[6].location.Y == monster[3].location.Y)
		{
			monsterhit = true;
		}
		if (monster[6].location.X == monster[4].location.X && monster[6].location.Y == monster[4].location.Y)
		{
			monsterhit = true;
		}
	}
	
	return monsterhit;
}

int monsterslain(struct SGameChar g_sChar, struct monstatus monster[])
{
	if (g_sChar.m_cLocation.X == monster[0].location.X && g_sChar.m_cLocation.Y == monster[0].location.Y)
	{
		return 0;
	}
	else if (g_sChar.m_cLocation.X == monster[1].location.X && g_sChar.m_cLocation.Y == monster[1].location.Y)
	{
		return 1;
	}
	else if (g_sChar.m_cLocation.X == monster[2].location.X && g_sChar.m_cLocation.Y == monster[2].location.Y)
	{
		return 2;
	}
	else if (g_sChar.m_cLocation.X == monster[3].location.X && g_sChar.m_cLocation.Y == monster[3].location.Y)
	{
		return 3;
	}
	else if (g_sChar.m_cLocation.X == monster[4].location.X && g_sChar.m_cLocation.Y == monster[4].location.Y)
	{
		return 4;
	}
	else if (g_sChar.m_cLocation.X == monster[5].location.X && g_sChar.m_cLocation.Y == monster[5].location.Y)
	{
		return 5;
	}
}

bool touchkey(char array[30][101], int playerycoord, int playerxcoord)//checks if player encounters a key
{
	if (array[playerycoord][playerxcoord] == 'k')
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool touchend(char array[30][101], int playerycoord, int playerxcoord)//checks if player encounters the end of the level
{
	if (array[playerycoord][playerxcoord] == 'o')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool touchplayer(struct monstatus monster[], struct SGameChar g_sChar, int i)
{
	bool touches = false;

	if (monster[i].location.X == g_sChar.m_cLocation.X && monster[i].location.Y == g_sChar.m_cLocation.Y)
	{
		touches = true;
	}

	return touches;
}