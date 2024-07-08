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

void EndingScene::KeyboardContoroller(void)
{
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::TITLE, true);
	}
}

void EndingScene::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::TITLE, true);
	}
}
