/*!
@file ProjectShader.cpp
@brief プロジェクトで使用するシェーダー実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ーーーーーーーーーーーーーーーーーーーーーー遅い敵（フンコロガシ）ーーーーーーーーーーーーーーーーーーーーーーーー
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	Enemy_Low::Enemy_Low(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& strPos,
		const Vec3& tagePos
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Pos(strPos),
		m_targetPos(tagePos)
	{}

	Enemy_Low::~Enemy_Low(){}

	void Enemy_Low::OnCreate(){

		SetState();

		auto ptrTransform = GetComponent<Transform>();

		ptrTransform->SetScale(Vec3(m_Scale));
		ptrTransform->SetPosition(m_Pos);

		//当たり判定
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetFixed(true);

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"scarab");
		ptrDraw->SetOwnShadowActive(true);
		//ptrDraw->SetTextureResource(L"SKY_TX");

		//物理計算球体
		//WorldMatrixをもとにRigidbodySphereのパラメータを作成
		PsSphereParam param(ptrTransform->GetWorldMatrix(), 1.0f, true, PsMotionType::MotionTypeActive);
		auto PsPtr = AddComponent<RigidbodySphere>(param);

	}

	void Enemy_Low::SetState() {
		m_Speed = 0.5f;
		m_SeekSpeed = 3.0f;
		m_initial = 0.0f;
		m_strPos = m_Pos;
		s_balance = m_sqrt((m_targetPos.x - m_strPos.x) * (m_targetPos.x - m_strPos.x));//スタートとターゲットのプラスの差を求める
		v_balance = m_sqrt((m_targetPos.z - m_strPos.z) * (m_targetPos.z - m_strPos.z));
		m_side = 0;
		m_vertical = 0;
		moveflag = true;
		m_walkflg = false;

		//横方向の判定
		if (m_strPos.x == m_targetPos.x) {
		}
		else if (m_strPos.x < m_targetPos.x) {
			m_side = 1;
			s_case = 1;
		}
		else {
			m_side = 2;
			s_case = 2;
		}
		//縦方向の判定
		if (m_strPos.z == m_targetPos.z) {
		}
		else if (m_strPos.z < m_targetPos.z) {
			m_vertical = 1;
			v_case = 1;
		}
		else {
			m_vertical = 2;
			v_case = 2;
		}
		m_strvertical = m_vertical;
		m_strside = m_side;
	}

	void Enemy_Low::OnUpdate() {
		MoveChange();
	}

	void Enemy_Low::OnUpdate2() {
		auto ptrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//位置情報はそのまま設定
		ptrTrans->SetPosition(ptrPs->GetPosition());
		auto ro = ptrTrans->GetRotation();
		auto enePos = ptrTrans->GetPosition();
		ro = Vec3(0.f, 0.f, 0.f);
		ro = Vec3(sin(enePos.x), 0.0f, cos(enePos.z));
		ptrTrans->SetRotation(ro);
	} 

	void Enemy_Low::MoveChange() {
		//playerをとってくる
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player", true);
		if (player) {
			auto playerPos = player->GetComponent<Transform>()->GetPosition();
			m_playerPos = playerPos;
		}

		//エネミーの位置をとってくる
		auto bodyComp = GetComponent<RigidbodySphere>();
		auto eneComp = GetComponent<Transform>();
		auto enePos = eneComp->GetPosition();

		//敵の向きをとってくる
		auto pointview = this->GetComponent<Transform>()->GetQuaternion();

		//プレイヤーとの距離を見て行動を変える
		if ((Vec3(enePos.x, 0.0f, enePos.z) - Vec3(m_playerPos.x, 0.0f, m_playerPos.z)).length() < 3.0f) {
			m_walkflg = true;
			Seek();
		} else if(m_walkflg == true && (Vec3(m_strPos.x, 0.0f, m_strPos.z) - Vec3(enePos.x, 0.0f, enePos.z)).length()){
			auto bodyComp = GetComponent<RigidbodySphere>();
			auto eneComp = GetComponent<Transform>();
			auto enePos = eneComp->GetPosition();
			p_balance = m_strPos - enePos;
			p_balance.y = 0.0f;
			enePos += p_balance.normalize() * m_SeekSpeed * App::GetApp()->GetElapsedTime();
			float len = (Vec3(m_strPos.x, 0.0f, m_strPos.z) - Vec3(enePos.x, 0.0f, enePos.z)).length();
			if (m_sqrt(len * len) < 0.5f) {
				m_strPos.y = enePos.y;
				enePos = m_strPos; 
				m_vertical = m_strvertical;
				m_side = m_strside;
				m_walkflg = false;
			}
			bodyComp->SetPosition(enePos);
		}
		else {
			Walk();
		}
	}

	void Enemy_Low::Horizon() {

	}

	void Enemy_Low::Seek() {
		auto bodyComp = GetComponent<RigidbodySphere>();
		auto eneComp = GetComponent<Transform>();
		auto enePos = eneComp->GetPosition();
		p_balance = m_playerPos - enePos;
		p_balance.y = 0.0f;
		enePos += p_balance.normalize() * m_SeekSpeed * App::GetApp()->GetElapsedTime();
		bodyComp->SetPosition(enePos);
	}

	void Enemy_Low::Walk() {
	//ゴールのポジションの縦が一緒なら一方鋼に動く
	//違うなら先に横ｘの移動をしてから縦ｙの移動をする
		auto bodyComp = GetComponent<RigidbodySphere>();
		auto eneComp = GetComponent<Transform>();
		auto enePos = eneComp->GetPosition();
		if (m_strPos.x == m_targetPos.x) {
			//縦の移動
			switch (m_vertical) {
			case 0:
				break;
			case 1:
				enePos.z += m_Speed * App::GetApp()->GetElapsedTime();
				bodyComp->SetPosition(enePos);
				if (v_case == 1 && v_balance < m_sqrt((m_strPos.z - enePos.z) * (m_strPos.z - enePos.z))) {
					m_vertical = 2;
				}
				if (v_case == 2 && v_balance < m_sqrt((m_targetPos.z - enePos.z) * (m_targetPos.z - enePos.z))) {
					m_vertical = 2;
				}
				break;
			case 2:
				enePos.z -= m_Speed * App::GetApp()->GetElapsedTime();
				bodyComp->SetPosition(enePos);
				if (v_case == 1 && v_balance < m_sqrt((m_targetPos.z - enePos.z) * (m_targetPos.z - enePos.z))) {
					m_vertical = 1;
				}
				if (v_case == 2 && v_balance < m_sqrt((m_strPos.z - enePos.z) * (m_strPos.z - enePos.z))) {
					m_vertical = 1;
				}
				break;
			}
		} else if (m_strPos.z == m_targetPos.z) {
			//横の移動
			switch (m_side) {
			case 0:
				break;
			case 1:
				enePos.x += m_Speed * App::GetApp()->GetElapsedTime();
				bodyComp->SetPosition(enePos);
				if (s_case == 1 && s_balance < m_sqrt((m_strPos.x - enePos.x) * (m_strPos.x - enePos.x))) {
					m_side = 2;
				}
				if (s_case == 2 && s_balance < m_sqrt((m_targetPos.x - enePos.x) * (m_targetPos.x - enePos.x))) {
					m_side = 2;
				}
				break;
			case 2:
				enePos.x -= m_Speed * App::GetApp()->GetElapsedTime();
				bodyComp->SetPosition(enePos);
				if (s_case == 1 && s_balance < m_sqrt((m_targetPos.x - enePos.x) * (m_targetPos.x - enePos.x))) {
					m_side = 1;
				}
				if (s_case == 2 && s_balance < m_sqrt((m_strPos.x - enePos.x) * (m_strPos.x - enePos.x))) {
					m_side = 1;
				}
				break;
			}
		} else {
			if (moveflag == true) {
				if (s_case == 1 && v_case == 1) {//横プラス、縦プラス
					spin_case = 1;
					m_spin = 1;
				}
				if (s_case == 1 && v_case == 2) {//横プラス、縦マイナス
					spin_case = 2;
					m_spin = 2;
				}
				if (s_case == 2 && v_case == 1) {//横マイナス、縦プラス
					spin_case = 3;
					m_spin = 3;
				}
				if (s_case == 2 && v_case == 2) {//横マイナス、縦マイナス
					spin_case = 4;
					m_spin = 4;
				}
				moveflag = false;
			}

			//四角形を描いて移動
			switch (m_spin) {
			case 0:
				break;
			case 1:
				enePos.z += m_Speed * App::GetApp()->GetElapsedTime();
				bodyComp->SetPosition(enePos);
				if (spin_case == 1 && v_balance < m_sqrt((m_strPos.z - enePos.z) * (m_strPos.z - enePos.z))) {
					m_spin = 2;
				}
				if (spin_case == 2 && v_balance < m_sqrt((m_targetPos.z - enePos.z) * (m_targetPos.z - enePos.z))) {
					m_spin = 2;
				}
				if (spin_case == 3 && v_balance < m_sqrt((m_strPos.z - enePos.z) * (m_strPos.z - enePos.z))) {
					m_spin = 2;
				}
				if (spin_case == 4 && v_balance < m_sqrt((m_targetPos.z - enePos.z) * (m_targetPos.z - enePos.z))) {
					m_spin = 4;
				}
				break;
			case 2:
				enePos.x += m_Speed * App::GetApp()->GetElapsedTime();
				bodyComp->SetPosition(enePos);
				if (spin_case == 1 && s_balance < m_sqrt((m_strPos.x - enePos.x) * (m_strPos.x - enePos.x))) {
					m_spin = 3;
				}
				if (spin_case == 2 && s_balance < m_sqrt((m_strPos.x - enePos.x) * (m_strPos.x - enePos.x))) {
					m_spin = 3;
				}
				if (spin_case == 3 && s_balance < m_sqrt((m_targetPos.x - enePos.x) * (m_targetPos.x - enePos.x))) {
					m_spin = 3;
				}
				if (spin_case == 4 && s_balance < m_sqrt((m_targetPos.x - enePos.x) * (m_targetPos.x - enePos.x))) {
					m_spin = 1;
				}
				break;
			case 3:
				enePos.z -= m_Speed * App::GetApp()->GetElapsedTime();
				bodyComp->SetPosition(enePos);
				if (spin_case == 1 && v_balance < m_sqrt((m_targetPos.z - enePos.z) * (m_targetPos.z - enePos.z))) {
					m_spin = 4;
				}
				if (spin_case == 2 && v_balance < m_sqrt((m_strPos.z - enePos.z) * (m_strPos.z - enePos.z))) {
					m_spin = 4;
				}
				if (spin_case == 3 && v_balance < m_sqrt((m_targetPos.z - enePos.z) * (m_targetPos.z - enePos.z))) {
					m_spin = 4;
				}
				if (spin_case == 4 && v_balance < m_sqrt((m_strPos.z - enePos.z) * (m_strPos.z - enePos.z))) {
					m_spin = 2;
				}
				break;
			case 4:
				enePos.x -= m_Speed * App::GetApp()->GetElapsedTime();
				bodyComp->SetPosition(enePos);
				if (spin_case == 1 && s_balance < m_sqrt((m_targetPos.x - enePos.x) * (m_targetPos.x - enePos.x))) {
					m_spin = 1;
				}
				if (spin_case == 2 && s_balance < m_sqrt((m_targetPos.x - enePos.x) * (m_targetPos.x - enePos.x))) {
					m_spin = 1;
				}
				if (spin_case == 3 && s_balance < m_sqrt((m_strPos.x - enePos.x) * (m_strPos.x - enePos.x))) {
					m_spin = 1;
				}
				if (spin_case == 4 && s_balance < m_sqrt((m_strPos.x - enePos.x) * (m_strPos.x - enePos.x))) {
					m_spin = 3;
				}
				break;
			}
		}
	}


	float Enemy_Low::m_sqrt(float s)
	{
		float x = s / 2.0f;
		float last_x = 0.0f;

		while (x != last_x)
		{
			last_x = x;
			x = (x + s / x) / 2.0f;
		}
		return x;
	}
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ーーーーーーーーーーーーーーーーーーーーーー早い敵+（爬虫類）ーーーーーーーーーーーーーーーーーーーーーーーーーー
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

}
//end basecross


/*

未来の自分へ

これを読むころにはとても大変な思いをしていると思います。
それでも、たとえ少しずつだとしても前に進むことを忘れないでください。
それでもきつくなった時にはVtuberの動画を見て心を癒してください。
そしてこの後書くことを絶対に実行してください
・敵の視界つける
・足の速い敵を作る
　（その時にプレイヤーが弾に入っているかの判定を忘れないでください）
 つらいこともあるかもしれないけど頑張ってください
 それと時間があればでいいので
 子クラスと親クラスを作ることをお勧めします
 それじゃまた後で

 　　　　　　　　　　　　　　　　　　　　過去の自分より
*/