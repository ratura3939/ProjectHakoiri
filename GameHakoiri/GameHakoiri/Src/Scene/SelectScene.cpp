#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/ResourceManager.h"
#include"../Manager/SoundManager.h"
#include"../Utility/Utility.h"
#include"../Application.h"
#include"../System/Plate.h"
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
	prevStick_ = {0,0};
	selectNum_ = 0;
	selectBack_ = false;

	ResetRot();

	stageNumImg_[0]= ResourceManager::GetInstance().Load(ResourceManager::SRC::STAGE_1_IMG).handleId_;
	stageNumImg_[1]= ResourceManager::GetInstance().Load(ResourceManager::SRC::STAGE_2_IMG).handleId_;
	stageNumImg_[2]= ResourceManager::GetInstance().Load(ResourceManager::SRC::STAGE_3_IMG).handleId_;

	checkImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::CHECK_IMG).handleId_;
	backTitleImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::BACK_TITLE_IMG).handleId_;

	frame_[0] = ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_IMG).handleId_;
	frame_[1] = ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_2_IMG).handleId_;

	stageNumPos_[0] = { Application::SCREEN_SIZE_X / 4,Application::SCREEN_SIZE_Y / 4 };
	stageNumPos_[1] = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 4 };
	stageNumPos_[2] = { Application::SCREEN_SIZE_X / 4 + Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 4 };


	SoundManager::GetInstance().PlayBgmOfSelect();

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

	if (rotDecre_)
	{
		stageNumRot_[selectNum_] -= ROT_UNIT;
		if (stageNumRot_[selectNum_] < ROT_MIN)rotDecre_ = false;
	}
	else
	{
		stageNumRot_[selectNum_] += ROT_UNIT;
		if (stageNumRot_[selectNum_] > ROT_MAX)rotDecre_ = true;
	}
}
//�`��
//********************************************************
void SelectScene::Draw(void)
{

	auto& stg = SceneManager::GetInstance();

	//�X�e�[�W�i���o�[�̕`��
	for (int i = 0; i < STAGE_NUM; i++)
	{
		DrawRotaGraph(stageNumPos_[i].x, stageNumPos_[i].y,
			1.0f, stageNumRot_[i] * Utility::DEG2RAD,
			stageNumImg_[i], true, false);
		if (stg.IsClearStage(i))
		{
			DrawRotaGraph(stageNumPos_[i].x, stageNumPos_[i].y,
				1.0f, 0.0f * Utility::DEG2RAD,
				checkImg_, true, false);
		}
	}

	//�^�C�g���ɖ߂�̕`��
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y - BACK_TITLE_Y / 2,
		1.0f, 0.0f * Utility::DEG2RAD,
		backTitleImg_, true, false);

	//�t���[���̕`��
	if (selectBack_)	//�^�C�g���ɖ߂�ɃJ�[�\���������Ă�����
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y - BACK_TITLE_Y / 2,
			4.0f, 0.0f * Utility::DEG2RAD,
			frame_[1], true, false);
	}
	else
	{
		DrawRotaGraph(stageNumPos_[selectNum_].x, stageNumPos_[selectNum_].y,
			4.0f, stageNumRot_[selectNum_] * Utility::DEG2RAD,
			frame_[0], true, false);
	}
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

	auto prevSelect = selectNum_;
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		if (!selectBack_)
		{
			SoundManager::GetInstance().StopBgmOfSelect();
			//�X�e�[�W�i���o�[���󂯓n���V�[���؂�ւ�
			SceneManager::GetInstance().SetStageNum(selectNum_ + 1);
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::GAME, true);
		}
		else
		{
			SoundManager::GetInstance().StopBgmOfSelect();
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::TITLE, true);
		}
	}
	//���E�ړ�
	if (ins.IsTrgDown(KEY_INPUT_RIGHT))
	{
		selectNum_++;
		if (selectNum_ >= STAGE_NUM)selectNum_ = STAGE_NUM - 1;
	}
	if (ins.IsTrgDown(KEY_INPUT_LEFT))
	{
		selectNum_--;
		if (selectNum_ < 0)selectNum_ = 0;
	}
	if (prevSelect != selectNum_)ResetRot();
	//�����ɂ���ĉ��i�ɂ��邩��i�ɂ��邩��ݒ�
	if (ins.IsTrgDown(KEY_INPUT_DOWN))selectBack_ = true;
	if (ins.IsTrgDown(KEY_INPUT_UP))selectBack_ = false;
}

void SelectScene::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		if (!selectBack_)
		{
			SoundManager::GetInstance().StopBgmOfSelect();
			//�X�e�[�W�i���o�[���󂯓n���V�[���؂�ւ�
			SceneManager::GetInstance().SetStageNum(selectNum_ + 1);
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::GAME, true);
		}
		else
		{
			SoundManager::GetInstance().StopBgmOfSelect();
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::TITLE, true);
		}
	}

	// ���X�e�B�b�N�̉���
	auto leftStickX = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
	// ���X�e�B�b�N�̏c��
	auto leftStickY = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;

	auto prevSelect = selectNum_;
	//���E�ړ�
	if (prevStick_.x == 0)
	{
		if (leftStickX > 0)
		{
			selectNum_++;
			if (selectNum_ >= STAGE_NUM)selectNum_ = STAGE_NUM - 1;
		}
		else if (leftStickX < 0)
		{
			selectNum_--;
			if (selectNum_ < 0)selectNum_ = 0;
		}
		if (prevSelect != selectNum_)ResetRot();
	}
	//Y���ړ�
	if (prevStick_.y == 0)
	{
		//�����ɂ���ĉ��i�ɂ��邩��i�ɂ��邩��ݒ�
		if (leftStickY > 0)selectBack_ = true;
		else if (leftStickY < 0)selectBack_ = false;
	}

	prevStick_ = { leftStickX ,leftStickY };
}

void SelectScene::SetSelectBack(const bool flag)
{
	selectBack_ = flag;
}

void SelectScene::ResetRot(void)
{
	stageNumRot_[0] = 0.0f;
	stageNumRot_[1] = 0.0f;
	stageNumRot_[2] = 0.0f;
	rotDecre_ = false;
}
