#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/ResourceManager.h"
#include"../Application.h"
#include"../Utility/Utility.h"
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
	auto& rsM = ResourceManager::GetInstance();

	endImg_= rsM.Load(ResourceManager::SRC::THANK_IMG).handleId_;
	backTitleImg_ = rsM.Load(ResourceManager::SRC::BACK_TITLE_IMG).handleId_;

	endEx_ = EX_S;
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

	endEx_ += 0.01f;
	if (endEx_ > EX_F)endEx_ = EX_S;
}
//�`��
//********************************************************
void EndingScene::Draw(void)
{
	DrawString(0, 0, "EndingScene", 0xffffff, true);

	//TahnkyouForPlaying�̕`��
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2 - THANK_SIZE / 2, Application::SCREEN_SIZE_Y / 2 - THANK_SIZE / 2,
		endEx_, 0.0f * Utility::DEG2RAD,
		endImg_, true, false);

	//�^�C�g���ɖ߂�̕`��
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y - BACK_TITLE_Y / 2,
		1.0f, 0.0f * Utility::DEG2RAD,
		backTitleImg_, true, false);
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
