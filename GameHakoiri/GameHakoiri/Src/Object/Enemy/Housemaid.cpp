#include"../../Manager/ResourceManager.h"
#include "Housemaid.h"

void Housemaid::SetParam(void)
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::MAID_IMGS).handleIds_;
	dir_ = CharacterBase::DIR::RIGHT;
	speed_ = SPEED;
	move_ = MOVE_POW;
	type_ = TYPE::HOUSEMADE;
	SetIsUse(false);
}
