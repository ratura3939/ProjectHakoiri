#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"SelectScene.h"


//�R���X�g���N�^
//********************************************************
SelectScene::SelectScene(void)
{
	selectNum_ = 0;
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
	selectNum_ = 1;
	//����ɏ������s��ꂽ�̂�
	return true;
}
//�X�V
//********************************************************
void SelectScene::Update(void)
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

void SelectScene::KeyboardContoroller(void)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		//�X�e�[�W�i���o�[���󂯓n���V�[���؂�ւ�
		SceneManager::GetInstance().SetStageNum(selectNum_);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::GAME, true);
	}
}

void SelectScene::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		//�X�e�[�W�i���o�[���󂯓n���V�[���؂�ւ�
		SceneManager::GetInstance().SetStageNum(selectNum_);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::GAME, true);
	}
}
