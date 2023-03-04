#include "NdiConnection.h"

#include <Processing.NDI.Lib.h>


using namespace NDIReceiver;

NdiConnection::NdiConnection(const NdiSource& s) :
	source			(s),
	connection		(nullptr),
	currentState	(State::Invalid)
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

	NDIlib_source_t s(source.name.c_str(), source.url.c_str());

	// Connect to our sources
	NDIlib_recv_connect(reinterpret_cast<NDIlib_recv_instance_t>(connection), &s);
}

std::shared_ptr<NdiFrame> NdiConnection::recv()
{
	std::shared_ptr<NdiFrame> frame = nullptr;

	// only interested in video frames
	NDIlib_video_frame_v2_t video_frame;

	switch (NDIlib_recv_capture_v3(reinterpret_cast<NDIlib_recv_instance_t>(connection), &video_frame, nullptr, nullptr, 5000)) {
		// No data
	case NDIlib_frame_type_none:
		break;
	case NDIlib_frame_type_audio:
		break;

		// Video data
	case NDIlib_frame_type_video:

		frame = std::make_shared<NdiFrame>(
			video_frame.xres,
			video_frame.yres,
			video_frame.frame_rate_N,
			video_frame.frame_rate_D,
			video_frame.picture_aspect_ratio,
			video_frame.timecode,
			video_frame.line_stride_in_bytes,
			video_frame.data_size_in_bytes,
			video_frame.p_metadata,
			video_frame.timestamp
		);

		if (buf.capacity() < frame->data_size_in_bytes) buf.reserve(frame->data_size_in_bytes);
		//frame->p_data.reserve(frame->data_size_in_bytes);
		memcpy(buf.data(), video_frame.p_data, frame->data_size_in_bytes);


		NDIlib_recv_free_video_v2(reinterpret_cast<NDIlib_recv_instance_t>(connection), &video_frame);
		break;
	}

	return frame;
}


void NdiConnection::close()
{
	if (!connection) return;

	// Destroy the receiver
	NDIlib_recv_destroy(reinterpret_cast<NDIlib_recv_instance_t>(connection));
	
	connection		= nullptr;
	currentState	= NdiConnection::State::Invalid;
}

NdiConnection::State NdiConnection::state()
{
	return currentState;
}


