#pragma once
#include "StageBase.h"
class FirstStage :
    public StageBase
{
public:
    FirstStage(std::vector<std::vector<int>>::iterator it, int sizeX, int sizeY);
    ~FirstStage();
    void SetParam(void)override;
};

