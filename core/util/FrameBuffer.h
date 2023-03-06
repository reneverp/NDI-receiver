#pragma once

#include <vector>
#include <queue>

#include <cstdint>

namespace NDIReceiver
{
    class FrameBuffer
    {
    public:
        class Slot {
        public:
            Slot(size_t size, bool locked) : buffer(size), locked(locked) {};
            ~Slot() {};

            Slot(Slot&)                     = delete;
            Slot& operator=(Slot const&)    = delete;

            Slot(Slot&&)                    = default;
            Slot& operator=(Slot&&)         = default;

            std::vector<uint8_t>    buffer;
            bool                    locked;

        private:

        };

                FrameBuffer         ();
        virtual ~FrameBuffer        ();

        //TODO
        void    init                (int count, int frameSize);
        bool    initialized         ();

        Slot&    getSlot            ();

    private:
        std::vector<Slot>           buffer;
        bool                        valid;
    };

};