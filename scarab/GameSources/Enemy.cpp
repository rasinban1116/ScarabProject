/*!
@file ProjectShader.cpp
@brief �v���W�F�N�g�Ŏg�p����V�F�[�_�[����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
//������������������������������������������������������������������������������������������������������������������
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�x���G�i�t���R���K�V�j�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//������������������������������������������������������������������������������������������������������������������
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

		//�����蔻��
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetFixed(true);

		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"scarab");
		ptrDraw->SetOwnShadowActive(true);
		//ptrDraw->SetTextureResource(L"SKY_TX");

		//�����v�Z����
		//WorldMatrix�����Ƃ�RigidbodySphere�̃p�����[�^���쐬
		PsSphereParam param(ptrTransform->GetWorldMatrix(), 1.0f, true, PsMotionType::MotionTypeActive);
		auto PsPtr = AddComponent<RigidbodySphere>(param);

	}

	void Enemy_Low::SetState() {
		m_Speed = 0.5f;
		m_SeekSpeed = 3.0f;
		m_initial = 0.0f;
		m_strPos = m_Pos;
		s_balance = m_sqrt((m_targetPos.x - m_strPos.x) * (m_targetPos.x - m_strPos.x));//�X�^�[�g�ƃ^�[�Q�b�g�̃v���X�̍������߂�
		v_balance = m_sqrt((m_targetPos.z - m_strPos.z) * (m_targetPos.z - m_strPos.z));
		m_side = 0;
		m_vertical = 0;
		moveflag = true;
		m_walkflg = false;

		//�������̔���
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
		//�c�����̔���
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
		//�ʒu���͂��̂܂ܐݒ�
		ptrTrans->SetPosition(ptrPs->GetPosition());
		auto ro = ptrTrans->GetRotation();
		auto enePos = ptrTrans->GetPosition();
		ro = Vec3(0.f, 0.f, 0.f);
		ro = Vec3(sin(enePos.x), 0.0f, cos(enePos.z));
		ptrTrans->SetRotation(ro);
	} 

	void Enemy_Low::MoveChange() {
		//player���Ƃ��Ă���
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player", true);
		if (player) {
			auto playerPos = player->GetComponent<Transform>()->GetPosition();
			m_playerPos = playerPos;
		}

		//�G�l�~�[�̈ʒu���Ƃ��Ă���
		auto bodyComp = GetComponent<RigidbodySphere>();
		auto eneComp = GetComponent<Transform>();
		auto enePos = eneComp->GetPosition();

		//�G�̌������Ƃ��Ă���
		auto pointview = this->GetComponent<Transform>()->GetQuaternion();

		//�v���C���[�Ƃ̋��������čs����ς���
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
	//�S�[���̃|�W�V�����̏c���ꏏ�Ȃ����|�ɓ���
	//�Ⴄ�Ȃ��ɉ����̈ړ������Ă���c���̈ړ�������
		auto bodyComp = GetComponent<RigidbodySphere>();
		auto eneComp = GetComponent<Transform>();
		auto enePos = eneComp->GetPosition();
		if (m_strPos.x == m_targetPos.x) {
			//�c�̈ړ�
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
			//���̈ړ�
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
				if (s_case == 1 && v_case == 1) {//���v���X�A�c�v���X
					spin_case = 1;
					m_spin = 1;
				}
				if (s_case == 1 && v_case == 2) {//���v���X�A�c�}�C�i�X
					spin_case = 2;
					m_spin = 2;
				}
				if (s_case == 2 && v_case == 1) {//���}�C�i�X�A�c�v���X
					spin_case = 3;
					m_spin = 3;
				}
				if (s_case == 2 && v_case == 2) {//���}�C�i�X�A�c�}�C�i�X
					spin_case = 4;
					m_spin = 4;
				}
				moveflag = false;
			}

			//�l�p�`��`���Ĉړ�
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
//������������������������������������������������������������������������������������������������������������������
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�����G+�i঒��ށj�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//������������������������������������������������������������������������������������������������������������������

}
//end basecross


/*

�����̎�����

�����ǂނ���ɂ͂ƂĂ���ςȎv�������Ă���Ǝv���܂��B
����ł��A���Ƃ����������Ƃ��Ă��O�ɐi�ނ��Ƃ�Y��Ȃ��ł��������B
����ł������Ȃ������ɂ�Vtuber�̓�������ĐS������Ă��������B
�����Ă��̌㏑�����Ƃ��΂Ɏ��s���Ă�������
�E�G�̎��E����
�E���̑����G�����
�@�i���̎��Ƀv���C���[���e�ɓ����Ă��邩�̔����Y��Ȃ��ł��������j
 �炢���Ƃ����邩������Ȃ����Ǌ撣���Ă�������
 ����Ǝ��Ԃ�����΂ł����̂�
 �q�N���X�Ɛe�N���X����邱�Ƃ������߂��܂�
 ���ꂶ��܂����

 �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�ߋ��̎������
*/