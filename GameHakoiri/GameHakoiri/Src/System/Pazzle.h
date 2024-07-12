//#pragma once
#include<memory>

class GameScene;
class StageManager;

class Pazzle
{
public:
	Pazzle(void);	//�R���X�g���N�^
	~Pazzle(void);	//�f�X�g���N�^

	void Update(void);	//�X�V

	
	bool IsSelect(void);	//IsSelect�̎擾
	bool IsNeutral(void);	//IsSelect�̎擾
	bool IsFinish(void);
	void ChangeIsFinish(bool flag);	//IsNeutral�̕ύX

private:
	bool isFinish_;		//�p�Y���������������ǂ���
	bool isSelect_;		//�I�𒆂��ǂ���
	bool isNeutral_;	//�X�e�B�b�N���j���[�g������Ԃ�
	Vector2 neutralStick_;	//�X�e�B�b�N�̃j���[�g������Ԃ�����
	

	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���

	void ChangeIsSelect(bool flag);	//IsSelect�̕ύX
	void ChangeIsNeutral(bool flag);	//IsNeutral�̕ύX
	bool IsStickNeutral(Vector2 stick);	//�X�e�B�b�N�̃j���[�g������Ԃ�
	Utility::DIR MoveStick(Vector2 stick);	//�ǂ̕����ɃX�e�B�b�N������������ԋp
};

