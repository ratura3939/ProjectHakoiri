#pragma once
#include<memory>
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"

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
	enum class MAPTHIP
	{
		BATH,
		EXTERIA,
		INTERIA,
		MAX
	};

	//�萔
	static constexpr int TUTORIAL_PAZZLE_SIZE_X = 6;
	static constexpr int TUTORIAL_PAZZLE_SIZE_Y = 6;
	static constexpr int FIRST_PAZZLE_SIZE_X = 6;
	static constexpr int FIRST_PAZZLE_SIZE_Y = 6;
	static constexpr int SECOND_PAZZLE_SIZE_X = 6;
	static constexpr int SECOND_PAZZLE_SIZE_Y = 6;
	static constexpr int THIRD_PAZZLE_SIZE_X = 6;
	static constexpr int THIRD_PAZZLE_SIZE_Y = 6;

	static constexpr int NOMAL_MAP_X = 30;
	static constexpr int NOMAL_MAP_Y = 30;
	static constexpr int OBLONG_MAP_X = 30;
	static constexpr int OBLONG_MAP_Y = 60;
	static constexpr int OBLONG_2_MAP_X = 60;
	static constexpr int OBLONG_2_MAP_Y = 30;

	static constexpr int OTHER_MAP_X = 0;
	static constexpr int OTHER_MAP_Y = 0;


	bool Init(STAGENUM);	//������
	void Update(GameScene::MODE mode);	//�X�V
	void Draw(GameScene::MODE mode);	//�`��
	bool Release(void);	//���

	void MoveCursor(Utility::DIR dir);	//�J�[�\���̈ړ�
	void MovePiece(Utility::DIR dir);	//��̈ړ�
	void PazzleReset(void);		//�Ֆʃ��Z�b�g
	void SetFlash(bool flag);	//�g�_��
	

	//�V���O���g����
	static bool CreateInstance(STAGENUM);	//�O������ÓI�C���X�^���X�𐶐�
	static StageManager& GetInstance(void);	//�C���X�^���X�̎擾
	
private:

	//�C���X�^���X
	StageBase* stage_;

	STAGENUM num_;	//��������X�e�[�W�ԍ���ێ�

	Vector2 dir_[static_cast<int>(Utility::DIR::MAX)];

	//IMG
	int roomImg_[static_cast<int>(RoomBase::TYPE::MAX)];
	
	//Csv
	//�p�Y���X�e�[�W�ێ�
	std::vector<std::vector<int>> stageCsv_[static_cast<int>(STAGENUM::MAX)];


	std::vector<std::vector<int>> mapCsv_[static_cast<int>(RoomBase::TYPE::MAX)];	//�}�b�v��Csv�f�[�^�̐擪�A�h���X�i�[
	std::vector<std::vector<int>> objCsv_[static_cast<int>(RoomBase::TYPE::MAX)];	//�I�u�W�F�N�g��Csv�f�[�^�̐擪�A�h���X�i�[
	int* mapTile_[static_cast<int>(MAPTHIP::MAX)];	//�}�b�v�摜���擾

	void LoadImg(void);
	void LoadCsv(void);


	//�V���O���g����
	StageManager(void);	//�R���X�g���N�^
	StageManager(const StageManager&);	//�R�s�[�R���X�g���N�^
	void Destroy(void);	//�f�X�g���N�^

	static  StageManager* instance_;	//���̂��m��
};