//
//  main.cpp
//  dcpp
//
//  Created by Jorge López on 10/10/15.
//  Copyright © 2015 Jorge López. All rights reserved.
//

#include "testgame.h"

#include <cstdio>

using namespace dc;

int main(int argc, const char * argv[])
{
	printf("Creating app\n");
	CApp* app = CApp::New<CTestGameApp>();
	
	printf("Running app\n");
    app->Run();

	CApp::Destroy();
	
    return 0;
}
