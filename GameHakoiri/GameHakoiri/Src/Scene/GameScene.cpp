#include<DxLib.h>
#include"../Manager/SceneManager.h"
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
	DrawString(0, 0, "GameScene", 0xffffff, true);
	DrawBox(50, 50, 500, 500, 0x0000ff, true);
}
//���
//********************************************************
bool GameScene::Release(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}