#include "../../SFMLAudioEngine/PolicyBasedQueue.h"
#include <iostream>
#include <vector>

int main()
{
	PolicyBasedQueue<std::list<std::string>, Policy::DiscardFirst> q{2};

	std::cout << "Max Size: " << q.GetMaxSize() << std::endl;
	std::cout << "Queue Size: " << q.GetQueueSize() << std::endl;

	q.Push("first");
	std::cout << "Queue Size: " << q.GetQueueSize() << std::endl;

	q.Push("second");
	std::cout << "Queue Size: " << q.GetQueueSize() << std::endl;
	
	q.Push("third");
	std::cout << "Queue Size: " << q.GetQueueSize() << std::endl;

	auto c = q.GetContainer().front();
	q.Pop(c);
	std::cout << "Queue Size: " << q.GetQueueSize() << std::endl;
	
	//q.Pop("fourth");
	//std::cout << "Queue Size: " << q.GetQueueSize() << std::endl;

	return 0;
}
