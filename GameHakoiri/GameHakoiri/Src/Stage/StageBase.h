#pragma once
#include<vector>
#include<list>

//StageBase�͊e�X�e�[�W�̏��u����Ƃ����F��

class RoomBase;

class StageBase
{
public:

	//�񋓌^
	enum class STAGENUM
	{
		TUTORIAL
		, FIRST
		, SECOND
		, THIRD
		, MAX
	};

	StageBase(void);	//�R���X�g���N�^
	virtual ~StageBase(void);	//�f�X�g���N�^

	virtual bool Init(void);	//������
	virtual void Update(void);	//�X�V
	virtual void Draw(void);	//�`��
	virtual bool Release(void);	//���


	virtual void SetParam(void);	//�������Ƃ̃p�����[�^�ݒ�

private:
	std::vector<RoomBase*> rooms_;	//�����̓��I�Ǘ�

protected:

	//�e�X�g�p
	int test_[5];
};