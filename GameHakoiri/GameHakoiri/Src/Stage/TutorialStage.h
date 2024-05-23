//#pragma once
#include "StageBase.h"

class TutorialStage : public StageBase
{
public:
    TutorialStage(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
        std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
        int* roomImg, int* mapchip[]);
    ~TutorialStage();
    void SetParam(void)override;
};

