#pragma once
#include "RoomBase.h"
class Bath :public RoomBase
{
public:
	Bath(int roomImg, int sizeX, int sizeY);
	~Bath(void);
	void SetParam(void) override; //ƒpƒ‰ƒ[ƒ^‚Ìİ’è
};

