#pragma once
#include "StageBase.h"
class SecondStage :public StageBase
{
public:
    SecondStage(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
        std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
        int* roomImg, int* mapchip[]);
    ~SecondStage();
    void SetParam(void)override;
};

