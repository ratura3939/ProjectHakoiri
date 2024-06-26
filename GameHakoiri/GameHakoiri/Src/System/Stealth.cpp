#include<DxLib.h>

#include"../Application.h"

#include"../Utility/Utility.h"
#include"../Manager/InputManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include"../Object/Player.h"
#include"../Object/CharacterBase.h"
#include"../Object/Enemy/Housemaid.h"
#include"../Object/Enemy/Seneschal.h"
#include"Stealth.h"

//�R���X�g���N�^
//********************************************************
Stealth::Stealth(void)
{
	player_ = nullptr;
}
//�f�X�g���N�^
//********************************************************
Stealth::~Stealth(void)
{

}

//������
//********************************************************
bool Stealth::Init(void)
{
	StageManager::GetInstance().ChangeModeInit();
	//�J�����Ƀ}�b�v�̃T�C�Y��ݒ�
	auto& camera = Camera::GetInstance();
	camera.SetMapSize(StageManager::GetInstance().GetMapMaxSize());
	player_ = new Player;
	player_->Init();

	EnemyInit();
	SetEnemy();
	
	//�������������I�������̂�
	return true;
}
//�X�V
//********************************************************
void Stealth::Update(void)
{
	//�J�������v���C���[�ɐݒ�
	auto& camera = SceneManager::GetInstance().GetCamera();
	camera.SetTargetPos(player_->GetPos());

	//enemy
	for (auto& e : useEnemy_)
	{
		e->Update();
	}

	//player
	player_->Update();


	Collision();
}
//�`��
//********************************************************
void Stealth::Draw(void)
{
	player_->Draw();
	//StageManager::GetInstance().DrawObject();
	for (auto& e : useEnemy_)
	{
		e->Draw();
	}
	DrawDebug();

	auto& ins = InputManager::GetInstance();
	if (ins.IsNew(KEY_INPUT_M))
	{
		StageManager::GetInstance().Draw(GameScene::MODE::PAZZLE);
	}
}
//���
//********************************************************
bool Stealth::Release(void)
{
	player_->Release();
	for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)
	{
		enemyMng_[i]->Release();
	}
	useEnemy_.clear();
	memorizePos_.clear();
	memorizeType_.clear();
	//�������������I�������̂�
	return true;
}

#pragma region �����蔻��

//�����蔻�葍��
void Stealth::Collision(void)
{
	//�v���C���[
	//--------------------------------------------------------
	//to�}�b�v�`�b�v
	CollisionMapchip(player_,true);
	
	
	//�G
	//--------------------------------------------------------
	for (auto& e : useEnemy_)
	{
		//to�}�b�v�`�b�v
		CollisionMapchip(e, false);
		//�G���Փ˂��Ă���Ƃ�
		if (IsEnemyMove())
		{
			//�G�𓮂��I���̏�Ԃ�
			e->SetIsMove(false);
		}
	}
}


