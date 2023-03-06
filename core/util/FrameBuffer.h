#pragma once

#include <vector>
#include <queue>

#include <cstdint>

namespace NDIReceiver
{
	class FrameBuffer
	{
	public:
		struct Slot {
			std::vector<uint8_t>	buffer;
			bool					locked;
		};

				FrameBuffer		();
		virtual ~FrameBuffer	();

		//TODO
		void	init			(int count, int frameSize);
		bool	initialized		();

		Slot*	getSlot			();

	private:
		std::vector<Slot>	buffer;
		bool				valid;
	};

};