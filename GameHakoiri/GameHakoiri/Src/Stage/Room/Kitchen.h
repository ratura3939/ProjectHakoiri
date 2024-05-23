#pragma once
#include "RoomBase.h"
class Kitchen :public RoomBase
{
public:
	Kitchen(int roomImg, int sizeX, int sizeY);
	~Kitchen(void);
	void SetParam(void) override; //ƒpƒ‰ƒ[ƒ^‚Ìİ’è
};

