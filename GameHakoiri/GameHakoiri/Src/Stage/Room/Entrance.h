#pragma once
#include "RoomBase.h"
class Entrance :public RoomBase
{
public:
	Entrance(int roomImg, int sizeX, int sizeY);
	~Entrance(void);
	void SetParam(void) override; //ƒpƒ‰ƒ[ƒ^‚Ìİ’è

};

