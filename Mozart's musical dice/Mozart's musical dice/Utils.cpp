#include "stdafx.h"
#include "Utils.h"



int randomInt(int min, int max)
{
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(min, max);
	int random = dist(engine);
	return random;
}

int rollDice()
{
	int dice1 = randomInt(1, 6);
	int dice2 = randomInt(1, 6);

	return dice1 + dice2;
}

vector<vector<int>> readTable()
{
	vector< vector<int> > table;
	ifstream fin("dice.txt");
	int rows = TABLE_ROWS;
	int cols = TABLE_COLS;
	table.resize(rows);
	for (int i = 0; i < rows; i++)
		table[i].resize(cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			fin >> table[i][j];
	return table;
}

vector<int> peekSequence()
{
	vector< vector<int> > table = readTable();
	vector<int> seq;
	int rows = TABLE_ROWS;

	for (int i = 0; i < rows; i++)
	{
		int dice = rollDice();
		seq.push_back(table[i][dice - 1]);
	}
	return seq;
}

vector<vector<string>> readNotes()
{
	ifstream fin("notes.txt");
	vector < vector<string> > notes;

	int cols = NOTES_COLS;
	int n = NOTES_ROWS;

	for (int i = 0; i < n; i++)
	{
		notes.push_back({"", "", ""});
		for (int j = 0; j < cols; j++)
		{
			string s;
			fin >> s;
			notes[i][j] = s;
		}
	}

	return notes;
}

void composeMusic()
{
	ofstream fout("song.txt");
	vector<vector<string>> notes = readNotes();
	vector<int> seq = peekSequence();
	int measure = 0;
	int size = TABLE_ROWS;
	int n = NOTES_ROWS;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < n; j++)
		{
			double beat = stod(notes[j][1]);
			if (beat >= seq[i] && beat < seq[i] + 3)
			{
				cout << notes[j][0] << " " << beat - (seq[i] - measure) << " " << notes[j][2] << endl;
				fout << notes[j][0] << " " << beat - (seq[i] - measure) << " " << notes[j][2] << endl;
			}
			if (beat >= seq[i] + 3)
				break;
		}
		measure += 3;
	}
}
