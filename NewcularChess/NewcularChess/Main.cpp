#include <iostream>
#include <stdlib.h>
using namespace std;


char gb[9][7];
int mv[10][126];
int mvSize = 5;
int mvCol;
int maxDepth = 5;
int min(int depth);
int max(int depth);
int evaluate();
int check4winner();
void moveGen(int turn, int depth);
void boardInit();
void printBoard();
void getMove();
void checkGameOver();
void makeMove();
void printMoves();

int main(){
	boardInit();
	printBoard();
	int turn;
	cout << "Would you like move 1 or 2?" << endl;
	cin >> turn;
	if (turn == 1) {
		for (;;) {
			getMove();
			printBoard();
			checkGameOver();
			makeMove();
			printBoard();
			checkGameOver();
		}
	}
	else {
		for (;;) {
			makeMove();
			printBoard();
			checkGameOver();
			getMove();
			printBoard();
			checkGameOver();
		}
	}
}

void boardInit() {
	//Initialize Gameboard
	gb[0][0] = '-'; gb[0][1] = 'N'; gb[0][2] = 'R'; gb[0][3] = 'K'; gb[0][4] = 'R'; gb[0][5] = 'N'; gb[0][6] = '-'; //Row 1
	gb[1][0] = '-'; gb[1][1] = '-'; gb[1][2] = '-'; gb[1][3] = 'B'; gb[1][4] = '-';	gb[1][5] = '-';	gb[1][6] = '-';	//Row 2
	gb[2][0] = '-';	gb[2][1] = '-';	gb[2][2] = '-';	gb[2][3] = 'B';	gb[2][4] = '-';	gb[2][5] = '-'; gb[2][6] = '-'; //Row 3
	gb[3][0] = 'P';	gb[3][1] = '-';	gb[3][2] = 'P';	gb[3][3] = '-';	gb[3][4] = 'P';	gb[3][5] = '-';	gb[3][6] = 'P'; //Row 4
	gb[4][0] = '-';	gb[4][1] = '-';	gb[4][2] = '-';	gb[4][3] = '-';	gb[4][4] = '-';	gb[4][5] = '-';	gb[4][6] = '-'; //Row 5
	gb[5][0] = 'p';	gb[5][1] = '-';	gb[5][2] = 'p';	gb[5][3] = '-';	gb[5][4] = 'p';	gb[5][5] = '-';	gb[5][6] = 'p'; //Row 6
	gb[6][0] = '-';	gb[6][1] = '-';	gb[6][2] = '-';	gb[6][3] = 'b';	gb[6][4] = '-';	gb[6][5] = '-';	gb[6][6] = '-'; //Row 7
	gb[7][0] = '-';	gb[7][1] = '-';	gb[7][2] = '-';	gb[7][3] = 'b';	gb[7][4] = '-';	gb[7][5] = '-';	gb[7][6] = '-'; //Row 8
	gb[8][0] = '-';	gb[8][1] = 'n';	gb[8][2] = 'r';	gb[8][3] = 'k';	gb[8][4] = 'r';	gb[8][5] = 'n';	gb[8][6] = '-'; //Row 9

	//Initialize move list
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 126; j++) {
			mv[i][j] = 0;
		}
	}
}

