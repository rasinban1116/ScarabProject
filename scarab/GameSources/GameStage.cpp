/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//ステージを作り終わったら一定範囲内以外をスリープさせる処理を書く


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

	void GameStage::CreateBox(){
		auto treeGrope = CreateSharedObjectGroup(L"Tree");
		//AddGameObject<WallPsBox>(Vec3(1), Quat(0),Vec3(-60.0f, 8.5f, -25.0f),int(1));
		//AddGameObject<WallPsBox>(Vec3(1), Quat(0), Vec3(-50.0f, 10.5f, -20.0f), int(1));
		//AddGameObject<WallPsBox>(Vec3(1), Quat(0), Vec3(-30.0f, 10.5f, -35.0f), int(3));


	}
	//ボックスの作成
	void GameStage::CreateFixedBox() {
		CreateSharedObjectGroup(L"TilingBox");
		Vec3 Rot;
		//CSVの行単位の配列
		vector<wstring> LineVec;
		//0番目のカラムがL"TilingFixedBox"である行を抜き出す
		m_GameStageCsvB.GetSelect(LineVec, 0, L"TilingFixedBox");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);



			//回転は「XM_PIDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Quat rot;
			float x, y, z;
			x = (float)_wtof(Tokens[4].c_str());
			y = (float)_wtof(Tokens[5].c_str());
			z = (float)_wtof(Tokens[6].c_str());
			rot.setX(x);
			rot.setY(y);
			rot.setZ(z);
			//Rot = rot;
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			//各値がそろったのでオブジェクト作成
			auto Tiling = AddGameObject<TilingFixedBox>(Scale, Rot, Pos, 1.0f, 1.0f, Tokens[10]);
		}

		//0番目のカラムがL"TilingFixedBox"である行を抜き出す
		m_GameStageCsvB.GetSelect(LineVec, 0, L"SlopeFixedBox");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);



			//回転は「XM_PIDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Quat rot;
			float x, y, z;
			x = (float)_wtof(Tokens[4].c_str());
			y = (float)_wtof(Tokens[5].c_str());
			z = (float)_wtof(Tokens[6].c_str());
			rot.setX(x);
			rot.setY(y);
			rot.setZ(z);
			//Rot = rot;
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			//各値がそろったのでオブジェクト作成
			auto Tiling = AddGameObject<SlopeFixedBox>(Scale, Rot, Pos, 1.0f, 1.0f, Tokens[10]);
		}
	}

	

	void GameStage::CreateUI() {
		auto UI = AddGameObject<UIDraw>();
		SetSharedGameObject(L"UI", UI);
	}
	void GameStage::GameSystemObj() {
		auto Clear = AddGameObject<StageClearObj>(Vec3(0.0f,3.0f,0.0f),Vec3(0.5f));
	}


	//プレイヤ―の生成
	void GameStage::CreatePlayer() {
		//プレーヤーの作成
		auto ptrPlayer = AddGameObject<Player>(Vec3(-89.0f, 0.5f, -35.0f));
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}

	//プレイヤーを継承した子オブジェクト（ふんころがしになる予定）を生成
	void GameStage::CreatePlayerChild() {
		auto Unko = AddGameObject<UnkoBoll>(Vec3(-85.0f, 0.5f, -33.0f),Vec3(1.0f),Vec3(0.0f), Vec3(0.0f, 6.0f, 5.0f));
		SetSharedGameObject(L"UnkoBoll", Unko);
		Unko->AddTag(L"UnkoBoll");
	}

	void GameStage::CreateLowEnemy() {
		//フンコロガシの生成
		auto group = CreateSharedObjectGroup(L"EnemyGroup");
		vector< vector<Vec3> > vecSca = {
			{ Vec3(-15.0f, 3.0f, -5.0f), Vec3(-23.0f,3.0f,-4.0f) },
			{ Vec3(5.0f, 0.5f, 1.0f), Vec3(-1.0f,5.0f, 7.0f) },
			{ Vec3(-73.0f, 0.5f, -40.0f), Vec3(-70.0f,0.5f, -35.0f) },
			{ Vec3(-75.0f, 0.5f,-2.0f), Vec3(-70.0f,2.0f, 1.0f) },
			{ Vec3(-30.0f, 0.5f,-34.0f), Vec3(30.0f,2.0f, -34.0f) },



		};
		for (auto v : vecSca) {
			auto ptreneobj = AddGameObject<Enemy>(v[0], v[1], 1, L"SCARAB_TX", L"Enemy");
		}

		//トカゲの生成
		vector< vector<Vec3> > vecLiz = {
			{ Vec3(10.0f ,0.5f, 0.0f), Vec3(0.0f, 0.0f, 5.0f) },
			{ Vec3(-70.0f, 0.5f,-40.0f), Vec3(69.0f,2.0f, -49.0f) },
			{ Vec3(-68.0f, 0.5f,-0.0f), Vec3(-68.0f,2.0f, -34.0f) },
			{ Vec3(-30.0f, 0.5f,-40.0f), Vec3(30.0f,2.0f, 34.0f) },

		};
		for (auto v : vecLiz) {
			auto ptreneobj = AddGameObject<Enemy>(v[0], v[1], 1, L"Lizad_TX", L"Lizad");

		}
	}

	void GameStage::CreateGimmickObj() {
		auto group = CreateSharedObjectGroup(L"CoinGrope");
		
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f),  Quat(), Vec3(0.0f, 0.f, -3.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f),  Quat(), Vec3(3.0f, 0.f, -3.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-78.0f, 0.f, -35.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-71.0f, 0.f, -30.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-35.0f, 0.f, -4.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-27.0f, 0.f, 1.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-29.0f, 0.f, -32.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-32.0f, 0.f, -38.0f));
		AddGameObject<GimmickObj>(Vec3(0.25f, 0.25f, 0.25f), Quat(), Vec3(-77.0f, 0.f, -4.2f));
	
	}
	void  GameStage::CreateWoods() {
		auto woods = CreateSharedObjectGroup(L"WoodsGrope");
		
		AddGameObject<StageObj>(Vec3(1), Vec3(1), 0);

	}
	

	void GameStage::CreateClearObj() {
		auto ClearObj = AddGameObject<StageClearObj>(Vec3(0,0.f,0), Vec3(0.5f));
		SetSharedGameObject(L"Clear",ClearObj);
	}

	void GameStage::CreateSky() {
		AddGameObject<SkyObj>(Vec3(200.f, 100.f, 0.5f), Quat(), Vec3(0.0f, 0.0f, 100.0f));
		AddGameObject<SkyObj>(Vec3(200.f, 100.f, 0.5f), Quat(), Vec3(0.0f, 0.0f, -100.0f));
		AddGameObject<SkyObj>(Vec3(0.5f, 100.f, 200.0f), Quat(), Vec3(100.0f, 0.0f, 0.0f));
		AddGameObject<SkyObj>(Vec3(0.5f, 100.f, 200.0f), Quat(), Vec3(-100.0f, 0.0f, 0.0f));
		AddGameObject<SkyObj>(Vec3(200.0f, 0.5f, 200.0f), Quat(), Vec3(0.0f, 50.0f, 0.0f));

	}




	void GameStage::OnCreate() {
		auto gm = GameManager::GetInstance();
		gm->UnkoNumReSet();
		try {
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//物理演算のオンオフ
			SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			////CSVファイルそのBの読み込み
			m_GameStageCsvB.SetFileName(DataDir + L"Stage2.csv");
			m_GameStageCsvB.ReadCsv();
			//物理演算するボックスの作成
			CreateFixedBox();
			//物理演算するコリジョンを持ったプレイヤーの作成
			CreatePlayer();
			//プレイヤーを継承した子オブジェクトの作成
			CreatePlayerChild();
			//敵の追加
			CreateLowEnemy();
			//空の追加
			CreateSky();
			//ギミックの生成
			CreateGimmickObj();
			CreateClearObj();
			//UIの表示
			CreateUI();
			//壁の生成
			CreateBox();
			//木々の生成
			CreateWoods();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
