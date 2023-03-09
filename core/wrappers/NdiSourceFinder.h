#pragma once

#include "source.h"

#include <string>
#include <vector>

namespace NDIReceiver 
{

class NdiSourceFinder
{
public:
    NdiSourceFinder();
    virtual ~NdiSourceFinder() = default;

    std::vector<NdiSource> findSources(int timeout);
};

} // namespace