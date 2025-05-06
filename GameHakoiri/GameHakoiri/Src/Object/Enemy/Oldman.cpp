#include"../../Manager/ResourceManager.h"
#include "Oldman.h"

void Oldman::SetParam(void)
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::OLDMAN_IMGS).handleIds_;
	dir_ = CharacterBase::DIR::TOP;
	speed_ = SPEED;
	move_ = MOVE_POW;
	type_ = TYPE::HOUSEMADE;
	SetIsUse(false);
}
