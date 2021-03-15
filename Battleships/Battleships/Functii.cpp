#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Functii.h"
#include <stdlib.h>
#include <stdio.h>
using namespace std;


bool AreLoc3Sus(char matrice[20][20], int i, int j) {
	bool areLoc = true;

	//verific in sus
	for (int k = i ; k >= i - 2; k--)
	{
		if (matrice[k][j] == 'x') {
			areLoc = false;
			break;
		}
		if (Vecini(matrice, k, j)) {
			areLoc = false;
			break;
		}
		if (k - 1 == -1 && k - 1 >= i - 2) {
			areLoc = false;
			break;
		}
	}
	return areLoc;
}
bool AreLoc3Jos(char matrice[20][20], int i, int j) {
	bool areLoc = true;
	for (int k = i; k <= i+2; k++)
	{
		if (matrice[k][j] == 'x') {
			areLoc = false;
			break;
		}
		if (Vecini(matrice, k, j)) {
			areLoc = false;
			break;
		}
		if (k + 1 == 10 && k+1<=i+2) {
			areLoc = false;
			break;
		}
	}
	return areLoc;
}
bool AreLoc3Dreapta(char matrice[20][20], int i, int j) {
	bool areLoc = true;
	for (int k = j; k <= j + 4; k=k+2)
	{
		if (matrice[i][k] == 'x') {
			areLoc = false;
			break;
		}
		if (Vecini(matrice, i, k)) {
			areLoc = false;
			break;
		} 
		if (k + 2 == 20 && k + 2 <= j + 4) {
			areLoc = false;
			break;
		}
	}
	return areLoc;
}
bool AreLoc3Stanga(char matrice[20][20], int i, int j) {
	bool areLoc = true;
	for (int k = j; k >= j - 4; k=k-2)
	{
		if (matrice[i][k] == 'x') {
			areLoc = false;
			break;
		}
		if (Vecini(matrice, i, k)) {
			areLoc = false;
			break;
		}
		if (k - 2 == -2 && k - 2 >= j - 4) {
			areLoc = false;
			break;
		}
	}
	return areLoc;
}
bool Vecini(char matrice[20][20], int i, int j) {
	bool areVecini = false;

	// aici pot sa pun conditii pt fiecare caz (daca numarul este in colt, daca este pe margine
	//, daca este in marginea dreapta, marginea stanga, marginea de sus sau marginea de jos, 
	// sau unul din cele 4 colturi
	
	//colturile
	if (i == 0 && j == 0) {
		if (matrice[0][2] == 'x' || matrice[1][2] == 'x' || matrice[1][0] == 'x' || matrice[0][0]=='x') areVecini = true;
	}
	else if (i == 0 && j == 18) {
		if (matrice[0][16] == 'x' || matrice[1][16] == 'x' || matrice[1][18] == 'x' || matrice[0][18]=='x') areVecini = true;
	}
	else if (i == 9 && j == 18) {
		if (matrice[9][16] == 'x' || matrice[8][16] == 'x' || matrice[8][18] == 'x' || matrice[9][18] == 'x') areVecini = true;
	}
	else if (i == 9 && j == 0) {
		if (matrice[9][2] == 'x' || matrice[8][2] == 'x' || matrice[8][0] == 'x' || matrice[9][0] == 'x') areVecini = true;
	}

	//toate liniile si coloanele marginale
	if (i == 9) {
		if (matrice[i][j] == 'x' || matrice[i][j - 2] == 'x' || matrice[i - 1][j - 4] == 'x' || matrice[i - 1][j] == 'x' || matrice[i - 1][j + 2] == 'x' || matrice[i][j + 2] == 'x') areVecini = true;
	}
	else if (i == 0) {
		if (matrice[i][j] == 'x' || matrice[i][j - 2] == 'x' || matrice[i + 1][j - 2] == 'x' || matrice[i + 1][j] == 'x' || matrice[i + 1][j + 2] == 'x' || matrice[i][j + 2] == 'x') areVecini = true;
	}
	else if (j == 0) {
		if (matrice[i][j] == 'x' || matrice[i - 1][j] == 'x' || matrice[i - 1][j + 2] == 'x' || matrice[i][j +2] == 'x' || matrice[i + 1][j + 2] == 'x' || matrice[i + 1][j] == 'x') areVecini = true;
	}
	else if (j == 18) {
		if (matrice[i][j] == 'x' || matrice[i - 1][j] == 'x' || matrice[i - 1][j - 2] == 'x' || matrice[i][j - 2] == 'x' || matrice[i + 1][j - 2] == 'x' || matrice[i + 1][j] == 'x') areVecini = true;
	}


	else if (matrice[i + 1][j] == 'x' || matrice[i + 1][j + 2] == 'x' || matrice[i][j + 2] == 'x' || matrice[i - 1][j + 2] == 'x' || matrice[i - 1][j] == 'x' || matrice[i - 1][j - 2] == 'x' || matrice[i][j - 2] == 'x' || matrice[i+1][j-2]=='x')
		areVecini = true;
	return areVecini;
}


	

	

	

	

