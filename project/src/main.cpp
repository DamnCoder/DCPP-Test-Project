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
	CApp* app = new CTestGameApp();

	printf("Running app\n");
    app->Run();

    delete app;
    app = 0;

    return 0;
}
