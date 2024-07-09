#include "Plate.h"
#include"../Manager/ResourceManager.h"

Plate::Plate(void)
{
	isFinishAnim_ = false;
	plateSelectImg_ = 0;
	plateChangeImg_ = 0;
	frameImg_ = 0;
}

Plate::~Plate(void)
{
}

void Plate::Init(void)
{
	plateSelectImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLATE_SELECT_IMG).handleId_;
	plateChangeImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLATE_CHECK_IMG).handleId_;
	frameImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_2_IMG).handleId_;
}

bool Plate::Update(TYPE type)
{
	switch (state_)
	{
	case Plate::STATE::GO:
		UpdateGo();
		break;
	case Plate::STATE::STOP:
		if (type == Plate::TYPE::SELECT)
		{
			if (UpdateStopSelect())
			{
				return true;
			}
		}
		else if (type == Plate::TYPE::CHECK)
		{
			if (UpdateStopCheck())
			{
				return true;
			}
		}
		break;
	case Plate::STATE::BACK:
		UpdateBack();
		break;
	}
    return false;
}

void Plate::UpdateGo(void)
{
}

bool Plate::UpdateStopSelect(void)
{
	return false;
}

bool Plate::UpdateStopCheck(void)
{
	return false;
}

void Plate::UpdateBack(void)
{
}

void Plate::Draw(void)
{
}

void Plate::Release(void)
{
	
}
