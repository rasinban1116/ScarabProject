#pragma once
#include "stdafx.h"


namespace basecross {
//--------------------------------------------------------------------------------------
///	スプライトの親
//--------------------------------------------------------------------------------------
	class Sprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		vector<VertexPositionColorTexture> m_vertices;
	public:
		// 構築と破棄
		Sprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~Sprite();

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;

	};

//--------------------------------------------------------------------------------------
///	スコア表示のスプライト
//--------------------------------------------------------------------------------------
	class ScoreSprite : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		int m_score;

		//桁数
		UINT m_numberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_backupVertices;
	public:


		ScoreSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~ScoreSprite() {}

		void SetScore(int f) {
			m_score += f;
		}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}