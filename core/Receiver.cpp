#include <vector>
#include <chrono>

#include "Receiver.h"

using namespace NDIReceiver;

Receiver::Receiver()
{
	// Not required, but "correct" (see the SDK documentation).
	if (!NDIlib_initialize())
		throw std::exception("could not initialize NDIlib");

	// Create a finder
	ndiFinder = NDIlib_find_create_v2();

}

Receiver::~Receiver()
{
	// Destroy the NDI finder. We needed to have access to the pointers to p_sources[0]
	NDIlib_find_destroy(ndiFinder);

	NDIlib_destroy();
}

void Receiver::start()
{
	//TODO: eventloop? or sync
	//eventloop.executeAsync(

	//	[this]
	//	{

	//	}
	//	);

	auto sources = findsource();

	if (sources.size() == 0) return;

	// We now have at least one source, so we create a receiver to look at it.
	NDIlib_recv_instance_t rcv = NDIlib_recv_create_v3();
	if (!rcv) return;

	// Connect to our sources
	NDIlib_recv_connect(rcv, &sources[0]);

	// Run for one minute
	using namespace std::chrono;
	for (const auto start = high_resolution_clock::now(); high_resolution_clock::now() - start < minutes(5);) {
		// The descriptors
		NDIlib_video_frame_v2_t video_frame;
		NDIlib_audio_frame_v2_t audio_frame;

		switch (NDIlib_recv_capture_v2(rcv, &video_frame, &audio_frame, nullptr, 5000)) {
			// No data
		case NDIlib_frame_type_none:
			printf("No data received.\n");
			break;

			// Video data
		case NDIlib_frame_type_video:
			printf("Video data received (%dx%d).\n", video_frame.xres, video_frame.yres);
			NDIlib_recv_free_video_v2(rcv, &video_frame);
			break;
		}
	}

	// Destroy the receiver
	NDIlib_recv_destroy(rcv);
}

void Receiver::stop()
{
}

std::vector<NDIlib_source_t> Receiver::findsource()
{
	std::vector<NDIlib_source_t> sources;

	// Wait until there is one source
	uint32_t srcCount = 0;
	const NDIlib_source_t* p_sources;
	while (!srcCount) {
		NDIlib_find_wait_for_sources(ndiFinder, 1000);
		p_sources = NDIlib_find_get_current_sources(ndiFinder, &srcCount);
	}

	for (uint32_t i = 0; i < srcCount; i++)
	{
		sources.push_back(*(p_sources + i));
	}

	return sources;

}


