#pragma once
#include "RoomBase.h"
class Goal :public RoomBase
{
public:
	Goal(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
		int* mapchip);	//コンストラクタ
	~Goal(void);
	void SetParam(void) override; //パラメータの設定
};

