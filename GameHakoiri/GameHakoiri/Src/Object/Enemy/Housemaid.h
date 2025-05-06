#pragma once
#include "../EnemyBase.h"
class Housemaid :
    public EnemyBase
{
public:

    static constexpr float SPEED = 0.5f;
    static constexpr float MOVE_POW = 5.0f;
    
    void SetParam(void)override;
};

