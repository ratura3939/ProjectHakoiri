#include<DxLib.h>
#include<math.h>

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
#include"../Object/Enemy/Oldman.h"
#include"Stealth.h"

//�R���X�g���N�^
//********************************************************
Stealth::Stealth(void)
{
	player_ = nullptr;
	enemyMng_[0] = nullptr;
	enemyMng_[1] = nullptr;
	enemyMng_[2] = nullptr;
	enemyMng_[3] = nullptr;
	enemyMng_[4] = nullptr;
	enemyMng_[5] = nullptr;

	isEnemyMove_ = false;
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
	
	isFailed_ = false;

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

	if (player_->GetHp() <= 0.0f)
	{
		isFailed_ = true;
	}
}
//�`��
//********************************************************
void Stealth::Draw(void)
{
	
	//StageManager::GetInstance().DrawObject();
	for (auto& e : useEnemy_)
	{
		e->Draw();
	}

	player_->Draw();

	//DrawDebug();

	if (player_->IsDrawMap())
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

bool Stealth::IsFailde(void)
{
	return isFailed_;
}



#pragma region �����蔻��

//�����蔻�葍��
void Stealth::Collision(void)
{
	//�����ړ��t���O���Z�b�g
	isMoveRoom_ = false;

	//�v���C���[
	//--------------------------------------------------------
	//to�}�b�v�`�b�v
	CollisionMapchip(player_,true);

	//�N���A���Ă��邩�����̈ړ����������Ȃ炱�̌�̓����蔻��͍s��Ȃ�
	if (StageManager::GetInstance().IsClear()||isMoveRoom_)
	{
    		return;
	}
	
	
	//�G
	//--------------------------------------------------------
	auto pPos = player_->GetPos();
	for (auto& e : useEnemy_)
	{
		//to�}�b�v�`�b�v
		CollisionMapchip(e, false);
		

		e->SetVisionState(EnemyBase::VISION_STATE::MISSING);
		//�G��player�𔭌��ł��Ă��Ȃ��Ƃ�
		if (!e->FindPlayer(pPos))
		{
			//�G���Փ˂��Ă���Ƃ�
			if (IsEnemyMove())
			{
				//�G�𓮂��I���̏�Ԃ�
				e->SetIsMove(false);
			}
		}
		else
		{
			auto ePos = e->GetPos();
			auto EtoP = pPos - ePos;
			auto PtoE = ePos - pPos;

			//�Ԃɂ�������I�u�W�F�N�g�����鎞
			if (CheckObjectPToE(pPos, e))
			{
				//�������Ă��Ȃ��̂ł��̎��̓������s��
				//�G���Փ˂��Ă���Ƃ�
				if (IsEnemyMove())
				{
					//�G�𓮂��I���̏�Ԃ�
					e->SetIsMove(false);
				}
			}
			else
			{
				e->SetVisionState(EnemyBase::VISION_STATE::FIND);
				player_->Damage();
			}
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
		if (type == StageManager::OBJECT::EVENT)
		{
			if (isPlayer)
			{
				CollisionEvent(mapPos);
			}
			else
			{
				CollisionObstacle(character);
			}
		}
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
	isMoveRoom_ = true;

	if (stage.IsClear())
	{
		return;	//�S�[�����Ă��珈�����f
	}

	if (!stage.IsMoveMap())		//�ړ��ł��Ȃ��Ƃ�
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

//�v���C���[�ƓG�Ƃ̊Ԃɒʂ蔲���s�ȃI�u�W�F�N�g�͂���̂�
bool Stealth::CheckObjectPToE(Vector2F pPos, EnemyBase* enemy)
{
	//�o�����̃x�N�g�����擾
	//���̂Q��xy�̕������t�Ȃ���
	auto ePos = enemy->GetPos();
	auto EtoP = pPos - ePos;
	auto PtoE = ePos - pPos;

	//�܂������Ղ���̂��������Ă��Ȃ��Ƃ��̏���
	//������̃I�u�W�F�N�g���擾�i�z��n�j
	auto pMapPos = StageManager::GetInstance().GetVector2MapPos(pPos.ToVector2());
	auto eMapPos = StageManager::GetInstance().GetVector2MapPos(ePos.ToVector2());
	auto obj = GetWithinFieldOfViewObject(pMapPos, eMapPos);

	std::vector<Vector2> RightObjectOfPlayer;
	std::vector<Utility::DIR> ObjectToPlayerDir;
	std::vector<Vector2> RightObjectOfEnemy;
	std::vector<Utility::DIR> ObjectToEnemyDir;

	//�S�ẴI�u�W�F�N�g�ƃL�����N�^�[�̈ʒu�֌W�𒲂ׂ�
	//���ʂƂ��ē���͓̂��ς��Ƃ��Đ��̕����ɂ�����̂���
	for (auto& o : obj)
	{
		//�I�u�W�F�N�g�ʒu��z��n������W�n��
		auto objWorldPos = o;
		objWorldPos.x *= StageManager::UNIT_STEALTH_SIZE_X;
		objWorldPos.y *= StageManager::UNIT_STEALTH_SIZE_Y;

		auto objPos = objWorldPos.ToVector2F();

		//�L�����N�^�[���猩�ĉE��O�̈ʒu�͉��������߂�
		//�}�b�v�`�b�v���猩�ēG��p�v���C���[���ǂ��ɂ��邩�𒲂ׂ�
		auto OtoP = pPos - objPos;
		auto OtoE = ePos - objPos;

		auto OtoPRad = atan2(OtoP.y, OtoP.x);
		auto OtoPDir = GetObjToCharacterDir(OtoPRad);

		auto OtoERad = atan2(OtoE.y, OtoE.x);
		auto OtoEDir = GetObjToCharacterDir(OtoERad);

		//�������猩�ă}�b�v�`�b�v�̉E��O�ɓ�������̂Ƃ̃x�N�g��
		auto PtoO = GetJudgementPos(objPos, OtoPDir) - pPos;
		auto EtoO = GetJudgementPos(objPos, OtoEDir) - ePos;

		//�O�όv�Z
		auto Pgaiseki = Utility::GetCrossProductF(PtoE, PtoO);
		auto Egaiseki = Utility::GetCrossProductF(EtoP, EtoO);	//�����炭����


		//��O�Ȃ����p

		Utility::DIR PspareDir = Utility::DIR::MAX;
		Utility::DIR EspareDir = Utility::DIR::MAX;

		PspareDir = CreateSpareLine(pPos, objWorldPos, OtoPDir);
		EspareDir = CreateSpareLine(ePos, objWorldPos, OtoEDir);

		if (PspareDir != Utility::DIR::MAX)
		{
			auto PtoO2 = GetJudgementPos(objWorldPos, PspareDir) - pPos;
			auto Pgaiseki2 = Utility::GetCrossProductF(PtoE, PtoO2);
			if (IsSameSign(Pgaiseki2, Egaiseki))
			{
				return true;
			}
		}
		if (EspareDir != Utility::DIR::MAX)
		{
			auto EtoO2 = GetJudgementPos(objWorldPos, EspareDir) - ePos;
			auto Egaiseki2 = Utility::GetCrossProductF(EtoP, EtoO2);
			if (IsSameSign(Pgaiseki, Egaiseki2))
			{
				return true;
			}
		}

		//���݂����������ɋ�`�����鎞
		if (IsSameSign(Pgaiseki, Egaiseki))
		{
			return true;
		}
	}
	
	return false;
}


//�����̈����͂��ꂼ��̈ʒu���}�b�v�z��ɕϊ���������
std::vector<Vector2> Stealth::GetWithinFieldOfViewObject(Vector2 pMapPos, Vector2 eMapPos)	
{
	//�����̍��W�𒸓_�Ɋ܂ނS�p�`�𐧍�
	// ���̂S�p�`�͈̔͂ɂ���I�u�W�F�N�g�𐸍�����
	//�S�p�`�̎n�_�i����j�ƏI�_�i�E���j�𐧍�
	//���̒��g�͔z��̔ԍ��Ƃ���
	Vector2 stPos = { 0,0 };
	Vector2 edPos = { 0,0 };

	//�v���C���[���G��荶���ɂ���Ƃ�
	if (pMapPos.x < eMapPos.x)
	{
		//�n�_��X���W�ɂ̓v���C���[��X���W��
		stPos.x = pMapPos.x;
		edPos.x = eMapPos.x;
	}
	else
	{
		//�n�_��X���W�ɂ͓G��X���W��
		stPos.x = eMapPos.x;
		edPos.x = pMapPos.x;
	}

	//�v���C���[���G����ɂ���Ƃ�
	if (pMapPos.y < eMapPos.y)
	{
		//�n�_��Y���W�ɂ̓v���C���[��Y���W��
		stPos.y = pMapPos.y;
		edPos.y = eMapPos.y;
	}
	else
	{
		//�n�_��Y���W�ɂ͓G��Y���W��
		stPos.y = eMapPos.y;
		edPos.y = pMapPos.y;
	}


	//�X�e�[�W�}�l�[�W���擾
	auto& stage = StageManager::GetInstance();

	//�n�_����I�_�܂ł̋�`�̒��łǂ��ɃI�u�W�F�N�g�����邩�𒲂ׂ�
	//�I�u�W�F�N�g�̈ʒu�S�̕ۑ��p
	std::vector<Vector2> objectPos;
	//�ʕۑ��ifor��)�p
	Vector2 obPos;

	//�n�_����I�_�܂ł�for��
	for (int y = stPos.y; y <= edPos.y; y++)
	{
		for (int x = stPos.x; x <= edPos.x; x++)
		{
			obPos = { x,y };
			//�ʂ蔲���s�Ȃ��̂��L�^���Ă���
			if (stage.GetObjectType(obPos) == StageManager::OBJECT::OBSTACLE)
			{
				objectPos.push_back(obPos);
			}
			else if (stage.GetObjectType(obPos) == StageManager::OBJECT::THROUGH)
			{
				if (stage.IsBottomObject(obPos))
				{
					objectPos.push_back(obPos);
				}
			}
		}
	}

	return objectPos;
}
//�p�x�ɉ����ăL�����N�^�[���ǂ̕����ɂ��邩�����蓖�Ă�
Utility::DIR Stealth::GetObjToCharacterDir(double rad)
{
	Utility::DIR ret = Utility::DIR::MAX;
	
	auto deg = Utility::Rad2DegF(static_cast<float>(rad));
	// 0�x�`360�x�ȓ��Ɋp�x�������߂�
	deg = static_cast<float>(Utility::DegIn360(deg));

	//�p�x�ɉ����ăL�����N�^�[���ǂ̕����ɂ��邩�����蓖�Ă�
	if (deg<=UNIT_DEG || deg> UNIT_DEG + (NOMAL_DEG * 3))
	{
		ret = Utility::DIR::RIGHT;
	}
	else if (deg > UNIT_DEG && deg <= UNIT_DEG + NOMAL_DEG)
	{
		ret = Utility::DIR::DOWN;
	}
	else if (deg > UNIT_DEG + NOMAL_DEG && deg <= UNIT_DEG + (NOMAL_DEG*2))
	{
		ret = Utility::DIR::LEFT;
	}
	else if (deg > UNIT_DEG + (NOMAL_DEG * 2) && deg <= UNIT_DEG + (NOMAL_DEG * 3))
	{
		ret = Utility::DIR::UP;
	}

	return ret;
}

//�I�u�W�F�N�g�̂ǂ��̓_�Ɣ��肷�邩�����߂�
Vector2F Stealth::GetJudgementPos(Vector2F pos, Utility::DIR dir)
{
	auto objPos = pos;

	switch (dir)
	{
	case Utility::DIR::UP:
		objPos += 
			Vector2F{ -StageManager::UNIT_STEALTH_SIZE_X / 2,-StageManager::UNIT_STEALTH_SIZE_Y / 2 };
		break;
	case Utility::DIR::RIGHT:
		objPos +=
			Vector2F{ StageManager::UNIT_STEALTH_SIZE_X / 2,-StageManager::UNIT_STEALTH_SIZE_Y / 2 };
		break;
	case Utility::DIR::DOWN:
		objPos +=
			Vector2F{ StageManager::UNIT_STEALTH_SIZE_X / 2,StageManager::UNIT_STEALTH_SIZE_Y / 2 };
		break;
	case Utility::DIR::LEFT:
		objPos +=
			Vector2F{ -StageManager::UNIT_STEALTH_SIZE_X / 2,StageManager::UNIT_STEALTH_SIZE_Y / 2 };
		break;
	case Utility::DIR::MAX:
		OutputDebugString("�������ݒ肳��Ă��܂���\n");
		break;
	default:
		break;
	}

	return objPos;
}

//�����蔻��\���̐�
Utility::DIR Stealth::CreateSpareLine(Vector2F charaPos, Vector2 obj, Utility::DIR dir)
{
	Utility::DIR ret = Utility::DIR::MAX;

	//��O���Ȃ������߂̓G���ɓ�{�ڂ̃x�N�g���𐧍�
	if (charaPos.x < obj.x - (StageManager::UNIT_STEALTH_SIZE_X / 2))
	{
		if (dir != Utility::DIR::LEFT)
		{
			ret = Utility::DIR::LEFT;
		}
		else
		{
			if (charaPos.y < obj.y - (StageManager::UNIT_STEALTH_SIZE_Y / 2))
			{
				ret = Utility::DIR::UP;
			}
			else if (charaPos.y > obj.y + (StageManager::UNIT_STEALTH_SIZE_Y / 2))
			{
				ret = Utility::DIR::DOWN;
			}
		}
	}
	if (charaPos.x > obj.x + (StageManager::UNIT_STEALTH_SIZE_X / 2))
	{
		if (dir != Utility::DIR::RIGHT)
		{
			ret = Utility::DIR::RIGHT;
		}
		else
		{
			if (charaPos.y < obj.y - (StageManager::UNIT_STEALTH_SIZE_Y / 2))
			{
				ret = Utility::DIR::UP;
			}
			else if (charaPos.y > obj.y + (StageManager::UNIT_STEALTH_SIZE_Y / 2))
			{
				ret = Utility::DIR::DOWN;
			}
		}
	}

	return ret;
}

void Stealth::ChangeRoom(void/*�����ꂩ�͓��������̎w�萔�������*/)
{

	//�J�����Ƀ}�b�v�̃T�C�Y��ݒ�
	auto& camera = Camera::GetInstance();
	camera.SetMapSize(StageManager::GetInstance().GetMapMaxSize());
}

bool Stealth::IsSameSign(float v1, float v2) const
{
	if (v1 >= 0.0f)
	{
		if (v2 >= 0.0f)
		{
			return true;
		}
	}
	else
	{
		if (v2 < 0.0f)
		{
			return true;
		}
	}
	return false;
}

bool Stealth::IsStraght(Vector2F v1, Vector2F v2) const
{
	if (fabsf(v1.x) == fabs(v2.x) && fabs(v1.y) == fabs(v2.y))
	{
		return true;
	}
	return false;
}

void Stealth::DrawDebug(void)
{
	auto pos = player_->GetCollisionPos();
	auto pPos = player_->GetPos();
	auto pMapPos = StageManager::GetInstance().GetVector2MapPos(pPos.ToVector2());
	auto hp = player_->GetHp();
	

	DrawFormatString(0, 0, 0xff0000,
		"player�̍��W��(%.1f,%.1f)\nplayer�̓����蔻�聁(%.1f,%.1f)\nplayer�̈ʒu���o%d,%d}\nHP=%.1f",
		pPos.x,pPos.y,pos.x,pos.y,pMapPos.x,pMapPos.y,hp);


}

void Stealth::EnemyInit(void)
{
	for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)
	{
		//�G��6�̂�����
		if (i < OBLONG_ENEMY_NUM)
		{
			enemyMng_[i] = new Housemaid;
		}
		else if (i < OBLONG_ENEMY_NUM * 2)
		{
			enemyMng_[i] = new Seneschal;
		}
		else
		{
			enemyMng_[i] = new Oldman;
		}
		enemyMng_[i]->Init();
	}

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][0] = { NX1,NY1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][1] = { NX2,NY2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][2] = { NX1,NY1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][3] = { NX2,NY2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][4] = { NX1,NY1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][5] = { NX2,NY2 };

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][0] = { OBX1,OBY1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][1] = { OBX2,OBY2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][2] = { OBX3,OBY3 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][3] = { OBX4,OBY4 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][4] = { OBX5,OBY5 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][5] = { OBX6,OBY6 };

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][0] = { OB2X1,OB2Y1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][1] = { OB2X2,OB2Y2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][2] = { OB2X3,OB2Y3 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][3] = { OB2X4,OB2Y4 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][4] = { OB2X5,OB2Y5 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][5] = { OB2X6,OB2Y6 };
}

void Stealth::CreateEnemy(void)
{
	int rnd = 0;
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
	memorizeType_[key].clear();

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

