#pragma once
#include "StageBase.h"
class ThirdStage : public StageBase
{
public:
    ThirdStage(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
        std::vector<std::vector<int>> map[], std::vector<std::vector<int>> obj[],
        int* roomImg, int* mapchip[]);
    ~ThirdStage();
    void SetParam(void)override;
};

