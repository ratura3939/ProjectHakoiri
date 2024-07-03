#pragma once
#include "CharacterBase.h"
#include <DxLib.h>

class EnemyBase :
    public CharacterBase
{
public:

	enum class TYPE
	{
		HOUSEMADE,
		SENESCHAL,
		MAX
	};

	enum class VISION_STATE
	{
		MISSING,
		FIND,
		MAX
	};

	//定数
	static constexpr int MOVE_UNIT = 32;	//敵の基礎移動量
	static constexpr float VIEW_RANGE = 320.0f;	// 視野の広さ(10マス)
	static constexpr float VIEW_ANGLE = 45.0f;	// 視野角
	static constexpr float VIEW_DELTA = 90.0f;	// 視野角誤差合わせ用（普通は右が0だが視野角は上からなので)

	EnemyBase(void);
	~EnemyBase(void)override;

	void Init(void)override;
	void SetParam(void)override;
	void Draw(void)override;
	void Move(void)override;

	bool FindPlayer(Vector2F pPos)const;	//視野内にplayerがいるか

	void SetIsUse(bool flag);	//敵を使用しているかをセット
	bool IsUse(void);			//敵が使用済みかを確認
	TYPE GetType(void);			//敵の種類を獲得
	void SetIsMove(bool flag);	//動いているかをセット	
	void SetVisionState(VISION_STATE state);	//敵の視覚状態をセット
	void SetColObject(const Vector2 obj);	//視界を遮るオブジェクトの位置（配列指数）をセット
	void ResetColObject(void);				//視界を遮るオブジェクトの位置（配列指数）をリセット
	Vector2 GetColObject(void)const;		//視界を遮るオブジェクトの位置（配列指数）をゲット

protected:
	TYPE type_;	//敵のタイプを保持
	bool isUse_;//すでに使用されているかを保持
	Vector2F moveStartPos_;
	int moveLimit_;	//一回での移動マス量限度
	VECTOR moveDir_;	//動く方向のベクター
	float speed_;		//動きの速さ

private:
	//視界
	int visionImg_[static_cast<int>(VISION_STATE::MAX)];	//視野画像
	double drawVisionRot_;	//視野角の描画のみ使用
	VISION_STATE state_;	//敵の発見状態

	bool isMove_;	//動いているか
	Vector2 colObject_;	//敵の視界を遮るオブジェクトを保存

	void DrawVision(Vector2F cameraPos);	//視界の描画
	void DecideDir(void);					//方向決め
					
};

