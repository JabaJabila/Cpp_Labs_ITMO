#include <iostream>
#include <utility>
#include <string>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <stdexcept>

const char UP[4]    = {0, 0, 0, 2};
const char DOWN[4]  = {2, 2, 0, 2};
const char LEFT[4]  = {0, 2, 0, 0};
const char RIGHT[4] = {0, 2, 2, 2};

const std::pair<const char, const char*> ROTATION_IND[6][4] =  {{{5, DOWN},  {3, UP},    {2, UP},    {1, UP}},
											 					{{0, LEFT},  {2, LEFT},  {4, LEFT},  {5, LEFT}},
																{{0, DOWN},  {3, LEFT},  {4, UP},    {1, RIGHT}},
																{{0, RIGHT}, {5, RIGHT}, {4, RIGHT}, {2, RIGHT}},
																{{2, DOWN},  {3, DOWN},  {5, UP},    {1, DOWN}},
																{{4, DOWN},  {3, RIGHT}, {0, UP},    {1, LEFT}}};

class Cube {
public:
	Cube() {
		for (char i = 0; i < 6; ++i)
			for (char j = 0; j < 3; ++j) {
				sides[i][j][0] = i + 48;
				sides[i][j][1] = i + 48;
				sides[i][j][2] = i + 48;
			}
	}

	void d90_right_rotation(const char s) {
		if (s > 5 || s < 0)
			throw std::logic_error("Number of side must be in range [0..5]\n");

		char x = 0, y;
		char tmp1[3][3];

		for (char j = 0; j < 3; ++j) {
			y = 0;
			for (char i = 3; i > 0; --i) {
				tmp1[x][y] = sides[s][i - 1][j];
				++y;
			}
			++x;
		}

		for (char i = 0; i < 3; ++i)
			for (char j = 0; j < 3; ++j)
				sides[s][i][j] = tmp1[i][j];

		char tmp2[4][3];
		x = 0;

		for (char k = 0; k < 4; ++k) {
			y = 0;
			for (char i = ROTATION_IND[s][k].second[0]; i <= ROTATION_IND[s][k].second[1]; ++i)
				for (char j = ROTATION_IND[s][k].second[2]; j <= ROTATION_IND[s][k].second[3]; ++j) {
					tmp2[x][y] = sides[ROTATION_IND[s][k].first][i][j];
					++y;
				}
			if ((s == 0 && (k == 0 || k == 3)) || (s == 2 && (k == 1 || k == 3))  || (s == 4 && (k == 1 || k == 2))  || (s == 5 && (k == 0 || k == 2)))
				std::swap(tmp2[x][0], tmp2[x][2]);
			++x;
		}

		x = 0;
		for (char k = 0; k < 4; ++k) {
			y = 0;
			for (char i = ROTATION_IND[s][(k + 1) % 4].second[0]; i <= ROTATION_IND[s][(k + 1) % 4].second[1]; ++i)
				for (char j = ROTATION_IND[s][(k + 1) % 4].second[2]; j <= ROTATION_IND[s][(k + 1) % 4].second[3]; ++j) {
					sides[ROTATION_IND[s][(k + 1) % 4].first][i][j] = tmp2[x][y];
					++y;
				}
			++x;
		}	
	}

	void d90_left_rotation(const char s) {
		d90_right_rotation(s);
		d90_right_rotation(s);
		d90_right_rotation(s);
	}

	void d180_rotation(const char s) {
		d90_right_rotation(s);
		d90_right_rotation(s);
	}

	std::string shuffle(std::string combination = "", bool rand = true) {
		if (combination == "") {
			if (rand)
				std::srand(time(nullptr));
			unsigned turns = std::rand() % 150 + 50;
			unsigned num;
			std::string tmp;
			std::string answer = "";
			for (unsigned i = 1; i <= turns; ++i) {
				num = std::rand() % 18;
				make_turn(num);
				tmp = translate(num);
				answer += tmp;
				if (i != turns)
					answer += ' ';
			}
			return answer;
		}
		int pos = combination.find(" ");
		char turn;
		std::string tmp;
		while (pos != -1 && combination.size() > 1) {
			tmp = combination.substr(0, pos);
			combination = combination.substr(pos + 1, combination.size());
			pos = combination.find(" ");
			turn = translate(tmp);
			make_turn(turn);
		}
		turn = translate(combination);
		make_turn(turn);
		return combination;
	}

	friend std::ostream& operator<<(std::ostream&, const Cube&);

