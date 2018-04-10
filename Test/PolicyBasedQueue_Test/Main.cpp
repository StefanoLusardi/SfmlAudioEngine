#include "../../SFMLAudioEngine/PolicyBasedQueue.h"
#include <iostream>
#include <vector>
#include <memory>

int main()
{
	auto q = std::make_unique<PolicyBasedQueue<std::list<std::string>>>(2);
	q->SetPolicy(std::make_unique<Policy::DiscardFirst<std::list<std::string>>>());

	std::cout << "\nMax Size: " << q->GetMaxSize() << std::endl;
	std::cout << "\nQueue Size: " << q->GetQueueSize() << std::endl;

	// Element discarded from the queue
	std::string out;

	const auto p1 = q->Push("first", out);
	std::cout << "\nQueue Size: " << q->GetQueueSize() << std::endl;
	for (const auto& elem : q->GetContainer()) { std::cout << elem.c_str() << "\n"; }

	const auto p2 = q->Push("second", out);
	std::cout << "\nQueue Size: " << q->GetQueueSize() << std::endl;
	for (const auto& elem : q->GetContainer()) { std::cout << elem.c_str() << "\n"; }
	
	const auto p3 = q->Push("third", out);
	std::cout << "\nQueue Size: " << q->GetQueueSize() << std::endl;
	for (const auto& elem : q->GetContainer()) { std::cout << elem.c_str() << "\n"; }

	auto c = q->GetContainer().front();
	q->Pop(c);
	std::cout << "\nQueue Size: " << q->GetQueueSize() << std::endl;
	for (const auto& elem : q->GetContainer()) { std::cout << elem.c_str() << "\n"; }

	//q->Pop("fourth");
	//std::cout << "Queue Size: " << q->GetQueueSize() << std::endl;

	return 0;
}
