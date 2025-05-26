#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>

class ScoreboardScene final : public Engine::IScene {
private:
    float ticks;
    ALLEGRO_SAMPLE_ID bgmId;

public:
    int pageId;
    std::vector<std::pair<int, std::string>> scoreData;
    explicit ScoreboardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void ReadScore();
    void BackOnClick(int stage);
    void ChangePageOnClick(int deltapage);
};

#endif   // SCOREBOARDSCENE_HPP
