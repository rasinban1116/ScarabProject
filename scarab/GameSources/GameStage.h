/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect {
		openingCamera,
		myCamera,
		objCamera,
	};

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//OpeningCamera用のビュー
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		//ObjCamera用のビュー
		shared_ptr<SingleView> m_ObjCameraView;
		CameraSelect m_CameraSelect;
		//CSVファイルそのA
		CsvFile m_GameStageCsvA;
		//CSVファイルそのB
		CsvFile m_GameStageCsvB;
		//固定のボックスの作成
		void CreateFixedBox();
		//固定の傾いたボックスの作成
		void CreateBox();
		//プレイヤーの作成
		void CreatePlayer();
		//敵の作成
		void CreateLowEnemy();;
		//プレイヤーを継承した子オブジェクトの継承
		void CreatePlayerChild();
		//動く球体
		void activeboll();
		//ギミック用のオブジェクト生成
		void CreateGimmickObj();
		//ゲームクリア用のオブジェクト作成
		void CreateClearObj();
		//UIの表示
		void CreateUI();
		void GameSystemObj();
		//カメラマンの作成
		void CreateCameraman();
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}
		//初期化
		virtual void OnCreate()override;
		void ToMyCamera();
		void ToObjCamera();
	};


}
//end basecross

