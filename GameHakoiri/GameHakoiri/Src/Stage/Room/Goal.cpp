#include<DxLib.h>
#include"RoomBase.h"
#include "Goal.h"

Goal::Goal(int roomImg) :RoomBase(roomImg)
{

}
Goal::~Goal(void)
{

}
//パラメータの設定
void Goal::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::GOAL;

	

	//テスト用
	dbgColor_ = 0x00ffff;
}