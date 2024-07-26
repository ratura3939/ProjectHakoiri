#pragma once
#include "RoomBase.h"
class Own :public RoomBase
{
public:
	Own(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//コンストラクタ
	Own(int roomImg);	//コピーコンストラクタ
	~Own(void);
	void SetParam(void) override; //パラメータの設定
	void DrawPazzle(void) override;	//パズルシーンにおける部屋の描画

private:
	int* chara_;
};

