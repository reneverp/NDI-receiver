#include "ReceiverAsync.h"
#include <NdiSourceFinder.h>
#include <NdiConnection.h>

#include <Thread.h>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace NDIReceiver;

int main()
{
    std::cout << "waiting for sources" << std::endl;
    
    auto mainthread = Thread{};
    auto finder     = NdiSourceFinder{};
    auto sources    = finder.findSources(5000);

    if (sources.empty()) 
    {
        std::cout << "no sources found within timeout" << std::endl;
        return 0;
    }

    std::cout << "found source: " << sources[0].name << " " << sources[0].url << std::endl;

    auto connection = NdiConnection{sources[0]};
    auto reciever   = ReceiverAsync{mainthread, connection};

    connection.open();
    uint frameCount = 0;

    reciever.eventImage = [&frameCount, &connection, &reciever](std::shared_ptr<NdiFrame> frame) 
    {
        if (!frame) return;

        ++frameCount;
        auto f = cv::Mat{cv::Size(frame->xres, frame->yres), CV_8UC4, frame->data()};
                
        cv::imshow("test", f);
        cv::waitKey(1);

        if (frameCount == 1)                        std::cout << (double)frame->frame_rate_N / (double)frame->frame_rate_D << "fps" << std::endl;
        if (connection.buffer.slotsLocked() > 1)    std::cout << "More than 1 buffer slot in use:" << connection.buffer.slotsLocked() << std::endl;
        if (frameCount % 100 == 0)                  std::cout << "\rBuffer size:" << connection.buffer.size() << std::flush;

        reciever.recvAsync();
    };

    reciever.recvAsync();

    getchar();

    reciever  .stop();
    mainthread.stop();
    connection.close();

    return 0;
}