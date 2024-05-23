#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Living.h"

Living::Living(int roomImg, int sizeX, int sizeY) :RoomBase(roomImg, sizeX, sizeY)
{

}
Living::~Living(void)
{

}
//ÉpÉâÉÅÅ[É^ÇÃê›íË
void Living::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::LIVING;

	mapCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::LIVING_MAP_CSV).csv_;
	objCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::LIVING_OBJ_CSV).csv_;
}