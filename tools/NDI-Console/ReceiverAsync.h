#pragma once

#include "Thread.h"
#include "frame.h"

#include "NdiConnection.h"

namespace NDIReceiver {
    class ReceiverAsync {
    public:
        ReceiverAsync(Thread &mainThread, NdiConnection &ndiConnection);
        virtual ~ReceiverAsync();

        void recvAsync();
        void stop();

        std::function<void(std::shared_ptr<NdiFrame>)> eventImage;

    private:
        NdiConnection &connection;

        Thread background;
        Thread &mainThread;


    };

};