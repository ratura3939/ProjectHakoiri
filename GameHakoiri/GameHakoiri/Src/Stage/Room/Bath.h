#pragma once
#include "RoomBase.h"
class Bath :public RoomBase
{
public:
	Bath(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//コンストラクタ
	~Bath(void);
	void SetParam(void) override; //パラメータの設定
};

