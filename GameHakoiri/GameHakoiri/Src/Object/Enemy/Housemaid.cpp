#include"../../Manager/ResourceManager.h"
#include "Housemaid.h"

void Housemaid::SetParam(void)
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IMGS).handleIds_;
	dir_ = CharacterBase::DIR::BOTTOM;
	pos_ = { 1420.0f,400.0f };
	move_ = 2.0f;
}
