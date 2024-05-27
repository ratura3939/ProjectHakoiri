//#pragma once
#include "StageBase.h"

class TutorialStage : public StageBase
{
public:
    TutorialStage(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
        std::vector<std::vector<int>> map[], std::vector<std::vector<int>> obj[],
        int* roomImg, int* mapchip[]);
    ~TutorialStage();
    void SetParam(void)override;
};

