#include "ReceiverAsync.h"

using namespace NDIReceiver;

ReceiverAsync::ReceiverAsync(Thread& mainThread, NdiConnection &con) :
	mainThread(mainThread),
	connection(con)
{
}

ReceiverAsync::~ReceiverAsync()
{
}

void ReceiverAsync::recvAsync()
{
	background.executeAsync([this] {

		auto frame = connection.recv();
		
		if (frame)
		{
			mainThread.executeAsync([this, frame] {
				if (eventImage) eventImage(frame);
				});
		}

	});
}

void ReceiverAsync::stop()
{
	background.stop();
}
