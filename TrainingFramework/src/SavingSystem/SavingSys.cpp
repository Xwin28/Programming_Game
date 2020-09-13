#include <fstream>
#include <iostream>
#include <string>
#include <bitset>
#include "SavingSys.h"

SavingSys::SavingSys():
m_Coin(0), m_IntroScene(false), m_EndGame(false), m_BlockBullet(0), m_Dodge(0), m_CompletedScene(0), m_SceneManage(0),m_heal(1), m_damage(1)
{}
SavingSys::SavingSys(int _Coin, bool _IntroScene, bool _EndGame):
    m_Coin(_Coin), m_IntroScene(_IntroScene), m_EndGame(_EndGame), m_BlockBullet(0), m_Dodge(0), m_CompletedScene(0), m_SceneManage(0)
{
}

#pragma region GET_SET
int SavingSys::getM_Coin()
{
    return m_Coin;
}

bool SavingSys::isM_IntroScene()
{
    return m_IntroScene;
}

bool SavingSys::isM_EndGame()
{
    return m_EndGame;
}

int SavingSys::getM_BlockBullet() 
{
    return m_BlockBullet;
}

int SavingSys::getM_Dodge() {
    return m_Dodge;
}

int SavingSys::getM_CompletedScene()
{
    return m_CompletedScene;
}

void SavingSys::setM_Coin(int _Coin)
{
    m_Coin = _Coin;
}

void SavingSys::setM_IntroScene(bool _IntroScene)
{
    m_IntroScene = _IntroScene;
}

void SavingSys::setM_EndGame(bool _EndGame)
{
    m_EndGame = _EndGame;
}

void SavingSys::setM_BlockBullet(int _BlockBullet) 
{
    m_BlockBullet = _BlockBullet;
}

void SavingSys::setM_Dodge(int _Dodge)
{
    m_Dodge = _Dodge;
}

void SavingSys::setM_CompletedScene(int _CompletedScene)
{
    m_CompletedScene = _CompletedScene;
}

#pragma endregion






void SavingSys::Save()
{
    std::ofstream SavedFile("..\\Data\\SAVE_FILE\\Save.txt");
    if (SavedFile.is_open())
    {
        SavedFile << m_Coin << "\n";
        SavedFile << m_IntroScene << "\n";
        SavedFile << m_EndGame << "\n";
        SavedFile << m_heal << "\n";
        SavedFile << m_damage << "\n";
        SavedFile.close();
    }
}

void SavingSys::Load()
{
    std::string line;
    std::ifstream SavedFile("..\\Data\\SAVE_FILE\\Save.txt");
    if (SavedFile.is_open())
    {
        int _temp0 = 0;
        while (getline(SavedFile, line))
        {
            std::cout << line << '\n';
            switch (_temp0)
            {
            case 0:
                m_Coin = std::stoi(line);
                break;
            case 1:
                m_IntroScene = std::stoi(line);
                break;
            case 2:
                m_EndGame = std::stoi(line);
                break;
            case 3:
                m_heal = std::stoi(line);
                break;
            case 4:
                m_damage = std::stoi(line);
                break;
            }
            ++_temp0;
        }
        SavedFile.close();
    }

}