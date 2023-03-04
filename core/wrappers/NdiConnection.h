#pragma once

#include "source.h"
#include "frame.h"

#include <memory>

namespace NDIReceiver {

	class NdiConnection {

	public:
		enum class State {
			Valid,
			Invalid
		};

									NdiConnection	(const NdiSource& source);
		virtual						~NdiConnection	();

		void						open			();
		std::shared_ptr<NdiFrame>	recv			();
		void						close			();

		State						state			();


	private:
		State currentState;
		const NdiSource source;
		void* connection;

		std::vector<uint8_t> buf;

	};

};
