#include <iostream>
#include "curses.h"
#include <cstdlib>
#include <string>
#include "Player.h"
#include "Functii.h"
#include <fstream>
#include <ctime>
#include <windows.h>
#include <time.h>
#include <random>

using namespace std;


int main() {

	 PlaySound("background.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	
#pragma region Citesc, declar

	 minstd_rand simple_rand;
	 simple_rand.seed(time(0));

	 int esc = 0;
	char matriceJucator[20][20];
	char matriceComputer[20][20];
	char matriceLovite[20][20]; // initial va fi initializata toata cu '-'
	char dejaLovite[20][20]; // initial va fi initializata toata cu '-'
	
	ifstream fin;
	fin.open("Battleships.in");
# pragma region verific erori

	if (!fin.is_open()) {
		exit(EXIT_FAILURE);
	}
	if (!fin) {
		cerr << "The file can't be found!";
		exit(1);
	}
	if (fin.fail()) {
		cerr << "Error opening file";
		exit(1);
	}

#pragma endregion
	//citesc datele din fisierul battleships.in

	while (!fin.eof()) {
		for (int i = 0; i < 10; i=i+1)
		{
			for (int j = 0; j < 20; j=j+2)
			{
				fin >> matriceJucator[i][j];
				matriceJucator[i][j+1]=' ';
			}
		}
	}
	
#pragma endregion

#pragma region Generare aleatoare a pozitiilor

	//initializez fiecare element al matricei Computerului cu caracterul '-', ca sa-mi afiseze frumos. Si pun cate un spatiu intre ele
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j += 2)
		{
			matriceComputer[i][j] = '-';
			matriceComputer[i][j + 1] = ' ';
		}
	}
	
#pragma region Nava mare de 4 patratele
	int i, j;
		i = simple_rand() % 10;
		j = (simple_rand() % 10)*2;
	
	matriceComputer[i][j] = 'x';



	// 1 nava de 4 patratele
	int directiaNavei = simple_rand() % 4; // in ce directie se indreapta nava, fata de punctul initial, matriceComputer[i][j], in sus, jos, dreapta sau stanga?

	//in sus
	if (directiaNavei == 0 && i >= 3) {
		for (int k = i; k >= i - 3; k--)
		{
			matriceComputer[k][j] = 'x';
		}
	} 
	else if (directiaNavei==0 && i < 3) {
		for (int k = i; k <= i + 3; k++)
		{
			matriceComputer[k][j] = 'x';
		}
	}
	
	//in jos
	 if (directiaNavei == 2 && i<=6) {
		for (int k = i; k <= i+3; k++)
		{
			matriceComputer[k][j] = 'x';
		}
	 }else if (directiaNavei==2 && i > 6) {
		 for (int k = i; k >= i - 3; k--)
		 {
			 matriceComputer[k][j] = 'x';
		 }
	 }

	 //la dreapta
	if (directiaNavei == 1 && j<=12) {
		for (int k = j; k <= j + 6; k=k+2)
		{
			matriceComputer[i][k] = 'x';
		}
	}else if (directiaNavei==1 && j > 12) {
		for (int k = j; k >= j - 6; k=k-2)
		{
			matriceComputer[i][k] = 'x';
		}
	}
		
	// la stanga
	if (directiaNavei == 3 && j>=6) {
	
		for (int k = j; k >= j - 6; k=k-2)
		{
			matriceComputer[i][k] = 'x';
		}
	}else if (directiaNavei==3 && j < 6) {
		for (int k = j; k <= j + 6; k=k+2)
		{
			matriceComputer[i][k] = 'x';
		}
	}
	
#pragma endregion

