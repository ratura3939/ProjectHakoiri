#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"../../Manager/StageManager.h"
#include"RoomBase.h"
#include "Goal.h"

Goal::Goal(int roomImg) 
	:RoomBase(roomImg)
{

}
Goal::~Goal(void)
{

}
//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Goal::SetParam(void)
{
	pazzleSize_ = { StageManager::NOMAL_PAZZLE_X,StageManager::NOMAL_MAP_Y };
	type_ = TYPE::GOAL;
	isDrawRoom_ = true;
}