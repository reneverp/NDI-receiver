#pragma once

#include "source.h"
#include "frame.h"
#include "FrameBuffer.h"

#include <memory>

namespace cv { class Mat; }

namespace NDIReceiver 
{

class NdiConnection 
{
public:
    enum class State 
    {
        Valid,
        Invalid
    };
    
    explicit                     NdiConnection  (const NdiSource& source);
    virtual                     ~NdiConnection  ();

    void                        open            ();
    std::shared_ptr<NdiFrame>   recv            ();
    void                        close           ();

    State                       state           ();

public:
    FrameBuffer                 buffer;

private:
    State                       currentState;
    const NdiSource             source;
    void*                       connection;

    std::unique_ptr<cv::Mat>    matUYVY;
    std::unique_ptr<cv::Mat>    matRGB;

private:
    NdiConnection             (NdiConnection const&)    = delete;
    NdiConnection& operator=  (NdiConnection const&)    = delete;
    NdiConnection             (NdiConnection&&)         = delete;
    NdiConnection& operator=  (NdiConnection&&)         = delete;

};

};
