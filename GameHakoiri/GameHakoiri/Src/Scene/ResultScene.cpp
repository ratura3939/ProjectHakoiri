#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/ResourceManager.h"
#include"../Application.h"
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
	auto& rsM = ResourceManager::GetInstance();
	backSelectImg_= rsM.Load(ResourceManager::SRC::BACK_SELECT_IMG).handleId_;
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
	DrawGraph(Application::SCREEN_SIZE_X / 4, Application::SCREEN_SIZE_Y - 256, backSelectImg_, true);
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
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}

void ResultScene::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}
