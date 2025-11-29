// snake.cpp - console snake (Windows)
// Full corrected file with Input() fix and WinMain wrapper.

#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;

int width = 40, height = 20;
bool gameOver;
int score;
int headX, headY;
vector<pair<int,int>> snake;
int dirX, dirY;
pair<int,int> fruit;

void Setup() {
    gameOver = false;
    score = 0;
    headX = width/2;
    headY = height/2;
    snake.clear();
    snake.push_back({headX, headY});
    dirX = 1; dirY = 0;
    srand((unsigned)time(nullptr));
    fruit = { rand() % width, rand() % height };
}

void Draw() {
    system("cls");
    for (int i=0;i<width+2;i++) cout << '#';
    cout << '\n';

    for (int y=0; y<height; y++) {
        cout << '#';
        for (int x=0; x<width; x++) {
            bool printed = false;
            if (x==fruit.first && y==fruit.second) { cout << 'F'; printed=true; }
            else {
                for (size_t k=0;k<snake.size();k++){
                    if (snake[k].first==x && snake[k].second==y) {
                        if (k==0) cout<<'O'; else cout<<'o';
                        printed = true;
                        break;
                    }
                }
            }
            if (!printed) cout << ' ';
        }
        cout << "#\n";
    }

    for (int i=0;i<width+2;i++) cout << '#';
    cout << "\nScore: " << score << "\n";
    cout << "Use W A S D to move. Press X to quit.\n";
}

void Input() {
    if (_kbhit()) {
        char c = _getch();
        if (c=='a' || c=='A') { dirX = -1; dirY = 0; }
        if (c=='d' || c=='D') { dirX = 1; dirY = 0; }
        if (c=='w' || c=='W') { dirX = 0; dirY = -1; }
        if (c=='s' || c=='S') { dirX = 0; dirY = 1; }
        if (c=='x' || c=='X') gameOver = true;
    }
}

void Logic() {
    headX += dirX;
    headY += dirY;

    if (headX < 0) headX = width-1;
    if (headX >= width) headX = 0;
    if (headY < 0) headY = height-1;
    if (headY >= height) headY = 0;

    snake.insert(snake.begin(), {headX, headY});

    if (headX == fruit.first && headY == fruit.second) {
        score += 10;
        while (true) {
            pair<int,int> f = { rand()%width, rand()%height };
            bool onSnake = false;
            for (auto &p: snake) if (p==f) { onSnake = true; break; }
            if (!onSnake) { fruit = f; break; }
        }
    } else {
        snake.pop_back();
    }

    for (size_t i=1;i<snake.size();i++){
        if (snake[i].first==headX && snake[i].second==headY) {
            gameOver = true;
            break;
        }
    }
}

int main(){
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(120);
    }
    cout << "Game Over! Final score: " << score << "\n";
    cout << "Press any key to exit...\n";
    _getch();
    return 0;
}

// Simple WinMain wrapper to avoid "undefined reference to WinMain" on some MinGW setups
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    return main();
}
#endif
