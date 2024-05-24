#pragma once
#include "RoomBase.h"
class Storage :public RoomBase
{
public:
	Storage(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
		int* mapchip);	//コンストラクタ
	~Storage(void);
	void SetParam(void) override; //パラメータの設定
};

