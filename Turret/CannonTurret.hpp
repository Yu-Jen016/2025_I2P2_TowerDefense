#ifndef CANNONTURRET_HPP
#define CANNONTURRET_HPP
#include "Turret.hpp"

class CannonTurret : public Turret {
public:
    static const int Price;
    CannonTurret(float x, float y);
    void CreateBullet() override;
};
#endif   // CANNONTURRET_HPP
