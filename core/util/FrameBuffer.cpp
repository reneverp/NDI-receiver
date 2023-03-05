#include "FrameBuffer.h"

using namespace NDIReceiver;

FrameBuffer::FrameBuffer():
	valid(false)
{
}

FrameBuffer::~FrameBuffer()
{
	buffer.clear();
}

void FrameBuffer::init(int count, int frameSize)
{
	buffer.clear();
	for (int i = 0; i < count; i++)
	{
		buffer.push_back(FrameBuffer::Slot(std::vector<uint8_t>(frameSize), false));
	}

	valid = true;
}

bool FrameBuffer::initialized()
{
	return valid;
}

FrameBuffer::Slot* FrameBuffer::getSlot()
{
	auto is_locked = [&](FrameBuffer::Slot& slot) { return !slot.locked; };

	auto res = std::find_if(begin(buffer), end(buffer), is_locked);

	if (res != std::end(buffer))
	{
		(*res).locked = true;
		return &(*res);
	}
	else
	{
		//double the buffer in case images are kept in memory;
		for (int i = 0; i < buffer.size(); i++)
		{
			buffer.push_back(FrameBuffer::Slot(std::vector<uint8_t>(buffer[0].buffer.size()), false));
		}

		return getSlot();
	}
}