void Stealth::CollisionMapchip(CharacterBase* character, bool isPlayer)
{
	//�G�p�̃t���O���Z�b�g
	SetIsEnemyMove(false);

	//�X�e�[�W�}�l�[�W���擾
	auto& stage = StageManager::GetInstance();
	//���肷��L�����N�^�[���W���}�b�v���W�ɕϊ�
	auto mapPos = stage.GetVector2MapPos(character->GetCollisionPos().ToVector2());

	if (stage.IsCollisionWall(mapPos))
	{
		CollisionObstacle(character);
	}
	else if (stage.IsCollisionObject(mapPos))
	{
		auto type = stage.GetObjectType(mapPos);
		if (type == StageManager::OBJECT::OBSTACLE) { CollisionObstacle(character); }
		if (type == StageManager::OBJECT::THROUGH) { CollisionTrough(mapPos, character); }
		//�C�x���g�}�b�v�`�b�v�̓v����[�����������Ȃ�
		if (type == StageManager::OBJECT::EVENT && isPlayer) { CollisionEvent(mapPos); }	

		//pCol = stage.GetVector2MapPos(player_->GetCollisionPos().ToVector2());
	}
}
//�ʂ蔲���s�ȃI�u�W�F�N�g
void Stealth::CollisionObstacle(CharacterBase* character)
{
	character->SetPos(character->GetPrevPos());
	//�G�p�̃t���O�Z�b�g
	SetIsEnemyMove(true);
}
//�ŉ��i�ȊO�͒ʂ蔲���\�ȃI�u�W�F�N�g
void Stealth::CollisionTrough(Vector2 pCol, CharacterBase* character)
{
	if(StageManager::GetInstance().IsBottomObject(pCol))
	{ 
		character->SetPos(character->GetPrevPos()); 
		//�G�p�̃t���O�Z�b�g
		SetIsEnemyMove(true);
	}
}
//���Ȃǂ̃C�x���g���N����I�u�W�F�N�g
void Stealth::CollisionEvent(Vector2 pCol)
{
	//�X�e�[�W�}�l�[�W���擾
	auto& stage = StageManager::GetInstance();
	auto prevKey = stage.GetKey();

	stage.ChangeMap(pCol);	//�����̈ړ�����

	if (stage.IsClear())
	{
		return;	//�S�[�����Ă��珈�����f
	}

	if (!stage.IsMove())		//�ړ��ł��Ȃ��Ƃ�
	{
		player_->SetPos(player_->GetPrevPos());
	}
	else
	{
		//�Ƃ肠�����ړ�������X�e�[�W�̐^�񒆂Ɂi�e�X�g�p�j
		//�J�����Ƀ}�b�v�̃T�C�Y��ݒ�
		auto& camera = Camera::GetInstance();
		auto mapSize = stage.GetMapMaxSize().ToVector2();
		camera.SetMapSize(mapSize.ToVector2F());

		//player�̈ړ���̈ʒu�ݒ�
		Vector2 pos;
		auto door = stage.GetDoor();
		auto doorSec = stage.GetDoorSecond();
		//�s����̌`������
		auto shape = stage.GetShape();

		//��܂��͉��̕����̔����痈���ꍇ�B�i�s����̉��܂��͏㑤�ɏo��j
		//�c�����㉺�Ɉړ����Ă���Ƃ���doorY��doorSec�������ꍇ�B���̑���̂Ƃ���doorSec��NONE�Ȃ̂ŉ��L�̋L�q

		if (door.y != StageManager::DOOR_Y::MIDDLE &&		//�ړ����^�񒆂ł͂Ȃ��Ƃ�
			(door.y == doorSec || doorSec == StageManager::DOOR_Y::NONE)	//doorSec�ł̊m�F
			)
		{
			switch (shape)	//�ړ���̌`�ɂ��ꏊ��ݒ�
			{
			case RoomBase::ROOM_SHAPE::NOMAL:
			case RoomBase::ROOM_SHAPE::OBLONG:
				if (door.y == StageManager::DOOR_Y::TOP)
				{
					pos = { DOOR_DISTANCE,mapSize.y - INIT_ROOM_POS };	//�}�b�v�����ɏo��
				}
				else if (door.y == StageManager::DOOR_Y::BOTTOM)
				{
					pos = { DOOR_DISTANCE, INIT_ROOM_POS };	//�}�b�v����ɏo��
				}

				break;
			case RoomBase::ROOM_SHAPE::OBLONG_SIDE:
				//�����`�̓�R�}�ڂɏo���`�Ղ��������ꍇ
				if (stage.IsSecondEvidence())
				{
					if (door.y == StageManager::DOOR_Y::TOP)
					{
						//�E���̉��o��
						pos = { mapSize.x - DOOR_DISTANCE,mapSize.y - INIT_ROOM_POS };
					}
					else if (door.y == StageManager::DOOR_Y::BOTTOM)
					{
						//�E���̏�ɏo��
						pos = { mapSize.x - DOOR_DISTANCE,INIT_ROOM_POS };
					}
				}
				else 
				{
					if (door.y == StageManager::DOOR_Y::TOP)
					{
						//�����̉��ɏo��
						pos = { DOOR_DISTANCE,mapSize.y - INIT_ROOM_POS };
					}
					else if (door.y == StageManager::DOOR_Y::BOTTOM)
					{
						//�����̏�ɏo��
						pos = { DOOR_DISTANCE,INIT_ROOM_POS };
					}
					
				}	
				break;
			}
		}
		else
		{
			//���E�̈ړ��̂Ƃ�
			switch (shape)
			{
			case RoomBase::ROOM_SHAPE::NOMAL:
			case RoomBase::ROOM_SHAPE::OBLONG_SIDE:
				//player���ǂ������痈�����𔻒f
				if (door.x == StageManager::DOOR_X::LEFT)
				{
					pos = { mapSize.x - INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//�E�ɐݒ�
				}
				else if (door.x == StageManager::DOOR_X::RIGHT)
				{
					pos = { INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//���ɐݒ�
				}

				break;
			case RoomBase::ROOM_SHAPE::OBLONG:
				//�����`�̓�R�}�ڂɏo���`�Ղ��������ꍇ
				if (stage.IsSecondEvidence())
				{
					//player���ǂ������痈�����𔻒f
					if (door.x == StageManager::DOOR_X::LEFT)
					{
						pos = { mapSize.x - INIT_ROOM_POS_SIDE,mapSize.y - DOOR_DISTANCE };	//�E���ɐݒ�
					}
					else if (door.x == StageManager::DOOR_X::RIGHT)
					{
						pos = { INIT_ROOM_POS_SIDE,mapSize.y - DOOR_DISTANCE };	//�����ɐݒ�
					}
				}
				else
				{
					//player���ǂ������痈�����𔻒f
					if (door.x == StageManager::DOOR_X::LEFT)
					{
						pos = { mapSize.x - INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//�E��ɐݒ�
					}
					else if (door.x == StageManager::DOOR_X::RIGHT)
					{
						pos = { INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//����ɐݒ�
					}
				}
				break;
			}
		}

		//�G���̕ۑ�
		MemorizeEnemy(prevKey);
		//�G�̐ݒ�
		SetEnemy();

		//�^�[�Q�b�g�ݒ�
		camera.SetTargetPos(pos.ToVector2F());
		player_->SetPos(pos.ToVector2F());
	}
}

#pragma endregion


void Stealth::ChangeRoom(void/*�����ꂩ�͓��������̎w�萔�������*/)
{

	//�J�����Ƀ}�b�v�̃T�C�Y��ݒ�
	auto& camera = Camera::GetInstance();
	camera.SetMapSize(StageManager::GetInstance().GetMapMaxSize());
}

void Stealth::DrawDebug(void)
{
	auto pos = player_->GetCollisionPos();
	auto pPos = player_->GetPos();
	

	DrawFormatString(0, 0, 0xffffff,
		"player�̍��W��(%.1f,%.1f)\nplayer�̓����蔻�聁(%.1f,%.1f)\n",
		pPos.x,pPos.y,pos.x,pos.y);


}

void Stealth::EnemyInit(void)
{
	for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)
	{
		//�G���O�̂�����
		if (i < OBLONG_ENEMY_NUM)
		{
			enemyMng_[i] = new Housemaid;
		}
		else
		{
			enemyMng_[i] = new Seneschal;
		}
		enemyMng_[i]->Init();
	}

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][0] = { NX1,NY1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][1] = { NX2,NY2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][2] = { 0.0f,0.0f };

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][0] = { OBX1,OBY1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][1] = { OBX2,OBY2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][2] = { OBX3,OBY3 };

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][0] = { OB2X1,OB2Y1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][1] = { OB2X2,OB2Y2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][2] = { OB2X3,OB2Y3 };

	/*initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][0] = NOMAL_POS_1;
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][1] = NOMAL_POS_2;
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][2] = { 0.0f,0.0f };

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][0] = OBLONG_POS_1;
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][1] = OBLONG_POS_2;
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][2] = OBLONG_POS_3;

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][0] = OBLONG_2_POS_1;
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][1] = OBLONG_2_POS_2;
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][2] = OBLONG_2_POS_3;*/
}

