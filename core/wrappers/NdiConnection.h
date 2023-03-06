#pragma once

#include "source.h"
#include "frame.h"
#include "FrameBuffer.h"

#include <memory>

namespace cv {
    class Mat;
}

namespace NDIReceiver {

    class NdiConnection {

    public:
        enum class State {
            Valid,
            Invalid
        };

                                    NdiConnection   (const NdiSource& source);
        virtual                     ~NdiConnection  ();

        void                        open            ();
        std::shared_ptr<NdiFrame>   recv            ();
        void                        close           ();

        State                       state           ();

        NdiConnection(NdiConnection&)                   = delete;
        NdiConnection& operator=(NdiConnection const&)  = delete;

    private:
        State                       currentState;
        const NdiSource             source;
        void*                       connection;

        FrameBuffer                 buffer;

        std::unique_ptr<cv::Mat>    matUYVY;
        std::unique_ptr<cv::Mat>    matRGB;

    };

};
