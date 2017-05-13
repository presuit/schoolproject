#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

class Pin
{
public:
	Pin() : Pin(' ', ' ', 0, 0) {};
	Pin(char settype, char setpin, int setpow, int setdef) : type(settype), pin(setpin), power(setpow), defence(setdef) {};

	void move(Pin &target);
	void battle(Pin &loser);

	bool get_is_move();
	char get_type();
	char get_pin();
	int get_power();

	void add_power();
	void reset_power();
	void print_power();//for test, before submit it, delete this

	friend ostream& operator <<(ostream& os, const Pin& p);

private:
	bool is_move = false;
	char pin; // U RE TY
	char type; // King, Servant, People
	int power;
	int defence;
};

void Pin::move(Pin &target)
{
	Pin temp;

	temp.type = type;
	temp.pin = pin;
	temp.power = power;
	temp.defence = defence;
	temp.is_move = true;

	type = target.type;
	pin = target.pin;
	power = target.power;
	defence = target.defence;
	is_move = target.is_move;

	target.type = temp.type;
	target.pin = temp.pin;
	target.power = temp.power;
	target.defence = temp.defence;
	target.is_move = temp.is_move;
}

void Pin::battle(Pin &loser)
{
	int Class;
	int pick;
	bool isOk = false;

	do
	{
		cout << endl;
		cout << "Battle end" << endl;
		cout << "select changed King's class" << endl;
		cout << "1. Servant 2. People" << endl;
		cin >> Class;

		switch (Class)
		{
		case 1:
			pick = rand() % 2;
			if (pick == 0)
			{
				loser.type = 'S';
				loser.pin = 'R';
			}
			else if (pick == 1)
			{
				loser.type = 'S';
				loser.pin = 'E';
			}
			isOk = true;
			break;
		case 2:
			pick = rand() % 2;
			if (pick == 0)
			{
				loser.type = 'P';
				loser.pin = 'T';
			}
			else if (pick == 1)
			{
				loser.type = 'P';
				loser.pin = 'Y';
			}
			isOk = true;
			break;
		default:
			cout << "It is not valid value!" << endl;
			continue;
		}
	} while (isOk == false);

}

void Pin::reset_power()
{
	power = 0;
}

void Pin::print_power()
{
	cout << "The power : " << power << endl;
}

void Pin::add_power()
{
	power += 1;
}

char Pin::get_type()
{
	return type;
}

char Pin::get_pin()
{
	return pin;
}

bool Pin::get_is_move()
{
	return is_move;
}

int Pin::get_power()
{
	return power;
}

ostream& operator <<(ostream& os, const Pin& p)
{
	os << p.pin;
	return os;
}

vector <vector<Pin>> game_board;
vector <Pin> _game_board;

const int PRE_GAME = 1;
const int READY_GAME = 2;
const int IN_GAME = 3;
const int OUT_OF_GAME = 4;
const int END_GAME = 5;

int Game_Mode = 1;
int STAGE = 1;

void set_stageN();
void print_stage();
void check_stage();

int move();
int battle();

int main()
{
	int menu;
	int varMove;
	int varBattle;
	
	bool endGame = false;

	while (endGame == false) 
	{
		switch (Game_Mode)
		{
		case 1:
			//PRE_GAME
			//도입부 게임 인트로 장면 삽입부.
			//UI 개선 시간때 삽입 예졍
			Game_Mode = 2;
			break;
		case 2:
			//READY_GAME
			set_stageN();
			Game_Mode = 3;
			break;
		case 3:
			//IN_GAME
			while (Game_Mode == 3)
			{
				print_stage();
				cout << "=======================" << endl;
				cout << "1. Move. 2. Battle" << endl;
				cout << "=======================" << endl;
				cout << "Menu (1~2) : ";
				cin >> menu;
				switch (menu)
				{
				case 1:
					//Move
					varMove = move();
					if (varMove == 1)
						continue;
					break;
				case 2:
					//Battle
					varBattle = battle();
					if (varBattle == 1)
						continue;
					break;
				default:
					cout << endl;
					cout << "Input wrong answer please Input again" << endl;
				}
				check_stage();
			}
			break;
		case 4:
			//OUT_OF_GAME
			STAGE++;
			game_board.clear();
			if (STAGE == 3)
			{
				Game_Mode = 5;
			}
			Game_Mode = 2;
			break;
		case 5:
			//END_GAME
			cout << endl;
			cout << "You got True Eye! Congratulation " << endl;
			cout << endl;
			endGame = true;
			break;
		}
	}
	return 0;
}


