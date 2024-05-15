#pragma once
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include"../Common/Vector2.h"
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"
#include"Room/RoomBase.h"

//StageBase�͊e�X�e�[�W�̏��u����Ƃ����F��

class RoomBase;

class StageBase
{
public:

	enum class CURSOR
	{
		NORMAL,
		OBLONG,
		OBLONG_2,
		MAX
	};

	static constexpr int FRAME_INTERVAL = 15;

	StageBase(void);	//�R���X�g���N�^
	virtual ~StageBase(void);	//�f�X�g���N�^

	virtual bool Init(void);	//������
	virtual void Update(GameScene::MODE mode);	//�X�V
	virtual void Draw(GameScene::MODE mode);	//�`��
	virtual bool Release(void);	//���

	void LoadPazzle(void);			//�Ֆʂ̓ǂݍ���
	void CreateKey(int y, int x);	//�A�z�z��̃L�[����
	Vector2 GetNowCursorPos(void);	//���݂̃J�[�\���̈ʒu���擾
	void SetCursor(Vector2 move, Utility::DIR dir);	//�J�[�\���̃Z�b�g y��x�̓J�[�\���̈ړ���
	void SetPiece(Vector2 move, Utility::DIR dir);	//��̈ʒu����ւ� y��x�̓J�[�\���̈ړ���
	void SetFrameFlash(bool flag);	//�g�_�ŗp

	void ResetPazzl(void);	//�p�Y���̃��Z�b�g

private:
	std::map<std::string, RoomBase*> roomMng_;	//�����̏��ꊇ�Ǘ�
	std::map<std::string, RoomBase::TYPE> resetRoom_;//�����̃��Z�b�g�p
	std::string roomKey_;	//�A�z�z��̃L�[


	std::vector<std::vector<int>>pzlMap_;	//�p�Y���̒u������𐔎��ŊǗ�
	std::vector<int>pzlX_;
	std::map<std::string, Vector2F>pzlPos_;	//��̕`��ʒu�Ǘ�

	CURSOR type_;
	int frame_[static_cast<int>(CURSOR::MAX)];
	bool frameFlash_;
	int frameAnim_;
	
	bool MovePiece(const Vector2 csr,
		const std::string bfr, const std::string aft);	//���ۂ̈ړ������@�ړ���̃J�[�\���A�ړ��O��Key�A�ړ����Key

	//����n
	bool CheckInstanceUp(int y, int x, RoomBase* r);	//�����`�̂Q�R�}�ڂ��𔻒f����уC���X�^���X�̐���
	bool CheckInstanceLeft(int y, int x, RoomBase* r);
	bool IsOblong(std::string key);	//������ꏊ�������`��
	bool IsOblong(RoomBase::TYPE type);	//������ꏊ�������`��
	bool IsDontMoveBlock(std::string key);	//�ړ��s�ȃu���b�N���ǂ���

	//Get&Set
	RoomBase* GetSecondRoomInstance(RoomBase* r);		//�����`�Q�R�}�ڂ̃C���X�^���X�̐���
	void SetCursorType(CURSOR type);
	
	//�X�V
	void UpdateStealth(void);

	//�`��
	void DrawPazzle(void);	//�p�Y��
	void DrawCursor(void);	//�J�[�\��
	void DrawStealth(void);	//�X�e���X

	void LoadImgs(void);

protected:
	//�e�X�e�[�W�̃t�@�C����
	std::string file_Pzl;
	std::string file_Map;


	virtual void SetParam(void);	//�������Ƃ̃p�����[�^�ݒ�
};