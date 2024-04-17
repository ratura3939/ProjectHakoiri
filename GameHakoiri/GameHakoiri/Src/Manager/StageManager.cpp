#include<DxLib.h>
#include"StageManager.h"

//�V���O���g����(�C���X�^���X�̏�����)
StageManager* StageManager::instance_ = nullptr;

//�R���X�g���N�^
//********************************************************
StageManager::StageManager(void)
{

}
//�f�X�g���N�^
//********************************************************
void StageManager::Destroy(void)
{
	delete instance_;
}

//������
//********************************************************
bool StageManager::Init(void)
{

	//�������������I�������̂�
	return true;
}
//�X�V
//********************************************************
void StageManager::Update(void)
{

}
//�`��
//********************************************************
void StageManager::Draw(void)
{

}
//���
//********************************************************
bool StageManager::Release(void)
{

	//�������������I�������̂�
	return true;
}
//�O������ÓI�C���X�^���X�𐶐�
//********************************************************
bool StageManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new StageManager();	//�C���X�^���X����
	}
	if (!instance_->Init())	//�������Ɏ��s������
	{
		OutputDebugString("�V�[���}�l�[�W�����������s");
		return false;
	}
	//�������������I�������̂�
	return true;
}
//�C���X�^���X�̎擾
//********************************************************
StageManager& StageManager::GetInstance(void)
{
	return *instance_;
}