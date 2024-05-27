#pragma once
#include "RoomBase.h"
class None : public RoomBase
{
public:
	None(int roomImg);	//コンストラクタ
	~None(void);

	void SetParam(void)override;
};

