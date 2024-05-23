#pragma once
#include "RoomBase.h"
class Goal :public RoomBase
{
public:
	Goal(int roomImg, int sizeX, int sizeY);
	~Goal(void);
	void SetParam(void) override; //ƒpƒ‰ƒ[ƒ^‚Ìİ’è
};

