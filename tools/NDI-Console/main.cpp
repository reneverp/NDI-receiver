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
    auto sources = finder.findSources(5000);

    if (sources.size() > 0)
    {
        std::cout << "found  source: " << sources[0].name << " " << sources[0].url << std::endl;
        NdiConnection con(sources[0]);
        con.open();

        ReceiverAsync asyncReceiver(mainthread, con);

        uint frameCount = 0;

        asyncReceiver.eventImage = [&](std::shared_ptr<NdiFrame> frame) {
            if (frame) {

                cv::Mat f(cv::Size(frame->xres, frame->yres), CV_8UC4, frame->data());
                
                cv::imshow("test", f);
                cv::waitKey(1);

                frameCount++;

                if (frameCount == 1)
                {
                    std::cout << (double)frame->frame_rate_N / (double)frame->frame_rate_D << "fps" << std::endl;
                }

                if (con.buffer.slotsLocked() > 1) {
                    std::cout << "More than 1 buffer slot in use:" << con.buffer.slotsLocked() << std::endl;
                }

                if (frameCount % 100 == 0)
                {
                    std::cout << "\rBuffer size:" << con.buffer.size() << std::flush;
                }
                
            }

            asyncReceiver.recvAsync();
        };


        asyncReceiver.recvAsync();

        getchar();

        asyncReceiver.stop();
        mainthread.stop();

        con.close();

    }
    else
    {
        std::cout << "no sources found within timeout" << std::endl;

    }

    return 0;
}
