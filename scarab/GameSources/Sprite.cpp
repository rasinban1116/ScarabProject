#include "stdafx.h"
#include "Project.h"

namespace basecross {

//--------------------------------------------------------------------------------------
///	スプライトの親
//--------------------------------------------------------------------------------------
	Sprite::Sprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}
	void Sprite::OnUpdate() {

	}
	Sprite::~Sprite() {}
	void Sprite::OnCreate() {
		float HelfSize = 1.0f;
		//頂点配列(1個表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		SetDrawLayer(0);
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
	}

//--------------------------------------------------------------------------------------
///	スコア表示のスプライト
//--------------------------------------------------------------------------------------
	ScoreSprite::ScoreSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_numberOfDigits(NumberOfDigits),
		m_textureKey(TextureKey),
		m_trace(Trace),
		m_startScale(StartScale),
		m_startPos(StartPos),
		m_score(0)
	{}

	void ScoreSprite::OnCreate() {
		float xPiecesize = 1.0f / (float)m_numberOfDigits;
		float helfSize = 0.5f;

		//インデックス配列
		vector<uint16_t> indices;
		for (UINT i = 0; i < m_numberOfDigits; i++) {
			float vertex0 = -helfSize + xPiecesize * (float)i;
			float vertex1 = vertex0 + xPiecesize;
			//0
			m_backupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, helfSize, 0), Vec2(0.0f, 0.0f))
			);
			//1
			m_backupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, helfSize, 0), Vec2(0.1f, 0.0f))
			);
			//2
			m_backupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, -helfSize, 0), Vec2(0.0f, 1.0f))
			);
			//3
			m_backupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, -helfSize, 0), Vec2(0.1f, 1.0f))
			);
			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 2);
		}

		SetAlphaActive(m_trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_startPos.x, m_startPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_backupVertices, indices);
		ptrDraw->SetTextureResource(m_textureKey);
		GetStage()->SetSharedGameObject(L"ScoreSprite", GetThis<ScoreSprite>());
	}

	void ScoreSprite::OnUpdate() {
		vector<VertexPositionTexture> newVertices;
		UINT num;
		int verNum = 0;
		for (UINT i = m_numberOfDigits; i > 0; i--) {
			UINT base = (UINT)pow(10, i);
			num = ((UINT)m_score) % base;
			num = num / (base / 10);
			Vec2 uv0 = m_backupVertices[verNum].textureCoordinate;
			uv0.x = (float)num / 10.0f;
			auto v = VertexPositionTexture(
				m_backupVertices[verNum].position,
				uv0
			);
			newVertices.push_back(v);

			Vec2 uv1 = m_backupVertices[verNum + 1].textureCoordinate;
			uv1.x = uv0.x + 0.1f;
			v = VertexPositionTexture(
				m_backupVertices[verNum + 1].position,
				uv1
			);
			newVertices.push_back(v);

			Vec2 uv2 = m_backupVertices[verNum + 2].textureCoordinate;
			uv2.x = uv0.x;

			v = VertexPositionTexture(
				m_backupVertices[verNum + 2].position,
				uv2
			);
			newVertices.push_back(v);

			Vec2 uv3 = m_backupVertices[verNum + 3].textureCoordinate;
			uv3.x = uv0.x + 0.1f;

			v = VertexPositionTexture(
				m_backupVertices[verNum + 3].position,
				uv3
			);
			newVertices.push_back(v);

			verNum += 4;
		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}
}