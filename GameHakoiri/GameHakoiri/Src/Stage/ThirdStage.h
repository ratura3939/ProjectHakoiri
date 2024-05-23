#pragma once
#include "StageBase.h"
class ThirdStage : public StageBase
{
public:
    ThirdStage(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
        std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
        int* roomImg, int* mapchip[]);
    ~ThirdStage();
    void SetParam(void)override;
};

