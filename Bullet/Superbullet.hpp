#ifndef SUPERBULLET_HPP
#define SUPERBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}   // namespace Engine

class Superbullet : public Bullet {
public:
    explicit Superbullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent);
    void OnExplode(Enemy *enemy) override;
};
#endif   // SUPERBULLET_HPP