void printBoard() {
	cout << endl;
	cout << "  -----------------------------" << endl;
	cout << "9 | " << gb[0][0] << " | " << gb[0][1] << " | " << gb[0][2] << " | " << gb[0][3] << " | " << gb[0][4] << " | " << gb[0][5] << " | " << gb[0][6] << " | " << endl;
	cout << "  -----------------------------" << endl;
	cout << "8 | " << gb[1][0] << " | " << gb[1][1] << " | " << gb[1][2] << " | " << gb[1][3] << " | " << gb[1][4] << " | " << gb[1][5] << " | " << gb[1][6] << " | " << endl;
	cout << "  -----------------------------" << endl;
	cout << "7 | " << gb[2][0] << " | " << gb[2][1] << " | " << gb[2][2] << " | " << gb[2][3] << " | " << gb[2][4] << " | " << gb[2][5] << " | " << gb[2][6] << " | " << endl;
	cout << "  -----------------------------" << endl;
	cout << "6 | " << gb[3][0] << " | " << gb[3][1] << " | " << gb[3][2] << " | " << gb[3][3] << " | " << gb[3][4] << " | " << gb[3][5] << " | " << gb[3][6] << " | " << endl;
	cout << "  -----------------------------" << endl;
	cout << "5 | " << gb[4][0] << " | " << gb[4][1] << " | " << gb[4][2] << " | " << gb[4][3] << " | " << gb[4][4] << " | " << gb[4][5] << " | " << gb[4][6] << " | " << endl;
	cout << "  -----------------------------" << endl;
	cout << "4 | " << gb[5][0] << " | " << gb[5][1] << " | " << gb[5][2] << " | " << gb[5][3] << " | " << gb[5][4] << " | " << gb[5][5] << " | " << gb[5][6] << " | " << endl;
	cout << "  -----------------------------" << endl;
	cout << "3 | " << gb[6][0] << " | " << gb[6][1] << " | " << gb[6][2] << " | " << gb[6][3] << " | " << gb[6][4] << " | " << gb[6][5] << " | " << gb[6][6] << " | " << endl;
	cout << "  -----------------------------" << endl;
	cout << "2 | " << gb[7][0] << " | " << gb[7][1] << " | " << gb[7][2] << " | " << gb[7][3] << " | " << gb[7][4] << " | " << gb[7][5] << " | " << gb[7][6] << " | " << endl;
	cout << "  -----------------------------" << endl;
	cout << "1 | " << gb[8][0] << " | " << gb[8][1] << " | " << gb[8][2] << " | " << gb[8][3] << " | " << gb[8][4] << " | " << gb[8][5] << " | " << gb[8][6] << " | " << endl;
	cout << "  -----------------------------" << endl;
	cout << "    a   b   c   d   e   f   g " << endl;

}
void makeMove() {
	int best = -20000, depth = 0, score, myMove, c, d, mi, mj, ma, mb;
	char temp, a, b;
	moveGen(0, depth);
	for (int i = 0; i < mv[0][0]; i++) {
		if (mv[0][i*mvSize + 1] == 1) {
			// make move
			ma = mv[0][i*mvSize + 2];
			mb = mv[0][i*mvSize + 3];
			mi = mv[0][i * mvSize + 4];
			mj = mv[0][i*mvSize + 5];
			temp = gb[mi][mj];
			gb[mi][mj] = gb[ma][mb];
			gb[ma][mb] = '-';
			score = min(depth + 1);

			if (score > best) {
				myMove = i;
				best = score;
			}
			//undo move
			gb[ma][mb] = gb[mi][mj];
			gb[mi][mj] = temp;
		}
	}
	for (int i = 0; i < mv[0][0]; i++) {
		if (mv[0][i*mvSize + 1] == 0) {
			// make move
			ma = mv[0][i*mvSize + 2];
			mb = mv[0][i*mvSize + 3];
			mi = mv[0][i * mvSize + 4];
			mj = mv[0][i*mvSize + 5];
			temp = gb[mi][mj];
			gb[mi][mj] = gb[ma][mb];
			gb[ma][mb] = '-';
			score = min(depth + 1);

			if (score > best) {
				myMove = i;
				best = score;
			}
			//undo move
			gb[ma][mb] = gb[mi][mj];
			gb[mi][mj] = temp;
		}
	}

	switch (mv[0][myMove*mvSize + 3]) {
	case 0: a = 'A'; break;
	case 1: a = 'B'; break;
	case 2: a = 'C'; break;
	case 3: a = 'D'; break;
	case 4: a = 'E'; break;
	case 5: a = 'F'; break;
	case 6: a = 'G'; break;
	}
	switch (mv[0][myMove*mvSize + 2]) {
	case 0: c = 9; break;
	case 1: c = 8; break;
	case 2: c = 7; break;
	case 3: c = 6; break;
	case 4: c = 5; break;
	case 5: c = 4; break;
	case 6: c = 3; break;
	case 7: c = 2; break;
	case 8: c = 1; break;
	}
	switch (mv[0][myMove*mvSize + 5]) {
	case 0: b = 'A'; break;
	case 1: b = 'B'; break;
	case 2: b = 'C'; break;
	case 3: b = 'D'; break;
	case 4: b = 'E'; break;
	case 5: b = 'F'; break;
	case 6: b = 'G'; break;
	}
	switch (mv[0][myMove*mvSize + 4]) {
	case 0: d = 9; break;
	case 1: d = 8; break;
	case 2: d = 7; break;
	case 3: d = 6; break;
	case 4: d = 5; break;
	case 5: d = 4; break;
	case 6: d = 3; break;
	case 7: d = 2; break;
	case 8: d = 1; break;
	}

	ma = mv[0][myMove*mvSize + 2];
	mb = mv[0][myMove*mvSize + 3];
	mi = mv[0][myMove* mvSize + 4];
	mj = mv[0][myMove*mvSize + 5];
	temp = gb[mi][mj];
	gb[mi][mj] = gb[ma][mb];
	gb[ma][mb] = '-';
	cout << "My move is: " << a << c << b << d;

}
int min(int depth) {
	moveGen(1, depth);
	int best = 20000, score, ma, mb, mi, mj;
	char temp;
	if (check4winner() != -1) return (check4winner());
	if (depth == maxDepth) return (evaluate());
	for (int i = 0; i < mv[0][0]; i++) {
		if (mv[0][i*mvSize + 1] == 1) {
			// make move
			ma = mv[0][i*mvSize + 2];
			mb = mv[0][i*mvSize + 3];
			mi = mv[0][i * mvSize + 4];
			mj = mv[0][i*mvSize + 5];
			temp = gb[mi][mj];
			gb[mi][mj] = gb[ma][mb];
			gb[ma][mb] = '-';
			score = min(depth + 1);

			if (score < best) {
			
				best = score;
			}
			//undo move
			gb[ma][mb] = gb[mi][mj];
			gb[mi][mj] = temp;
		}
	}
	for (int i = 0; i < mv[0][0]; i++) {
		if (mv[0][i*mvSize + 1] == 0) {
			// make move
			ma = mv[0][i*mvSize + 2];
			mb = mv[0][i*mvSize + 3];
			mi = mv[0][i * mvSize + 4];
			mj = mv[0][i*mvSize + 5];
			temp = gb[mi][mj];
			gb[mi][mj] = gb[ma][mb];
			gb[ma][mb] = '-';
			score = min(depth + 1);

			if (score < best) {

				best = score;
			}
			//undo move
			gb[ma][mb] = gb[mi][mj];
			gb[mi][mj] = temp;
		}
	}
	return best;
}
int max(int depth) {
	moveGen(0, depth);
	int best = -20000, score, ma, mb, mi, mj;
	char temp;
	if (check4winner() != -1) return (check4winner());
	if (depth == maxDepth) return (evaluate());
	for (int i = 0; i < mv[0][0]; i++) {
		if (mv[0][i*mvSize + 1] == 1) {
			// make move
			ma = mv[0][i*mvSize + 2];
			mb = mv[0][i*mvSize + 3];
			mi = mv[0][i * mvSize + 4];
			mj = mv[0][i*mvSize + 5];
			temp = gb[mi][mj];
			gb[mi][mj] = gb[ma][mb];
			gb[ma][mb] = '-';
			score = min(depth + 1);

			if (score > best) {

				best = score;
			}
			//undo move
			gb[ma][mb] = gb[mi][mj];
			gb[mi][mj] = temp;
		}
	}
	for (int i = 0; i < mv[0][0]; i++) {
		if (mv[0][i*mvSize + 1] == 0) {
			// make move
			ma = mv[0][i*mvSize + 2];
			mb = mv[0][i*mvSize + 3];
			mi = mv[0][i * mvSize + 4];
			mj = mv[0][i*mvSize + 5];
			temp = gb[mi][mj];
			gb[mi][mj] = gb[ma][mb];
			gb[ma][mb] = '-';
			score = min(depth + 1);

			if (score > best) {

				best = score;
			}
			//undo move
			gb[ma][mb] = gb[mi][mj];
			gb[mi][mj] = temp;
		}
	}
	return best;
}
int evaluate() {
	int total = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 7; j++) {
			if (gb[i][j] == 'k') total -= 5000;
			if (gb[i][j] == 'K') total += 5000;
			if (gb[i][j] == 'b') total -= 5;
			if (gb[i][j] == 'B') total += 5;
			if (gb[i][j] == 'n') total -= 7;
			if (gb[i][j] == 'N') total += 7;
			if (gb[i][j] == 'R') total -= 6;
			if (gb[i][j] == 'R') total += 6;
			if (gb[i][j] == 'p') total -= 3;
			if (gb[i][j] == 'P') total += 3;
		}
	}
	return total;
}
int check4winner() {
	int total = -1;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 7; j++) {
			if (gb[i][j] == 'k') total -= 5000;
			if (gb[i][j] == 'K') total += 5000;
		}
	}
	return total;
}
void checkGameOver() {
	if (check4winner() == -5000) {
		cout << "You Win!" << endl;
		exit(0);
	}
	else if (check4winner() == 5000) {
		cout << "I Win!" << endl;
		exit(0);
	}
	
	
}

