#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Pin
{
public:
	Pin() : Pin(' ', 0, 0) {};
	Pin(char pin, int setpow, int setdef) : type(pin), power(setpow), defence(setdef) {};

	void move(Pin &target);
	void battle(Pin &loser);
	void defeated();
	bool get_is_move();
	char get_type();

	friend ostream& operator <<(ostream& os, const Pin& p);

private:
	bool is_move = false;
	char type; // u, re, ty
	int power;
	int defence;
};

void Pin::move(Pin &target) 
{
	Pin temp;

	temp.type = type;
	temp.power = power;
	temp.defence = defence;
	temp.is_move = true;

	type = target.type;
	power = target.power;
	defence = target.defence;
	is_move = target.is_move;

	target.type = temp.type;
	target.power = temp.power;
	target.defence = temp.defence;
	target.is_move = temp.is_move;
}

void Pin::battle(Pin &loser) 
{
}

char Pin::get_type() 
{
	return type;
}

bool Pin::get_is_move() 
{
	return is_move;
}

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
	int menu;
	int x, y, x2, y2;
	int whereto;
	bool isright = false;

		set_stage1();

		Game_Mode = 2;
		while (Game_Mode == 2) 
		{
			print_stage();
			cout << "1. Move. 2. Battle 3. Submit" << endl;
			cin >> menu;
			switch (menu)
			{
			case 1:
				//Move
				cout << "Input target x, y coordinates" << endl;
				cout << "X : ";
				cin >> x;
				cout << "Y : ";
				cin >> y;

				if (game_board[x][y].get_is_move() == true) 
				{
					cout << "you already moved that Pin!" << endl;
					continue;
				}
				cout << "you choose " << game_board[x][y] << ". where to move ?" << endl;
				while (isright == false) 
				{
					cout << "1. Up  2. Left  3. Right  4. Down" << endl;
					cin >> whereto;
					switch (whereto)
					{
					case 1:
						//up
						if (x - 1 >= 0 && x - 1 < game_board.size())
						{
							game_board[x][y].move(game_board[x - 1][y]);
							isright = true;
						}
						else
						{
							cout << "Not valid position!" << endl;
						}
						break;
					case 2:
						//left
						if (y - 1 >= 0 && y - 1 < game_board[x].size())
						{
							game_board[x][y].move(game_board[x][y - 1]);
							isright = true;
						}
						else
						{
							cout << "Not valid position!" << endl;
						}
						break;
					case 3:
						//right
						if (y + 1 >= 0 && y + 1 < game_board[x].size())
						{
							game_board[x][y].move(game_board[x][y + 1]);
							isright = true;
						}
						else
						{
							cout << "Not valid position!" << endl;
						}
						break;
					case 4:
						//down
						if (x + 1 >= 0 && x + 1 < game_board.size())
						{
							game_board[x][y].move(game_board[x + 1][y]);
							isright = true;
						}
						else
						{
							cout << "Not valid position!" << endl;
						}
						break;
					default:
						cout << "Input wrong answer please Input value again" << endl;
					}
				}
				break;
			case 2:
				//Battle
				cout << "Input attack U's x, y coordinates." << endl;
				cout << "X : ";
				cin >> x;
				cout << "Y : ";
				cin >> y;
				if (game_board[x][y].get_type() != 'U') 
				{
					cout << "It is not U's position!" << endl;
					continue;
				}
				cout << "Input attacked U's x, y coordinates." << endl;
				cout << "X : ";
				cin >> x2;
				cout << "Y : ";
				cin >> y2;
				if (game_board[x2][y2].get_type() != 'U')
				{
					cout << "It is not U's position!" << endl;
					continue;
				}
				break;
			case 3:
				cout << "hi I'm menu 3" << endl;
				break;
			default:
				cout << "input wrong answer please Input again" << endl;
			}
		}
			
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