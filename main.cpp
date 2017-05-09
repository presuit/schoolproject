#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Pin
{
public:
	Pin() : type(' '), power(0), defence(0) {};
	Pin(char pin, int setpow, int setdef) : type(pin), power(setpow), defence(setdef) {};

	void battle();
	void defeated();

	friend ostream& operator <<(ostream& os, const Pin& p);

private:
	bool is_move = false;
	char type; // u, re, ty
	int power;
	int defence;
};


ostream& operator <<(ostream& os, const Pin& p) 
{
	os << p.type;
	return os;
}

vector <vector<Pin>> game_board;
vector <Pin> _game_board;

const int PRE_GAME = 0;
const int READY_GAME = 1;
const int IN_GAME = 2;
const int OUT_OF_GAME = 3;
const int END_GAME = 4;

int Game_Mode = 0;

void set_stage1();
void print_stage();

int main()
{
	do
	{
		set_stage1();
		print_stage();
	} while (Game_Mode  != 4);
	return 0;
}


void set_stage1()
{
	for (int i = 0; i < 4; i++)
	{
		game_board.push_back(_game_board);
	}

	game_board[0].push_back(Pin('T', 1, 0));
	game_board[0].push_back(Pin('R', 0, 0));
	game_board[0].push_back(Pin('T', 1, 0));
	game_board[0].push_back(Pin('Y', 1, 0));

	game_board[1].push_back(Pin('T', 1, 0));
	game_board[1].push_back(Pin('R', 0, 0));
	game_board[1].push_back(Pin('U', 0, 0));
	game_board[1].push_back(Pin('R', 0, 0));

	game_board[2].push_back(Pin('E', 0, 0));
	game_board[2].push_back(Pin('U', 0, 0));
	game_board[2].push_back(Pin('E', 0, 0));
	game_board[2].push_back(Pin('Y', 1, 0));

	game_board[3].push_back(Pin('Y', 1, 0));
	game_board[3].push_back(Pin('R', 0, 0));
	game_board[3].push_back(Pin('Y', 1, 0));
	game_board[3].push_back(Pin('R', 0, 0));
}

void print_stage() 
{
	for (int i = 0; i < game_board.size(); i++)
	{
		for (int j = 0; j < game_board[i].size(); j++)
		{
			cout << setw(2) << game_board[i][j];
		}
		cout << endl;
	}
}