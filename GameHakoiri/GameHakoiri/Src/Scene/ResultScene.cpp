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
	auto cnt = SceneManager::GetInstance().GetController();

	switch (cnt)
	{
	case SceneManager::CONTROLLER::KEYBOARD:
		KeyboardContoroller();
		break;
	case SceneManager::CONTROLLER::PAD:
		GamePadController();
		break;
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

void ResultScene::KeyboardContoroller(void)
{
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::ENDING, true);
	}
}

void ResultScene::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::ENDING, true);
	}
}
