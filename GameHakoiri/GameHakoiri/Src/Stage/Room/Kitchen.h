#pragma once
#include "RoomBase.h"
class Kitchen :public RoomBase
{
public:
	Kitchen(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//コンストラクタ
	~Kitchen(void);
	void SetParam(void) override; //パラメータの設定
};

