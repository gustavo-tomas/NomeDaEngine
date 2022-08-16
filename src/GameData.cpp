#include "../header/GameData.h"

#include <iostream>
#include <fstream>
#include <sstream>

const int GameData::WIDTH = 1024;
const int GameData::HEIGHT = 600;
const char* GameData::TITLE = "Gustavo Tomas de Paula - 190014148";

bool GameData::playerVictory = false;
float GameData::targetFPS = 60.0f;
float GameData::currentFPS = 0.0f;
float GameData::delay = 1000.0f / targetFPS;

int GameData::score = 0;
int GameData::playerLives = 0;

pair<string, int> GameData::GetHighScore()
{
    string file = "./data/HighScore.txt";
    ifstream fileStream(file);
    pair<string, int> highScore;

    if (fileStream.is_open())
    {
        string name, line, score;

        getline(fileStream, line, '\n');
        stringstream strStream(line);
        getline(strStream, name, ',');
        getline(strStream, score, '\n');

        fileStream.close();
        highScore = pair<string, int>(name, stoi(score));
    }
    else
    {
        cout << "Unable to open HighScore file" << endl;
        highScore = pair<string, int>("", -1);
    }
    return highScore;
}

void GameData::SetHighScore(pair<string, int> score)
{
    string file = "./data/HighScore.txt";
    ofstream fileStream(file);

    if (fileStream.is_open())
    {
        fileStream << score.first + "," << score.second << endl;
        fileStream.close();
    }
    else
        cout << "Unable to open HighScore file" << endl;
}