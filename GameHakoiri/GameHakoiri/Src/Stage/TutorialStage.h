//#pragma once
#include "StageBase.h"

class TutorialStage : public StageBase
{
public:
    TutorialStage(std::vector<std::vector<int>>::iterator it, int sizeX, int sizeY);
    ~TutorialStage();
    void SetParam(void)override;
};