int move() 
{
	int x, y, whereto;
	bool isright = false;

	cout << endl;
	cout << "Input target x, y coordinates" << endl;
	cout << "X : ";
	cin >> x;
	if (x > game_board.size())
	{
		cout << endl;
		cout << "It is not valid position!" << endl;
		return 1;
	}
	cout << "Y : ";
	cin >> y;
	if (y > game_board[x].size())
	{
		cout << endl;
		cout << "It is not valid position!" << endl;
		return 1;
	}
	if (game_board[x][y].get_type() == 'K') 
	{
		cout << endl;
		cout << "You can't move King!" << endl;
		return 1;
	}
	if (game_board[x][y].get_is_move() == true)
	{
		cout << endl;
		cout << "you already moved that Pin!" << endl;
		return 1;
	}
	cout << endl;
	cout << "you choose " << game_board[x][y] << ". where to move ?" << endl;
	isright = false;
	while (isright == false)
	{
		cout << "===================================" << endl;
		cout << "1. Up  2. Left  3. Right  4. Down" << endl;
		cout << "===================================" << endl;
		cin >> whereto;
		switch (whereto)
		{
		case 1:
			//up
			if (x - 1 >= 0 && x - 1 < game_board.size())
			{
				if (game_board[x-1][y].get_type() == 'K') 
				{
					cout << endl;
					cout << "You can't move King!" << endl;
					continue;
				}
				game_board[x][y].move(game_board[x - 1][y]);
				isright = true;
			}
			else
			{
				cout << endl;
				cout << "Not valid position!" << endl;
			}
			break;
		case 2:
			//left
			if (y - 1 >= 0 && y - 1 < game_board[x].size())
			{
				if (game_board[x][y-1].get_type() == 'K')
				{
					cout << endl;
					cout << "You can't move King!" << endl;
					continue;
				}
				game_board[x][y].move(game_board[x][y - 1]);
				isright = true;
			}
			else
			{
				cout << endl;
				cout << "Not valid position!" << endl;
			}
			break;
		case 3:
			//right
			if (y + 1 >= 0 && y + 1 < game_board[x].size())
			{
				if (game_board[x][y+1].get_type() == 'K')
				{
					cout << endl;
					cout << "You can't move King!" << endl;
					continue;
				}
				game_board[x][y].move(game_board[x][y + 1]);
				isright = true;
			}
			else
			{
				cout << endl;
				cout << "Not valid position!" << endl;
			}
			break;
		case 4:
			//down
			if (x + 1 >= 0 && x + 1 < game_board.size())
			{
				if (game_board[x+1][y].get_type() == 'K')
				{
					cout << endl;
					cout << "You can't move King!" << endl;
					continue;
				}
				game_board[x][y].move(game_board[x + 1][y]);
				isright = true;
			}
			else
			{
				cout << endl;
				cout << "Not valid position!" << endl;
			}
			break;
		default:
			cout << endl;
			cout << "Input wrong answer please Input value again" << endl;
		}
	}

	return 0;
}

