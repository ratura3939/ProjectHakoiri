#pragma once
#include "RoomBase.h"
class Entrance :public RoomBase
{
public:
	Entrance(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
		int* mapchip);	//コンストラクタ
	~Entrance(void);
	void SetParam(void) override; //パラメータの設定

};

