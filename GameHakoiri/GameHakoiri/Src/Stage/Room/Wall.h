#pragma once
#include "RoomBase.h"
class Wall :public RoomBase
{
public:
	Wall(int roomImg);	//コンストラクタ
	~Wall(void);
	void SetParam(void) override; //パラメータの設定
};

