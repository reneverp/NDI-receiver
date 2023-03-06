#pragma once

#include <string>
#include <vector>

#include "source.h"

namespace NDIReceiver {

    class NdiSourceFinder
    {
    public:
                                NdiSourceFinder();
        virtual                    ~NdiSourceFinder();

        std::vector<NdiSource>    findSources();


    };


};