int battle()
{
	int x, y, x2, y2;
	bool canIWage = false;

	cout << endl;
	cout << "Input attack U's x, y coordinates." << endl;
	cout << "X : ";
	cin >> x;
	if (x > game_board.size())
	{
		cout << endl;
		cout << "It is not valid position!" << endl;
		return 1;
	}
	cout << "Y : ";
	cin >> y;
	if (y > game_board[x].size())
	{
		cout << endl;
		cout << "It is not valid position!" << endl;
		return 1;
	}
	if (game_board[x][y].get_type() != 'K')
	{
		cout << endl;
		cout << "It is not U's position!" << endl;
		return 1;
	}
	cout << endl;
	cout << "Input attacked U's x, y coordinates." << endl;
	cout << "X : ";
	cin >> x2;
	cout << "Y : ";
	cin >> y2;
	if (game_board[x2][y2].get_type() != 'K')
	{
		cout << endl;
		cout << "It is not U's position!" << endl;
		return 1;
	}
	//check can wage battle  
	if (x - 1 <= game_board.size() && y - 1 <= game_board[x - 1].size())
	{
		if (game_board[x - 1][y - 1].get_type() == 'K')
		{
			canIWage = true;
		}
	}
	if (x - 1 <= game_board.size() && y <= game_board[x - 1].size())
	{
		if (game_board[x - 1][y].get_type() == 'K')
		{
			canIWage = true;
		}
	}
	if (x - 1 <= game_board.size() && y + 1 <= game_board[x - 1].size())
	{
		if (game_board[x - 1][y + 1].get_type() == 'K')
		{
			canIWage = true;
		}
	}
	if (x <= game_board.size() && y - 1 <= game_board[x].size())
	{
		if (game_board[x][y - 1].get_type() == 'K')
		{
			canIWage = true;
		}
	}
	if (x <= game_board.size() && y + 1 <= game_board[x].size())
	{
		if (game_board[x][y + 1].get_type() == 'K')
		{
			canIWage = true;
		}
	}
	if (x + 1 <= game_board.size() && y - 1 <= game_board[x + 1].size())
	{
		if (game_board[x + 1][y - 1].get_type() == 'K')
		{
			canIWage = true;
		}
	}
	if (x + 1 <= game_board.size() && y <= game_board[x + 1].size())
	{
		if (game_board[x + 1][y].get_type() == 'K')
		{
			canIWage = true;
		}
	}
	if (x + 1 <= game_board.size() && y + 1 <= game_board[x + 1].size())
	{
		if (game_board[x + 1][y + 1].get_type() == 'K')
		{
			canIWage = true;
		}
	}

	if (canIWage == true) 
	{
		//find People x, y
		if (x - 1 <= game_board.size() && y - 1 <= game_board[x - 1].size())
		{
			if (game_board[x - 1][y - 1].get_type() == 'P')
			{
				game_board[x][y].add_power();
			}
		}
		if (x - 1 <= game_board.size() && y <= game_board[x - 1].size())
		{
			if (game_board[x - 1][y].get_type() == 'P')
			{
				game_board[x][y].add_power();
			}
		}
		if (x - 1 <= game_board.size() && y + 1 <= game_board[x - 1].size())
		{
			if (game_board[x - 1][y + 1].get_type() == 'P')
			{
				game_board[x][y].add_power();
			}
		}
		if (x <= game_board.size() && y - 1 <= game_board[x].size())
		{
			if (game_board[x][y - 1].get_type() == 'P')
			{
				game_board[x][y].add_power();
			}
		}
		if (x <= game_board.size() && y + 1 <= game_board[x].size())
		{
			if (game_board[x][y + 1].get_type() == 'P')
			{
				game_board[x][y].add_power();
			}
		}
		if (x + 1 <= game_board.size() && y - 1 <= game_board[x + 1].size())
		{
			if (game_board[x + 1][y - 1].get_type() == 'P')
			{
				game_board[x][y].add_power();
			}
		}
		if (x + 1 <= game_board.size() && y <= game_board[x + 1].size())
		{
			if (game_board[x + 1][y].get_type() == 'P')
			{
				game_board[x][y].add_power();
			}
		}
		if (x + 1 <= game_board.size() && y + 1 <= game_board[x + 1].size())
		{
			if (game_board[x + 1][y + 1].get_type() == 'P')
			{
				game_board[x][y].add_power();
			}
		}
		//x2, y2
		if (x2 - 1 <= game_board.size() && y2 - 1 <= game_board[x2 - 1].size())
		{
			if (game_board[x2 - 1][y2 - 1].get_type() == 'P')
			{
				game_board[x2][y2].add_power();
			}
		}
		if (x2 - 1 <= game_board.size() && y2 <= game_board[x2 - 1].size())
		{
			if (game_board[x2 - 1][y2].get_type() == 'P')
			{
				game_board[x2][y2].add_power();
			}
		}
		if (x2 - 1 <= game_board.size() && y2 + 1 <= game_board[x2 - 1].size())
		{
			if (game_board[x2 - 1][y2 + 1].get_type() == 'P')
			{
				game_board[x2][y2].add_power();
			}
		}
		if (x2 <= game_board.size() && y2 - 1 <= game_board[x2].size())
		{
			if (game_board[x2][y2 - 1].get_type() == 'P')
			{
				game_board[x2][y2].add_power();
			}
		}
		if (x2 <= game_board.size() && y2 + 1 <= game_board[x2].size())
		{
			if (game_board[x2][y2 + 1].get_type() == 'P')
			{
				game_board[x2][y2].add_power();
			}
		}
		if (x2 + 1 <= game_board.size() && y2 - 1 <= game_board[x2 + 1].size())
		{
			if (game_board[x2 + 1][y2 - 1].get_type() == 'P')
			{
				game_board[x2][y2].add_power();
			}
		}
		if (x2 + 1 <= game_board.size() && y2 <= game_board[x2 + 1].size())
		{
			if (game_board[x2 + 1][y2].get_type() == 'P')
			{
				game_board[x2][y2].add_power();
			}
		}
		if (x2 + 1 <= game_board.size() && y2 + 1 <= game_board[x2 + 1].size())
		{
			if (game_board[x2 + 1][y2 + 1].get_type() == 'P')
			{
				game_board[x2][y2].add_power();
			}
		}

		if (game_board[x][y].get_power() > game_board[x2][y2].get_power())
		{
			game_board[x][y].battle(game_board[x2][y2]);
		}
		else if (game_board[x][y].get_power() < game_board[x2][y2].get_power())
		{
			game_board[x2][y2].battle(game_board[x][y]);
		}
		else
		{
			cout << endl;
			cout << "Both King's power are same , can't wage war" << endl;
			game_board[x][y].reset_power();
			game_board[x2][y2].reset_power();
			return 1;
		}
		game_board[x][y].reset_power();
		game_board[x2][y2].reset_power();
	}
	else 
	{
		cout << endl;
		cout << "There is no King around ( " << x << ", " << y << " )!" << endl;
		return 1;
	}

	return 0;
}

