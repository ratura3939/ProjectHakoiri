#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/InputManager.h"
#include"../System/Pazzle.h"
#include"../System/Stealth.h"
#include"GameScene.h"


//�R���X�g���N�^
//********************************************************
GameScene::GameScene(void)
{
	mode_ = MODE::PAZZLE;
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

	mode_ = MODE::PAZZLE;
	pzl_ = new Pazzle;

	//����ɏ������s��ꂽ�̂�
	return true;
}
//�X�V
//********************************************************
void GameScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_W))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::RESULT, true);
	}


	switch (mode_)
	{
	case GameScene::MODE::PAZZLE:
		pzl_->Update();
		break;
	case GameScene::MODE::STEALTH:

		break;
	}

}
//�`��
//********************************************************
void GameScene::Draw(void)
{
	StageManager::GetInstance().Draw();
	DrawString(0, 0, "GameScene", 0xffffff, true);
	DrawFormatString(0, 100, 0xffffff, "%d", pzl_->IsNeutral(), true);
}
//���
//********************************************************
bool GameScene::Release(void)
{
	StageManager::GetInstance().Release();
	delete pzl_;
	pzl_ = nullptr;
	delete stl_;
	stl_ = nullptr;

	//����ɏ������s��ꂽ�̂�
	return true;
}