void Stealth::CreateEnemy(void)
{
	int rnd;
	do
	{
		//�����擾
		rnd = rand();

		//�G�̑����Ŋ������]����擾
		rnd %= OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX);
	} while (enemyMng_[rnd]->IsUse());

	//�G�̃t���O���Ǘ�
	enemyMng_[rnd]->SetIsUse(true);


	//�g�p����G�̃Z�b�g
	useEnemy_.push_back(enemyMng_[rnd]);
	
}

void Stealth::InitEnemyPos(const RoomBase::ROOM_SHAPE type)
{
	for (int i = 0; i < useEnemy_.size(); i++)
	{
		useEnemy_[i]->SetPos(initPos_[static_cast<int>(type)][i]);
	}
}

void Stealth::SetEnemy(void)
{

	//�X�e�[�W�}�l�[�W���擾
	auto& stage = StageManager::GetInstance();
	auto key = stage.GetKey();

	//���݂̕����ɓG�̐����L�^���Ȃ�������
	if (memorizePos_[key].empty())
	{
		auto type = stage.GetShape();
		//�G�̐���
		if (type == RoomBase::ROOM_SHAPE::NOMAL)
		{
			//�����`�̏ꍇ
			for (int i = 0; i < NOMAL_ENEMY_NUM; i++)
			{
				CreateEnemy();
				
			}
		}
		else
		{
			//�����`�̏ꍇ
			for (int i = 0; i < OBLONG_ENEMY_NUM; i++)
			{
				CreateEnemy();
			}
		}
		InitEnemyPos(type);
	}
	else
	{
		//�����L�^���������ꍇ
		auto size = memorizePos_[key].size();
		for (int m = 0; m < size; m++)	//�G�̐���������
		{
			SearchSetEnemy(key, m);
		}
	}
}

