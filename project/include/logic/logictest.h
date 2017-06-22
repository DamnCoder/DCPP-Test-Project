//
//	logictest
//	DCPPTest
//
//	Created by Jorge López González on 21/06/2017 12:59:45.
//

#ifndef CLOGICTEST_H
#define CLOGICTEST_H

#include <component/component.h>
#include <component/transform.h>

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	/**
	 * \class CLogicTest
	 * \brief
	 * \author Jorge López González
	 *
	 * Description.
	 */
class CLogicTest : public CComponent
{
	// ===========================================================
	// Constant / Enums / Typedefs internal usage
	// ===========================================================
	RTTI_DECLARATIONS(CLogicTest, CComponent)
private:
	const float MOVE_SPEED = 5.f;
	const float ROTATION_SPEED = 50.f;
	// ===========================================================
	// Static fields / methods
	// ===========================================================

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Constructors
	// ===========================================================
public:
	CLogicTest(): mp_transform(0)
	{}

	~CLogicTest()
	{}
	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================
	
public:
	void Initialize() override;
	void Terminate() override;
	
	void Awake() override;
	void Start() override;
	void Update() override;
	void Finish() override;
	void Sleep() override;

	// ===========================================================
	// Methods
	// ===========================================================
	
private:
	void Left();
	void Right();
	void Up();
	void Down();
	
	void RotateXPos();
	void RotateXNeg();
	
	void Move(const math::Vector3f& direction, const float speed);
	void Rotate(const math::Vector3f& direction, const float speed);
	
	void Rotate(const float direction, const float speed);
	// ===========================================================
	// Fields
	// ===========================================================
private:
	CTransform* mp_transform;
	
	float rotationX;
};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* CLOGICTEST_H */
