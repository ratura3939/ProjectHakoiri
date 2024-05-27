#pragma once
#include "RoomBase.h"
class Entrance :public RoomBase
{
public:
	Entrance(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//コンストラクタ
	Entrance(int roomImg);	//コピーコンストラクタ
	~Entrance(void);
	void SetParam(void) override; //パラメータの設定

};

