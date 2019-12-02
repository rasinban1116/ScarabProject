/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//CSVファイルそのA
		CsvFile m_GameStageCsvA;
		//CSVファイルそのB
		CsvFile m_GameStageCsvB;
		//固定のボックスの作成
		void CreateFixedBox();
		//固定の傾いたボックスの作成
		void CreateFixedSlopeBox();
		//プレイヤーの作成
		void CreatePlayer();
		//プレイヤーを継承した子オブジェクトの継承
		void CreatePlayerChild();
		//動く球体
		void activeboll();
		//ギミック用のオブジェクト生成
		void CreateGimmickObj();
		//UIの表示
		void CreateUI();
		void GameSystemObj();
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
	};


}
//end basecross