void set_stageN()
{
	switch (STAGE) 
	{
	case 1:
		for (int i = 0; i < 4; i++)
		{
			game_board.push_back(_game_board);
		}

		game_board[0].push_back(Pin('P', 'T', 1, 0));
		game_board[0].push_back(Pin('S', 'R', 0, 0));
		game_board[0].push_back(Pin('P', 'T', 1, 0));
		game_board[0].push_back(Pin('P', 'Y', 1, 0));

		game_board[1].push_back(Pin('P', 'T', 1, 0));
		game_board[1].push_back(Pin('S', 'R', 0, 0));
		game_board[1].push_back(Pin('K', 'U', 0, 0));
		game_board[1].push_back(Pin('S', 'R', 0, 0));

		game_board[2].push_back(Pin('S', 'E', 0, 0));
		game_board[2].push_back(Pin('K', 'U', 0, 0));
		game_board[2].push_back(Pin('S', 'E', 0, 0));
		game_board[2].push_back(Pin('P', 'Y', 1, 0));

		game_board[3].push_back(Pin('P', 'Y', 1, 0));
		game_board[3].push_back(Pin('S', 'R', 0, 0));
		game_board[3].push_back(Pin('P', 'Y', 1, 0));
		game_board[3].push_back(Pin('S', 'R', 0, 0));
		break;
	case 2:
		for (int i = 0; i < 3; i++) 
		{
			game_board.push_back(_game_board);
		}

		game_board[0].push_back(Pin('K', 'U', 0, 0));
		game_board[0].push_back(Pin('S', 'R', 0, 0));
		game_board[0].push_back(Pin('P', 'T', 1, 0));
		game_board[0].push_back(Pin('P', 'Y', 1, 0));

		game_board[1].push_back(Pin('P', 'T', 1, 0));
		game_board[1].push_back(Pin('S', 'R', 0, 0));
		game_board[1].push_back(Pin('K', 'U', 0, 0));
		game_board[1].push_back(Pin('S', 'R', 0, 0));

		game_board[2].push_back(Pin('S', 'E', 0, 0));
		game_board[2].push_back(Pin('K', 'U', 0, 0));
		game_board[2].push_back(Pin('S', 'E', 0, 0));
		game_board[2].push_back(Pin('P', 'Y', 1, 0));
		break;
	default: 
		break;
	}
}

void print_stage()
{
	cout << endl;
	cout << "#Stage[ " << STAGE << " ]" << endl;
	cout << "----------" << endl;
	for (int i = 0; i < game_board.size(); i++)
	{
		for (int j = 0; j < game_board[i].size(); j++)
		{
			cout << setw(2) << game_board[i][j];
		}
		cout << endl;
	}
	cout << "----------" << endl;
	cout << endl;
}

void check_stage() 
{
	int countK = 0;
	int countS = 0;

	for (int i = 0; i < game_board.size(); i++) 
	{
		for (int j = 0; j < game_board[i].size(); j++) 
		{
			if (game_board[i][j].get_type() == 'K') 
			{
				countK++;
				if (i-1 <= game_board.size() && j <= game_board[i-1].size()) 
				{
					if (game_board[i - 1][j].get_type() == 'S') 
					{
						countS++;
					}
				}
				if (i <= game_board.size() && j-1 <= game_board[i].size())
				{
					if (game_board[i][j-1].get_type() == 'S')
					{
						countS++;
					}
				}
				if (i <= game_board.size() && j+1 <= game_board[i].size())
				{
					if (game_board[i][j+1].get_type() == 'S')
					{
						countS++;
					}
				}
				if (i + 1 <= game_board.size() && j <= game_board[i + 1].size())
				{
					if (game_board[i + 1][j].get_type() == 'S')
					{
						countS++;
					}
				}
			}
		}
	}

	if (countK == 1 && countS == 4) 
	{
		cout << endl;
		cout << "Stage clear" << endl;
		cout << "Move on next stage." << endl;
		cout << "This is test version" << endl;
		sleep_until(system_clock::now() + 2s);
		Game_Mode = 4;
	}
}
