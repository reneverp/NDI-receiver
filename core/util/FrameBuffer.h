#pragma once

#include <vector>
#include <queue>

#include <cstdint>

namespace NDIReceiver
{

class FrameBuffer
{
public:
    class Slot 
    {
    public:
        Slot(size_t size, bool locked): buffer(size), locked(locked) {};
        ~Slot() = default;

        std::vector<uint8_t>    buffer;
        bool                    locked;

    private:
        Slot(Slot&)                     = delete;
        Slot& operator=(Slot const&)    = delete;

        Slot(Slot&&)                    = default;
        Slot& operator=(Slot&&)         = default;
    };

    FrameBuffer ();
    virtual ~FrameBuffer() = default;

    //TODO
    void    init                (size_t count, size_t frameSize);
    bool    initialized         ();

    Slot&   getSlot             ();

    size_t  slotsLocked         ();
    size_t  size                ();

private:
    std::vector<Slot>           buffer;
    bool                        valid;
};

} // namespace