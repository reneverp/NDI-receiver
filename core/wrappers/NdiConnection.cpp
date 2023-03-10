#include "NdiConnection.h"

#include <Processing.NDI.Lib.h>
#include <opencv2/imgproc.hpp>

using namespace NDIReceiver;

NdiConnection::NdiConnection(const NdiSource& s) :
    source          (s),
    connection      (nullptr),
    currentState    (State::Invalid)
{
}

NdiConnection::~NdiConnection()
{
    close();
}

void NdiConnection::open()
{
    connection = NDIlib_recv_create_v3();
    if (!connection) return;

    auto s = NDIlib_source_t{source.name.c_str(), source.url.c_str()};

    // Connect to our sources
    NDIlib_recv_connect(reinterpret_cast<NDIlib_recv_instance_t>(connection), &s);
}

std::shared_ptr<NdiFrame> NdiConnection::recv()
{
    auto frame       = std::shared_ptr<NdiFrame>{};
    auto video_frame = NDIlib_video_frame_v2_t{}; // only interested in video frames
    auto frame_type  = NDIlib_recv_capture_v3(reinterpret_cast<NDIlib_recv_instance_t>(connection), &video_frame, nullptr, nullptr, 1000);

    switch (frame_type) 
    {
        case NDIlib_frame_type_none:            break;
        case NDIlib_frame_type_audio:           break;
        case NDIlib_frame_type_metadata:        break;
        case NDIlib_frame_type_error:           break;
        case NDIlib_frame_type_status_change:   break;
        case NDIlib_frame_type_video:
        {
            //receive 4:2:2 YUV frame, return RGBA;
            auto rgbFrameSizeBytes = video_frame.xres * video_frame.yres * 4;

            if (!buffer.initialized()) buffer.init(10, rgbFrameSizeBytes);

            if (!matUYVY) matUYVY = std::make_unique<cv::Mat>(cv::Size(video_frame.xres, video_frame.yres), CV_8UC2);
            if (!matRGB ) matRGB  = std::make_unique<cv::Mat>(cv::Size(video_frame.xres, video_frame.yres), CV_8UC4);


            frame = std::make_shared<NdiFrame>(
                video_frame.xres,
                video_frame.yres,
                video_frame.frame_rate_N,
                video_frame.frame_rate_D,
                video_frame.picture_aspect_ratio,
                video_frame.timecode,
                rgbFrameSizeBytes,
                video_frame.p_metadata,
                video_frame.timestamp,
                buffer.getSlot()
            );

            matUYVY ->data = video_frame.p_data;
            matRGB  ->data = frame->data();

            cv::cvtColor(*matUYVY, *matRGB, cv::COLOR_YUV2BGRA_UYVY);

            NDIlib_recv_free_video_v2(reinterpret_cast<NDIlib_recv_instance_t>(connection), &video_frame);
        }
    }

    return frame;
}


void NdiConnection::close()
{
    if (!connection) return;

    // Destroy the receiver
    NDIlib_recv_destroy(reinterpret_cast<NDIlib_recv_instance_t>(connection));
    
    connection        = nullptr;
    currentState    = NdiConnection::State::Invalid;

    NDIlib_destroy();
}

NdiConnection::State NdiConnection::state()
{
    return currentState;
}


