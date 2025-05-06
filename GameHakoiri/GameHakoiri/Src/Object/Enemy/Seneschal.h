#pragma once
#include "../EnemyBase.h"
class Seneschal :
    public EnemyBase
{
public:
    static constexpr float SPEED = 1.0f;
    static constexpr float MOVE_POW = 10.0f;

    void SetParam(void)override;
};

