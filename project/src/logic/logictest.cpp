//
//	logictest
//	DCPPTest
//
//	Created by Jorge López González on 21/06/2017 12:59:45.
//

#include "logictest.h"

#include <app.h>
#include <component/gameobject.h>
#include <subsystem/inputsubsystem.h>
#include <subsystem/timesubsystem.h>

namespace dc
{
	void CLogicTest::Initialize()
	{
		mp_transform = GameObject()->GetComponent<CTransform>();
		auto* inputSubsystem = CApp::Pointer()->GetSubsystem<CInputSubsystem>();
		
		rotationX = 0.f;
		
		auto* keyInputManager = inputSubsystem->KeyInputManager();
		
		keyInputManager->GetSignal(EKeyState::PRESS, SDLK_LEFT)->Connect(this, &CLogicTest::Left);
		keyInputManager->GetSignal(EKeyState::HOLD, SDLK_LEFT)->Connect(this, &CLogicTest::Left);
		
		keyInputManager->GetSignal(EKeyState::PRESS, SDLK_RIGHT)->Connect(this, &CLogicTest::Right);
		keyInputManager->GetSignal(EKeyState::HOLD, SDLK_RIGHT)->Connect(this, &CLogicTest::Right);
		
		keyInputManager->GetSignal(EKeyState::PRESS, SDLK_UP)->Connect(this, &CLogicTest::Up);
		keyInputManager->GetSignal(EKeyState::HOLD, SDLK_UP)->Connect(this, &CLogicTest::Up);
		
		keyInputManager->GetSignal(EKeyState::PRESS, SDLK_DOWN)->Connect(this, &CLogicTest::Down);
		keyInputManager->GetSignal(EKeyState::HOLD, SDLK_DOWN)->Connect(this, &CLogicTest::Down);
		
		keyInputManager->GetSignal(EKeyState::PRESS, '+')->Connect(this, &CLogicTest::Forward);
		keyInputManager->GetSignal(EKeyState::HOLD, '+')->Connect(this, &CLogicTest::Forward);
		
		keyInputManager->GetSignal(EKeyState::PRESS, '`')->Connect(this, &CLogicTest::Backward);
		keyInputManager->GetSignal(EKeyState::HOLD, '`')->Connect(this, &CLogicTest::Backward);
		
		keyInputManager->GetSignal(EKeyState::PRESS, 'a')->Connect(this, &CLogicTest::RotateXPos);
		keyInputManager->GetSignal(EKeyState::HOLD, 'a')->Connect(this, &CLogicTest::RotateXPos);
		
		keyInputManager->GetSignal(EKeyState::PRESS, 'd')->Connect(this, &CLogicTest::RotateXNeg);
		keyInputManager->GetSignal(EKeyState::HOLD, 'd')->Connect(this, &CLogicTest::RotateXNeg);
	}
	
	void CLogicTest::Terminate()
	{
		
	}
	
	void CLogicTest::Awake()
	{
		
	}
	
	void CLogicTest::Start()
	{
		
	}
	
	void CLogicTest::Update()
	{
		
	}
	
	void CLogicTest::Finish()
	{
		
	}
	
	void CLogicTest::Sleep()
	{
		
	}
	
	void CLogicTest::Left()
	{
		Move(math::Vector3f::Left(), MOVE_SPEED);
	}
	
	void CLogicTest::Right()
	{
		Move(math::Vector3f::Right(), MOVE_SPEED);
	}
	
	void CLogicTest::Up()
	{
		Move(math::Vector3f::Up(), MOVE_SPEED);
	}
	
	void CLogicTest::Down()
	{
		Move(math::Vector3f::Down(), MOVE_SPEED);
	}
	
	void CLogicTest::Forward()
	{
		Move(math::Vector3f::Front(), MOVE_SPEED);
	}
	
	void CLogicTest::Backward()
	{
		Move(math::Vector3f::Back(), MOVE_SPEED);
	}
	
	void CLogicTest::Move(const math::Vector3f& direction, const float speed)
	{
		const float dt = CTimeSubsystem::Timer().DT();
		math::Vector3f position = mp_transform->LocalPosition();
		
		position += direction * speed * dt;
		
		mp_transform->Position(position);
	}
	
	void CLogicTest::RotateXPos()
	{
		//Rotate(math::Vector3f::Left(), ROTATION_SPEED);
		Rotate(1.f, ROTATION_SPEED);
	}
	
	void CLogicTest::RotateXNeg()
	{
		//Rotate(math::Vector3f::Right(), ROTATION_SPEED);
		Rotate(-1.f, ROTATION_SPEED);
	}
	
	void CLogicTest::RotateYPos()
	{
		//Rotate(math::Vector3f::Left(), ROTATION_SPEED);
		Rotate(1.f, ROTATION_SPEED);
	}
	
	void CLogicTest::RotateYNeg()
	{
		//Rotate(math::Vector3f::Right(), ROTATION_SPEED);
		Rotate(-1.f, ROTATION_SPEED);
	}
	
	void CLogicTest::Rotate(const math::Vector3f& direction, const float speed)
	{
		const float dt = CTimeSubsystem::Timer().DT();
		
		math::Quaternionf rotation = mp_transform->LocalMatrix().Rotation();
		math::Vector3f eulerRotationStep = direction * speed * dt;
		
		math::Quaternionf rotationStep = math::Quaternionf::FromEulerRad(eulerRotationStep * math::DC_PI_OVER_180);
		
		mp_transform->Rotation(rotation * rotationStep);
	}
	
	void CLogicTest::Rotate(const float direction, const float speed)
	{
		const float dt = CTimeSubsystem::Timer().DT();

		rotationX += direction * speed * dt;
		
		math::Quaternionf rotation = math::Quaternionf::FromEulerRad(0.f, math::DegToRad(rotationX), 0.f);
		
		mp_transform->Rotation(rotation);

	}
}
