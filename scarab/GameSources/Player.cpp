/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	�p�r: �v���C���[
	//--------------------------------------------------------------------------------------
	//�\�z
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Scale(0.5f),
		active(true),
		isGrand(true),
		m_PlayVelo(0, 0, 0),
		m_Speed(10.0f)
	{}



	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		//�L�[�{�[�h�̎擾(�L�[�{�[�h�D��)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//�O
			ret.y = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//��
			ret.x = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//���
			ret.y = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//�E
			ret.x = 1.0f;
		}
		return ret;
	}

	void Player::RotToHead(const Vec3& Velocity, float LerpFact) {
		if (LerpFact <= 0.0f) {
			//��ԌW����0�ȉ��Ȃ牽�����Ȃ�
			return;
		}
		auto ptrTransform = GetComponent<Transform>();
		//��]�̍X�V
		if (Velocity.length() > 0.0f) {
			Vec3 temp = Velocity;
			temp.normalize();
			float toAngle = atan2(temp.x, temp.z);
			Quat qt;
			qt.rotationRollPitchYawFromVector(Vec3(0, toAngle, 0));
			qt.normalize();
			//���݂̉�]���擾
			Quat nowQt = ptrTransform->GetQuaternion();
			//���݂ƖڕW����
			if (LerpFact >= 1.0f) {
				nowQt = qt;
			}
			else {
				//�N�I�[�^�j�I���̕�ԏ���
				nowQt = XMQuaternionSlerp(nowQt, qt, LerpFact);
			}
			ptrTransform->SetQuaternion(nowQt);
		}
	}
	
	Vec3 Player::GetMoveVector()const {
		Vec3 angle(0, 0, 0);
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}
		//�L�[�{�[�h�̎擾(�L�[�{�[�h�D��)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//�O
			fThumbLY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//��
			fThumbLX = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//���
			fThumbLY = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//�E
			fThumbLX = 1.0f;
		}
		
		if (fThumbLX != 0 || fThumbLY != 0) {
			float moveLength = 0;	//���������̃X�s�[�h
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//�i�s�����̌������v�Z
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//�i�s������������̊p�x���Z�o
			float frontAngle = atan2(front.z, front.x);
			//�R���g���[���̌����v�Z
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//�R���g���[���̌�������p�x���v�Z
			float cntlAngle = atan2(-moveX, moveZ);
			//�g�[�^���̊p�x���Z�o
			float totalAngle = frontAngle + cntlAngle;
			//�p�x����x�N�g�����쐬
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//���K������
			angle.normalize();
			//�ړ��T�C�Y��ݒ�B
			angle *= moveSize;
			//Y���͕ω������Ȃ�
			angle.y = 0;
		}
		return angle;
	}

	//�v���C���[�̓���
	void Player::Move() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		auto vec = GetMoveVector();
		auto ptrPs = GetComponent<RigidbodySphere>();
		m_PlayVelo = ptrPs->GetLinearVelocity();
		auto forces = GetComponent<Transform>();
		auto force = GetComponent<Rigidbody>();
		//x��z�̑��x���C��
		m_PlayVelo.x = vec.x * m_Speed;
		m_PlayVelo.z = vec.z * m_Speed;
		if (isGrand == false) {
			m_PlayVelo.y += -150.0f*App::GetApp()->GetElapsedTime();
		}
		//���x��ݒ�
		ptrPs->SetLinearVelocity(m_PlayVelo);
		m_PlayVelo = Vec3(0, 0, 0);
	}

	void Player::ChangeTrans() {
		//RigidbodySphere����Transform�ւ̃p�����[�^�̐ݒ�
		//�����I�ɐݒ�͂���Ȃ��ݒ�ɂȂ��Ă���̂Ŏ����ōs��
		auto ptrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//�ʒu���͂��̂܂ܐݒ�
		ptrTrans->SetPosition(ptrPs->GetPosition());
		//��]�̌v�Z
		Vec3 angle = GetMoveVector();
		if (angle.length() > 0.0f) {
			//��ԏ������s����]�B
			RotToHead(angle, 0.1f);
		}
	}

	//������
	void Player::OnCreate() {
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(0.5f, 0.5f, 0.5f);	//���a25�Z���`�̋���
		ptr->SetRotation(45.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0, 0.5f, 0));

		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionSphere>();

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


		//WorldMatrix�����Ƃ�RigidbodySphere�̃p�����[�^���쐬
		PsSphereParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//RigidbodySphere�R���|�[�l���g��ǉ�
		auto psPtr = AddComponent<RigidbodySphere>(param);
		//�����I��Transform��ݒ肷��t���O�͖���
		psPtr->SetAutoTransform(false);


		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//�`�悷��e�N�X�`����ݒ�
		ptrDraw->SetTextureResource(L"J_TX");

		//��������
		SetAlphaActive(true);
	}


	//�X�V
	void Player::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<Player>());
		if (active) {
			Move();
		}
	}

	//��X�V
	void Player::OnUpdate2() {
		ChangeTrans();
		//������̕\��
		//DrawStrings();
	}

	//A�{�^���n���h��
	void  Player::OnPushA() {
		active = false;	
	
		
	}


	//B�{�^���n���h��
	void  Player::OnPushB() {
		active = true;

		
	}

	


	//�R���W�����������ɓ����������̏���
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {	
		isGrand = true;
		
	}

	//�R���W�������������痣�ꂽ���̏���
	void Player::OnCollisionExit(shared_ptr<GameObject>& Other) {
		isGrand = false;
	}

	

	//������̕\��
	void Player::DrawStrings() {

		//������\��
		wstring strMess(L"B�{�^���ōēǂݍ���\n");
		//�I�u�W�F�N�g��
		auto ObjCount = GetStage()->GetGameObjectVec().size();
		wstring  strObjCount(L"OBJ_COUNT: ");
		strObjCount += Util::SizeTToWStr(ObjCount);
		auto bodyCount = GetStage()->GetBasePhysics().GetNumBodies();
		strObjCount += L", BODY_COUNT: ";
		strObjCount += Util::SizeTToWStr(bodyCount);
		strObjCount += L"\n";
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring strFps(L"FPS: ");
		strFps += Util::UintToWStr(fps);
		strFps += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		strFps += Util::FloatToWStr(ElapsedTime);
		strFps += L"\n";

		auto pos = GetComponent<Transform>()->GetPosition();
		wstring strPos(L"Position:\t");
		strPos += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		strPos += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		strPos += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";
		
		wstring boolact(L"isGrand");
		boolact +=  Util::FloatToWStr(isGrand);

		wstring str = strMess + strObjCount + strFps + strPos + boolact;
		//�����������
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}


	//--------------------------------------------------------------------------------------
	//	�v���C���[�̒Ǐ]�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	PlayerChild::PlayerChild(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_StateChangeSize(5.0f),
		m_Force(0),
		m_Velocity(0),
		active(true)
	{
	}
	PlayerChild::~PlayerChild() {}

	//������
	void PlayerChild::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetPosition(m_StartPos);
		ptrTransform->SetScale(0.25f, 0.25f, 0.25f);
		ptrTransform->SetRotation(0.0f, 5.0f, 0.0f);

		//�I�u�W�F�N�g�̃O���[�v�𓾂�
		auto group = GetStage()->GetSharedObjectGroup(L"SeekGroup");
		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<PlayerChild>());
		//Obb�̏Փ˔��������
		auto ptrColl = AddComponent<CollisionObb>();
		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();
		//WorldMatrix�����Ƃ�RigidbodySphere�̃p�����[�^���쐬
		PsSphereParam param(ptrTransform->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//RigidbodySphere�R���|�[�l���g��ǉ�
		auto psPtr = AddComponent<RigidbodySphere>(param);
		//�����I��Transform��ݒ肷��t���O�͖���
		psPtr->SetAutoTransform(false);
		//�����s��������
		auto PtrSep = GetBehavior<SeparationSteering>();
		PtrSep->SetGameObjectGroup(group);
		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		/*ptrDraw->SetMeshResource();*/
		ptrDraw->SetMeshResource(L"scarab");
		ptrDraw->SetTextureResource(L"A_TX");
		//��������������
		SetAlphaActive(true);

		//�X�e�[�g�}�V���̍\�z
		m_StateMachine.reset(new StateMachine<PlayerChild>(GetThis<PlayerChild>()));
		//�ŏ��̃X�e�[�g��SeekFarState�ɐݒ�
		m_StateMachine->ChangeState(PlayerChildFarState::Instancee());

		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		auto stage = GetStage();
		auto Plyaer = stage->GetSharedGameObject<Player>(L"Player", false);
		if (ptrCamera||!Plyaer) {
			//MyCamera�ł���
			//MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			ptrCamera->SetTargetObject(Plyaer);
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));
		}
	}



	//����
	void PlayerChild::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<PlayerChild>());
		if (active) {
			m_Force = Vec3(0);
			//�X�e�[�g�}�V����Update���s��
			//���̒��ŃX�e�[�g�̐؂�ւ����s����
			m_StateMachine->Update();
			auto ptrUtil = GetBehavior<UtilBehavior>();
			ptrUtil->RotToHead(1.0f);
		}
	}

	void PlayerChild::OnPushA() {
		SetDrawActive(false);
	}
	void PlayerChild::OnPushB() {
		SetDrawActive(true);
	}


	Vec3 PlayerChild::GetTargetPos()const {
		auto ptrTarget = GetStage()->GetSharedObject(L"Player",true);
		if (ptrTarget) {
			return ptrTarget->GetComponent<Transform>()->GetWorldPosition();
		}
	}


	void PlayerChild::ApplyForce() {
		auto trans = GetComponent<Transform>();
		auto pos = trans->GetPosition();
		auto player = GetStage()->GetSharedObject(L"Player", true);
		if (player) {
			auto playertrans = player->GetComponent<Transform>();
			auto playerpos = playertrans->GetPosition();
			Vec3 Velo = Vec3(0);
			Velo += (playerpos - pos)*5.0f;
			Velo *= 1.8f;
			pos += Velo *= App::GetApp()->GetElapsedTime();
			trans->SetPosition(pos);
		}
	}

