#pragma once

#include "stdafx.h"

#define TABLE_ROWS	16
#define TABLE_COLS	11

#define NOTES_COLS	3
#define NOTES_ROWS	1386

using namespace std;

int randomInt(int min, int max);
int rollDice();

vector< vector<int> > readTable();
vector<int> peekSequence();
vector< vector<string> > readNotes();
void composeMusic();