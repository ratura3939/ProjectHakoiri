#include<DxLib.h>
#include"RoomBase.h"
#include"Wasitu.h"

Wasitu::Wasitu(int roomImg) :RoomBase(roomImg)
{

}
Wasitu::~Wasitu(void)
{

}

//ƒpƒ‰ƒ[ƒ^‚Ìİ’è
void Wasitu::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::WASITU;
}