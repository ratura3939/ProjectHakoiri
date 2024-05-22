#pragma once
#include "StageBase.h"
class ThirdStage : public StageBase
{
public:
    ThirdStage(std::vector<std::vector<int>>::iterator it, int sizeX, int sizeY);
    ~ThirdStage();
    void SetParam(void)override;
};

