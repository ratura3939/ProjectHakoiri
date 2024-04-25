#pragma once
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include"../Common/Vector2.h"

//StageBase�͊e�X�e�[�W�̏��u����Ƃ����F��

class RoomBase;

class StageBase
{
public:

	StageBase(void);	//�R���X�g���N�^
	virtual ~StageBase(void);	//�f�X�g���N�^

	virtual bool Init(void);	//������
	virtual void Update(void);	//�X�V
	virtual void PazzleDraw(void);	//�`��
	virtual bool Release(void);	//���


	virtual void SetParam(void);	//�������Ƃ̃p�����[�^�ݒ�
	void LoadPazzle(void);			//�Ֆʂ̓ǂݍ���
	void CreateKey(int y, int x);	//�A�z�z��̃L�[����
	Vector2 GetNowCursorPos(void);	//���݂̃J�[�\���̈ʒu���擾
	void SetCursor(int moveY, int moveX);	//�J�[�\���̃Z�b�g y��x�̓J�[�\���̈ړ���
	void SetPiece(int moveY, int moveX);	//��̈ʒu����ւ� y��x�̓J�[�\���̈ړ���

private:
	std::map<std::string, RoomBase*> roomMng_;	//�����̏��ꊇ�Ǘ�
	std::string roomKey_;	//�A�z�z��̃L�[


	std::vector<int>pzlX_;
	std::vector<std::vector<int>>pzlMap_;	//�p�Y���̒u������𐔎��ŊǗ�

protected:

	//�e�X�g�p
	//std::string testName_;
};