void getMove() {
	moveGen(1, 0);
	printMoves();
	char x, y, i, j, piece; // char inputs from player. and piece type
	int a, b, c, d; // interger conversion of char for array 
	bool validMove = false;
	while (!validMove) {
		cout << "Move From: " << endl;
		cin >> x >> y;
		cout << "Move To: " << endl;
		cin >> i >> j;
		cout << "x:" << x << " y:" << y << " i:" << i << " j:" << j << endl;

		switch (x) {
		case 'a': a = 0; break;
		case 'b': a = 1; break;
		case 'c': a = 2; break;
		case 'd': a = 3; break;
		case 'e': a = 4; break;
		case 'f': a = 5; break;
		case 'g': a = 6; break;
		}

		switch (y) {
		case '1': b = 8; break;
		case '2': b = 7; break;
		case '3': b = 6; break;
		case '4': b = 5; break;
		case '5': b = 4; break;
		case '6': b = 3; break;
		case '7': b = 2; break;
		case '8': b = 1; break;
		case '9': b = 0; break;
		}

		switch (i) {
		case 'a': c = 0; break;
		case 'b': c = 1; break;
		case 'c': c = 2; break;
		case 'd': c = 3; break;
		case 'e': c = 4; break;
		case 'f': c = 5; break;
		case 'g': c = 6; break;
		}

		switch (j) {
		case '1': d = 8; break;
		case '2': d = 7; break;
		case '3': d = 6; break;
		case '4': d = 5; break;
		case '5': d = 4; break;
		case '6': d = 3; break;
		case '7': d = 2; break;
		case '8': d = 1; break;
		case '9': d = 0; break;
		}
		for (int move = 0; move < mv[0][0]; move++) {
			if (mv[0][move*mvSize + 2] == b && mv[0][move*mvSize + 3] == a && mv[0][move*mvSize + 4] == d && mv[0][move*mvSize + 5] == c) {
				piece = gb[b][a];
				gb[b][a] = '-';
				gb[d][c] = piece;
				validMove = true;
			}
		}
		if (!validMove) cout << "That was not a valid move" << endl;
	}

}

