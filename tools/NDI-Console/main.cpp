// BasicCmakeSetup.cpp : Defines the entry point for the application.
//

#include <iostream>

#include "NdiSourceFinder.h"
#include "NdiConnection.h"

#include <chrono>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Thread.h"
#include "ReceiverAsync.h"

using namespace std;
using namespace NDIReceiver;

int main()
{
	Thread mainthread;
	NdiSourceFinder finder;

	std::cout << "waiting for sources" << std::endl;
	auto sources = finder.findSources();

	if (sources.size() > 0)
	{
		NdiConnection con(sources[0]);
		con.open();

		ReceiverAsync asyncReceiver(mainthread, con);

		//auto start = std::chrono::system_clock::now();

		cv::Mat f(720, 1280, CV_8UC2);
		cv::Mat bgrFrame(720, 1280, CV_8UC3);


		asyncReceiver.eventImage = [&](std::shared_ptr<NdiFrame> frame) {
			if (frame) {

				f.data = frame->p_data->buffer.data();
				cv::cvtColor(f, bgrFrame, cv::COLOR_YUV2BGR_UYVY, 0);

				cv::imshow("test", bgrFrame);

				cv::waitKey(1);
			}

			asyncReceiver.recvAsync();
		};


		asyncReceiver.recvAsync();


		//auto end = std::chrono::system_clock::now();

		//std::cout << 250 / std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count() << std::endl;

		getchar();

		asyncReceiver.stop();
		mainthread.stop();

		con.close();

	}

	return 0;
}
