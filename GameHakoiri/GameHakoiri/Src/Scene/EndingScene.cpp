#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
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
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
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