#pragma region nava 1 (de 3 patratele)
	bool seIntersecteaza=true; // presupun ca nu se intersecteaza
	do { 

		do {
			i = simple_rand() % 10;
			j = (simple_rand() % 10)*2;
		} while (matriceComputer[i][j] == 'x');

		directiaNavei = simple_rand() % 4;

		//in sus
		if (directiaNavei == 0 && i >= 2 && AreLoc3Sus(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k >= i - 2; k--)
			{
				matriceComputer[k][j] = 'x';
			}
		}
		else if (directiaNavei == 0 && i < 2 && AreLoc3Jos(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k <= i + 2; k++)
			{
				matriceComputer[k][j] = 'x';
			}
		}

		//in jos
		if (directiaNavei == 2 && i <= 7 && AreLoc3Jos(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k <= i + 2; k++)
			{
				matriceComputer[k][j] = 'x';
			}
		}
		else if (directiaNavei == 2 && i > 7 && AreLoc3Sus(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k >= i - 2; k--)
			{
				matriceComputer[k][j] = 'x';
			}
		}


		//la dreapta
		if (directiaNavei == 1 && j <= 14 && AreLoc3Dreapta(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k <= j + 4; k=k+2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
		else if (directiaNavei == 1 && j > 14 && AreLoc3Stanga(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k >= j - 4; k=k-2)
			{
				matriceComputer[i][k] = 'x';
			}
		}

		// la stanga
		if (directiaNavei == 3 && j >= 4 && AreLoc3Stanga(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k >= j - 4; k=k-2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
		else if (directiaNavei == 3 && j < 2 && AreLoc3Dreapta(matriceComputer, i, j)) {
			seIntersecteaza = false; 
			for (int k = j; k <= j + 4; k+=2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
	} while (seIntersecteaza == true);

#pragma endregion
	
#pragma region nava 2 (de 3 patratele)

	//nava2
	seIntersecteaza = true; // presupun ca nu se intersecteaza
	do {

		do {
			i = simple_rand() % 10;
			j = (simple_rand() % 10) * 2;
		} while (matriceComputer[i][j] == 'x');

		directiaNavei = simple_rand() % 4;

		//in sus
		if (directiaNavei == 0 && i >= 2 && AreLoc3Sus(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k >= i - 2; k--)
			{
				matriceComputer[k][j] = 'x';
			}
		}
		else if (directiaNavei == 0 && i < 2 && AreLoc3Jos(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k <= i + 2; k++)
			{
				matriceComputer[k][j] = 'x';
			}
		}

		//in jos
		if (directiaNavei == 2 && i <= 7 && AreLoc3Jos(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k <= i + 2; k++)
			{
				matriceComputer[k][j] = 'x';
			}
		}
		else if (directiaNavei == 2 && i > 7 && AreLoc3Sus(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k >= i - 2; k--)
			{
				matriceComputer[k][j] = 'x';
			}
		}


		//la dreapta
		if (directiaNavei == 1 && j <= 14 && AreLoc3Dreapta(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k <= j + 4; k = k + 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
		else if (directiaNavei == 1 && j > 14 && AreLoc3Stanga(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k >= j - 4; k = k - 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}

		// la stanga
		if (directiaNavei == 3 && j >= 4 && AreLoc3Stanga(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k >= j - 4; k = k - 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
		else if (directiaNavei == 3 && j < 2 && AreLoc3Dreapta(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k <= j + 4; k += 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
	} while (seIntersecteaza == true);

#pragma endregion 

#pragma region nava 1(de 2 patratele)
	seIntersecteaza = true; // presupun ca nu se intersecteaza
	do {

		do {
			i = simple_rand() % 10;
			j = (simple_rand() % 10) * 2;
		} while (matriceComputer[i][j] == 'x');

		directiaNavei = simple_rand() % 4;

		//in sus
		if (directiaNavei == 0 && i >= 2 && AreLoc3Sus(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k >= i - 1; k--)
			{
				matriceComputer[k][j] = 'x';
			}
		}
		else if (directiaNavei == 0 && i < 2 && AreLoc3Jos(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k <= i + 1; k++)
			{
				matriceComputer[k][j] = 'x';
			}
		}

		//in jos
		if (directiaNavei == 2 && i <= 7 && AreLoc3Jos(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k <= i + 1; k++)
			{
				matriceComputer[k][j] = 'x';
			}
		}
		else if (directiaNavei == 2 && i > 7 && AreLoc3Sus(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k >= i - 1; k--)
			{
				matriceComputer[k][j] = 'x';
			}
		}


		//la dreapta
		if (directiaNavei == 1 && j <= 14 && AreLoc3Dreapta(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k <= j + 2; k = k + 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
		else if (directiaNavei == 1 && j > 14 && AreLoc3Stanga(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k >= j - 2; k = k - 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}

		// la stanga
		if (directiaNavei == 3 && j >= 4 && AreLoc3Stanga(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k >= j - 2; k = k - 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
		else if (directiaNavei == 3 && j < 2 && AreLoc3Dreapta(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k <= j + 2; k += 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
	} while (seIntersecteaza == true);
#pragma endregion

#pragma region nava 2(de 2 patratele)
	seIntersecteaza = true; // presupun ca nu se intersecteaza
	do {

		do {
			i = simple_rand() % 10;
			j = (simple_rand() % 10) * 2;
		} while (matriceComputer[i][j] == 'x');

		directiaNavei = simple_rand() % 4;

		//in sus
		if (directiaNavei == 0 && i >= 2 && AreLoc3Sus(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k >= i - 1; k--)
			{
				matriceComputer[k][j] = 'x';
			}
		}
		else if (directiaNavei == 0 && i < 2 && AreLoc3Jos(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k <= i + 1; k++)
			{
				matriceComputer[k][j] = 'x';
			}
		}

		//in jos
		if (directiaNavei == 2 && i <= 7 && AreLoc3Jos(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k <= i + 1; k++)
			{
				matriceComputer[k][j] = 'x';
			}
		}
		else if (directiaNavei == 2 && i > 7 && AreLoc3Sus(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k >= i - 1; k--)
			{
				matriceComputer[k][j] = 'x';
			}
		}


		//la dreapta
		if (directiaNavei == 1 && j <= 14 && AreLoc3Dreapta(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k <= j + 2; k = k + 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
		else if (directiaNavei == 1 && j > 14 && AreLoc3Stanga(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k >= j - 2; k = k - 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}

		// la stanga
		if (directiaNavei == 3 && j >= 4 && AreLoc3Stanga(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k >= j - 2; k = k - 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
		else if (directiaNavei == 3 && j < 2 && AreLoc3Dreapta(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k <= j + 2; k += 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
	} while (seIntersecteaza == true);


#pragma endregion

#pragma region nava 3(de 2 patratele)

	seIntersecteaza = true; // presupun ca nu se intersecteaza
	do {

		do {
			i = simple_rand() % 10;
			j = (simple_rand() % 10) * 2;
		} while (matriceComputer[i][j] == 'x');

		directiaNavei = simple_rand() % 4;

		//in sus
		if (directiaNavei == 0 && i >= 2 && AreLoc3Sus(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k >= i - 1; k--)
			{
				matriceComputer[k][j] = 'x';
			}
		}
		else if (directiaNavei == 0 && i < 2 && AreLoc3Jos(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k <= i + 1; k++)
			{
				matriceComputer[k][j] = 'x';
			}
		}

		//in jos
		if (directiaNavei == 2 && i <= 7 && AreLoc3Jos(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k <= i + 1; k++)
			{
				matriceComputer[k][j] = 'x';
			}
		}
		else if (directiaNavei == 2 && i > 7 && AreLoc3Sus(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = i; k >= i - 1; k--)
			{
				matriceComputer[k][j] = 'x';
			}
		}


		//la dreapta
		if (directiaNavei == 1 && j <= 14 && AreLoc3Dreapta(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k <= j + 2; k = k + 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
		else if (directiaNavei == 1 && j > 14 && AreLoc3Stanga(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k >= j - 2; k = k - 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}

		// la stanga
		if (directiaNavei == 3 && j >= 4 && AreLoc3Stanga(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k >= j - 2; k = k - 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
		else if (directiaNavei == 3 && j < 2 && AreLoc3Dreapta(matriceComputer, i, j)) {
			seIntersecteaza = false;
			for (int k = j; k <= j + 2; k += 2)
			{
				matriceComputer[i][k] = 'x';
			}
		}
	} while (seIntersecteaza == true);

#pragma endregion

#pragma region nava 1(de 1 patratel)

	seIntersecteaza = true; // presupun ca nu se intersecteaza
	do {

		do {
			i = simple_rand() % 10;
			j = (simple_rand() % 10)*2;
		} while (matriceComputer[i][j] == 'x');

		if (!Vecini(matriceComputer,i,j)) seIntersecteaza=false;

	} while (seIntersecteaza == true);

	matriceComputer[i][j] = 'x';

#pragma endregion

#pragma region nava 2(de 1 patratel)

	seIntersecteaza = true; // presupun ca nu se intersecteaza
	do {

		do {
			i = simple_rand() % 10;
			j = (simple_rand() % 10) * 2;
		} while (matriceComputer[i][j] == 'x');

		if (!Vecini(matriceComputer, i, j)) seIntersecteaza = false;

	} while (seIntersecteaza == true);

	matriceComputer[i][j] = 'x';

#pragma endregion

#pragma region nava 3(de 1 patratel)

	seIntersecteaza = true; // presupun ca nu se intersecteaza
	do {

		do {
			i = simple_rand() % 10;
			j = (simple_rand() % 10) * 2;
		} while (matriceComputer[i][j] == 'x');

		if (!Vecini(matriceComputer, i, j)) seIntersecteaza = false;

	} while (seIntersecteaza == true);

	matriceComputer[i][j] = 'x';

#pragma endregion

#pragma region nava 4(de 1 patratel)

	seIntersecteaza = true; // presupun ca nu se intersecteaza
	do {

		do {
			i = simple_rand() % 10;
			j = (simple_rand() % 10) * 2;
		} while (matriceComputer[i][j] == 'x');

		if (!Vecini(matriceComputer, i, j)) seIntersecteaza = false;

	} while (seIntersecteaza == true);

	matriceComputer[i][j] = 'x';

#pragma endregion

#pragma endregion

#pragma region Pornesc CURSES

	initscr();
	noecho();
	cbreak();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_RED, COLOR_GREEN);
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
#pragma region ascii
	attron(COLOR_PAIR(1));
	mvprintw(5, xMax - (xMax - 15), "88                                     88                      88          88");
	mvprintw(6, xMax - (xMax - 15), "88                       ,d      ,d    88                      88          \"\"");
	mvprintw(7, xMax - (xMax - 15), "88                       88      88    88                      88 ");
	mvprintw(8, xMax - (xMax - 15), "88,dPPYba,  ,adPPYYba, MM88MMM MM88MMM 88  ,adPPYba, ,adPPYba, 88,dPPYba,  88 8b,dPPYba,  ,adPPYba,");
	mvprintw(9, xMax - (xMax - 15), "88P'    \"8a \"\"     `Y8   88      88    88 a8P_____88 I8[    \"\" 88P'    \"8a 88 88P'    \"8a I8[\"");
	mvprintw(10, xMax - (xMax - 15), "88       d8 ,adPPPPP88   88      88    88 8PP\"\"\"\"\"\"\"  `\"Y8ba,  88       88 88 88       d8  `\"Y8ba,");
	mvprintw(11, xMax - (xMax - 15), "88b,   ,a8\" 88, ,   88   88,     88,   88 \"8b,   ,aa aa    ]8I 88       88 88 88b,   ,a8\" aa    ]8I");
	mvprintw(12, xMax - (xMax - 15), "8Y\"Ybbd8\"'  `\"8bbdP\"Y8   \"Y888   \"Y888 88  `\"Ybbd8\"' `\"YbbdP\"' 88       88 88 88`YbbdP\"'  `\"YbbdP\"'");
	mvprintw(13, xMax - (xMax - 15), "                                                                              88");
	mvprintw(14, xMax - (xMax - 15), "                                                                              88");
	attroff(COLOR_PAIR(1));
#pragma endregion
	

#pragma region MENIUL PRINCIPAL

	// o fereastra pt meniu
	WINDOW* menuwin = newwin(4,xMax-15, yMax-10,xMax-(xMax-10));
	wbkgd(menuwin, COLOR_PAIR(1));
	box(menuwin, ' ', ' ');
	refresh();
	wrefresh(menuwin);
	keypad(menuwin, true);
	string choices[3] = { "New Game", "Resume Game", "Quit" };

	int highlight2 = 0;

	while (1) {
		for (int i = 0; i < 3; i++)
		{
			if (i == highlight2 )
				wattron(menuwin, A_REVERSE);
				mvwprintw(menuwin, i + 1, 1, choices[i].c_str());
				wattroff(menuwin, A_REVERSE);
		}
		int choice2 = wgetch(menuwin);

		switch (choice2)
		{
		case KEY_UP:
			highlight2--;
			if (highlight2 == -1) highlight2 = 0;
			break;
		case KEY_DOWN:
			highlight2++;
			if (highlight2 == 3) highlight2 = 2;
			break;
		default:
			break;
		}

		if (choice2 == 10) {
			if (highlight2 == 0) {
				PlaySound("start.wav", NULL, SND_ASYNC | SND_FILENAME);
				clear();
#pragma region Ferestre nave

#pragma region Fereastra Jucator

				WINDOW* playerwin = newwin(10, 20, 5, 5);
				refresh();

				//wborder(playerwin,left,right,top,bottom,tlc,trc,blc,brc);
				refresh();
				wborder(playerwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
				wbkgd(playerwin, COLOR_PAIR(3));

				// adaug matricea jucatorului, cu pozitiile navelor in fereastra din consola
				for (int i = 0; i < 10; i = i + 1)
				{
					for (int j = 0; j < 20; j = j + 2)
					{
						wattron(playerwin, COLOR_PAIR(3));
						mvwaddch(playerwin, i, j, matriceJucator[i][j]);
						mvwaddch(playerwin, i, j + 1, ' ');
						wattroff(playerwin, COLOR_PAIR(3));
					}
				}

				//box(playerwin, ' ', ' ');
				attron(COLOR_PAIR(1));
				mvprintw(3, 5, "Navele tale");
				attroff(COLOR_PAIR(1));
				refresh();
				wrefresh(playerwin);

#pragma endregion

#pragma region Fereastra Computer

				//creare fereastra computer
				WINDOW* computerwin = newwin(10, 20, 5, 45);
				wbkgd(computerwin, COLOR_PAIR(3));

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 20; j += 2)
					{
						matriceLovite[i][j] = '-';
						matriceLovite[i][j + 1] = ' ';
					}
				}

				// adaug matricea Computerului cu pozitiile navelor in fereastra din consola 
				//(de fapt toate elementele vor fi '-' pt ca nu vreau sa se vada unde sunt ascunse navele)
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 20; j += 1)
					{
						wattron(computerwin, COLOR_PAIR(3));
						mvwaddch(computerwin, i, j, matriceLovite[i][j]);
						mvwaddch(computerwin, i, j + 1, matriceLovite[i][j]);
						wattroff(computerwin, COLOR_PAIR(3));
					}
				}
				//box(computerwin, ' ', ' ');
				attron(COLOR_PAIR(1));
				mvprintw(3, 45, "Navele computerului");
				attroff(COLOR_PAIR(1));

				refresh();
				wrefresh(computerwin);
				// wgetch(computerwin);



#pragma endregion


#pragma endregion

#pragma endregion

#pragma region Incepe Jocul
				
				keypad(computerwin, true);
				int choice;
				int highlightI = 0;
				int highlightJ = 0;
				int tura = 1;

				//initializez matricea dejaLovite, ca sa pot tine evidenta, sa nu dea de mai multe ori in acelasi loc
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 20; j += 2)
					{
						dejaLovite[i][j] = '-';
						dejaLovite[i][j + 1] = ' ';
					}
				}

				//initializez matricea matriceLovite[i][j] sa pot tine evidenta unde a lovit jucatorul deja
				// Astfel, daca incerc sa dau in acelasi loc de mai multe ori, programul ma va atentiona printr-un mesaj
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 20; j += 2)
					{
						matriceLovite[i][j + 1] = ' ';
					}
				}

				int naveJucator = 20;
				int naveComputer = 20;

				while ((tura == 1 || tura == 0) && (naveJucator > 0 && naveComputer > 0)&& esc==0) {

					
					refresh();
					attron(COLOR_PAIR(1));
					mvprintw(0, 50, "To exit press esc!");
					attroff(COLOR_PAIR(1));
					// randul jucatorului
					while (tura == 1 && esc==0) {
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 20; j += 1) {
								if (i == highlightI && j == highlightJ)
									wattron(computerwin, A_REVERSE);
								mvwaddch(computerwin, i, j, matriceLovite[i][j]);
								wattroff(computerwin, A_REVERSE);
							}
						}
						choice = wgetch(computerwin);
						switch (choice) {
						case KEY_UP:
							highlightI--;
							PlaySound("blink.wav", NULL, SND_ASYNC | SND_FILENAME);
							if (highlightI == -1) highlightI = 0;
							break;
						case KEY_DOWN:
							highlightI++;
							PlaySound("blink.wav", NULL, SND_ASYNC | SND_FILENAME);
							if (highlightI == 10) 	highlightI = 9;
							break;
						case KEY_LEFT:
							highlightJ = highlightJ - 2;
							PlaySound("blink.wav", NULL, SND_ASYNC | SND_FILENAME);
							if (highlightJ == -2) highlightJ = 0;
							break;
						case KEY_RIGHT:
							highlightJ = highlightJ + 2;
							PlaySound("blink.wav", NULL, SND_ASYNC | SND_FILENAME);
							if (highlightJ == 20) highlightJ = 18;
							break;
						default:
							break;
						}

						if (choice == 10) {
							if (matriceLovite[highlightI][highlightJ] != '-') {
								PlaySound("bump.wav", NULL, SND_ASYNC | SND_FILENAME);
								attron(COLOR_PAIR(1));
								mvprintw(0, 0, "Deja ai lovit acolo, incearca in alt loc!");
								attroff(COLOR_PAIR(1));
								wrefresh(computerwin);
								refresh();
								break;
							}
							else if (matriceComputer[highlightI][highlightJ] == 'x') {
								move(0, 0);
								clrtoeol();
								PlaySound("hit.wav", NULL, SND_ASYNC | SND_FILENAME);
								matriceLovite[highlightI][highlightJ] = 'x';
								wattron(computerwin, COLOR_PAIR(4));
								mvwaddch(computerwin, highlightI, highlightJ + 2, matriceLovite[highlightI][highlightJ]);
								wattroff(computerwin, COLOR_PAIR(4));
								tura = 1;
								naveComputer--;
							}
							else {
								move(0, 0);
								clrtoeol();
								matriceLovite[highlightI][highlightJ] = '*';
								PlaySound("fail.wav", NULL, SND_ASYNC | SND_FILENAME);
								wattron(computerwin, COLOR_PAIR(4));
								mvwaddch(computerwin, highlightI, highlightJ + 2, matriceLovite[highlightI][highlightJ]);
								wattroff(computerwin, COLOR_PAIR(4));
								tura = 0;
							}
							
						}
						else if (choice == 27) {
							WINDOW* menuwin = newwin(4, xMax - 15, yMax - 10, 5);
							wbkgd(menuwin, COLOR_PAIR(1));
							box(menuwin, ' ', ' ');
							refresh();
							wrefresh(menuwin);
							keypad(menuwin, true);
							string choices[3] = { "New Game", "Resume Game", "Quit" };

							int highlight2 = 0;

							while (esc==0) {
								for (int i = 0; i < 3; i++)
								{
									if (i == highlight2)
										wattron(menuwin, A_REVERSE);
									mvwprintw(menuwin, i + 1, 1, choices[i].c_str());
									wattroff(menuwin, A_REVERSE);
								}
								int choice2 = wgetch(menuwin);

								switch (choice2)
								{
								case KEY_UP:
									highlight2--;
									if (highlight2 == -1) highlight2 = 0;
									break;
								case KEY_DOWN:
									highlight2++;
									if (highlight2 == 3) highlight2 = 2;
									break;
								default:
									break;
								}

								if (choice2 == 10) {
									if (highlight2 == 2) esc = 1;

								}
								else if (choice2 == 27) esc = 1;
							}
							if (esc == 1) break;
						} if (esc == 1) break;
						refresh(); 
						wrefresh(computerwin);
					}

					//randul calculatorului
					while (tura == 0 && esc==0) {
						do {
							i = simple_rand() % 20;
							j = simple_rand() % 20;
						} while (dejaLovite[i][j] != '-');
						if (matriceJucator[i][j] == 'x') {
							wattron(playerwin, COLOR_PAIR(4));
							mvwaddch(playerwin, i, j, 'x');
							wattroff(playerwin, COLOR_PAIR(4));
							dejaLovite[i][j] = 'x';
							tura = 0;
							naveJucator--;
						}
						else if (matriceJucator[i][j] == '-') {
							wattron(playerwin, COLOR_PAIR(4));
							mvwaddch(playerwin, i, j, '*');
							wattroff(playerwin, COLOR_PAIR(4));
							dejaLovite[i][j] = '*';
							tura = 1;
						}
						//	refresh();
							//wrefresh(playerwin);
					}
					refresh();
					wrefresh(playerwin);
				}

				move(0, 0);
				clrtoeol();
				if (naveJucator > 0 && naveComputer > 0) {
					clear();
					mvprintw(0, 0, "Ai renuntat!");
					PlaySound("boo.wav", NULL, SND_ASYNC | SND_FILENAME);
				}
				else if (naveJucator > naveComputer) {
					mvprintw(0, 0, "Felicitari, ai castigat!");
					getch();
					PlaySound("Win.wav", NULL, SND_ASYNC | SND_FILENAME);
					getch();
				}
				else {
					attron(COLOR_PAIR(1));
					mvprintw(0, 0, "Ai pierdut!");
					attroff(COLOR_PAIR(1));
					getch();
					PlaySound("Lose.wav", NULL, SND_ASYNC | SND_FILENAME);
					getch();
				}
				refresh();
				wrefresh(computerwin);
				wrefresh(playerwin);
			
			}
		}
		else if (choice2 == 27) break;
			
	}
	wrefresh(menuwin);
	// printw("Your choice was: %s", choices[highlight].c_str());
	refresh();


#pragma endregion



#pragma endregion

		

#pragma endregion


	/*int c = wgetch(menuwin);
	if (c == KEY_UP) {
		mvwprintw(menuwin, 1, 1, "You pressed up!");
		wrefresh(menuwin);
		getch();
	endwin(); 
	} */

	/*
	//freopen("/dev/tty", "rw", stdin);
	initscr();
	noecho();
	cbreak();

	int yMax, xMax;
	getmaxyx(stdscr,yMax,xMax);

	//create a window for the input

	WINDOW* playwin = newwin(20,50,(yMax/2)-10,10);
	box(playwin,0,0);
	refresh();
	wrefresh(playwin);




	Player* p = new Player(playwin,1,1,'@');
	do  {
		p->display();
		wrefresh(playwin);
	} while (p->getmv() != 'x');


	//make sure program waits before exiting...

	getch();
	endwin();
	        */
	
	/*
#pragma region CULOARE



	
if (has_colors() == FALSE)
{
	endwin();
	printf("Your terminal does not support color\n");
	exit(1);
}
start_color();			
init_pair(1, COLOR_MAGENTA, COLOR_WHITE);

attron(COLOR_PAIR(1));
print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
attroff(COLOR_PAIR(1));






// functia asta urmeaza dupa main

void print_in_middle(WINDOW* win, int starty, int startx, int width, const char* str)
{
	int length, x, y;
	float temp;

	if (win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if (startx != 0)
		x = startx;
	if (starty != 0)
		y = starty;
	if (width == 0)
		width = 80;

	length = strlen(str);
	temp = (width - length) / 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", str);
	refresh();

	
} */

	endwin();
	return 0;
}











