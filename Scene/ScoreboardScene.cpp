#include <functional>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "ScoreboardScene.hpp"

void ScoreboardScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    if(scoreData.empty()){
        ScoreboardScene::ReadScore();
    }

    AddNewObject(new Engine::Label("SCOREBOARD", "pirulen.ttf", 48, halfW, 30, 0, 255, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label(std::string("Page:") + std::to_string(pageId + 1), "pirulen.ttf", 48, halfW, 100, 0, 255, 0, 255, 0.5, 0.5));

    for(int i = 0; i < 5; ++i){
        AddNewObject(new Engine::Label(std::to_string(pageId*5+i+1), "pirulen.ttf", 48, halfW - 300, 300 + i * 50, 0, 255, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label(scoreData[pageId*5+i].second, "pirulen.ttf", 48, halfW, 300 + i * 50, 0, 255, 0, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label(std::to_string(scoreData[pageId*5+i].first), "pirulen.ttf", 48, halfW + 300, 300 + i * 50, 0, 255, 0, 255, 0.5, 0.5));
    }

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 650, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::ChangePageOnClick, this, -1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("PREV", "pirulen.ttf", 48, halfW - 450, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW + 250, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::ChangePageOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("NEXT", "pirulen.ttf", 48, halfW + 450, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("happy.ogg");
}
void ScoreboardScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void ScoreboardScene::Update(float deltaTime) {
    ticks += deltaTime;
}
void ScoreboardScene::ReadScore(){
    std::pair<int, std::string> data;
    std::ifstream fin("Resource/scoreboard.txt");
    if(!fin){
        // std::cout << "READ ERROR!!" << std::endl;
    }
    while (fin >> data.second >> data.first){
        scoreData.push_back(data);
    }
    scoreData.resize(50);
    std::sort(scoreData.begin(), scoreData.end(), [](auto a, auto b){return a > b;});
}
void ScoreboardScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void ScoreboardScene::ChangePageOnClick(int deltapage){
    ScoreboardScene *scene = dynamic_cast<ScoreboardScene *>(Engine::GameEngine::GetInstance().GetScene("scoreboard"));
    if(deltapage + pageId < 0){
        scene->pageId = 0;
    }
    else if(deltapage + pageId > 9){
        scene->pageId = 9;
    }
    else {
        scene->pageId = pageId + deltapage;
    }
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
}