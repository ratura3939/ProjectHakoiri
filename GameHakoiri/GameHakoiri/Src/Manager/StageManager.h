#pragma once

class StageManager
{
public:
	//�񋓌^
	enum class STAGENUM
	{
		
	};

	StageManager(void);	//�R���X�g���N�^
	virtual ~StageManager(void);	//�f�X�g���N�^

	virtual bool Init(void);	//������
	virtual void Update(void);	//�X�V
	virtual void Draw(void);	//�`��
	virtual bool Release(void);	//���
};