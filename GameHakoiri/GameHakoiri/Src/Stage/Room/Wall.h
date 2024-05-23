#pragma once
#include "RoomBase.h"
class Wall :public RoomBase
{
public:
	Wall(int roomImg, int sizeX, int sizeY);
	~Wall(void);
	void SetParam(void) override; //ƒpƒ‰ƒ[ƒ^‚Ìİ’è
};

