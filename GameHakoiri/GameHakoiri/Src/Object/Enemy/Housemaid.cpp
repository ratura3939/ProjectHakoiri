#include"../../Manager/ResourceManager.h"
#include "Housemaid.h"

void Housemaid::SetParam(void)
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IMGS).handleIds_;
	dir_ = CharacterBase::DIR::BOTTOM;
	move_ = 2.0f;
	type_ = TYPE::HOUSEMADE;
	SetIsUse(false);
}
