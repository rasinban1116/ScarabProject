#pragma once
#include "stdafx.h"


namespace basecross {
//--------------------------------------------------------------------------------------
///	�X�v���C�g�̐e
//--------------------------------------------------------------------------------------
	class Sprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		vector<VertexPositionColorTexture> m_vertices;
	public:
		// �\�z�Ɣj��
		Sprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~Sprite();

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override;

	};

//--------------------------------------------------------------------------------------
///	�X�R�A�\���̃X�v���C�g
//--------------------------------------------------------------------------------------
	class ScoreSprite : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		int m_score;

		//����
		UINT m_numberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
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