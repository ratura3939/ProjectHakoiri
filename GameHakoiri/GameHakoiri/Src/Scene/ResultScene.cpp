#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"ResultScene.h"


//�R���X�g���N�^
//********************************************************
ResultScene::ResultScene(void)
{

}
//�f�X�g���N�^
//********************************************************
ResultScene::~ResultScene(void)
{

}
//������
//********************************************************
bool ResultScene::Init(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}
//�X�V
//********************************************************
void ResultScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::ENDING, true);
	}
}
//�`��
//********************************************************
void ResultScene::Draw(void)
{
	DrawString(0, 0, "ResultScene", 0xffffff, true);
	DrawBox(50, 50, 500, 500, 0x00ffff, true);
}
//���
//********************************************************
bool ResultScene::Release(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}