#pragma once
#include "../EnemyBase.h"
class Oldman :
    public EnemyBase
{
public:
    static constexpr float SPEED = 2.0f;
    static constexpr float MOVE_POW = 2.0f;

    void SetParam(void)override;
};

