#pragma once
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<vector>
#include"../Common/Vector2.h"
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"
#include"../Manager/StageManager.h"
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

	//�萔
	static constexpr int FRAME_INTERVAL = 15;
	static constexpr int STRING_TO_INT = 10;

	StageBase(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
		std::vector<std::vector<int>> map[], std::vector<std::vector<int>> obj[],
		int* roomImg,int* mapchip[]);	//�R���X�g���N�^
	virtual ~StageBase(void);			//�f�X�g���N�^
		
	virtual bool Init(void);					//������
	virtual void Update(GameScene::MODE mode);	//�X�V
	virtual void Draw(GameScene::MODE mode);	//�`��
	virtual bool Release(void);					//���

	void CreateKey(int y, int x);	//�A�z�z��̃L�[����
	std::string GetKey(void)const;

	//�p�Y���V�[��
	Vector2 GetNowCursorPos(void);	//���݂̃J�[�\���̈ʒu���擾
	void SetCursor(Vector2 move, Utility::DIR dir);	//�J�[�\���̃Z�b�g y��x�̓J�[�\���̈ړ���
	void SetPiece(Vector2 move, Utility::DIR dir);	//��̈ʒu����ւ� y��x�̓J�[�\���̈ړ���
	void SetFrameFlash(bool flag);					//�g�_�ŗp
	void ResetPazzl(void);							//�p�Y���̃��Z�b�g

	//�X�e���X�V�[��
	bool InitStealth(void);				//�X�e���X�V�[���ڍs���̏�����
	void DrawObject(void);				//�I�u�W�F�N�g�`��
	Position GetNowDrawMapSize(void);	//���ݕ`�悵�Ă���}�b�v�̍ő�T�C�Y���擾
	bool IsMapObj(Vector2 pMapPos);		//���W�ɃI�u�W�F�N�g�����邩�ǂ���
	bool IsMoveRoom(void);				//�����̈ړ����\����������Ԃ�
	int GetObjNum(Vector2 pMapPos);		//���W�ɂ���I�u�W�F�N�g��������Ԃ�
	int GetMapNum(Vector2 pMapPos);		//���W�ɂ���}�b�v�`�b�v����������Ԃ�
	StageManager::MAPCHIP GetMapchipType(void);	//���ݕ`�悵�Ă���}�b�v�`�b�v��ԋp
	RoomBase::ROOM_SHAPE GetNowShape(void);	//�����̌`������(������)
	bool CheckOneDownObject(Vector2 pMapPos);	//����̃}�b�v�`�b�v���I�u�W�F�N�g���������B
	void ChangeRoom(Vector2 pMapPos);			//�����̐؂�ւ�

	StageManager::DOOR GetDoorPos(void)const;			//�h�A�̈ړ��ꏊ�ԋp
	StageManager::DOOR_Y GetDoorPosSecond(void)const;	//����
	bool IsSecondRoom(void)const;
	bool IsGoal(void)const;

private:
	std::map<std::string, RoomBase*> roomMng_;			//�����̏��ꊇ�Ǘ�
	std::map<std::string, RoomBase::TYPE> resetRoom_;	//�����̃��Z�b�g�p
	std::string roomKey_;								//�A�z�z��̃L�[

	
	std::map<std::string, Position>pzlPos_;	//��̕`��ʒu�Ǘ�

	CURSOR type_;		//�J�[�\�������݉����w���Ă��邩��ێ�
	int frame_[static_cast<int>(CURSOR::MAX)];	//�J�[�\���t���[���̉摜��ێ�
	bool frameFlash_;							//�J�[�\����_�ł����邩�ǂ���
	int frameAnim_;								//�J�[�\���_�ŃJ�E���g�p

	bool isMoveRoom_;		//�����̈ړ����\��������
	StageManager::DOOR door_;	//�ړ��Ɏg�p����h�A�̈ʒu
	bool isSecondRoom_;	//�����`�̓�}�X�ڂɏo����
	bool isGoal_;	//�S�[���ɂ��ǂ蒅������
	

	bool MovePiece(const Vector2 csr,
		const std::string bfr, const std::string aft);	//���ۂ̈ړ������@�ړ���̃J�[�\���A�ړ��O��Key�A�ړ����Key

	void MoveRoom(const Vector2 after, const std::string prvKey);


	//����n
	bool CheckInstanceUp(int y, int x, RoomBase* r);	//�����`�̂Q�R�}�ڂ��𔻒f����уC���X�^���X�̐���
	bool CheckInstanceLeft(int y, int x, RoomBase* r);
	RoomBase::ROOM_SHAPE GetRoomShape(std::string key);	//�����̌`������(������)
	RoomBase::ROOM_SHAPE GetRoomShape(RoomBase::TYPE type);	//�����̌`������(��ތ���)
	bool IsDontMoveBlock(std::string key);	//�ړ��s�ȃu���b�N���ǂ���

	Vector2 MoveLeftOrRight(const StageManager::DOOR_X door);	//���E�̈ړ��ʂ�ԋp
	StageManager::DOOR SearchDoor(const Vector2 pMapPos);		//�h�A�̌���
	StageManager::DOOR SplitRoom(const Vector2 pMapPos,const Vector2 size,const Vector2 startPos);	//�����̕���

	

	//Get&Set
	RoomBase* GetSecondRoomInstance(RoomBase* r);		//�����`�Q�R�}�ڂ̃C���X�^���X�̐���
	void SetIsMoveRoom(bool flag);	//�t���O�̃Z�b�g
	void SetIsSecondRoom(bool flag);	//�t���O�̃Z�b�g
	void SetIsGoal(bool flag);

	//�����`�Q�R�}�ڂ��𔻒f���邽�߂ɕK�v�ȃC���X�^���X�𐶐�����
	RoomBase* CreateInstance4Confirmation(RoomBase::TYPE type);

	void SetCursorType(CURSOR type);
	StageManager::DOOR_Y GetDoorSpare(void);			//�c���p�̒ǉ�����̃h�A���m��ԋp
	
	
	//�X�V
	void UpdateStealth(void);

	//�`��
	void DrawPazzle(void);	//�p�Y��
	void DrawCursor(void);	//�J�[�\��
	void DrawStealth(void);	//�X�e���X

	void LoadImgs(void);	//�摜�ǂݍ���

protected:
	////�e�X�e�[�W�̃t�@�C����
	//std::string file_Pzl;
	//std::string file_Map;

	std::vector<std::vector<int>>::iterator pzlCsv_;
	Vector2 size_;
	virtual void SetParam(void);	//�������Ƃ̃p�����[�^�ݒ�

	std::vector<std::vector<int>>* mapCsv_;	//�}�b�v��Csv�f�[�^�̐擪�A�h���X�i�[
	std::vector<std::vector<int>>* objCsv_;	//�I�u�W�F�N�g��Csv�f�[�^�̐擪�A�h���X�i�[
	int* roomImg_;		//�p�Y���V�[���̋�摜�󂯎��
	int** mapchip_;		//�X�e���X�V�[���̃}�b�v�`�b�v�󂯎��

	StageManager::DOOR_Y doorSpare_;	//�h�A����c���p(�����`�Ɖ�����NONE)
};