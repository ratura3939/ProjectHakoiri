#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"EndingScene.h"


//�R���X�g���N�^
//********************************************************
EndingScene::EndingScene(void)
{
}
//�f�X�g���N�^
//********************************************************
EndingScene::~EndingScene(void)
{

}
//������
//********************************************************
bool EndingScene::Init(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}
//�X�V
//********************************************************
void EndingScene::Update(void)
{
	if (SceneManager::GetInstance().SpaceHit() == true)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::TITLE , true);
	}
}
//�`��
//********************************************************
void EndingScene::Draw(void)
{
	DrawString(0, 0, "EndingScene", 0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xffffff, true);
}
//���
//********************************************************
bool EndingScene::Release(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}