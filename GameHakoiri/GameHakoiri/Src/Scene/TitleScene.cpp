#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"TitleScene.h"


//�R���X�g���N�^
//********************************************************
TitleScene::TitleScene(void)
{
}
//�f�X�g���N�^
//********************************************************
TitleScene::~TitleScene(void)
{

}
//������
//********************************************************
bool TitleScene::Init(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}
//�X�V
//********************************************************
void TitleScene::Update(void)
{
	KeyboardContoroller();
	GamePadController();
}
//�`��
//********************************************************
void TitleScene::Draw(void)
{
	DrawString(0, 0, "TitleScene",0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xffff00, true);
}
//���
//********************************************************
bool TitleScene::Release(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}

void TitleScene::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::KEYBOARD);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}

void TitleScene::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::PAD);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}
