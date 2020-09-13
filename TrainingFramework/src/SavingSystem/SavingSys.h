#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <bitset>
class SavingSys
{
private:

    int m_Coin;
    bool m_IntroScene;
    bool m_EndGame;
    int m_BlockBullet;// number of BlockBullet
    int m_Dodge;// number of Dodge
    int m_CompletedScene;// Out of 10 ==> to Boss Scene

public:
    int m_heal;
    int m_damage;
    SavingSys();
    SavingSys(int m_Coin, bool _IntroScene, bool _EndGame);
    int m_SceneManage;// 0= load IntroStoryline, 1 = load Home, 2 = load GSPLay, 3 = Load Menu
#pragma region GET_SET
    int getM_Coin();
    bool isM_IntroScene();
    bool isM_EndGame();
    int getM_BlockBullet();
    int getM_Dodge();
    int getM_CompletedScene();
    void setM_Coin(int m_Coin);
    void setM_IntroScene(bool m_IntroScene);
    void setM_EndGame(bool m_EndGame);
    void setM_BlockBullet(int m_BlockBullet);
    void setM_Dodge(int m_Dodge);
    void setM_CompletedScene(int m_CompletedScene);
#pragma endregions
    void Save();
    void Load();
};
