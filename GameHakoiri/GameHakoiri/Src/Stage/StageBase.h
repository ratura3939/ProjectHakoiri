#pragma once
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include"../Common/Vector2.h"
#include"../Utility/Utility.h"
#include"Room/RoomBase.h"

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

	void LoadPazzle(void);			//�Ֆʂ̓ǂݍ���
	void CreateKey(int y, int x);	//�A�z�z��̃L�[����
	Vector2 GetNowCursorPos(void);	//���݂̃J�[�\���̈ʒu���擾
	void SetCursor(Vector2 move, Utility::DIR dir);	//�J�[�\���̃Z�b�g y��x�̓J�[�\���̈ړ���
	void SetPiece(Vector2 move, Utility::DIR dir);	//��̈ʒu����ւ� y��x�̓J�[�\���̈ړ���

private:
	std::map<std::string, RoomBase*> roomMng_;	//�����̏��ꊇ�Ǘ�
	std::string roomKey_;	//�A�z�z��̃L�[


	std::vector<std::vector<int>>pzlMap_;	//�p�Y���̒u������𐔎��ŊǗ�
	std::vector<int>pzlX_;
	std::map<std::string, Vector2F>pzlPos_;	//��̕`��ʒu�Ǘ�

	int frame_;
	int frameImg_;
	int frameObImg_;
	int frameOb2Img_;
	
	void MovePiece(const Vector2 csr,
		const std::string bfr, const std::string aft);	//���ۂ̈ړ������@�ړ���̃J�[�\���A�ړ��O��Key�A�ړ����Key

	//����n
	bool CheckInstanceUp(int y, int x, RoomBase* r);	//�����`�̂Q�R�}�ڂ��𔻒f����уC���X�^���X�̐���
	bool CheckInstanceLeft(int y, int x, RoomBase* r);
	bool IsOblong(std::string key);	//������ꏊ�������`��
	bool IsOblong(RoomBase::TYPE type);	//������ꏊ�������`��

	//Get&Set
	RoomBase* GetSecondRoomInstance(RoomBase* r);		//�����`�Q�R�}�ڂ̃C���X�^���X�̐���

	void DrawCursor(void);	//�J�[�\���̕`��

protected:

	virtual void SetParam(void);	//�������Ƃ̃p�����[�^�ݒ�

	//�e�X�g�p
	//std::string testName_;
};