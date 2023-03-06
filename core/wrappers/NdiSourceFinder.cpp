#include "NdiSourceFinder.h"

#include <Processing.NDI.Lib.h>

using namespace NDIReceiver;

NdiSourceFinder::NdiSourceFinder()
{
	// Not required, but "correct" (see the SDK documentation).
	if (!NDIlib_initialize())
		throw std::exception("could not initialize NDIlib");
}

NdiSourceFinder::~NdiSourceFinder()
{
}

std::vector<NdiSource> NdiSourceFinder::findSources()
{
	std::vector<NdiSource> sources;


	auto ndiFinder = NDIlib_find_create_v2();


	// Wait until there is one source
	uint32_t srcCount = 0;
	const NDIlib_source_t* p_sources;
	while (!srcCount) {
		NDIlib_find_wait_for_sources(ndiFinder, 1000);
		p_sources = NDIlib_find_get_current_sources(ndiFinder, &srcCount);
	}

	for (uint32_t i = 0; i < srcCount; i++)
	{
		sources.push_back(NdiSource(p_sources[i].p_ndi_name, p_sources[i].p_url_address));
	}

	NDIlib_find_destroy(ndiFinder);

	return sources;
}


