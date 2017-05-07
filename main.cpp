#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Pin
{
public:
	Pin(char pin, int setpow, int setdef) : type(pin), power(setpow), defence(setdef) {};

	void move();
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

int Game_Mode;

void set_stage1();
void print_stage();

int main()
{
	set_stage1();
	print_stage();

	return 0;
}


void set_stage1()
{
	Pin K1('U', 0, 0), K2('U', 0, 0), PT1('T', 1, 0), PT2('T', 1, 0), PT3('T', 1, 0),
		SR1('R', 0, 0), SR2('R', 0, 0), SR3('R', 0, 0), SR4('R', 0, 0), SR5('R', 0, 0),
		SE1('E', 0, 0), SE2('E', 0, 0), PY1('Y', 1, 0), PY2('Y', 1, 0), PY3('Y', 1, 0), PY4('Y', 1, 0);

	for (int i = 0; i < 4; i++)
	{
		game_board.push_back(_game_board);
	}

	game_board[0].push_back(PT1);
	game_board[0].push_back(SR1);
	game_board[0].push_back(PT2);
	game_board[0].push_back(PY1);

	game_board[1].push_back(PT3);
	game_board[1].push_back(SR2);
	game_board[1].push_back(K1);
	game_board[1].push_back(SR3);

	game_board[2].push_back(SE1);
	game_board[2].push_back(K2);
	game_board[2].push_back(SE2);
	game_board[2].push_back(PY2);

	game_board[3].push_back(PY3);
	game_board[3].push_back(SR4);
	game_board[3].push_back(SR5);
	game_board[3].push_back(PY4);
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