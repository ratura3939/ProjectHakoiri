#pragma once
#include "RoomBase.h"
class Storage :public RoomBase
{
public:
	Storage(int roomImg, int sizeX, int sizeY);
	~Storage(void);
	void SetParam(void) override; //ƒpƒ‰ƒ[ƒ^‚Ìİ’è
};

