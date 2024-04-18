#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/StageManager.h"
#include"../System/Pazzle.h"
#include"../System/Stealth.h"
#include"GameScene.h"


//�R���X�g���N�^
//********************************************************
GameScene::GameScene(void)
{

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
	if (!StageManager::CreateInstance())
	{
		return false;	//���������s�̂��߃V�X�e���I��
	}

	//����ɏ������s��ꂽ�̂�
	return true;
}
//�X�V
//********************************************************
void GameScene::Update(void)
{
	if (SceneManager::GetInstance().SpaceHit() == true)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::RESULT, true);
	}
}
//�`��
//********************************************************
void GameScene::Draw(void)
{
	StageManager::GetInstance().Draw();
	DrawString(0, 0, "GameScene", 0xffffff, true);
	//DrawBox(50, 50, 500, 500, 0x0000ff, true);
}
//���
//********************************************************
bool GameScene::Release(void)
{
	StageManager::GetInstance().Release();
	//����ɏ������s��ꂽ�̂�
	return true;
}