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

int main(int argc, char* argv[])
{
    int width = 0;
    int height = 0;
    bool writeVideo = false;

    if (argc == 2)
    {
        writeVideo = true;

        if (std::string(argv[1]) == "1") width = 1280, height = 1024; else
        if (std::string(argv[1]) == "2") width = 1600, height = 1200; else
        if (std::string(argv[1]) == "3") width = 1920, height = 1080; 
        else
        {
            std::cout << "usage: NDI-receiver [mode (for writing video out)] : modes (1 = 1280x1024, 2=1600x1200, 3=1920x1080)" << std::endl;  
            return -1;
        }

    }

    Thread mainthread;
    NdiSourceFinder finder;

    cv::VideoWriter writer("test.avi", 0, 30, cv::Size(width, height));

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

                if (writeVideo)
                {
                    cv::Mat b(cv::Size(frame->xres, frame->yres), CV_8UC3);

                    cv::cvtColor(f, b, cv::COLOR_BGRA2BGR);
                    writer.write(b);
                }

                cv::imshow("test", f);
                cv::waitKey(1);

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