	bool check_lower_flower() {
		return (sides[4][0][1] == 52 && sides[4][1][0] == 52 && sides[4][1][2] == 52 && sides[4][2][1] == 52);
	}

	bool check_lower_cross() {
		return (check_lower_flower() && sides[1][2][1] == 49 && sides[2][2][1] == 50 && sides[3][2][1] == 51 && sides[5][0][1] == 53);
	}

	bool check_first_layer() {
		return (check_lower_cross() && sides[4][0][0] == 52 && sides[4][0][2] == 52 && sides[4][2][0] == 52 && sides[4][2][2] == 52
			    && sides[2][2][0] == 50 && sides[2][2][2] == 50 && sides[5][0][0] == 53 && sides[5][0][2] == 53);
	}

	bool check_second_layer() {
		return (check_first_layer() && sides[2][1][0] == 50 && sides[2][1][2] == 50 && sides[1][1][0] == 49 && sides[1][1][2] == 49
			    && sides[3][1][0] == 51 && sides[3][1][2] == 51 && sides[5][1][0] == 53 && sides[5][1][2] == 53);
	}

	bool check_upper_flower() {
		return (check_second_layer() && sides[0][0][1] == 48 && sides[0][1][0] == 48 && sides[0][1][2] == 48 && sides[0][2][1] == 48);
	}

	bool check_upper_cross() {
		return (check_upper_flower() && sides[1][0][1] == 49 && sides[2][0][1] == 50 && sides[3][0][1] == 51 && sides[5][2][1] == 53);
	}

	bool check_complete() {
		return (check_upper_cross() && sides[0][0][0] == 48 && sides[0][0][2] == 48 && sides[0][2][0] == 48 && sides[0][2][2] == 48
			    && sides[1][0][0] == 49 && sides[1][0][2] == 49 && sides[3][0][0] == 51 && sides[3][0][2] == 51);
	}

	void make_turn(char num) {
		char side = num / 3;
		char turn = num % 3;
		switch (turn) {
			case 0:
				d90_right_rotation(side);
				break;
			case 1:
				d180_rotation(side);
				break;
			case 2:
				d90_left_rotation(side);
				break;
		}
	}

private:
	char sides[6][3][3];

	static std::string translate(char num) {
		std::string answer = "";
		char side = num / 3;
		char turn = num % 3;
		switch (side) {
			case 0:
				answer += 'U';
				break;
			case 1:
				answer += 'L';
				break;
			case 2:
				answer += 'F';
				break;
			case 3:
				answer += 'R';
				break;
			case 4:
				answer += 'D';
				break;
			case 5:
				answer += 'B';
				break;
			default:
				throw std::logic_error("Impossible num to translate to turn!");
		}
		switch (turn) {
			case 0:
				break;
			case 1:
				answer += '2';
				break;
			case 2:
				answer += '\'';
				break;
		}
		return answer;
	}

	static char translate(std::string& str) {
		char side, turn;
		switch (str[0]) {
			case 'U':
				side = 0;
				break;
			case 'L':
				side = 1;
				break;
			case 'F':
				side = 2;
				break;
			case 'R':
				side = 3;
				break;
			case 'D':
				side = 4;
				break;
			case 'B':
				side = 5;
				break;
			default:
				throw std::logic_error("Turn form isn't correct!");
				break;
		}

		if (str.size() == 1) 
			turn = 0;
		else if (str[1] == '2')
			turn = 1;
		else
			turn = 2;
		return 3 * side + turn;
	}
};


std::ostream& operator<<(std::ostream& stream, const Cube& cube) {
	for (char i = 0; i < 3; ++i) {
		stream << "       ";
		for (char j = 0; j < 3; ++j)
			stream << cube.sides[0][i][j] << ' ';
		stream << '\n';
	}
	stream << '\n';
	for (char i = 0; i < 3; ++i) {
		for (char j = 1; j < 4; ++j) {
			for (char k = 0; k < 3; ++k)
				stream << cube.sides[j][i][k] << ' ';
			stream << ' ';
		}
		stream << '\n';
	}
	stream << '\n';
	for (char i = 4; i < 6; ++i) {
		for (char k = 0; k < 3; ++k) {
			stream << "       ";
			for (char j = 0; j < 3; ++j)
				stream << cube.sides[i][k][j] << ' ';
			stream << '\n';
		}
		stream << '\n';
	}
	return stream;
}


class Solver {
public:
	explicit Solver() : genome(new char[100]), fitness(0) {
		for (unsigned i = 0; i < 100; ++i)
			genome[i] = std::rand() % 50;
	}

