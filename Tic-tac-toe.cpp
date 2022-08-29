#include <iostream>
#include <vector>
#include "windows.h"
#include <exception>

class Game {																	// Абстрактный родительский класс
public:
	virtual void PvP() = 0;														// Виртуальные методы
	virtual void PvE() = 0;
	virtual void Demo() = 0;
};
//--------------------------------------------------------------------------------------------------------------------------------------
class Five : public Game {														// Класс наследник без наследования родительских методов
private:																		// Крестики-нолики 5х5
	std::vector<std::vector<char>> game_board;
public:
	Five() {																	// Конструктор для вектора 5х5
		game_board = std::vector<std::vector<char>>(5, std::vector<char> (5));
	}
	void PlayerTurn(const char& symb) {											// Ход игрока
		int row, col;
		try {
			std::cout << "Row: ";
			std::cin >> row;
			std::cout << "Column: ";
			std::cin >> col;
			std::cout << std::endl;
			SetSymb(row - 1, col - 1, symb);
		} catch (std::invalid_argument&) {										// При искоюченнии просит повторного ввода
			std::cout << "This cell is not empty!\nPlease try again" << std::endl;
			PlayerTurn(symb);
		}
		PrintBoard();
	}
	void AiTurn(const char& csymb, const char& symb) {							// Ход компьютера
		Sleep(3000);															// Задержка работы Игрока-компьютера
		Ai(csymb, symb);
		PrintBoard();
	}
	bool GameOver(const char& symb) {											// Проверка на окончание игры
		bool toleft = true, toright = true, rows, cols;
		for (int i = 0; i < 5; ++i) {
			rows = true;
			cols = true;
			toleft &= (game_board[i][i] == symb);
			toright &= (game_board[4 - i][i] == symb);
			for (int j = 0; j < 5; ++j) {
				rows &= (game_board[i][j] == symb);
				cols &= (game_board[j][i] == symb);
			}
			if (rows || cols) {
				return true;
			}
		}
		if (toleft || toright) {
			return true;
		}
		return false;
	}
	void SetSymb(const int& row, const int& col, const char& symb) {			// Ввод хода игрока
		if (row >= 0 && row <=4 && col >= 0 && col <=4 && 
			game_board[row][col] != 'X' && game_board[row][col] != 'O') {		// Проверка на корректность введенных данных
			game_board[row][col] = symb;
		} else {
			throw std::invalid_argument("");									// При непрохождении условия выкидывает исключение
		}
	}
	void PrintBoard() {															// Вывод Интерфейса игры на экран
		std::string row = "Row";
		for (int i = 0; i < 5; ++i) {
			if (i == 0) {
				std::cout << "   Column" << std::endl;
				std::cout << "  ";
				for (int n = 0; n < 5; ++n) {
					std::cout << " " << n + 1; 
				}
				std::cout << std::endl;
			}
			if (i < row.size()) {
				std::cout << row[i] << " ";
			} else {
				std::cout << "  ";
			}
			std::cout << i + 1;
			for (int j = 0; j < 5; ++j) {
				if (game_board[i][j] == 'X' || game_board[i][j] == 'O') {
					std::cout << game_board[i][j];
				} else {
					std::cout << " ";
				}
				if (j < 4) {
					std::cout << "|";
				}
			}
			std::cout << std::endl;
			if (i < 4) {
				std::cout << "   ---------" << std::endl;
			}
		}
		std::cout << std::endl;
	}
	bool AiStepToWin_LoseD(char symb, char another_symb, const int& flag) {		// Критический шаг для компьютера чтобы выиграть или 
		char copy;																// предотвратить поражение (по диагоналям)
		int r = 0, rn = 0, l = 0, ln = 0;
		for (int i = 0; i < 5; ++i) {
			if (game_board[i][i] == symb) {
				r += i;
				++rn;
			}
			if (game_board[4 - i][i] == symb) {
				l += i;
				++ln;
			}
		}
		if (flag == 1) {
			copy = symb;
			symb = another_symb;
			another_symb = copy;
		}
		if (rn == 4) {
			if (r = 10 && game_board[4][4] != another_symb && game_board[4][4] != symb) {
				game_board[4][4] = symb;
				return true;
			} else if (r = 11 && game_board[3][3] != another_symb && game_board[3][3] != symb) {
				game_board[3][3] = symb;
				return true;
			} else if (r = 12 && game_board[2][2] != another_symb && game_board[2][2] != symb) {
				game_board[2][2] = symb;
				return true;
			} else if (r = 13 && game_board[1][1] != another_symb && game_board[1][1] != symb) {
				game_board[1][1] = symb;
				return true;
			} else if (r = 14 && game_board[0][0] != another_symb && game_board[0][0] != symb) {
				game_board[0][0] = symb;
				return true;
			}
		}
		if (ln == 4) {
			if (l = 10 && game_board[0][4] != another_symb && game_board[0][4] != symb) {
				game_board[0][4] = symb;
				return true;
			} else if (l = 11 && game_board[1][3] != another_symb && game_board[1][3] != symb) {
				game_board[1][3] = symb;
				return true;
			} else if (l = 12 && game_board[2][2] != another_symb && game_board[2][2] != symb) {
				game_board[2][2] = symb;
				return true;
			} else if (l = 13 && game_board[3][1] != another_symb && game_board[3][1] != symb) {
				game_board[3][1] = symb;
				return true;
			} else if (l = 14 && game_board[4][0] != another_symb && game_board[4][0] != symb) {
				game_board[4][0] = symb;
				return true;
			}
		}
		return false;
	}
	bool AiSteToWin_LoseRC(char symb, char another_symb, const int& flag) {		// Критический шаг для компьютера чтобы выиграть или 
		char copy;																// предотвратить поражение (по строкам и столбцам)
		for (int i = 0; i < 5; ++i) {
			int r = 0, rn = 0, c = 0, cn = 0;
			for (int j = 0; j < 5; ++j) {
				if (game_board[i][j] == symb) {
					r += i;
					++rn;
				}
				if (game_board[j][i] == symb) {
					c += i;
					++cn;
				}
			}
			if (flag == 1) {
				copy = symb;
				symb = another_symb;
				another_symb = copy;
			}
			if (rn == 4) {
				if (r = 10 && game_board[i][4] != another_symb && game_board[i][4] != symb) {
					game_board[i][4] = symb;
					return true;
				} else if (r = 11 && game_board[i][3] != another_symb && game_board[i][3] != symb) {
					game_board[i][3] = symb;
					return true;
				} else if (r = 12 && game_board[i][2] != another_symb && game_board[i][2] != symb) {
					game_board[i][2] = symb;
					return true;
				} else if (r = 13 && game_board[i][1] != another_symb && game_board[i][1] != symb) {
					game_board[i][1] = symb;
					return true;
				} else if (r = 14 && game_board[i][0] != another_symb && game_board[i][0] != symb) {
					game_board[i][0] = symb;
					return true;
				}
			}
			if (cn == 4) {
				if (c = 10 && game_board[4][i] != another_symb && game_board[4][i] != symb) {
					game_board[4][i] = symb;
					return true;
				} else if (c = 11 && game_board[3][i] != another_symb && game_board[3][i] != symb) {
					game_board[3][i] = symb;
					return true;
				} else if (c = 12 && game_board[2][i] != another_symb && game_board[2][i] != symb) {
					game_board[2][i] = symb;
					return true;
				} else if (c = 13 && game_board[1][i] != another_symb && game_board[1][i] != symb) {
					game_board[1][i] = symb;
					return true;
				} else if (c = 14 && game_board[0][i] != another_symb && game_board[0][i] != symb) {
					game_board[0][i] = symb;
					return true;
				}
			}
			if (flag == 1) {
				copy = symb;
				symb = another_symb;
				another_symb = copy;
			}
		}
		return false;
	}
	bool SafeStep(const char& csymb, const char& symb) {						// Безопасный шаг для компютера
		for (int i = 1; i < 4; i += 2) {										// Приоритеты: диагонали -> пустые клетки вне диагоналей
			for (int j = 1; j < 4; j += 2) {
				if (game_board[i][j] != csymb && game_board[i][j] != symb) {
					game_board[i][j] = csymb;
					return true;
				}
			}
		}
		for (int i = 0; i < 5; i += 4) {
			for (int j = 0; j < 5; j += 4) {
				if (game_board[i][j] != csymb && game_board[i][j] != symb) {
					game_board[i][j] = csymb;
					return true;
				}
			}
		}
		for (int i = 0; i < 5; ++i) {
			if (game_board[i][2] != csymb && game_board[i][2] != symb) {
				game_board[i][2] = csymb;
				return true;
			} 
			if (game_board[2][i] != csymb && game_board[2][i] != symb) {
				game_board[2][i] = csymb;
				return true;
			}
		}
		for (int i = 1; i < 4; ++i) {
			if (game_board[i][0] != csymb && game_board[i][0] != symb) {
				game_board[i][0] = csymb;
				return true;
			} 
			if (game_board[0][i] != csymb && game_board[0][i] != symb) {
				game_board[0][i] = csymb;
				return true;
			}
			if (game_board[i][4] != csymb && game_board[i][4] != symb) {
				game_board[i][4] = csymb;
				return true;
			} 
			if (game_board[4][i] != csymb && game_board[4][i] != symb) {
				game_board[4][i] = csymb;
				return true;
			}
		}
		return false;
	}
	void Ai(const char& csymb, const char& symb) {								// Действия компьютера по игре
		if (game_board[2][2] != 'X' && game_board[2][2] != 'O') {				// Приоритеты: центр -> шаг для выигрыша ->
			game_board[2][2] = csymb;											// шаг для предотвращения проигрыша ->
		} else {																// безопасный шаг
			if (AiStepToWin_LoseD(csymb, symb, 0) || AiSteToWin_LoseRC(csymb, symb, 0)) {
				return;
			} else if (AiStepToWin_LoseD(symb, csymb, 1) || AiSteToWin_LoseRC(symb, csymb, 1)) {
				return;
			}
			if (SafeStep(csymb, symb)) {
				return;
			}
		}
	}
	void PvE() {																// Режим игры: Игрок против компьютера
		int row, col, turn, turns;
		char symb, csymb;
		std::string fin = "Draw";
		while(true) {			
			std::cout << "Player turn: ";
			std::cin >> turn;
			if (turn == 1 || turn == 2) {
				break;
			} else {
				std::cout << "Wrong number! Please try again" << std::endl;
			}
		}
		PrintBoard();
		for (int i = 0; i < 13; ++i) {
			if (turn == 1) {
				symb = 'X';
			} else if (turn == 2) {
				symb = 'O';
			}
			if (symb == 'X') {
				csymb = 'O';
			} else if (symb == 'O') {
				csymb = 'X';
			}
			if (turn == 1) {
				PlayerTurn(symb);
				if (GameOver(symb)) {
					fin = "Win";
					break;
				}
				if (i == 12) {
					break;
				}
				AiTurn(csymb, symb);
				if (GameOver(csymb)) {
					fin = "Lose";
					break;
				}
			} else if (turn == 2) {
				AiTurn(csymb, symb);
				if (GameOver(csymb)) {
					fin = "Lose";
					break;
				}
				if (i == 12) {
					break;
				}
				PlayerTurn(symb);
				if (GameOver(symb)) {
					fin = "Win";
					break;
				}

			}
		}
		std::cout << fin << std::endl << std::endl;
	}
	void PvP() {																// Режим игры: Игрок против игрока
		int row, col;
		char symb;
		std::string fin = "Draw";
		PrintBoard();
		for (int i = 0; i < 25; ++i) {
			if (i % 2 == 0) {
				symb = 'X';
				std::cout << "Player 1 turn" << std::endl;
			} else {
				symb = 'O';
				std::cout << "Player 2 turn" << std::endl;
			}
			PlayerTurn(symb);
			if (GameOver(symb)) {
				if (symb == 'X') {
					fin = "Player 1 win";
				} else if (symb == 'O') {
					fin = "Player 2 win";				
				}
				break;
			}
		}
		std::cout << fin << std::endl << std::endl;
	}
	void Demo() {																// Демонстративный режим: Компьютер против компьютера
		char symb, csymb;
		std::string fin = "Draw";
		PrintBoard();
		for (int i = 0; i < 25; ++i) {
			if (i % 2 == 0) {
				symb = 'X';
				csymb = 'O';
			} else {
				csymb = 'X';
				symb = 'O';
			}
			AiTurn(symb, csymb);
			if (GameOver(symb)) {
				if (symb == 'X') {
					fin = "Player 1 win";
				} else {
					fin = "Player 2 win";
				}
				break;
			}
		}
		std::cout << fin << std::endl << std::endl;
	}
};
//--------------------------------------------------------------------------------------------------------------------------------------
class Four : public Game {														// Класс наследник без наследования родительских методов
private:																		// Крестики-нолики 4х4
	std::vector<std::vector<char>> game_board;
public:
	Four() {																	// Конструктор для вектора 4х4
		game_board = std::vector<std::vector<char>>(4, std::vector<char> (4));
	}
	void PlayerTurn(const char& symb) {											// Ход игрока
		int row, col;
		try {
			std::cout << "Row: ";
			std::cin >> row;
			std::cout << "Column: ";
			std::cin >> col;
			std::cout << std::endl;
			SetSymb(row - 1, col - 1, symb);
		} catch (std::invalid_argument&) {										// При искоюченнии просит повторного ввода
			std::cout << "This cell is not empty!\nPlease try again" << std::endl;
			PlayerTurn(symb);
		}
		PrintBoard();
	}
	void AiTurn(const char& csymb, const char& symb) {							// Ход компьютера
		Sleep(3000);															// Задержка работы Игрока-компьютера
		Ai(csymb, symb);
		PrintBoard();
	}
	bool GameOver(const char& symb) {											// Проверка на окончание игры
		bool toleft = true, toright = true, rows, cols;
		for (int i = 0; i < 4; ++i) {
			rows = true;
			cols = true;
			toleft &= (game_board[i][i] == symb);
			toright &= (game_board[3 - i][i] == symb);
			for (int j = 0; j < 4; ++j) {
				rows &= (game_board[i][j] == symb);
				cols &= (game_board[j][i] == symb);
			}
			if (rows || cols) {
				return true;
			}
		}
		if (toleft || toright) {
			return true;
		}
		return false;
	}
	void SetSymb(const int& row, const int& col, const char& symb) {		// Ввод хода игрока
		if (row >= 0 && row <=3 && col >= 0 && col <=3 && 
			game_board[row][col] != 'X' && game_board[row][col] != 'O') {	// Проверка на корректность введенных данных
			game_board[row][col] = symb;
		} else {
			throw std::invalid_argument("");								// При непрохождении условия выкидывает исключение
		}
	}
	void PrintBoard() {														// Вывод Интерфейса игры на экран
		std::string row = "Row";
		for (int i = 0; i < 4; ++i) {
			if (i == 0) {
				std::cout << "   Column" << std::endl;
				std::cout << "  ";
				for (int n = 0; n < 4; ++n) {
					std::cout << " " << n + 1; 
				}
				std::cout << std::endl;
			}
			if (i < row.size()) {
				std::cout << row[i] << " ";
			} else {
				std::cout << "  ";
			}
			std::cout << i + 1;
			for (int j = 0; j < 4; ++j) {
				if (game_board[i][j] == 'X' || game_board[i][j] == 'O') {
					std::cout << game_board[i][j];
				} else {
					std::cout << " ";
				}
				if (j < 3) {
					std::cout << "|";
				}
			}
			std::cout << std::endl;
			if (i < 3) {
				std::cout << "   -------" << std::endl;
			}
		}
		std::cout << std::endl;
	}
	bool AiStepToWin_LoseD(char symb, char another_symb, const int& flag) {		// Критический шаг для компьютера чтобы выиграть или 
		char copy;																// предотвратить поражение (по диагоналям)
		int r = 0, rn = 0, l = 0, ln = 0;
		for (int i = 0; i < 4; ++i) {
			if (game_board[i][i] == symb) {
				r += i;
				++rn;
			}
			if (game_board[3 - i][i] == symb) {
				l += i;
				++ln;
			}
		}
		if (flag == 1) {
			copy = symb;
			symb = another_symb;
			another_symb = copy;
		}
		if (rn == 3) {
			if (r = 3 && game_board[3][3] != another_symb && game_board[3][3] != symb) {
				game_board[3][3] = symb;
				return true;
			} else if (r = 4 && game_board[2][2] != another_symb && game_board[2][2] != symb) {
				game_board[2][2] = symb;
				return true;
			} else if (r = 5 && game_board[1][1] != another_symb && game_board[1][1] != symb) {
				game_board[1][1] = symb;
				return true;
			} else if (r = 6 && game_board[0][0] != another_symb && game_board[0][0] != symb) {
				game_board[0][0] = symb;
				return true;
			}
		}
		if (ln == 3) {
			if (l = 3 && game_board[0][3] != another_symb && game_board[0][3] != symb) {
				game_board[0][3] = symb;
				return true;
			} else if (l = 4 && game_board[1][2] != another_symb && game_board[1][2] != symb) {
				game_board[1][2] = symb;
				return true;
			} else if (l = 5 && game_board[2][1] != another_symb && game_board[2][1] != symb) {
				game_board[2][1] = symb;
				return true;
			} else if (l = 6 && game_board[3][0] != another_symb && game_board[3][0] != symb) {
				game_board[3][0] = symb;
				return true;
			}
		}
		return false;
	}
	bool AiSteToWin_LoseRC(char symb, char another_symb, const int& flag) {		// Критический шаг для компьютера чтобы выиграть или 
		char copy;																// предотвратить поражение (по строкам и столбцам)
		for (int i = 0; i < 4; ++i) {
			int r = 0, rn = 0, c = 0, cn = 0;
			for (int j = 0; j < 4; ++j) {
				if (game_board[i][j] == symb) {
					r += i;
					++rn;
				}
				if (game_board[j][i] == symb) {
					c += i;
					++cn;
				}
			}
			if (flag == 1) {
				copy = symb;
				symb = another_symb;
				another_symb = copy;
			}
			if (rn == 3) {
				if (r = 3 && game_board[i][3] != another_symb && game_board[i][3] != symb) {
					game_board[i][3] = symb;
					return true;
				} else if (r = 4 && game_board[i][2] != another_symb && game_board[i][2] != symb) {
					game_board[i][2] = symb;
					return true;
				} else if (r = 5 && game_board[i][1] != another_symb && game_board[i][1] != symb) {
					game_board[i][1] = symb;
					return true;
				} else if (r = 6 && game_board[i][0] != another_symb && game_board[i][0] != symb) {
					game_board[i][0] = symb;
					return true;
				}
			}
			if (cn == 3) {
				if (c = 3 && game_board[3][i] != another_symb && game_board[3][i] != symb) {
					game_board[3][i] = symb;
					return true;
				} else if (c = 4 && game_board[2][i] != another_symb && game_board[2][i] != symb) {
					game_board[2][i] = symb;
					return true;
				} else if (c = 5 && game_board[1][i] != another_symb && game_board[1][i] != symb) {
					game_board[1][i] = symb;
					return true;
				} else if (c = 6 && game_board[0][i] != another_symb && game_board[0][i] != symb) {
					game_board[0][i] = symb;
					return true;
				}
			}
			if (flag == 1) {
				copy = symb;
				symb = another_symb;
				another_symb = copy;
			}
		}
		return false;
	}
	bool SafeStep(const char& csymb, const char& symb) {						// Безопасный шаг для компьютера
		for (int i = 1; i < 3; ++i) {											// Приоритеты: центр -> диагонали -> пустые клетки вне диагоналей
			for (int j = 1; j < 3; ++j) {
				if (game_board[i][j] != csymb && game_board[i][j] != symb) {
					game_board[i][j] = csymb;
					return true;
				}
			}
		}
		for (int i = 0; i < 4; i += 3) {
			for (int j = 0; j < 4; j += 3) {
				if (game_board[i][j] != csymb && game_board[i][j] != symb) {
					game_board[i][j] = csymb;
					return true;
				}
			}
		}
		for (int i = 0; i < 4; i += 3) {
			if (game_board[i][1] != csymb && game_board[i][1] != symb) {
				game_board[i][1] = csymb;
				return true;
			} 
			if (game_board[i][2] != csymb && game_board[i][2] != symb) {
				game_board[i][2] = csymb;
				return true;
			} 
			if (game_board[1][i] != csymb && game_board[1][i] != symb) {
				game_board[1][i] = csymb;
				return true;
			}
			if (game_board[2][i] != csymb && game_board[2][i] != symb) {
				game_board[2][i] = csymb;
				return true;
			}
		}
		return false;
	}
	void Ai(const char& csymb, const char& symb) {										// Действия компьютера по игре
		if (AiStepToWin_LoseD(csymb, symb, 0) || AiSteToWin_LoseRC(csymb, symb, 0)) {	// Приоритеты: шаг для выигрыша -> шаг для предотвращения проигрыша ->
			return;																		// безопасный шаг
		} else if (AiStepToWin_LoseD(symb, csymb, 1) || AiSteToWin_LoseRC(symb, csymb, 1)) {
			return;
		}
		if (SafeStep(csymb, symb)) {
			return;
		}
	}
	void PvE() {																// Режим игры: Игрок против компьютера
		int row, col, turn;
		char symb, csymb;
		std::string fin = "Draw";
		while(true) {			
			std::cout << "Player turn: ";
			std::cin >> turn;
			if (turn == 1 || turn == 2) {
				break;
			} else {
				std::cout << "Wrong number! Please try again" << std::endl;
			}
		}
		PrintBoard();
		for (int i = 0; i < 8; ++i) {
			if (turn == 1) {
				symb = 'X';
			} else if (turn == 2) {
				symb = 'O';
			}
			if (symb == 'X') {
				csymb = 'O';
			} else if (symb == 'O') {
				csymb = 'X';
			}
			if (turn == 1) {
				PlayerTurn(symb);
				if (GameOver(symb)) {
					fin = "Win";
					break;
				}
				AiTurn(csymb, symb);
				if (GameOver(csymb)) {
					fin = "Lose";
					break;
				}
			} else if (turn == 2) {
				AiTurn(csymb, symb);
				if (GameOver(csymb)) {
					fin = "Lose";
					break;
				}
				PlayerTurn(symb);
				if (GameOver(symb)) {
					fin = "Win";
					break;
				}

			}
		}
		std::cout << fin << std::endl << std::endl;
	}
	void PvP() {																// Режим игры: Игрок против игрока
		int row, col;
		char symb;
		std::string fin = "Draw";
		PrintBoard();
		for (int i = 0; i < 16; ++i) {
			if (i % 2 == 0) {
				symb = 'X';
				std::cout << "Player 1 turn" << std::endl;
			} else {
				symb = 'O';
				std::cout << "Player 2 turn" << std::endl;
			}
			PlayerTurn(symb);
			if (GameOver(symb)) {
				if (symb == 'X') {
					fin = "Player 1 win";
				} else if (symb == 'O') {
					fin = "Player 2 win";				
				}
				break;
			}
		}
		std::cout << fin << std::endl << std::endl;
	}
	void Demo() {																// Демонстративный режим: Компьютер протиа компьютера
		char symb, csymb;
		std::string fin = "Draw";
		PrintBoard();
		for (int i = 0; i < 16; ++i) {
			if (i % 2 == 0) {
				symb = 'X';
				csymb = 'O';
			} else {
				csymb = 'X';
				symb = 'O';
			}
			AiTurn(symb, csymb);
			if (GameOver(symb)) {
				if (symb == 'X') {
					fin = "Player 1 win";
				} else {
					fin = "Player 2 win";
				}
				break;
			}
		}
		std::cout << fin << std::endl << std::endl;
	}
};
//--------------------------------------------------------------------------------------------------------------------------------------
class Three : public Game {														// Класс наследник без наследования родительских методов
private:																		// Крестики-нолики 3х3
	std::vector<std::vector<char>> game_board;
public:
	Three() {																	// Конструктор для вектора 3х3
		game_board = std::vector<std::vector<char>>(3, std::vector<char> (3));
	}
	void PlayerTurn(const char& symb) {											// Ход игрока
		int row, col;
		try {
			std::cout << "Row: ";
			std::cin >> row;
			std::cout << "Column: ";
			std::cin >> col;
			std::cout << std::endl;
			SetSymb(row - 1, col - 1, symb);
		} catch (std::invalid_argument&) {
			std::cout << "This cell is not empty!\nPlease try again" << std::endl;
			PlayerTurn(symb);
		}
		PrintBoard();
	}
	void AiTurn(const char& csymb, const char& symb) {
		Sleep(3000);
		Ai(csymb, symb);
		PrintBoard();
	}
	bool GameOver(const char& symb) {
		bool toleft = true, toright = true, rows, cols;
		for (int i = 0; i < 3; ++i) {
			rows = true;
			cols = true;
			toleft &= (game_board[i][i] == symb);
			toright &= (game_board[2 - i][i] == symb);
			for (int j = 0; j < 3; ++j) {
				rows &= (game_board[i][j] == symb);
				cols &= (game_board[j][i] == symb);
			}
			if (rows || cols) {
				return true;
			}
		}
		if (toleft || toright) {
			return true;
		}
		return false;
	}
	void SetSymb(const int& row, const int& col, const char& symb) {			// Проверка на корректность введенных данных
		if (row >= 0 && row <=2 && col >= 0 && col <=2 && 
			game_board[row][col] != 'X' && game_board[row][col] != 'O') {
			game_board[row][col] = symb;
		} else {
			throw std::invalid_argument("");									// При непрохождении условия выкидывает исключение
		}
	}
	void PrintBoard() {															// Вывод Интерфейса игры на экран
		std::string row = "Row";
		for (int i = 0; i < 3; ++i) {
			if (i == 0) {
				std::cout << "   Column" << std::endl;
				std::cout << "  ";
				for (int n = 0; n < 3; ++n) {
					std::cout << " " << n + 1; 
				}
				std::cout << std::endl;
			}
			if (i < row.size()) {
				std::cout << row[i] << " ";
			} else {
				std::cout << "  ";
			}
			std::cout << i + 1;
			for (int j = 0; j < 3; ++j) {
				if (game_board[i][j] == 'X' || game_board[i][j] == 'O') {
					std::cout << game_board[i][j];
				} else {
					std::cout << " ";
				}
				if (j < 2) {
					std::cout << "|";
				}
			}
			std::cout << std::endl;
			if (i < 2) {
				std::cout << "   -----" << std::endl;
			}
		}
		std::cout << std::endl;
	}
	bool AiStepToWin_LoseD(char symb, char another_symb, const int& flag) {		// Критический шаг для компьютера чтобы выиграть или 
		char copy;																// предотвратить поражение (по диагоналям)
		int r = 0, rn = 0, l = 0, ln = 0;
		for (int i = 0; i < 3; ++i) {
			if (game_board[i][i] == symb) {
				r += i;
				++rn;
			}
			if (game_board[2 - i][i] == symb) {
				l += i;
				++ln;
			}
		}
		if (flag == 1) {
			copy = symb;
			symb = another_symb;
			another_symb = copy;
		}
		if (rn == 2) {
			if (r = 1 && game_board[2][2] != another_symb && game_board[2][2] != symb) {
				game_board[2][2] = symb;
				return true;
			} else if (r = 2 && game_board[1][1] != another_symb && game_board[1][1] != symb) {
				game_board[1][1] = symb;
				return true;
			} else if (r = 3 && game_board[0][0] != another_symb && game_board[0][0] != symb) {
				game_board[0][0] = symb;
				return true;
			}
		}
		if (ln == 2) {
			if (l = 1 && game_board[0][2] != another_symb && game_board[0][2] != symb) {
				game_board[0][2] = symb;
				return true;
			} else if (l = 2 && game_board[1][1] != another_symb && game_board[1][1] != symb) {
				game_board[1][1] = symb;
				return true;
			} else if (l = 3 && game_board[2][0] != another_symb && game_board[2][0] != symb) {
				game_board[2][0] = symb;
				return true;
			}
		}
		return false;
	}
	bool AiSteToWin_LoseRC(char symb, char another_symb, const int& flag) {		// Критический шаг для компьютера чтобы выиграть или 
		char copy;																// предотвратить поражение (по строкам и столбцам)
		for (int i = 0; i < 3; ++i) {
			int r = 0, rn = 0, c = 0, cn = 0;
			for (int j = 0; j < 3; ++j) {
				if (game_board[i][j] == symb) {
					r += i;
					++rn;
				}
				if (game_board[j][i] == symb) {
					c += i;
					++cn;
				}
			}
			if (flag == 1) {
				copy = symb;
				symb = another_symb;
				another_symb = copy;
			}
			if (rn == 2) {
				if (r = 1 && game_board[i][2] != another_symb && game_board[i][2] != symb) {
					game_board[i][2] = symb;
					return true;
				} else if (r = 2 && game_board[i][1] != another_symb && game_board[i][1] != symb) {
					game_board[i][1] = symb;
					return true;
				} else if (r = 3 && game_board[i][0] != another_symb && game_board[i][0] != symb) {
					game_board[i][0] = symb;
					return true;
				}
			}
			if (cn == 2) {
				if (c = 1 && game_board[2][i] != another_symb && game_board[2][i] != symb) {
					game_board[2][i] = symb;
					return true;
				} else if (c = 2 && game_board[1][i] != another_symb && game_board[1][i] != symb) {
					game_board[1][i] = symb;
					return true;
				} else if (c = 3 && game_board[0][i] != another_symb && game_board[0][i] != symb) {
					game_board[0][i] = symb;
					return true;
				}
			}
			if (flag == 1) {
				copy = symb;
				symb = another_symb;
				another_symb = copy;
			}
		}
		return false;
	}
	bool SafeStep(const char& csymb, const char& symb) {						// Безопасный шаг для компютера
		for (int i = 0; i < 3; i += 2) {										// Приоритеты: диагонали -> пустые клетки вне диагоналей
			for (int j = 0; j < 3; j += 2) {
				if (game_board[i][j] != csymb && game_board[i][j] != symb) {
					game_board[i][j] = csymb;
					return true;
				}
			}
		}
		for (int i = 0; i < 3; i += 2) {
			if (game_board[i][1] != csymb && game_board[i][1] != symb) {
				game_board[i][1] = csymb;
				return true;
			} 
			if (game_board[1][i] != csymb && game_board[1][i] != symb) {
				game_board[1][i] = csymb;
				return true;
			}
		}
		return false;
	}
	void Ai(const char& csymb, const char& symb) {								// Действия компьютера по игре
		if (game_board[1][1] != 'X' && game_board[1][1] != 'O') {				// Приоритеты: центр -> шаг для выигрыша ->
			game_board[1][1] = csymb;											// шаг для предотвращения проигрыша ->
		} else {																// безопасный шаг
			if (AiStepToWin_LoseD(csymb, symb, 0) || AiSteToWin_LoseRC(csymb, symb, 0)) {
				return;
			} else if (AiStepToWin_LoseD(symb, csymb, 1) || AiSteToWin_LoseRC(symb, csymb, 1)) {
				return;
			}
			if (SafeStep(csymb, symb)) {
				return;
			}
		}
	}
	void PvE() {																// Режим игры: Игрок против компьютера
		int row, col, turn;
		char symb, csymb;
		std::string fin = "Draw";
		while(true) {			
			std::cout << "Player turn: ";
			std::cin >> turn;
			if (turn == 1 || turn == 2) {
				break;
			} else {
				std::cout << "Wrong number! Please try again" << std::endl;
			}
		}
		PrintBoard();
		for (int i = 0; i < 5; ++i) {
			if (turn == 1) {
				symb = 'X';
				csymb = 'O';
			} else if (turn == 2) {
				symb = 'O';
				csymb = 'X';
			}
			if (turn == 1) {
				PlayerTurn(symb);
				if (GameOver(symb)) {
					fin = "Win";
					break;
				}
				if (i == 4) {
					break;
				}
				AiTurn(csymb, symb);
				if (GameOver(csymb)) {
					fin = "Lose";
					break;
				}
			} else if (turn == 2) {
				AiTurn(csymb, symb);
				if (GameOver(csymb)) {
					fin = "Lose";
					break;
				}
				if (i == 4) {
					break;
				}
				PlayerTurn(symb);
				if (GameOver(symb)) {
					fin = "Win";
					break;
				}

			}
		}
		std::cout << fin << std::endl << std::endl;
	}
	void PvP() {																// Режим игры: Игрое против игрока
		int row, col;
		char symb;
		std::string fin = "Draw";
		PrintBoard();
		for (int i = 0; i < 9; ++i) {
			if (i % 2 == 0) {
				symb = 'X';
				std::cout << "Player 1 turn" << std::endl;
			} else {
				symb = 'O';
				std::cout << "Player 2 turn" << std::endl;
			}
			PlayerTurn(symb);
			if (GameOver(symb)) {
				if (symb == 'X') {
					fin = "Player 1 win";
				} else if (symb == 'O') {
					fin = "Player 2 win";				
				}
				break;
			}
		}
		std::cout << fin << std::endl << std::endl;
	}
	void Demo() {																// Демонстративный режим: Компьютер против компьютера
		char symb, csymb;
		std::string fin = "Draw";
		PrintBoard();
		for (int i = 0; i < 9; ++i) {
			if (i % 2 == 0) {
				symb = 'X';
				csymb = 'O';
			} else {
				csymb = 'X';
				symb = 'O';
			}
			AiTurn(symb, csymb);
			if (GameOver(symb)) {
				if (symb == 'X') {
					fin = "Player 1 win";
				} else {
					fin = "Player 2 win";
				}
				break;
			}
		}
		std::cout << fin << std::endl << std::endl;
	}
};
//--------------------------------------------------------------------------------------------------------------------------------------
class MainMenu {																// Главное меню
public:
	void Menu1() {																// Вывод меню для выбора игры
		std::cout << menu1 << std::endl;
	}
	void Menu2(const int& m1, Game& game) {										// Вывод меню для выбора режима игры
		int m2;																	// Передача объекта через родительский класс
		std::cout << menu2 << std::endl;
		std::cin >> m2;
		std::cout << std::endl;
		if (m2 == 0) {
			return;
		} else if (m2 == 1) {
			game.PvE();															// При вызове виртуальных методов, вызываются одноименные
		} else if (m2 == 2) {													// методы созданных объектов из конкретного наследуемого
			game.PvP();															// класса
		} else if (m2 == 3){
			game.Demo();
		} else {
			std::cout << "Please choose correct number" << std::endl;
		}
	}
private:
	std::string menu1 = "1. 3 x 3\n2. 4 x 4\n3. 5 x 5\n0. Exit\n";
	std::string menu2 = "1. 1 player\n2. 2 players\n3. 0 players (demo game)\n0. Back\n";
};

int main() {
	MainMenu menu;																// Создание объекта класса MainMenu
	int m1, m2;
	std::cout << "Press ENTER to start";
	std::cin.ignore();
	while (true) {
		menu.Menu1();
		std::cin >> m1;
		std::cout << std::endl;
		if (m1 == 0) {
			break;
		} else if (m1 == 1) {
			Three game;															// Создание объекта класса Three
			menu.Menu2(m1, game);
		} else if (m1 == 2) {
			Four game;															// Создание объекта класса Four
			menu.Menu2(m1, game);
		} else if (m1 == 3){
			Five game;															// Создание объекта класса Five
			menu.Menu2(m1, game);
		} else {
			std::cout << "Please choose correct number" << std::endl;
		}
	}
	std::cout << "Thanks for playing!\nSee you next time" << std::endl;
	std::cin.ignore();
	std::cin.get();
	return 0;
}