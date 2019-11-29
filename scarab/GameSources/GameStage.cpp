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
	//ボックスの作成
	void GameStage::CreateFixedBox() {
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
			Vec3 Rot;
			//回転は「XM_PIDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Quat rot;
			rot.x = (float)_wtof(Tokens[4].c_str());
			rot.y = (float)_wtof(Tokens[5].c_str());
			rot.z = (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			//各値がそろったのでオブジェクト作成
			auto tiling = AddGameObject<TilingFixedBox>(Scale, Rot, Pos, 1.0f, 1.0f, Tokens[10]);
			auto tilingquat = tiling->GetComponent<Transform>();
			//tilingquat->SetQuaternion(rot);
		}
	}


	//固定のボックスの作成
	//void GameStage::CreateFixedBox() {
	//	//下の台
	//	AddGameObject<FixedPsBox>(Vec3(30.0f, 1.0f, 30.0f), Quat(), Vec3(0.0f, -0.5f, 0.0f));
	//
	//	//動かない台
	//	AddGameObject<FixedPsBox>(Vec3(3.0f, 3.0f, 3.0f), Quat(), Vec3(0.0f, 0.0f, 3.0f));
	//	AddGameObject<FixedPsBox>(Vec3(2.0f, 3.0f, 2.0f), Quat(), Vec3(4.0f, 0.0f, 5.0f));

	//	//上から降ってくる球体
	//	AddGameObject<ActivePsSphere>(1.0f, Quat(), Vec3(0.0f, 6.0f, 5.0f));

	//}

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
		//オブジェクトのグループを作成する
		auto group = CreateSharedObjectGroup(L"SeekGroup");
		auto Target = GetSharedObject(L"Player", true);
		auto Targetrans = Target->GetComponent<Transform>();
		auto TargetPos = Targetrans->GetPosition();
		//配列の初期化
		vector<Vec3> vec = {
			{ TargetPos.x,TargetPos.y,TargetPos.z -0.5f },
		};

		//配置オブジェクトの作成
		for (size_t count = 0; count < vec.size(); count++) {
			AddGameObject<PlayerChild>(vec[count]);
		}

	}

	void GameStage::CreateLowEnemy() {
		auto group = CreateSharedObjectGroup(L"Enemy_LowGroup");
		vector< vector<Vec3> > vecSeek = {
			{ Vec3(5.0, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 5.0f) },
		};
		//追いかけるオブジェクトの作成
		for (auto v : vecSeek) {
			auto ptrPathobj = AddGameObject<FollowPathObject>(v[0], v[1]);
			SetSharedGameObject(L"Pathobj", ptrPathobj);
			ptrPathobj->AddTag(L"Pathobj");
			
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
			m_GameStageCsvB.SetFileName(DataDir + L"test0.csv");
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
			//クリアオブジェクト
			//GameSystemObj();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
