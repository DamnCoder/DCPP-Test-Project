//
//  testgame.hpp
//  dcpp
//
//  Created by Jorge López on 21/4/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef testgame_hpp
#define testgame_hpp

#include "app.h"

#include <map>
#include <signals/signal.h>
#include <help/callbacks.h>

namespace dc
{
	class CTestGameApp : public CApp
	{
		friend class CSingleton<CApp>;
	protected:
		CTestGameApp() {}
		~CTestGameApp() {}

	public:
		void Create()		override;
		void Configure()	override;

	private:
		void ExitApp();
		
		void Load();
		
		TAction pressAction;
		TAction releaseAction;
		TAction releaseToEraseAction;
		TAction closeAction;
	};
}

#endif /* testgame_hpp */
