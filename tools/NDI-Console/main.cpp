// BasicCmakeSetup.cpp : Defines the entry point for the application.
//

#include <iostream>

#include "NdiSourceFinder.h"
#include "NdiConnection.h"

#include <chrono>

using namespace std;
using namespace NDIReceiver;

int main()
{
	NdiSourceFinder finder;

	std::cout << "waiting for sources" << std::endl;
	auto sources = finder.findSources();

	if (sources.size() > 0)
	{
		NdiConnection con(sources[0]);

		con.open();

		auto start = std::chrono::system_clock::now();

		for (int i = 0; i < 250; i++)
		{
			auto frame = con.recv();
			/*if (frame) {
				std::cout << frame->xres << std::endl;
			}*/
		}

		auto end = std::chrono::system_clock::now();

		std::cout << 250 / std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count() << std::endl;

		con.close();
	}
	
	getchar();

	return 0;
}
