#pragma once
#include"RoomBase.h"

class Wasitu :public RoomBase
{
public:
	Wasitu(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//コンストラクタ
	~Wasitu(void);

	void SetParam(void) override; //パラメータの設定
};