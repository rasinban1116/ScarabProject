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
	}
	//ボックスの作成
	void GameStage::CreateFixedSlopeBox() {
		CreateSharedObjectGroup(L"TilingSlopeBox");
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
			if (Rot != Vec3(0)) {
				Tiling->AddTag(L"Slope");
			}
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
		auto ptrPlayer = AddGameObject<Player>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
		
	}

	//プレイヤーを継承した子オブジェクト（ふんころがしになる予定）を生成
	void GameStage::CreatePlayerChild() {
		auto Unko = AddGameObject<UnkoBoll>(Vec3(-85.0f, 21.0f, -33.0f),Vec3(1.0f),Vec3(0.0f), Vec3(0.0f, 6.0f, 5.0f));
		SetSharedGameObject(L"UnkoBoll", Unko);
		Unko->AddTag(L"UnkoBoll");
	}

	void GameStage::CreateLowEnemy() {
		auto group = CreateSharedObjectGroup(L"EnemyGroup");
		vector< vector<Vec3> > vecSeek = {
			{ Vec3(5.0, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 5.0f) },
		};
		//追いかけるオブジェクトの作成
		for (auto v : vecSeek) {
			auto ptreneobj = AddGameObject<Enemy>(v[0], v[1]);
			SetSharedGameObject(L"Enemy", ptreneobj);
			ptreneobj->AddTag(L"Enemy");
		}

	}

	void GameStage::activeboll() {
		AddGameObject<ActivePsSphere>(1.0f, Quat(), Vec3(0.0f, 6.0f, 5.0f));
	}

	void GameStage::CreateGimmickObj() {
		auto group = CreateSharedObjectGroup(L"CoinGroup");
		AddGameObject<GimmickObj>(Vec3(0.1f, 0.5f, 0.5f),  Quat(), Vec3(0.0f, 0.6f, -3.0f));
		AddGameObject<GimmickObj>(Vec3(0.1f, 0.5f, 0.5f),  Quat(), Vec3(3.0f, 0.6f, -3.0f));
		AddGameObject<GimmickObj>(Vec3(0.1f, 0.5f, 0.5f),  Quat(), Vec3(-3.0f, 0.6f, -3.0f));

		auto ptrScore = AddGameObject<ScoreSprite>(3,
			L"NUMBER_TX",
			true,
			Vec2(80.0f, 80.0f),
			Vec3(-480.0f, 360.0f, 0.0f));


		//vector< vector<Vec3> > vecSeek = {
		////	{ Vec3(5.0, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 5.0f), Vec3(0,0,0) },
		////};
		//////追いかけるオブジェクトの作成
		////for (auto v : vecSeek) {
		////	AddGameObject<SkyBox>(v[0], v[1], v[2]);
		////	//SetSharedGameObject(L"Enemy", ptreneobj);
		////	//ptreneobj->AddTag(L"Enemy");
		//}
	}


	void GameStage::OnCreate() {
		try {
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//物理演算のオンオフ
			SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			////CSVファイルそのBの読み込み
			m_GameStageCsvB.SetFileName(DataDir + L"test2.csv");
			m_GameStageCsvB.ReadCsv();
			//物理演算するボックスの作成
			CreateFixedBox();
			//物理演算するコリジョンを持ったプレイヤーの作成
			CreatePlayer();
			//プレイヤーを継承した子オブジェクトの作成
			CreatePlayerChild();
			CreateLowEnemy();
			//ギミックの生成
			CreateGimmickObj();
			//UIの表示
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
