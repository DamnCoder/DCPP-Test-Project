/*
 * testhfsm.h
 *
 *  Created on: 24 de abr. de 2016
 *      Author: jorge
 */

#ifndef TESTHFSM_H_
#define TESTHFSM_H_

#include "subsystem/hfsmsubsystem.h"

namespace dc
{
	class CTestHFSM : public CHFSMSubsystem
	{
	public:
		CTestHFSM() {}
		virtual ~CTestHFSM() {}

	public:
		void CreateStates() override;
	};
}

#endif /* TESTHFSM_H_ */
