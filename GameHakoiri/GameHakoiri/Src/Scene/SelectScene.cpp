#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"SelectScene.h"


//�R���X�g���N�^
//********************************************************
SelectScene::SelectScene(void)
{

}
//�f�X�g���N�^
//********************************************************
SelectScene::~SelectScene(void)
{

}
//������
//********************************************************
bool SelectScene::Init(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}
//�X�V
//********************************************************
void SelectScene::Update(void)
{
	if (SceneManager::GetInstance().SpaceHit() == true)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::GAME, true);
	}
}
//�`��
//********************************************************
void SelectScene::Draw(void)
{
	DrawString(0, 0, "SelectScene", 0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xff00ff, true);
}
//���
//********************************************************
bool SelectScene::Release(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}