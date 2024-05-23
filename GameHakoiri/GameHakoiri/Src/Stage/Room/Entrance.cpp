#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include "Entrance.h"

Entrance::Entrance(int roomImg, int sizeX, int sizeY) :RoomBase(roomImg, sizeX, sizeY)
{

}
Entrance::~Entrance(void)
{

}
//ÉpÉâÉÅÅ[É^ÇÃê›íË
void Entrance::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::ENTRANCE;

	mapCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::ENTRANCE_MAP_CSV).csv_;
	objCsv_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::ENTRANCE_OBJ_CSV).csv_;
}