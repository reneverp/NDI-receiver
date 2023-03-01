// BasicCmakeSetup.cpp : Defines the entry point for the application.
//

#include <iostream>

#include "Receiver.h"

using namespace std;
using namespace NDIReceiver;

int main()
{

	Receiver r;

	r.start();

	getchar();

	return 0;
}
