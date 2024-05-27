#pragma once
#include "StageBase.h"
class FirstStage :
    public StageBase
{
public:
    FirstStage(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
        std::vector<std::vector<int>> map[], std::vector<std::vector<int>> obj[],
        int* roomImg, int* mapchip[]);
    ~FirstStage();
    void SetParam(void)override;
};

