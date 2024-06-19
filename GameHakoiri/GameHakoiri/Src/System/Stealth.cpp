#include<DxLib.h>

#include"../Application.h"

#include"../Utility/Utility.h"
#include"../Manager/InputManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include"../Object/Player.h"
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
	prevPlayerPos_ = player_->GetPos();
	
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

	prevPlayerPos_ = player_->GetPos();
	player_->Update();


	Collision();
}
//�`��
//********************************************************
void Stealth::Draw(void)
{
	player_->Draw();
	//StageManager::GetInstance().DrawObject();
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
	//�������������I�������̂�
	return true;
}

#pragma region �����蔻��

//�����蔻�葍��
void Stealth::Collision(void)
{
	//�X�e�[�W�}�l�[�W���擾
	auto& stage = StageManager::GetInstance();

	//�v���C���[�ƃI�u�W�F�N�g�̓����蔻��
	//--------------------------------------------------------
	//�v���C���[�̓����蔻����W���}�b�v�̔z��ԍ��ɕϊ�
	auto pCol = stage.GetVector2MapPos(player_->GetCollisionPos().ToVector2());
	
	if (stage.IsCollisionWall(pCol))
	{
		CollisionObstacle();
	}
	else if (stage.IsCollisionObject(pCol))
	{
	 	auto type = stage.GetObjectType(pCol);
		if (type == StageManager::OBJECT::OBSTACLE) { CollisionObstacle(); }
		if (type == StageManager::OBJECT::THROUGH) { CollisionTrough(pCol); }
		if (type == StageManager::OBJECT::EVENT) { CollisionEvent(pCol); }

		//pCol = stage.GetVector2MapPos(player_->GetCollisionPos().ToVector2());
	}
	
}
//�ʂ蔲���s�ȃI�u�W�F�N�g
void Stealth::CollisionObstacle(void)
{
	player_->SetPos(prevPlayerPos_);
}
//�ŉ��i�ȊO�͒ʂ蔲���\�ȃI�u�W�F�N�g
void Stealth::CollisionTrough(Vector2 pCol)
{
	if(StageManager::GetInstance().IsBottomObject(pCol)){ player_->SetPos(prevPlayerPos_); }
}
//���Ȃǂ̃C�x���g���N����I�u�W�F�N�g
void Stealth::CollisionEvent(Vector2 pCol)
{
	//�X�e�[�W�}�l�[�W���擾
	auto& stage = StageManager::GetInstance();

	stage.ChangeMap(pCol);	//�����̈ړ�����
	if (!StageManager::GetInstance().IsMove())		//�ړ��ł��Ȃ��Ƃ�
	{
		player_->SetPos(prevPlayerPos_);
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
					pos = { DOOR_DISTANCE,mapSize.y_ - INIT_ROOM_POS };	//�}�b�v�����ɏo��
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
						pos = { mapSize.x_ - DOOR_DISTANCE,mapSize.y_ - INIT_ROOM_POS };
					}
					else if (door.y == StageManager::DOOR_Y::BOTTOM)
					{
						//�E���̏�ɏo��
						pos = { mapSize.x_ - DOOR_DISTANCE,INIT_ROOM_POS };
					}
				}
				else 
				{
					if (door.y == StageManager::DOOR_Y::TOP)
					{
						//�����̉��ɏo��
						pos = { DOOR_DISTANCE,mapSize.y_ - INIT_ROOM_POS };
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
					pos = { mapSize.x_ - INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//�E�ɐݒ�
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
						pos = { mapSize.x_ - INIT_ROOM_POS_SIDE,mapSize.y_ - DOOR_DISTANCE };	//�E���ɐݒ�
					}
					else if (door.x == StageManager::DOOR_X::RIGHT)
					{
						pos = { INIT_ROOM_POS_SIDE,mapSize.y_ - DOOR_DISTANCE };	//�����ɐݒ�
					}
				}
				else
				{
					//player���ǂ������痈�����𔻒f
					if (door.x == StageManager::DOOR_X::LEFT)
					{
						pos = { mapSize.x_ - INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//�E��ɐݒ�
					}
					else if (door.x == StageManager::DOOR_X::RIGHT)
					{
						pos = { INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//����ɐݒ�
					}
				}
				break;
			}
		}
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
		pPos.x_,pPos.y_,pos.x_,pos.y_);


}

