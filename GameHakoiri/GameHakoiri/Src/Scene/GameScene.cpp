#include<DxLib.h>
#include<memory>
#include"../Manager/SceneManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/SoundManager.h"
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
	isPlate_ = false;
	str_ = "NONE";

	SoundManager::GetInstance().PlayBgmOfPazzle();
	//�}�j���A���̃Z�b�g
	SceneManager::GetInstance().SetManual(MODE::PAZZLE);

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

	if (!isPlate_)
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
					//�t���b�V���̒�~
					stage.SetFlash(false);

					//BGM
					SoundManager::GetInstance().StopBgmOfPazzle();
					SoundManager::GetInstance().PlayBgmOfStealth();

					//�X�e���X�V�[���̏�����
					SetMode(MODE::STEALTH);
					stl_->Init();
					Update();	//�����������̂���
					SceneManager::GetInstance().SetManual(MODE::STEALTH);
				}
				else
				{
					pzl_->ChangeIsFinish(false);
					str_ = "���̏�Ԃł̓N���A�ł��܂���B";
					isPlate_ = true;
				}
			}
			break;
		case GameScene::MODE::STEALTH:
			stl_->Update();
			auto& mng = SceneManager::GetInstance();
			if (stage.IsClear())	//�N���A���Ă���
			{
				mng.ClearStage(mng.GetStageNum() - 1);	//�t���O�Z�b�g
				if (mng.CheckAllClear())
				{
					SoundManager::GetInstance().StopBgmOfStealth();
					mng.ChangeScene(SceneManager::SCENEID::ENDING, true);	//�V�[���J��
				}
				else
				{
					SoundManager::GetInstance().StopBgmOfStealth();
					mng.ChangeScene(SceneManager::SCENEID::RESULT, true);	//�V�[���J��
				}
				return;
			}
			if (stl_->IsFailde())	//�N���A���Ă���
			{
				SoundManager::GetInstance().StopBgmOfStealth();
				mng.ChangeScene(SceneManager::SCENEID::RESULT, true);	//�V�[���J��
			}
			camera.Update();
			break;
		}
	}
	else
	{
		auto& plate = Plate::GetInstance();
		plate.Update(Plate::TYPE::CHECK);
		if (plate.IsFinish() && plate.GetAnswer() == Plate::ANSWER::OK)	isPlate_ = false;
	}
}
//�`��
//********************************************************
void GameScene::Draw(void)
{
	StageManager::GetInstance().Draw(GetMode());
	if (mode_ == MODE::STEALTH) { stl_->Draw(); }
	if (isPlate_) Plate::GetInstance().Draw(Plate::TYPE::CHECK, str_, false);
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