/*
Generates all possible moves for each piece on the board. An integer turn is passed in that is incrememented after each move.
Using turn % 2, the generator will determine if it needs to generate moves for the computer or human.
*/
void moveGen(int turn, int depth) {
	int player = turn % 2; // 0 is computer, 1 is human
						   //vector<legalMoves>moves = lmoves;

	mv[depth][0] = 0;
	bool forward;
	bool left;
	bool right;
	bool back;
	bool fdl;
	bool fdr;
	bool bdl;
	bool bdr;
	int count;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			char p = gb[i][j];
			if (player == 0)
			{
				switch (p)
				{
				case 'P':
					if (i < 8) {
						if (gb[i + 1][j] == '-')
						{
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 1;
							mv[depth][mvCol + 5] = j;
							mv[depth][0]++;
						}
						if (j < 6)
						{
							if (gb[i + 1][j + 1] == 'p' || gb[i + 1][j + 1] == 'n' || gb[i + 1][j + 1] == 'b' ||
								gb[i + 1][j + 1] == 'r' || gb[i + 1][j + 1] == 'k')
							{

								mvCol = mv[depth][0] * mvSize;
								mv[depth][mvCol + 1] = 1;
								mv[depth][mvCol + 2] = i;
								mv[depth][mvCol + 3] = j;
								mv[depth][mvCol + 4] = i + 1;
								mv[depth][mvCol + 5] = j + 1;
								mv[depth][0]++;
							}
						}
						if (j > 0)
						{
							if (gb[i + 1][j - 1] == 'p' || gb[i + 1][j - 1] == 'n' || gb[i - 1][j - 1] == 'b' ||
								gb[i + 1][j - 1] == 'r' || gb[i + 1][j - 1] == 'k')
							{
								mvCol = mv[depth][0] * mvSize;
								mv[depth][mvCol + 1] = 1;
								mv[depth][mvCol + 2] = i;
								mv[depth][mvCol + 3] = j;
								mv[depth][mvCol + 4] = i - 1;
								mv[depth][mvCol + 5] = j - 1;
								mv[depth][0]++;
							}
						}
					}
					break;
				case 'N':
					if (i + 2 <= 8 && j + 1 <= 6) {
						if (gb[i + 2][j + 1] == '-') {
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 2;
							mv[depth][mvCol + 5] = j + 1;
							mv[depth][0]++;
						}
						else if (gb[i + 2][j + 1] == 'p' || gb[i + 2][j + 1] == 'n' || gb[i + 2][j + 1] == 'b' ||
							gb[i + 2][j + 1] == 'r' || gb[i + 2][j + 1] == 'k')
						{
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 2;
							mv[depth][mvCol + 5] = j + 1;
							mv[depth][0]++;
						}
					}
					if (i + 1 <= 8 && j + 2 <= 6) {
						if (gb[i + 1][j + 2] == '-') {
							
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 1;
							mv[depth][mvCol + 5] = j + 2;
							mv[depth][0]++;
						}
						else if (gb[i + 1][j + 2] == 'p' || gb[i + 1][j + 2] == 'n' || gb[i + 1][j + 2] == 'b' ||
							gb[i + 1][j + 2] == 'r' || gb[i + 1][j + 2] == 'k')
						{
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 1;
							mv[depth][mvCol + 5] = j + 2;
							mv[depth][0]++;
						}
					}
					if (i + 2 <= 8 && j - 1 >= 0) {
						if (gb[i + 2][j - 1] == '-') {

							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 2;
							mv[depth][mvCol + 5] = j - 1;
							mv[depth][0]++;
						}
						else if (gb[i + 2][j - 1] == 'p' || gb[i + 2][j - 1] == 'n' || gb[i + 2][j - 1] == 'b' ||
							gb[i + 2][j - 1] == 'r' || gb[i + 2][j - 1] == 'k')
						{
					
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 2;
							mv[depth][mvCol + 5] = j - 1;
							mv[depth][0]++;
						}
					}
					if (i + 1 <= 8 && j - 2 >= 0) {
						if (gb[i + 1][j - 2] == '-') {
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 1;
							mv[depth][mvCol + 5] = j - 2;
							mv[depth][0]++;
						}
						else if (gb[i + 1][j - 2] == 'p' || gb[i + 1][j - 2] == 'n' || gb[i + 1][j - 2] == 'b' ||
							gb[i + 1][j - 2] == 'r' || gb[i + 1][j - 2] == 'k')
						{
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 1;
							mv[depth][mvCol + 5] = j - 2;
							mv[depth][0]++;
						}
					}
					if (i - 2 >= 0 && j + 1 <= 6) {
						if (gb[i - 2][j + 1] == 'p' || gb[i - 2][j + 1] == 'n' || gb[i - 2][j + 1] == 'b' ||
							gb[i - 2][j + 1] == 'r' || gb[i - 2][j + 1] == 'k')
						{
				
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 2;
							mv[depth][mvCol + 5] = j + 1;
							mv[depth][0]++;
						}
					}
					if (i - 1 >= 0 && j + 2 <= 6) {
						if (gb[i - 1][j + 2] == 'p' || gb[i - 1][j + 2] == 'n' || gb[i - 1][j + 2] == 'b' ||
							gb[i - 1][j + 2] == 'r' || gb[i - 1][j + 2] == 'k')
						{
					
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 1;
							mv[depth][mvCol + 5] = j + 2;
							mv[depth][0]++;
						}
					}
					if (i - 2 >= 0 && j - 1 >= 0) {
						if (gb[i - 2][j - 1] == 'p' || gb[i - 2][j - 1] == 'n' || gb[i - 2][j - 1] == 'b' ||
							gb[i - 2][j - 1] == 'r' || gb[i - 2][j - 1] == 'k')
						{
					
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 2;
							mv[depth][mvCol + 5] = j -1;
							mv[depth][0]++;
						}
					}
					if (i - 1 <= 8 && j - 2 >= 0) {
						if (gb[i - 1][j - 2] == 'p' || gb[i - 1][j - 2] == 'n' || gb[i - 1][j - 2] == 'b' ||
							gb[i - 1][j - 2] == 'r' || gb[i - 1][j - 2] == 'k')
						{
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 1;
							mv[depth][mvCol + 5] = j - 2;
							mv[depth][0]++;
						}
					}
					break;
				case 'R':
					forward = true;
					left = true;
					right = true;
					back = true;
					count = 1;

					while (forward || left || right || back) {
						if (forward) {
							if (i + count <= 8) {
								if (gb[i + count][j] == '-') {
									
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 0;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i + count;
									mv[depth][mvCol + 5] = j;
									mv[depth][0]++;
								}
								else if (gb[i + count][j] == 'k' || gb[i + count][j] == 'r' || gb[i + count][j] == 'b' ||
									gb[i + count][j] == 'n' || gb[i + count][j] == 'p') {
									
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i + count;
									mv[depth][mvCol + 5] = j;
									mv[depth][0]++;
									forward = false;
								}
								else forward = false;
							}
							else forward = false;
						}
						if (back) {
							if (i - count >= 0) {
								if (gb[i - count][j] == 'k' || gb[i - count][j] == 'r' || gb[i - count][j] == 'b' ||
									gb[i - count][j] == 'n' || gb[i - count][j] == 'p') {
									
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i - count;
									mv[depth][mvCol + 5] = j;
									mv[depth][0]++;
									back = false;
								}
								else if (gb[i - count][j] == 'K' || gb[i - count][j] == 'R' || gb[i - count][j] == 'B' ||
									gb[i - count][j] == 'N' || gb[i - count][j] == 'P') {
									back = false;
								}
							}
							else back = false;
						}
						if (left) {
							if (j - count >= 0) {
								if (gb[i][j - count] == 'k' || gb[i][j - count] == 'r' || gb[i][j - count] == 'b' ||
									gb[i][j - count] == 'n' || gb[i][j - count] == 'p') {
								
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i;
									mv[depth][mvCol + 5] = j - count;
									mv[depth][0]++;
									left = false;
								}
								else if (gb[i][j - count] == 'K' || gb[i][j - count] == 'R' || gb[i][j - count] == 'B' ||
									gb[i][j - count] == 'N' || gb[i][j - count] == 'P') {
									left = false;
								}
							}
							else left = false;
						}
						if (right) {
							if (j + count <= 6) {
								if (gb[i][j + count] == 'k' || gb[i][j + count] == 'r' || gb[i][j + count] == 'b' ||
									gb[i][j + count] == 'n' || gb[i][j + count] == 'p') {
								
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i;
									mv[depth][mvCol + 5] = j + count;
									mv[depth][0]++;
									right = false;
								}
								else if (gb[i][j + count] == 'K' || gb[i][j + count] == 'R' || gb[i][j + count] == 'B' ||
									gb[i][j + count] == 'N' || gb[i][j + count] == 'P') {
									right = false;
								}
							}
							else right = false;
						}
						count++;
					}
					break;
				case 'B':
					fdl = true;
					fdr = true;
					bdl = true;
					bdr = true;
					count = 1;
					while (fdl || fdr || bdl || bdr) {
						if (bdl) {
							if (i - count >= 0 && j - count >= 0) {
								if (gb[i - count][j - count] == 'k' || gb[i - count][j - count] == 'r' || gb[i - count][j - count] == 'b' ||
									gb[i - count][j - count] == 'n' || gb[i - count][j - count] == 'p') {
									
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i - count;
									mv[depth][mvCol + 5] = j - count;
									mv[depth][0]++;
									bdl = false;
								}
								else if (gb[i - count][j - count] == 'K' || gb[i - count][j - count] == 'R' || gb[i - count][j - count] == 'B' ||
									gb[i - count][j - count] == 'N' || gb[i - count][j - count] == 'P') {
									bdl = false;
								}
							}
							else bdl = false;
						}
						if (bdr) {
							if (i - count >= 0 && j + count <= 6) {
								if (gb[i - count][j + count] == 'k' || gb[i - count][j + count] == 'r' || gb[i - count][j + count] == 'b' ||
									gb[i - count][j + count] == 'n' || gb[i - count][j + count] == 'p') {
								
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i - count;
									mv[depth][mvCol + 5] = j + count;
									mv[depth][0]++;
									bdr = false;
								}
								else if (gb[i - count][j + count] == 'K' || gb[i - count][j + count] == 'R' || gb[i - count][j + count] == 'B' ||
									gb[i - count][j + count] == 'N' || gb[i - count][j + count] == 'P') {
									bdr = false;
								}
							}
							else bdr = false;
						}
						if (fdl) {
							if (i + count <= 8 && j - count >= 0) {
								if (gb[i + count][j - count] == '-') {
							
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 0;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i + count;
									mv[depth][mvCol + 5] = j- count;
									mv[depth][0]++;
								}
								else if (gb[i + count][j - count] == 'k' || gb[i + count][j - count] == 'r' || gb[i + count][j - count] == 'b' ||
									gb[i + count][j - count] == 'n' || gb[i + count][j - count] == 'p') {
									
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i + count;
									mv[depth][mvCol + 5] = j - count;
									mv[depth][0]++;
									fdl = false;
								}
								else if (gb[i + count][j - count] == 'K' || gb[i + count][j - count] == 'R' || gb[i + count][j - count] == 'B' ||
									gb[i + count][j - count] == 'N' || gb[i + count][j - count] == 'P') {
									fdl = false;
								}
							}
							else fdl = false;
						}
						if (fdr) {
							if (i + count <= 8 && j + count <= 6) {
								if (gb[i + count][j + count] == '-') {
								
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 0;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i + count;
									mv[depth][mvCol + 5] = j + count;
									mv[depth][0]++;
								}
								else if (gb[i + count][j + count] == 'k' || gb[i + count][j + count] == 'r' || gb[i + count][j + count] == 'b' ||
									gb[i + count][j + count] == 'n' || gb[i + count][j + count] == 'p') {
						
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i + count;
									mv[depth][mvCol + 5] = j + count;
									mv[depth][0]++;
									fdr = false;
								}
								else if (gb[i + count][j + count] == 'K' || gb[i + count][j + count] == 'R' || gb[i + count][j + count] == 'B' ||
									gb[i + count][j + count] == 'N' || gb[i + count][j + count] == 'P') {
									fdr = false;
								}
							}
							else fdr = false;
						}

						count++;
					}
					break;
				case 'K':
					if (i + 1 <= 8) {
						if (gb[i + 1][j] == '-') {
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 1;
							mv[depth][mvCol + 5] = j;
							mv[depth][0]++;
						}
					}
					if (i + 1 <= 8 && j + 1 <= 6) {
						if (gb[i + 1][j + 1] == '-') {
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 1;
							mv[depth][mvCol + 5] = j + 1;
							mv[depth][0]++;
						}
					}
					if (i + 1 <= 8 && j - 1 >= 0) {
						if (gb[i + 1][j - 1] == '-') {
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 1;
							mv[depth][mvCol + 5] = j - 1;
							mv[depth][0]++;
						}
					}
					break;
				default:
					break;
				}
			}
			else
			{
				switch (p)
				{
				case 'p':
					if (i > 0)
					{
						if (gb[i - 1][j] == '-')
						{
							
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 1;
							mv[depth][mvCol + 5] = j;
							mv[depth][0]++;
						}
						if (j < 6)
						{
							if (gb[i - 1][j + 1] == 'P' || gb[i - 1][j + 1] == 'N' || gb[i - 1][j + 1] == 'B' ||
								gb[i - 1][j + 1] == 'R' || gb[i - 1][j + 1] == 'K')
							{															
								mvCol = mv[depth][0] * mvSize;
								mv[depth][mvCol + 1] = 1;
								mv[depth][mvCol + 2] = i;
								mv[depth][mvCol + 3] = j;
								mv[depth][mvCol + 4] = i - 1;
								mv[depth][mvCol + 5] = j + 1;
								mv[depth][0]++;
							}
						}
						if (j > 0)
						{
							if (gb[i - 1][j - 1] == 'P' || gb[i - 1][j - 1] == 'N' || gb[i - 1][j - 1] == 'B' ||
								gb[i - 1][j - 1] == 'R' || gb[i - 1][j - 1] == 'K')
							{
								mvCol = mv[depth][0] * mvSize;
								mv[depth][mvCol + 1] = 1;
								mv[depth][mvCol + 2] = i;
								mv[depth][mvCol + 3] = j;
								mv[depth][mvCol + 4] = i - 1;
								mv[depth][mvCol + 5] = j - 1;
								mv[depth][0]++;
							}
						}
					}
					break;
				case 'n':
					if (i - 2 >= 0 && j + 1 <= 6) {
						if (gb[i - 2][j + 1] == '-') {
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 2;
							mv[depth][mvCol + 5] = j + 1;
							mv[depth][0]++;
						}
						else if (gb[i - 2][j + 1] == 'P' || gb[i - 2][j + 1] == 'N' || gb[i - 2][j + 1] == 'B' ||
							gb[i - 2][j + 1] == 'R' || gb[i - 2][j + 1] == 'K')
						{
							
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 2;
							mv[depth][mvCol + 5] = j + 1;
							mv[depth][0]++;
						}
					}
					if (i - 1 >= 0 && j + 2 <= 6) {
						if (gb[i - 1][j + 2] == '-') {
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 1;
							mv[depth][mvCol + 5] = j + 2;
							mv[depth][0]++;
						}
						else if (gb[i - 1][j + 2] == 'P' || gb[i - 1][j + 2] == 'N' || gb[i - 1][j + 2] == 'B' ||
							gb[i - 1][j + 2] == 'R' || gb[i - 1][j + 2] == 'K')
						{
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 1;
							mv[depth][mvCol + 5] = j + 2;
							mv[depth][0]++;
						}
					}
					if (i - 2 >= 0 && j - 1 >= 0) {
						if (gb[i - 2][j - 1] == '-') {
			
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 2;
							mv[depth][mvCol + 5] = j - 1;
							mv[depth][0]++;
						}
						else if (gb[i - 2][j - 1] == 'P' || gb[i - 2][j - 1] == 'N' || gb[i - 2][j - 1] == 'B' ||
							gb[i - 2][j - 1] == 'R' || gb[i - 2][j - 1] == 'K')
						{
				
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 2;
							mv[depth][mvCol + 5] = j - 1;
							mv[depth][0]++;
						}
					}
					if (i - 1 <= 8 && j - 2 >= 0) {
						if (gb[i - 1][j - 2] == '-') {
			
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 1;
							mv[depth][mvCol + 5] = j - 2;
							mv[depth][0]++;
						}
						if (gb[i - 1][j - 2] == 'P' || gb[i - 1][j - 2] == 'N' || gb[i - 1][j - 2] == 'B' ||
							gb[i - 1][j - 2] == 'R' || gb[i - 1][j - 2] == 'K')
						{
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 1;
							mv[depth][mvCol + 5] = j - 2;
							mv[depth][0]++;
						}
					}
					if (i + 2 <= 8 && j + 1 <= 6) {
						if (gb[i + 2][j + 1] == 'P' || gb[i + 2][j + 1] == 'N' || gb[i + 2][j + 1] == 'B' ||
							gb[i + 2][j + 1] == 'R' || gb[i + 2][j + 1] == 'K')
						{
				
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 2;
							mv[depth][mvCol + 5] = j + 1;
							mv[depth][0]++;
						}
					}
					if (i + 1 <= 8 && j + 2 <= 6) {
						if (gb[i + 1][j + 2] == 'P' || gb[i + 1][j + 2] == 'N' || gb[i + 1][j + 2] == 'B' ||
							gb[i + 1][j + 2] == 'R' || gb[i + 1][j + 2] == 'K')
						{
					
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 1;
							mv[depth][mvCol + 5] = j + 2;
							mv[depth][0]++;
						}
					}
					if (i + 2 <= 8 && j - 1 >= 0) {
						if (gb[i + 2][j - 1] == 'P' || gb[i + 2][j - 1] == 'N' || gb[i + 2][j - 1] == 'B' ||
							gb[i + 2][j - 1] == 'R' || gb[i + 2][j - 1] == 'K')
						{
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 2;
							mv[depth][mvCol + 5] = j - 1;
							mv[depth][0]++;
						}
					}
					if (i + 1 <= 8 && j - 2 >= 0) {
						if (gb[i + 1][j - 2] == 'P' || gb[i + 1][j - 2] == 'N' || gb[i + 1][j - 2] == 'B' ||
							gb[i + 1][j - 2] == 'R' || gb[i + 1][j - 2] == 'K')
						{
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 1;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i + 1;
							mv[depth][mvCol + 5] = j - 2;
							mv[depth][0]++;
						}
					}
					break;
				case 'r':
					forward = true;
					left = true;
					right = true;
					back = true;
					count = 1;

					while (forward || left || right || back) {
						if (forward) {
							if (i - count >= 0) {
								if (gb[i - count][j] == '-') {
							
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 0;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i - count;
									mv[depth][mvCol + 5] = j;
									mv[depth][0]++;
								}
								else if (gb[i - count][j] == 'K' || gb[i - count][j] == 'R' || gb[i - count][j] == 'B' ||
									gb[i - count][j] == 'N' || gb[i - count][j] == 'P') {
								
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i - count;
									mv[depth][mvCol + 5] = j;
									mv[depth][0]++;
									forward = false;
								}
								else forward = false;
							}
							else forward = false;
						}
						if (back) {
							if (i + count <= 8) {
								if (gb[i + count][j] == 'K' || gb[i + count][j] == 'R' || gb[i + count][j] == 'B' ||
									gb[i + count][j] == 'N' || gb[i + count][j] == 'P') {
								
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i + count;
									mv[depth][mvCol + 5] = j;
									mv[depth][0]++;
									back = false;
								}
								else if (gb[i + count][j] == 'k' || gb[i + count][j] == 'r' || gb[i + count][j] == 'b' ||
									gb[i + count][j] == 'n' || gb[i + count][j] == 'p') {
									back = false;
								}
							}
							else back = false;
						}
						if (left) {
							if (j - count >= 0) {
								if (gb[i][j - count] == 'K' || gb[i][j - count] == 'R' || gb[i][j - count] == 'B' ||
									gb[i][j - count] == 'N' || gb[i][j - count] == 'P') {
								
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i;
									mv[depth][mvCol + 5] = j - count;
									mv[depth][0]++;
									left = false;
								}
								else if (gb[i][j - count] == 'k' || gb[i][j - count] == 'r' || gb[i][j - count] == 'b' ||
									gb[i][j - count] == 'n' || gb[i][j - count] == 'p') {
									left = false;
								}
							}
							else left = false;
						}
						if (right) {
							if (j + count <= 6) {
								if (gb[i][j + count] == 'K' || gb[i][j + count] == 'R' || gb[i][j + count] == 'B' ||
									gb[i][j + count] == 'N' || gb[i][j + count] == 'P') {
								
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i;
									mv[depth][mvCol + 5] = j + count;
									mv[depth][0]++;
									right = false;
								}
								else if (gb[i][j + count] == 'k' || gb[i][j + count] == 'r' || gb[i][j + count] == 'c' ||
									gb[i][j + count] == 'n' || gb[i][j + count] == 'p') {
									right = false;
								}
							}
							else right = false;
						}
						count++;
					}
					break;
				case 'b':
					fdl = true;
					fdr = true;
					bdl = true;
					bdr = true;
					count = 1;
					while (fdl || fdr || bdl || bdr) {
						if (fdl) {
							if (i - count >= 0 && j - count >= 0) {
								if (gb[i - count][j - count] == '-') {
									
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 0;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i - count;
									mv[depth][mvCol + 5] = j - count;
									mv[depth][0]++;
								}
								else if (gb[i - count][j - count] == 'k' || gb[i - count][j - count] == 'r' || gb[i - count][j - count] == 'b' ||
									gb[i - count][j - count] == 'n' || gb[i - count][j - count] == 'p') {
									fdl = false;
								}
								else if (gb[i - count][j - count] == 'K' || gb[i - count][j - count] == 'R' || gb[i - count][j - count] == 'B' ||
									gb[i - count][j - count] == 'N' || gb[i - count][j - count] == 'P') {
							
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i - count;
									mv[depth][mvCol + 5] = j - count;
									mv[depth][0]++;
									fdl = false;
								}
							}
							else fdl = false;
						}
						if (fdr) {

							if (i - count >= 0 && j + count <= 6) {
								if (gb[i - count][j + count] == '-') {
								
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 0;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i - count;
									mv[depth][mvCol + 5] = j + count;
									mv[depth][0]++;
								}
								else if (gb[i - count][j + count] == 'k' || gb[i - count][j + count] == 'r' || gb[i - count][j + count] == 'b' ||
									gb[i - count][j + count] == 'n' || gb[i - count][j + count] == 'p') {
									fdr = false;
								}
								else if (gb[i - count][j + count] == 'K' || gb[i - count][j + count] == 'R' || gb[i - count][j + count] == 'B' ||
									gb[i - count][j + count] == 'N' || gb[i - count][j + count] == 'P') {
					
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i - count;
									mv[depth][mvCol + 5] = j + count;
									mv[depth][0]++;
									fdr = false;
								}
							}
							else fdr = false;
						}
						if (bdl) {
							if (i + count <= 8 && j - count >= 0) {
								if (gb[i + count][j - count] == 'k' || gb[i + count][j - count] == 'r' || gb[i + count][j - count] == 'b' ||
									gb[i + count][j - count] == 'n' || gb[i + count][j - count] == 'p') {

									bdl = false;
								}
								else if (gb[i + count][j - count] == 'K' || gb[i + count][j - count] == 'R' || gb[i + count][j - count] == 'B' ||
									gb[i + count][j - count] == 'N' || gb[i + count][j - count] == 'P') {
							
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i + count;
									mv[depth][mvCol + 5] = j - count;
									mv[depth][0]++;
									bdl = false;
								}
							}
							else bdl = false;
						}
						if (bdr) {
							if (i + count <= 8 && j + count <= 6) {
								if (gb[i + count][j + count] == 'k' || gb[i + count][j + count] == 'r' || gb[i + count][j + count] == 'b' ||
									gb[i + count][j + count] == 'n' || gb[i + count][j + count] == 'p') {
									bdr = false;
								}
								else if (gb[i + count][j + count] == 'K' || gb[i + count][j + count] == 'R' || gb[i + count][j + count] == 'B' ||
									gb[i + count][j + count] == 'N' || gb[i + count][j + count] == 'P') {
							
									mvCol = mv[depth][0] * mvSize;
									mv[depth][mvCol + 1] = 1;
									mv[depth][mvCol + 2] = i;
									mv[depth][mvCol + 3] = j;
									mv[depth][mvCol + 4] = i + count;
									mv[depth][mvCol + 5] = j + count;
									mv[depth][0]++;
									bdr = false;
								}
							}
							else bdr = false;
						}

						count++;
					}
					break;
				case 'k':
					if (i - 1 >= 0) {
						if (gb[i - 1][j] == '-') {
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 1;
							mv[depth][mvCol + 5] = j;
							mv[depth][0]++;


						}
					}
					if (i - 1 >= 0 && j + 1 <= 6) {
						if (gb[i - 1][j + 1] == '-') {
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 1;
							mv[depth][mvCol + 5] = j + 1;
							mv[depth][0]++;
						}
					}
					if (i - 1 >= 0 && j - 1 >= 0) {
						if (gb[i - 1][j - 1] == '-') {
						
							mvCol = mv[depth][0] * mvSize;
							mv[depth][mvCol + 1] = 0;
							mv[depth][mvCol + 2] = i;
							mv[depth][mvCol + 3] = j;
							mv[depth][mvCol + 4] = i - 1;
							mv[depth][mvCol + 5] = j - 1;
							mv[depth][0]++;
						}
					}
					break;
				default:
					break;
				}
			}

		}
	}
}

