/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}

	//固定のボックスの作成
	void GameStage::CreateFixedBox() {
		//下の台
		AddGameObject<FixedPsBox>(Vec3(30.0f, 1.0f, 30.0f), Quat(), Vec3(0.0f, -0.5f, 0.0f));

		//動かない台
		AddGameObject<FixedPsBox>(Vec3(3.0f, 1.0f, 3.0f), Quat(), Vec3(0.0f, 0.5f, 3.0f));
		//AddGameObject<FixedPsBox>(Vec3(3.0f, 1.0f, 3.0f), Quat(0.5f), Vec3(4.0f, 0.5f, 5.0f));

	}
	void GameStage::CreateCollisionBox2() {
		vector <vector<Vec3>> vec = { {

				Vec3(10.0f, 0.5f, 10.0f),
				Vec3(-0.5f, 0.0f, -0.5f),
				Vec3(-10.0f, 0.25f, 10.0f)
		},
		{
				Vec3(10.0f, 0.5f, 10.0f),
				Vec3(-0.0f, 0.0f, -0.0f),
				Vec3(-10.0f,4.0f, 18.0f)
		},

		};
		//オブジェクトの作成
		for (auto v : vec) {
		auto SlopeObj = AddGameObject<FixedBox>(v[0], v[1], v[2]);
		//シェア配列に坂道オブジェクトを追加
		//auto SlopeGroup = CreateSharedObjectGroup(L"SlopeGroup");
		}

	}

	//プレイヤ―の生成
	void GameStage::CreatePlayer() {
		//プレーヤーの作成
		auto ptrPlayer = AddGameObject<Player>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}

	//プレイヤーを継承した子オブジェクト（ふんころがしになる予定）を生成
	void GameStage::CreatePlayerChild() {
		//オブジェクトのグループを作成する
		auto group = CreateSharedObjectGroup(L"SeekGroup");
		//配列の初期化
		vector<Vec3> vec = {
			{ 0, 0.125f, 10.0f },
			{ 10.0f, 0.125f, 0.0f },
			{ -10.0f, 0.125f, 0.0f },
			{ 0, 0.125f, -10.0f },
		};

		//配置オブジェクトの作成
		for (size_t count = 0; count < vec.size(); count++) {
			AddGameObject<PlayerChild>(vec[count]);
		}

	}

	void GameStage::activeboll() {
		AddGameObject<ActivePsSphere>(1.0f, Quat(), Vec3(0.0f, 6.0f, 5.0f));
	}


	void GameStage::OnCreate() {
		try {
			//物理演算のオンオフ
			SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			//物理演算するボックスの作成
			CreateFixedBox();
			//物理演算するコリジョンを持ったプレイヤーの作成
			CreatePlayer();
			//プレイヤーを継承した子オブジェクトの作成
			CreatePlayerChild();
			//コリジョンを持ったボックスの作成
			CreateCollisionBox2();
			//物理演算する球体の作成
			activeboll();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
