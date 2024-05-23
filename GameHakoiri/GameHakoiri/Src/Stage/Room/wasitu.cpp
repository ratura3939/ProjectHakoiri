#include<DxLib.h>
#include"../../Manager/ResourceManager.h"
#include"RoomBase.h"
#include"Wasitu.h"

Wasitu::Wasitu(int roomImg, int sizeX, int sizeY) :RoomBase(roomImg, sizeX, sizeY)
{

}
Wasitu::~Wasitu(void)
{

}

//ÉpÉâÉÅÅ[É^ÇÃê›íË
void Wasitu::SetParam(void)
{
	pazzleSize_ = { 1.0f,1.0f };
	type_ = RoomBase::TYPE::WASITU;
	
	mapCsv_= ResourceManager::GetInstance().Load(ResourceManager::SRC::WASITU_MAP_CSV).csv_;
	objCsv_= ResourceManager::GetInstance().Load(ResourceManager::SRC::WASITU_OBJ_CSV).csv_;
	mapTile_= ResourceManager::GetInstance().Load(ResourceManager::SRC::).handleIds_;
}