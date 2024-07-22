#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <chrono>
#undef main
#include <sstream>
#include <string>



using namespace std;

template <typename T>
std::string to_string(T value) {
	std::ostringstream os;
	os << value;
	return os.str();
}
vector<vector<int>> rotate(vector<vector<int>> board, int rotateamount, int current) {
	vector<vector<int>> piece = board;
	vector<vector<int>> newpiece = { {0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0} };
	for (int b = 0; b < rotateamount; b++) {
		if (current == 0) {
			for (int y2 = 0; y2 < 4; y2++) {
				for (int x2 = 0; x2 < 4; x2++) {
					if (piece[y2][x2] == 1) {
						newpiece[x2][3 - y2] = 1;
					}
				}
			}
		}
		else if (current == 1) {
			newpiece = piece;
		}
		else {
			for (int y2 = 0; y2 < 3; y2++) {
				for (int x2 = 0; x2 < 3; x2++) {
					if (piece[y2][x2] == 1) {
						newpiece[x2][2 - y2] = 1;
					}
				}
			}
		}
		piece = newpiece;
		newpiece = { {0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0} };
	}
	return piece;
}

int main(int argx, char* argv[])
{
	srand(time(NULL));
	int frequencia = 22050;
	Uint16 formato = AUDIO_S16SYS;
	int canal = 2;
	int buffer = 4096;
	Mix_OpenAudio(frequencia, formato, canal, buffer);
	int displaysizex = 800;
	int displaysizey = 1000;
	bool GameLoop = true;
	Mix_Chunk* sound_1;
	sound_1 = Mix_LoadWAV("../clear.wav");
	vector<vector<int>> new_row(10, vector<int>(3, 0));
	vector<vector<int>> board;
	if (sound_1 == NULL) {
		cout << "NOOOOOOO" << endl;
	}
	SDL_Event e;
	SDL_Rect rect;
	rect.w = 39;
	rect.h = 39;
	vector<int> b = {};
	vector<vector<int>> c = { { } };
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Tertris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, displaysizex, displaysizey, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	for (int y1 = 0; y1 < 20; y1++) {
		board.push_back(b);
		for (int x1 = 0; x1 < 10; x1++) {
			board[y1].push_back(0);
		}
	}
	vector<vector<vector<int>>> pieces = {
	{{0,0,1,0},
	{0,0,1,0},
	{0,0,1,0},
	{0,0,1,0}},
	{{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0},
	{0,0,0,0}},
	{{0,0,1,0},
	{0,0,1,0},
	{0,1,1,0},
	{0,0,0,0}},
	{{0,0,1,0},
	{0,1,1,0},
	{0,1,0,0},
	{0,0,0,0}},
	{{1,0,0,0},
	{1,1,0,0},
	{0,1,0,0},
	{0,0,0,0}},
	{{1,0,0,0},
	{1,0,0,0},
	{1,1,0,0},
	{0,0,0,0}},
	{{1,1,1,0},
	{0,1,0,0},
	{0,0,0,0},
	{0,0,0,0}}
	};
	vector<vector<vector<int>>> colorboard(20, std::vector<std::vector<int>>(10, std::vector<int>(3, 0)));
	int curpiece = rand() % 7;
	int piecex = 5;
	int piecey = 0;
	int speed;
	int rotation = 0;
	int framecounter = 0;
	int prevx;
	int prevy;
	int prevr;
	bool rotated = false;
	bool oldr = false;
	int lines = 0;
	int blocks;
	int level = 1;
	int totallines = 0;
	int totaltotallines = 0;
	int score = 0;
	vector<vector<int>> offset = { {3, 2, 3, 1}, {1, 1, 1, 1},{2, 2, 2, 1},{2, 2, 2, 2}, {1,2,2,1}, {1,2,2,1} };
	bool moveright = false;
	bool moveleft = false;
	int yd = 0;
	bool k = true;
	int nextpiece = rand() % 7;
	vector<int> piececolor = { (rand() % 150) + 100, (rand() % 150) + 100, (rand() % 150) + 100 };
	int starter = (int)chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	if (level < 9) {
		speed = round((48 - (5 * level)) * (16.6392673 * 2));
	}
	else if (level < 19) {
		speed = round(round((26 - level) / 3) * 16.6392673);
	}
	else if (level < 29) {
		speed = round(4 * 16.6392673);
	}
	else {
		speed = round(2 * 16.6392673);
	}
	int start = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	vector<int> line(10, 0);
	cout << "Score: " << score << endl;
	cout << "Lines: " << totaltotallines << endl;
	cout << "Level: " << level << endl;
	while (GameLoop) {
		framecounter++;
		prevy = piecey;
		prevx = piecex;
		prevr = rotation;
		oldr = rotated;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return 0;
			}
			else if (e.type == SDL_KEYDOWN) {
				if (SDLK_ESCAPE == e.key.keysym.sym) {
					return 0;
				}
				else if ('d' == (char)e.key.keysym.sym) { rotation += 1; }
				else if ('f' == (char)e.key.keysym.sym) { rotation += 3; }
				else if (SDLK_DOWN == e.key.keysym.sym) {
					if (level < 29) { speed = round(2 * 16.6392673); }
				}
			}
			else if (e.type == SDL_KEYUP) {
				if (SDLK_DOWN == e.key.keysym.sym) {
					if (level < 9) {
						speed = round((48 - (5 * level)) * (16.6392673 * 2));
					}
					else if (level < 19) {
						speed = round(round((26 - level) / 3) * 16.6392673);
					}
					else if (level < 29) {
						speed = round(4 * 16.6392673);
					}
					else {
						speed = round(2 * 16.6392673);
					}
				}
			}
		}
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		if ((int)chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count() - starter >= 100 && keystate[SDL_SCANCODE_RIGHT]) {
			starter = (int)chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
			piecex += 1;
		}
		if ((int)chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count() - starter >= 100 && keystate[SDL_SCANCODE_LEFT]) {
			starter = (int)chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
			piecex -= 1;
		}
		for (int y4 = 0; y4 < 4; y4++) {
			for (int x4 = 0; x4 < 4; x4++) {
				if (rotate(pieces[curpiece], rotation % 4, curpiece)[y4][x4] == 1) {
					if (x4 + piecex > 9 || x4 + piecex < 0) {
						piecex = prevx;
						rotation = prevr;
					}
				}
				if (x4 + piecex > 9 || y4 + piecey > 19 || x4 + piecex < 0) {
					continue;
				}
				if (board[y4 + piecey][x4 + piecex] == 1 && rotate(pieces[curpiece], rotation % 4, curpiece)[y4][x4] == 1) {
					piecex = prevx;
					rotation = prevr;
				}
			}
		}
		lines = 0;
		for (int y0 = 0; y0 < 20; y0++) {
			blocks = 0;
			for (int x0 = 0; x0 < 10; x0++) {
				if (board[y0][x0] == 1) {
					blocks += 1;
				}
			}
			if (blocks == 10) {
				lines += 1;
				board.erase(board.begin() + y0);
				board.insert(board.begin(), line);
				colorboard.erase(colorboard.begin() + y0);
				colorboard.insert(colorboard.begin(), new_row);
			}
		}
		if (lines == 1) {
			score += 40 * (level + 1);
		}
		else if (lines == 2) {
			score += 100 * (level + 1);
		}
		else if (lines == 3) {
			score += 300 * (level + 1);
		}
		else if (lines == 4) {
			score += 1200 * (level + 1);
		}
		totallines += lines;
		totaltotallines += lines;
		if (totallines >= 10) {
			totallines -= 10;
			level += 1;
			if (level < 9) {
				speed = round((48 - (5 * level)) * (16.6392673 * 2));
			}
			else if (level < 19) {
				speed = round(round((26 - level) / 3) * 16.6392673);
			}
			else if (level < 29) {
				speed = round(4 * 16.6392673);
			}
			else {
				speed = round(2 * 16.6392673);
			}
			piececolor = { (rand() % 150) + 50, (rand() % 150) + 50, (rand() % 150) + 50 };
		}
		if (((int)chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count() - start) >= speed) {
			framecounter = 0;
			piecey += 1;
			start = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		for (int y = 0; y < 800; y++) {
			for (int x = 0; x < 10; x++) {
				SDL_RenderDrawPoint(renderer, (x * 40) + 200, y + 100);
			}
			SDL_RenderDrawPoint(renderer, 600, y + 100);
		}
		for (int x = 0; x < 400; x++) {
			for (int y = 0; y < 20; y++) {
				SDL_RenderDrawPoint(renderer, x + 200, (y * 40) + 100);
			}
			SDL_RenderDrawPoint(renderer, x + 200, 900);
		}
		for (int y = 0; y < board.size(); y++) {
			for (int x = 0; x < board[0].size(); x++) {
				rect.x = (x * 40) + 201;
				rect.y = (y * 40) + 101;
				SDL_SetRenderDrawColor(renderer, colorboard[y][x][0], colorboard[y][x][1], colorboard[y][x][2], 255);
				if (board[y][x] == 1) { SDL_RenderFillRect(renderer, &rect); };
			}
		}
		for (int y2 = 0; y2 < 4; y2++) {
			for (int x2 = 0; x2 < 4; x2++) {
				if (rotate(pieces[curpiece], rotation % 4, curpiece)[y2][x2] == 1) {
					if (y2 + piecey == 20) {
						for (int y3 = 0; y3 < 4; y3++) {
							for (int x3 = 0; x3 < 4; x3++) {
								if (rotate(pieces[curpiece], rotation % 4, curpiece)[y3][x3] == 1) {
									board[y3 + piecey - 1][x3 + piecex] = 1;
									colorboard[y3 + piecey - 1][x3 + piecex] = piececolor;
								}
							}
						}
						curpiece = nextpiece;
						nextpiece = rand() % 7;
						piecey = 0;
						piecex = 5;
						for (int y6 = 0; y6 < 4; y6++) {
							for (int x6 = 0; x6 < 4; x6++) {
								if (rotate(pieces[curpiece], rotation % 4, curpiece)[y2][x2] == 1 && board[y6][x6] == 1) {
									return 0;
								}
							}
						}
					}
					if (board[y2 + piecey][x2 + piecex] == 1) {
						for (int y3 = 0; y3 < 4; y3++) {
							for (int x3 = 0; x3 < 4; x3++) {
								if (rotate(pieces[curpiece], rotation % 4, curpiece)[y3][x3] == 1) {
									board[y3 + prevy][x3 + piecex] = 1;
									colorboard[y3 + prevy][x3 + piecex] = piececolor;
								}
							}
						}
						curpiece = nextpiece;
						nextpiece = rand() % 7;
						piecey = 0;
						piecex = 5;
						for (int y6 = 0; y6 < 4; y6++) {
							for (int x6 = 0; x6 < 4; x6++) {
								if (rotate(pieces[curpiece], rotation % 4, curpiece)[y2][x2] == 1 && board[y6][x6] == 1) {
									return 0;
								}
							}
						}
					}
					SDL_SetRenderDrawColor(renderer, piececolor[0], piececolor[1], piececolor[2], 255);
					rect.x = ((x2 + piecex) * 40) + 201;
					rect.y = ((y2 + piecey) * 40) + 101;
					SDL_RenderFillRect(renderer, &rect);
				}
				if (pieces[nextpiece][y2][x2] == 1) {
					SDL_SetRenderDrawColor(renderer, piececolor[0], piececolor[1], piececolor[2], 255);
					rect.x = 630 + (x2 * 40);
					rect.y = 100 + (y2 * 40);
					SDL_RenderFillRect(renderer, &rect);
				}
			}
		}
		if (lines >= 1) {
			system("cls");
			cout << "Score: " << score << endl;
			cout << "Lines: " << totaltotallines << endl;
			cout << "Level: " << level << endl;
			Mix_PlayChannel(-1, sound_1, 0);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}
	return 0;
}
