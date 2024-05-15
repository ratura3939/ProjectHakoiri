#pragma once
#include "RoomBase.h"
class Living :public RoomBase
{
public:
	Living(int roomImg);
	~Living(void);
	void SetParam(void) override; //ƒpƒ‰ƒ[ƒ^‚Ìİ’è
};

