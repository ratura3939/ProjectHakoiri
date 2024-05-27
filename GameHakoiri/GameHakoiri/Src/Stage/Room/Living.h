#pragma once
#include "RoomBase.h"
class Living :public RoomBase
{
public:
	Living(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//コンストラクタ
	~Living(void);
	void SetParam(void) override; //パラメータの設定
};

