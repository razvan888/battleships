#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

bool AreLoc3Sus(char matrice[20][20], int i, int j);
bool AreLoc3Jos(char matrice[20][20], int i, int j);
bool AreLoc3Dreapta(char matrice[20][20], int i, int j);
bool AreLoc3Stanga(char matrice[20][20], int i, int j);
bool Vecini(char matrice[20][20], int i, int j);