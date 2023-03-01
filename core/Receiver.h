#pragma once

#include <memory>
#include <vector>

#include <Processing.NDI.Lib.h>

namespace NDIReceiver {

	class Receiver {

	public:
				Receiver	();
		virtual ~Receiver	();

		void	start		();
		void	stop		();

	private:

		std::vector<NDIlib_source_t>	findsource	();

		NDIlib_find_instance_type* ndiFinder;
	};


};