//--------------�q�I�u�W�F�N�g�̃X�e�[�g�}�V�[��-------------------

	//--------------------------------------------------------------------------------------
	//	�v���C���[���牓���Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	shared_ptr<PlayerChildFarState> PlayerChildFarState::Instancee() {
		static shared_ptr<PlayerChildFarState> instance(new PlayerChildFarState);
		return instance;
	}
	void PlayerChildFarState::Enter(const shared_ptr<PlayerChild>& Obj) {
	}
	void PlayerChildFarState::Execute(const shared_ptr<PlayerChild>& Obj) {
		auto ptrSeek = Obj->GetBehavior<SeekSteering>();
		auto ptrSep = Obj->GetBehavior<SeparationSteering>();
		auto force = Obj->GetForce();
		force = ptrSeek->Execute(force, Obj->GetVelocity(), Obj->GetTargetPos());
		force += ptrSep->Execute(force);
		Obj->SetForce(force);
		Obj->ApplyForce();
		float f = bsm::length(Obj->GetComponent<Transform>()->GetPosition() - Obj->GetTargetPos());
		if (f < Obj->GetStateChangeSize()) {
			Obj->GetStateMachine()->ChangeState(PlayerChildNearState::Instance());
		}
	}

	void PlayerChildFarState::Exit(const shared_ptr<PlayerChild>& Obj) {

	}

	//--------------------------------------------------------------------------------------
	//	�v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	shared_ptr<PlayerChildNearState> PlayerChildNearState::Instance() {
		static shared_ptr<PlayerChildNearState> instance(new PlayerChildNearState);
		return instance;
	}
	void PlayerChildNearState::Enter(const shared_ptr<PlayerChild>& Obj) {
		
	}
	void PlayerChildNearState::Execute(const shared_ptr<PlayerChild>& Obj) {
		float f = bsm::length(Obj->GetComponent<Transform>()->GetPosition() - Obj->GetTargetPos());
		if (f >= Obj->GetStateChangeSize()) {
			Obj->GetStateMachine()->ChangeState(PlayerChildFarState::Instancee());
		}
		else {
			Obj->GetStateMachine()->ChangeState(PlayerChildStayState::Instance());
		}
	}
	void PlayerChildNearState::Exit(const shared_ptr<PlayerChild>& Obj) {

	}

//--------------------------------------------------------------------------------------
//	�v���C���[�ɂ��Ă鎞�̍s��
//--------------------------------------------------------------------------------------
	shared_ptr<PlayerChildStayState> PlayerChildStayState::Instance() {
		static shared_ptr<PlayerChildStayState> instance(new PlayerChildStayState);
		return instance;
	}
	void PlayerChildStayState::Enter(const shared_ptr<PlayerChild>& Obj) {

	}
	void PlayerChildStayState::Execute(const shared_ptr<PlayerChild>& Obj) {
		Obj->ApplyForce();

	}
	void PlayerChildStayState::Exit(const shared_ptr<PlayerChild>& Obj) {

	}





}
//end basecross



