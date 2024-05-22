#pragma once
#include "StageBase.h"
class SecondStage :public StageBase
{
public:
    SecondStage(std::vector<std::vector<int>>::iterator it, int sizeX, int sizeY);
    ~SecondStage();
    void SetParam(void)override;
};

