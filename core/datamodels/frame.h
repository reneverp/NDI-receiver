#pragma once

#include <FrameBuffer.h>

#include <cstdint>

namespace NDIReceiver 
{

class NdiFrame  
{
public:
    NdiFrame
    (
        int                     xres,
        int                     yres,
        int                     frame_rate_N,
        int                     frame_rate_D,
        float                   picture_aspect_ratio,
        int64_t                 timecode,
        int                     data_size_in_bytes,
        const char*             p_metadata,
        int64_t                 timestamp,
        FrameBuffer::Slot&      s
    ) : 
        xres                    (xres),
        yres                    (yres),
        frame_rate_N            (frame_rate_N),
        frame_rate_D            (frame_rate_D),
        picture_aspect_ratio    (picture_aspect_ratio),
        timecode                (timecode),
        data_size_in_bytes      (data_size_in_bytes),
        p_metadata              (p_metadata),
        timestamp               (timestamp),
        slot                    (s)    
    { };

    ~NdiFrame() { slot.locked = false; };

    // The resolution of this frame.
    const int xres;
    const int yres;

    // What is the frame rate of this frame.
    // For instance NTSC is 30000,1001 = 30000/1001 = 29.97 fps.
    const int frame_rate_N;
    const int frame_rate_D;

    // What is the picture aspect ratio of this frame.
    // For instance 16.0/9.0 = 1.778 is 16:9 video
    // 0 means square pixels.
    const float picture_aspect_ratio;

    // The timecode of this frame in 100-nanosecond intervals.
    const int64_t timecode;

    // buffer size
    const int data_size_in_bytes;

    // Per frame metadata for this frame. This is a NULL terminated UTF8 string that should be in XML format.
    // If you do not want any metadata then you may specify NULL here.
    const char* p_metadata; // Present in >= v2.5

    // This is only valid when receiving a frame and is specified as a 100-nanosecond time that was the exact
    // moment that the frame was submitted by the sending side and is generated by the SDK. If this value is
    // NDIlib_recv_timestamp_undefined then this value is not available and is NDIlib_recv_timestamp_undefined.
    const int64_t timestamp; // Present in >= v2.5

    // Frame data in RGBA 32bits per pixel
    uint8_t* data() const { return slot.buffer.data(); };


private:
    FrameBuffer::Slot& slot;

private:
    NdiFrame(NdiFrame&)                     = delete;
    NdiFrame& operator=(NdiFrame const&)    = delete;

    NdiFrame(NdiFrame&&)                    = default;
    NdiFrame& operator=(NdiFrame&&)         = default;
};

} // namespace
