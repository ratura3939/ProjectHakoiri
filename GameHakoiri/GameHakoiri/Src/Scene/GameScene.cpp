#include<DxLib.h>
#include<memory>
#include"../Manager/SceneManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/Camera.h"
#include"../System/Pazzle.h"
#include"../System/Stealth.h"
#include"../System/Plate.h"
#include"GameScene.h"


//�R���X�g���N�^
//********************************************************
GameScene::GameScene(void)
{
	pzl_ = nullptr;
	stl_ = nullptr;
}
//�f�X�g���N�^
//********************************************************
GameScene::~GameScene(void)
{
	
}
//������
//********************************************************
bool GameScene::Init(void)
{
	//�C���X�^���X�̐���
	if (!StageManager::CreateInstance(static_cast<StageManager::STAGENUM>(SceneManager::GetInstance().GetStageNum())))
	{
		return false;	//���������s�̂��߃V�X�e���I��
	}
	SetMode(MODE::PAZZLE);
	pzl_ = new Pazzle;
	stl_ = new Stealth;
	isCheck_ = false;
	str_ = "NONE";

	//����ɏ������s��ꂽ�̂�
	return true;
}
//�X�V
//********************************************************
void GameScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	auto& camera = SceneManager::GetInstance().GetCamera();
	auto& stage = StageManager::GetInstance();

	stage.Update(GetMode());

	if (!isCheck_)
	{
		switch (mode_)
		{
		case GameScene::MODE::PAZZLE:
			pzl_->Update();
			if (pzl_->IsFinish())	//�p�Y���I��������
			{
				//�N���A�\�Ȃ�
				if (stage.CanGoal())
				{
					//�X�e���X�V�[���̏�����
					SetMode(MODE::STEALTH);
					stl_->Init();
					Update();	//�����������̂���
				}
				else
				{
					pzl_->ChangeIsFinish(false);
					str_ = "���̏�Ԃł̓N���A�ł��܂���B";
					isCheck_ = true;
				}
			}
			break;
		case GameScene::MODE::STEALTH:
			stl_->Update();
			if (stage.IsClear())	//�N���A���Ă���
			{
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::RESULT, true);	//�V�[���J��
			}
			if (stl_->IsFailde())	//�N���A���Ă���
			{
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::RESULT, true);	//�V�[���J��
			}
			camera.Update();
			break;
		}
	}
	else
	{
		auto& plate = Plate::GetInstance();
		plate.Update(Plate::TYPE::CHECK);
		if (plate.IsFinish() && plate.GetAnswer() == Plate::ANSWER::OK)	isCheck_ = false;
	}

}
//�`��
//********************************************************
void GameScene::Draw(void)
{
	StageManager::GetInstance().Draw(GetMode());
	if (mode_ == MODE::STEALTH) { stl_->Draw(); }
	if (isCheck_) Plate::GetInstance().Draw(Plate::TYPE::CHECK, str_);

	DrawString(0, 0, "GameScene", 0xffffff, true);
}
//���
//********************************************************
bool GameScene::Release(void)
{
	StageManager::GetInstance().Release();
	delete pzl_;
	pzl_ = nullptr;
	stl_->Release();
	delete stl_;
	stl_ = nullptr;

	//����ɏ������s��ꂽ�̂�
	return true;
}


void GameScene::SetMode(MODE mode)
{
	mode_ = mode;
}

GameScene::MODE GameScene::GetMode(void)
{
	return mode_;
}
