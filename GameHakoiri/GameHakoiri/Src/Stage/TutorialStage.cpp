#include "TutorialStage.h"

TutorialStage::TutorialStage(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
	std::vector<std::vector<int>> map[], std::vector<std::vector<int>> obj[],
	int* roomImg, int* mapchip[])
	:StageBase(pzlIt, pzlSizeX, pzlSizeY, map, obj, roomImg, mapchip)
{

}

TutorialStage::~TutorialStage()
{
}

void TutorialStage::SetParam(void)
{
}