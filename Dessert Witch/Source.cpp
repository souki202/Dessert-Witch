#include <iostream>
#include <string>
#include <algorithm>

char field[8][8];

char own[] = { 'o', 'x' };
char enemy[] = { 'x', 'o' };

int dx[] = { 1, 1, 0, -1, -1, -1, 0, 1 }, dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int countReverse(int x, int y, int turn) {
	if (field[y][x] != '.') return 0;
	int sum = 0;
	for (int i = 0; i < 8; i++) {
		int nx = x, ny = y;
		int cnt = 0;
		bool ok = true;
		while (ok) {
			nx += dx[i], ny += dy[i];
			if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) ok = false;
			else if (field[ny][nx] == '.') ok = false; //何もなし
			else if (field[ny][nx] == own[turn]) break; //挟んだやつが確定
			else if (field[ny][nx] == enemy[turn]) cnt++;
		}
		if (ok) sum += cnt;
	}
	return sum;
}

void reverse(int x, int y, int turn) {
	if (field[y][x] != '.') return;
	//置く
	field[y][x] = own[turn];
	for (int i = 0; i < 8; i++) {
		int nx = x, ny = y;
		bool ok = true;
		while (ok) {
			nx += dx[i], ny += dy[i];
			if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) ok = false;
			else if (field[ny][nx] == '.') ok = false; //何もなし
			else if (field[ny][nx] == own[turn]) break; //挟んだやつが確定
		}
		if (ok) {
			nx = x, ny = y;
			while (ok) {
				nx += dx[i], ny += dy[i];
				if (field[ny][nx] == own[turn]) break; //挟んだやつが確定
				else if (field[ny][nx] == enemy[turn]) field[ny][nx] = own[turn]; //反転
			}
		}
	}
}

int main() {
	for (int i = 0; i < 8; i++) {
		std::string s; std::cin >> s;
		for (int j = 0; j < 8; j++) {
			field[i][j] = s[j];
		}
	}

	int turn = 0;
	bool isReverse = false;
	while (1) {
		isReverse = false;
		int max = 0, x, y;
		if (turn == 0) { //マミさん
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					int cnt = countReverse(j, i, turn);
					if (max < cnt) {
						max = cnt;
						x = j; y = i;
						isReverse = true;
					}
				}
			}
		}
		if (max) reverse(x, y, turn);
		turn = !turn;
		max = 0;
		if (turn == 1) { //CHARLOTTE 
			for (int i = 7; i >= 0; i--) {
				for (int j = 7; j >= 0; j--) {
					int cnt = countReverse(j, i, turn);
					if (max < cnt) {
						max = cnt;
						x = j; y = i;
						isReverse = true;
					}
				}
			}
		}
		if (max) reverse(x, y, turn);
		turn = !turn;
		if (!isReverse) break;//両者pass
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << field[i][j];
		}
		std::cout << std::endl;
	}

	return 0;
}