void Stealth::SearchSetEnemy(std::string key, int num)
{
	for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)//�G�̊Ǘ��S��
	{
		if (memorizeType_[key][num] == enemyMng_[i]->GetType() &&	//�ۑ�����Ă����ނƓ�����������
			!enemyMng_[i]->IsUse())	//�܂��g�p����ĂȂ�������
		{
			//�G�̃t���O�Ǘ��ƈʒu�̐ݒ�
			enemyMng_[i]->SetPos(memorizePos_[key][num]);
			enemyMng_[i]->SetIsUse(true);
			//�G�̊i�[
			useEnemy_.push_back(enemyMng_[i]);

			return;
		}
	}
}

void Stealth::MemorizeEnemy(std::string key)
{
	auto size = useEnemy_.size();
	memorizePos_[key].clear();

	for (int i = 0; i < size; i++)
	{
		//�^�C�v�ƃ|�W�V�����̋L�^
		memorizePos_[key].push_back(useEnemy_[i]->GetPos());
		memorizeType_[key].push_back(useEnemy_[i]->GetType());
		//��ڂ��I�����̂Ŕ�g�p�ɕϊ�
		useEnemy_[i]->SetIsUse(false);
	}
	useEnemy_.clear();

	for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)
	{
		//�g�p�t���O��S�ă��Z�b�g
		enemyMng_[i]->SetIsUse(false);
	}
}

void Stealth::SetIsEnemyMove(bool flag)
{
	isEnemyMove_ = flag;
}

bool Stealth::IsEnemyMove(void) const
{
	return isEnemyMove_;
}

