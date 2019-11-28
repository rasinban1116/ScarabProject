/*!
@file ProjectShader.h
@brief �v���W�F�N�g�Ŏg�p����V�F�[�_�[
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Enemy_Low : public GameObject {
		Vec3 m_Scale; //�傫��
		Vec3 m_Pos; //�ʒu
		float m_Speed; //�����X�s�[�h
		float m_SeekSpeed;
		Vec3 m_playerPos; //�v���C���[�̈ʒu
		Vec3 m_targetPos; //�ړI�n
		Vec3 m_strPos; //�ŏ��̈ʒu

		bool m_walkflg;//���񂷂�ꏊ�ɂ��邩�ǂ���

		Vec3 p_balance;// �v���C���[�Ƃ̋���

		int horizoncase;//�ǂ̍s�����s�킹�邩


		int m_vertical;//���E�ǂ���ɐi�ނ�
		int m_side; //�㉺�ǂ���ɐi�ނ�
		int m_strvertical;
		int m_strside;
		float m_initial; //���̐ݒ�
		float s_balance; //���̍�
		float v_balance; //�c�̍�
		int s_case; //�ǂ�������ǂ����ɐi�ނ�
		int v_case;
		bool moveflag; //UpDate�ň�񂾂������
		int m_spin; //�X�^�[�g�̈ʒu
		int spin_case; //�ǂ�����肩

	public : 
		Enemy_Low(const shared_ptr<Stage>& StagePtr, 
			const Vec3& Scale,
			const Vec3& strPos,
			const Vec3& tagePos);
		virtual ~Enemy_Low();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		void SetState();
		void MoveChange();
		void Seek();
		void Walk();
		void Horizon();
		float m_sqrt(float s);
	};
	



	//class Enemy_Horizon : public Enemy_Low {
	//		Vec3 m_Scale;
	//		Quat m_Qt;
	//		Vec3 m_Position;
	//	public:
	//		//�\�z�Ɣj��
	//		Enemy_Horizon(const shared_ptr<Stage>& StagePtr,
	//			const Vec3& Scale,
	//			const Quat& Qt,
	//			const Vec3& Position
	//		);
	//		virtual ~Enemy_Horizon();
	//		//������
	//		virtual void OnCreate() override;
	//		virtual void OnUpdate() override;
	//};
}
//end basecross