void printMoves() {
	if (mv[0][0] > -1) {
		cout << "Number of Moves: " << mv[0][0] << endl;
		char a, b;
		int c, d;
		for (int i = 0; i <= mv[0][0]; i++) {
			switch (mv[0][i*mvSize + 3]) {
			case 0: a = 'A'; break;
			case 1: a = 'B'; break;
			case 2: a = 'C'; break;
			case 3: a = 'D'; break;
			case 4: a = 'E'; break;
			case 5: a = 'F'; break;
			case 6: a = 'G'; break;
			}
			switch (mv[0][i*mvSize + 2]) {
			case 0: c = 9; break;
			case 1: c = 8; break;
			case 2: c = 7; break;
			case 3: c = 6; break;
			case 4: c = 5; break;
			case 5: c = 4; break;
			case 6: c = 3; break;
			case 7: c = 2; break;
			case 8: c = 1; break;
			}
			switch (mv[0][i*mvSize + 5]) {
			case 0: b = 'A'; break;
			case 1: b = 'B'; break;
			case 2: b = 'C'; break;
			case 3: b = 'D'; break;
			case 4: b = 'E'; break;
			case 5: b = 'F'; break;
			case 6: b = 'G'; break;
			}
			switch (mv[0][i*mvSize + 4]) {
			case 0: d = 9; break;
			case 1: d = 8; break;
			case 2: d = 7; break;
			case 3: d = 6; break;
			case 4: d = 5; break;
			case 5: d = 4; break;
			case 6: d = 3; break;
			case 7: d = 2; break;
			case 8: d = 1; break;
			}
			if (i % 10 == 0) cout << endl;

			cout << a << c << b << d << " ";
		}
		cout << endl;
	}
}