	Solver(const Solver& other) : genome(new char[100]), fitness(other.fitness) {
		for (unsigned i = 0; i < 100; ++i)
			genome[i] = other.genome[i];
	}

	Solver& operator=(const Solver& other) {
		if (other != *this) {
			for (unsigned i = 0; i < 100; ++i)
				genome[i] = other.genome[i];
		}
		fitness = other.fitness;
		return *this;
	}

	~Solver() {
		delete[] genome;
	}

	bool operator==(const Solver& other) const {
		for (unsigned i = 0; i < 100; ++i)
			if (genome[i] != other.genome[i])
				return false;
		return true;
	}

	bool operator!=(const Solver& other) const {return !(*this == other);}

	char operator[](unsigned num) {
		return genome[num % 100];
	}

	void mutate() {
		unsigned r = std::rand() % 3 + 1;
		unsigned ind;
		for (unsigned i = 0; i < r; ++i) {
			ind = std::rand() % 100;
			genome[ind] = std::rand() % 50;
		}
	}

	void solve(Cube cube) {
		unsigned curr = 0;
		char g;
		bool flags[7] = {false, false, false, false, false, false, false};
		for (unsigned i = 0; i < 150; ++i) {
			g = (*this)[curr];
			if (g < 18)
				cube.make_turn(g);
			else if (g > 24) {
				curr += ((g - 24) * 4);
			}
			else {
				switch (g) {
					case(18):
						if (cube.check_lower_flower())
							if (!flags[0]) {
								flags[0] = true;
								fitness += 1;
							}
						else
							++curr;
						break;
					case(19):
						if (cube.check_lower_cross())
							if (!flags[1]) {
								flags[1] = true;
								fitness += 10;
							}
						else
							++curr;
						break;
					case(20):
						if (cube.check_first_layer())
							if (!flags[2]) {
								flags[2] = true;
								fitness += 50;
							}
						else
							++curr;
						break;
					case(21):
						if (cube.check_second_layer())
							if (!flags[3]) {
								flags[3] = true;
								fitness += 100;
							}
						else
							++curr;
						break;
					case(22):
						if (cube.check_upper_flower())
							if (!flags[4]) {
								flags[4] = true;
								fitness += 500;
							}
						else
							++curr;
						break;
					case(23):
						if (cube.check_upper_cross())
							if (!flags[5]) {
								flags[5] = true;
								fitness += 50;
							}
						else
							++curr;
						break;
					case(24):
						if (cube.check_complete()) {
							fitness += 10000;
							flags[6] = true;
						}
						else
							++curr;
						break;
				}
			}
			if (flags[6])
				break;
			++curr;
		}
	}

	unsigned get_fitness() const {return fitness;}
	void clear_fitness() {fitness = 0;}


private:
	char* genome;
	unsigned fitness;
};


int main() {

	Solver best_10[10];
	std::srand(time(nullptr));

	Solver* algos = new Solver[100];
	// Cube* cubes;
	Cube cube;
	std::cout << cube.shuffle() << "\n";
	std::cout << cube;

	unsigned counter = 0;
	bool flag = true;

	while (flag) {
		++counter;
		// cubes = new Cube[100];

		// for (unsigned i = 0; i < 100; ++i) {
		// 	cubes[i].shuffle("", false);
		// }
		std::srand(counter);
		for (unsigned k = 0; k < 100; ++k) {
			//for (unsigned i = 0; i < 100; ++i) {
				algos[k].solve(cube); //
			//}
			if (algos[k].get_fitness() >= 1000) {
				std::cout << "\nFound algorithm\n";
				for (unsigned j = 0; j < 100; ++j)
					std::cout << algos[k][j] + 0 << ' ';
				flag = false;
			}
		}

		std::sort(algos, algos + 100, [](Solver& a, Solver& b) {return a.get_fitness() > b.get_fitness();});
		std::cout << "\nGeneration #" << counter << "\nBest fitness = " << algos[0].get_fitness();
		// std::cout << "\n";
		// for (unsigned k = 0; k < 100; ++k) {
		// 	std::cout << algos[0][k] + 0<< ' ';
		// }
		// std::cout << "\n";
		for (unsigned i = 0; i < 10; ++i) {
			algos[i].clear_fitness();
			best_10[i] = algos[i];
		}

		for (unsigned i = 0; i < 10; ++i) {
			for (unsigned j = i * 10; j < i * 10 + 10; ++j) {
				algos[j] = best_10[i];
				if (j != 0)
					algos[j].mutate();
			}
		}

	//delete[] cubes; 
	}

	//delete[] cubes;
	delete[] algos;

	return 0;
}