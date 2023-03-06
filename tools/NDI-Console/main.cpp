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

        asyncReceiver.eventImage = [&](std::shared_ptr<NdiFrame> frame) {
            if (frame) {

                cv::Mat f(cv::Size(frame->xres, frame->yres), CV_8UC4, frame->data());

                //Looks odd, showing RGBA in BGRA, no need to convert though
                cv::imshow("test", f);

                cv::waitKey(1);
            }

            asyncReceiver.recvAsync();
        };


        asyncReceiver.recvAsync();

        getchar();

        asyncReceiver.stop();
        mainthread.stop();

        con.close();

    }

    return 0;
}
