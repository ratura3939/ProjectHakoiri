#pragma once
#include<memory>
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"
#include"../Stage/Room/RoomBase.h"
#include"../Manager/SceneManager.h"

class GameScene;
class StageBase;

class StageManager
{
public:

	//�񋓌^
	//��������X�e�[�W
	enum class STAGENUM
	{
		TUTORIAL
		, FIRST
		, SECOND
		, THIRD
		, MAX
	};

	//�}�b�v�Ɏg�p����}�b�v�`�b�v�̎��
	enum class MAPCHIP
	{
		BATH,
		EXTERIA,
		INTERIA,
		MAX
	};

	//�I�u�W�F�N�g�̎��
	enum class OBJECT
	{
		OBSTACLE,
		THROUGH,
		EVENT,
		MAX
	};

	//���̈ʒu
	enum class DOOR_X
	{
		NONE,
		LEFT,
		RIGHT
	};

	enum class DOOR_Y
	{
		NONE,
		TOP,
		MIDDLE,
		BOTTOM
	};

	struct DOOR
	{
		DOOR_X x;
		DOOR_Y y;
	};

	//�萔
	//�e�X�e�[�W�ɂ�����p�Y���̃T�C�YXY
	static constexpr int TUTORIAL_PAZZLE_SIZE_X = 6;
	static constexpr int TUTORIAL_PAZZLE_SIZE_Y = 6;
	static constexpr int FIRST_PAZZLE_SIZE_X = 6;
	static constexpr int FIRST_PAZZLE_SIZE_Y = 6;
	static constexpr int SECOND_PAZZLE_SIZE_X = 6;
	static constexpr int SECOND_PAZZLE_SIZE_Y = 7;
	static constexpr int THIRD_PAZZLE_SIZE_X = 7;
	static constexpr int THIRD_PAZZLE_SIZE_Y = 7;
	//�����̎�ޕʂ̃p�Y���ɂ�����傫��XY
	static constexpr int NOMAL_PAZZLE_X = 1;
	static constexpr int NOMAL_PAZZLE_Y = 1;
	static constexpr int OBLONG_PAZZLE_X = 1;
	static constexpr int OBLONG_PAZZLE_Y = 2;
	static constexpr int OBLONG_2_PAZZLE_X = 2;
	static constexpr int OBLONG_2_PAZZLE_Y = 1;
	//�����̎�ޕʂ̃}�b�v�ɂ�����傫��XY
	static constexpr int NOMAL_MAP_X = 30;
	static constexpr int NOMAL_MAP_Y = 30;
	static constexpr int OBLONG_MAP_X = 30;
	static constexpr int OBLONG_MAP_Y = 60;
	static constexpr int OBLONG_2_MAP_X = 60;
	static constexpr int OBLONG_2_MAP_Y = 30;

	//�e���[�h�ɂ������{�T�C�YXY
	static constexpr int UNIT_PAZZLE_SIZE_X = 64;
	static constexpr int UNIT_PAZZLE_SIZE_Y = 64;
	static constexpr int UNIT_STEALTH_SIZE_X = 32;
	static constexpr int UNIT_STEALTH_SIZE_Y = 32;

	//���̈ʒu�����̍ۂ̕����̕�����
	static constexpr int SPLIT_ROOM_X = 2;
	static constexpr int SPLIT_ROOM_Y = 3;

	//�}�j���A��
	static constexpr int MANUAL_SIZE = 256;
	static constexpr int MANUAL_FLASH = 40;
	static constexpr int MANUAL_FLASH_MAX = 3000;


	bool Init(STAGENUM);
	void Update(GameScene::MODE mode);
	void Draw(GameScene::MODE mode);
	void DrawObject(void);
	bool Release(void);	

#pragma region �p�Y���֘A
	//����**********************************************************************************
	/// <summary>
	/// �ړ�(�J�[�\��)
	/// </summary>
	/// <param name="dir">�ړ�����</param>
	void MoveCursor(Utility::DIR dir);

	/// <summary>
	/// �ړ�(��)
	/// </summary>
	/// <param name="dir">�ړ�����</param>
	void MovePiece(Utility::DIR dir);

	/// <summary>
	/// �Ֆʃ��Z�b�g
	/// </summary>
	void PazzleReset(void);

	//�ݒ�************************************************************************************
	/// <summary>
	/// �_��
	/// </summary>
	/// <param name="flag">true=�_�ł�����/fals=�_�ł����Ȃ�</param>
	void SetFlash(bool flag);

	/// <summary>
	/// �Q�[�������t���O�Z�b�g
	/// </summary>
	/// <param name="flag">true=�`�悷��/false=�`�悵�Ȃ�</param>
	void SetIsDrawPazzleManual(bool flag);

	//����**************************************************************************************
	/// <summary>
	/// �S�[���\�������Ԃ�
	/// </summary>
	/// <returns>true=�\/false=�s�\</returns>
	const bool IsCanGoal(void);
#pragma endregion

#pragma region �X�e���X�֘A
	//����**********************************************************************************
	/// <summary>
	/// �X�e���X���[�h�֕ύX�y�я�����
	/// </summary>
	void ChangeModeInit(void);

	/// <summary>
	/// �����̐؂�ւ�
	/// </summary>
	/// <param name="pMapPos">���ɐG�ꂽ���̃v���C���[�ʒu</param>
	void ChangeMap(Vector2 pMapPos);

	//����***********************************************************************************
	/// <summary>
	/// �����`�}�X�̖{�̂���Ȃ��ق���ʂ�����
	/// </summary>
	/// <returns> true=�ʂ���/false=�ʂ��Ă��Ȃ� </returns>
	const bool IsSecondEvidence(void)const;

