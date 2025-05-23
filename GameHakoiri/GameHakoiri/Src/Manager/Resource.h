#pragma once
#include <string>
#include <vector>

class Resource
{

public:

	// リソースタイプ
	enum class TYPE
	{
		NONE,
		IMG,
		IMGS,
		CSV,
		MODEL,
		SOUND,
		//EFFEKSEER
	};

	// コンストラクタ
	Resource(void);
	// コンストラクタ
	Resource(TYPE type, const std::string& path);
	// コンストラクタ(IMGS用)
	Resource(TYPE type, const std::string& path, int numX, int numY, int sizeX, int sizeY);

	// デストラクタ
	~Resource(void);

	// 読み込み
	void Load(void);

	void LoadCsv(void);

	// 解放
	void Release(void);

	// 複数画像ハンドルを別配列にコピー
	void CopyHandle(int* imgs);

	// リソースタイプ
	TYPE resType_;

	// リソースの読み込み先
	std::string path_;

	// 画像とモデルのハンドルID
	int handleId_;

	// IMGS::LoadDivGraph用
	int* handleIds_;
	int numX_;
	int numY_;
	int sizeX_;
	int sizeY_;

	//Csv用の動的二元
	std::vector<int> dmcHndIdX_;
	std::vector<std::vector<int>> dmcHandleIds_;
	std::vector<std::vector<int>>::iterator csv_;

	// モデル複製用
	std::vector<int> duplicateModelIds_;

};

