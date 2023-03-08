#include "ReceiverAsync.h"

using namespace NDIReceiver;

ReceiverAsync::ReceiverAsync
(
    Thread&         threadMain, 
    NdiConnection&  connection
):
    threadMain      (threadMain),
    connection      (connection)
{
}

void ReceiverAsync::recvAsync()
{
    threadBackground.executeAsync([this] 
    {
        auto frame = connection.recv();

        threadMain.executeAsync([this, frame] 
        {
            if (eventImage) eventImage(frame);
        });
    });
}

void ReceiverAsync::stop()
{
    threadBackground.stop();
}