	/// <summary>
	/// �I�u�W�F�N�g�ƏՓ˂��Ă��邩
	/// </summary>
	/// <param name="pMapPos">����Ώۂ̍��W</param>
	/// <returns> true=���Ă���/false=���Ă��Ȃ� </returns>
	const bool IsCollisionObject(const Vector2 pMapPos)const;

	/// <summary>
	/// �ǂƏՓ˂��Ă��邩
	/// </summary>
	/// <param name="pMapPos">����Ώۂ̍��W</param>
	/// <returns> true=���Ă���/false=���Ă��Ȃ� </returns>
	const bool IsCollisionWall(const Vector2 pMapPos)const;

	/// <summary>
	/// �}�b�v�ړ���������
	/// </summary>
	/// <returns> true=����/false=���Ă��Ȃ� </returns>
	const bool IsMoveMap(void);

	/// <summary>
	/// �N���A������
	/// </summary>
	/// <returns>true=����/false=���Ă��Ȃ�</returns>
	const bool IsClear(void)const;

	/// <summary>
	/// �c���̃I�u�W�F�N�g�̍ŉ����u���b�N�ł��邩�ǂ���
	/// </summary>
	/// <param name="pMapPos">����Ώۂ̍��W</param>
	/// <returns>true=�ŉ����ł���/false=�ŉ����ł͂Ȃ�</returns>
	const bool IsBottomObject(const Vector2 pMapPos)const;

	//���擾*********************************************************************************
	/// <summary>
	/// ���݂��镔���̃}�b�v�T�C�Y���擾
	/// </summary>
	/// <returns>�T�C�Y={float,float}</returns>
	Vector2F GetMapMaxSize(void)const;

	/// <summary>
	/// ���W���}�b�v�̗v�f���p�ɕϊ�
	/// </summary>
	/// <param name="pPos">���W</param>
	/// <returns>�v�f���ϊ����{X,Y}</returns>
	Vector2 GetVector2MapPos(const Vector2 pPos)const;

	/// <summary>
	/// ���W�ɏՓ˂��Ă���I�u�W�F�N�g�̎�ޕϊ�
	/// </summary>
	/// <param name="pMapPos">���W</param>
	/// <returns>�I�u�W�F�N�g�̎��(�ʂ蔲���\���Ȃ�)</returns>
	const OBJECT GetObjectType(const Vector2 pMapPos)const;		//�I�u�W�F�N�g�̃^�C�v��ԋp

	/// <summary>
	/// �����̌`���擾
	/// </summary>
	/// <returns>�����`OR�����`</returns>
	const RoomBase::ROOM_SHAPE GetShape(void);					//�����̌`�����`�������`���j

	/// <summary>
	/// ���̎擾
	/// </summary>
	/// <returns>���݂̔z��v�f��</returns>
	const std::string GetKey(void)const;						//�z��w�萔

	/// <summary>
	/// �h�A�̈ʒu���擾
	/// </summary>
	/// <returns></returns>
	const DOOR GetDoor(void)const;								//�ړ��Ɏg�p�����h�A�̈ʒu

	/// <summary>
	/// ��L�̕������c���������ꍇ�̕⑫��
	/// </summary>
	/// <returns>�⑫��̐��m�ȏꏊ</returns>
	const DOOR_Y GetDoorSecond(void)const;

private:
	/// <summary>
	/// �z��v�f�������W�ɕϊ�
	/// </summary>
	/// <param name="pPos">�}�b�v�z��v�f��</param>
	/// <returns>���W</returns>
	Vector2 GetMapPos2Vector(const Vector2 pPos)const;			//�}�b�v�̔z������W�ɕϊ�
#pragma endregion
	
public:
	//�V���O���g����
	static bool CreateInstance(STAGENUM);	//�O������ÓI�C���X�^���X�𐶐�
	static StageManager& GetInstance(void);	//�C���X�^���X�̎擾
	
private:

	std::unique_ptr<StageBase> stage_;	//�X�e�[�W�{��

	STAGENUM num_;						//��������X�e�[�W�ԍ�

	Vector2 dir_[static_cast<int>(Utility::DIR::MAX)];	//�ړ�����

	bool isDrawPazzleManual_;			//�p�Y���̑��������`�悷�邩�ǂ���
	int manualFlash_;												//�_�ŗp�J�E���^

	//IMG
	int roomImg_[static_cast<int>(RoomBase::TYPE::MAX)];			//����
	int* mapTile_[static_cast<int>(MAPCHIP::MAX)];					//�}�b�v�摜
	int manualImg_[static_cast<int>(SceneManager::CONTROLLER::MAX)];//����
	
	//Csv
	std::vector<std::vector<int>> stageCsv_[static_cast<int>(STAGENUM::MAX)];		//�p�Y��
	std::vector<std::vector<int>> mapCsv_[static_cast<int>(RoomBase::TYPE::MAX)];	//�}�b�v
	std::vector<std::vector<int>> objCsv_[static_cast<int>(RoomBase::TYPE::MAX)];	//�I�u�W�F�N�g
	std::vector<std::vector<int>>mapchipObj_[static_cast<int>(MAPCHIP::MAX)][static_cast<int>(OBJECT::MAX)];	//�}�b�v�`�b�v�����蔻��C


	//�f�[�^�ǂݍ���
	void LoadImg(void);
	void LoadCsv(void);

	//�V���O���g����
	StageManager(void);	//�R���X�g���N�^
	StageManager(const StageManager&);	//�R�s�[�R���X�g���N�^
	void Destroy(void);	//�f�X�g���N�^

	static  StageManager* instance_;	//���̂��m��
};