#include<Windows.h>
#include<DxLib.h>
#include"../Utility/Utility.h"
#include"../Application.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include"../Manager/ResourceManager.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase(void)
{
	moveDir_ = Utility::VECTOR_ZERO;
	isMove_ = false;
	moveStartPos_ = { 0.0f,0.0f };
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::Init(void)
{
	CharacterBase::Init();
	moveLimit_ = move_ * MOVE_UNIT;
	visionImg_[static_cast<int>(VISION_STATE::FIND)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::VISION_FIND_IMG).handleId_;

	visionImg_[static_cast<int>(VISION_STATE::MISSING)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::VISION_MISSING_IMG).handleId_;

	state_ = VISION_STATE::MISSING;
}

void EnemyBase::SetParam(void)
{
}

void EnemyBase::Draw(void)
{
	auto cameraPos = SceneManager::GetInstance().GetCamera().GetPos();
	
	//���E�̕`��
	//�~�ʏ�������
	DrawVision(cameraPos);

	//�O�p�`�i���j


	DrawRotaGraph(pos_.x - cameraPos.x,
		pos_.y - cameraPos.y,
		1.0f,
		Application::SIE * 180.0,
		img_[animIdx_],
		true,
		false);
	
}

//�ړ�����
void EnemyBase::Move(void)
{
	//�����ĂȂ��Ƃ���������
	if (!isMove_) { DecideDir(); }
	//�����Ă����Ԃ�
	SetIsMove(true);

	pos_ += Vector2F{ moveDir_.x * speed_,moveDir_.y * speed_ };

	auto diff = Utility::Distance(pos_.ToVector2(), moveStartPos_.ToVector2());

	if (static_cast<int>(diff) > moveLimit_) { SetIsMove(false); }
}

//������������
void EnemyBase::DecideDir(void)
{
	//�X�^�[�g�|�W�V�����ݒ�
	moveStartPos_ = pos_;

	//��������
	dir_ = static_cast<DIR>(rand() % static_cast<int>(DIR::MAX));
	ResetAnim(dir_);

	auto moveDir = Utility::VECTOR_ZERO;
	//���������ɉ������P�ʃx�N�g���Ɖ�]�̊p�x�̎w��
	int rot = ROT_UNIT;
	switch (dir_)
	{
	case DIR::BOTTOM:
		moveDir = { 0.0f,1.0f,0.0f };
		rot *= ROT_BTM;
		break;
	case DIR::LEFT:
		moveDir = { -1.0f,0.0f,0.0f };
		rot *= ROT_LFT;
		break;
	case DIR::RIGHT:
		moveDir = { 1.0f,0.0f,0.0f };
		rot *= ROT_RGH;
		break;
	case DIR::TOP:
		moveDir = { 0.0f,-1.0f,0.0f };
		rot *= ROT_TOP;
		break;
	case DIR::BOTTOM_LEFT:
		moveDir = { -1.0f,1.0f,0.0f };
		rot *= ROT_BTM_LFT;
		break;
	case DIR::BOTTOM_RIGHT:
		moveDir = { 1.0f,1.0f,0.0f };
		rot *= ROT_BTM_RGH;
		break;
	case DIR::TOP_LEFT:
		moveDir = { -1.0f,-1.0f,0.0f };
		rot *= ROT_TOP_LFT;
		break;
	case DIR::TOP_RIGHT:
		moveDir = { 1.0f,-1.0f,0.0f };
		rot *= ROT_TOP_RGH;
		break;
	}

	//�P�ʍs��
	MATRIX mat = MGetIdent();
	//�ړ������̉�]
	moveDir_ = VTransform(moveDir, mat);

	visionRot_ = static_cast<double>(rot);
}

//���E�̕`��
void EnemyBase::DrawVision(Vector2F cameraPos)
{
	//���E
	auto pos = GetCollisionPos();


	DrawRotaGraph3(pos.x - cameraPos.x,
		pos.y - cameraPos.y,
		VISION_SIZE_X / 2,
		VISION_SIZE_Y,
		1.0f,
		1.0f,
		visionRot_ * Application::SIE / 180.0,
		visionImg_[static_cast<int>(state_)],
		true,
		false,
		false);
}


void EnemyBase::SetIsMove(bool flag)
{
	isMove_ = flag;
}

void EnemyBase::SetVisionState(VISION_STATE state)
{
	state_ = state;
}


void EnemyBase::SetIsUse(bool flag)
{
	isUse_ = flag;
}

bool EnemyBase::IsUse(void)
{
	return isUse_;
}

EnemyBase::TYPE EnemyBase::GetType(void)
{
	return type_;
}