#pragma once
#include "RoomBase.h"
class Goal :public RoomBase
{
public:
	Goal(int roomImg);	//コンストラクタ
	~Goal(void);
	void SetParam(void) override; //パラメータの設定
};

