#include<DxLib.h>
#include"RoomBase.h"
#include "Kitchen.h"

Kitchen::Kitchen(int roomImg) :RoomBase(roomImg)
{

}
Kitchen::~Kitchen(void)
{

}
//パラメータの設定
void Kitchen::SetParam(void)
{
	PazzleSize_ = { 1.0f,2.0f };
	StealthSize_ = { 30.0f,60.0f };
	type_ = RoomBase::TYPE::KITCHEN;

	//テスト用
	dbgColor_ = 0xfaf0e6;
}