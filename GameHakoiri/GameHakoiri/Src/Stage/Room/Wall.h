#pragma once
#include "RoomBase.h"
class Wall :public RoomBase
{
public:
	Wall(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
		int* mapchip);	//コンストラクタ
	~Wall(void);
	void SetParam(void) override; //パラメータの設定
};

