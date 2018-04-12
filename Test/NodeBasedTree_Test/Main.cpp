#include "../../SFMLAudioEngine/Mock.h"
#include "../../SFMLAudioEngine/Mixer.h"

int main()
{
	Mixer mixer { Mock::GetMasterGroup(), Mock::GetMixerGroups() };
	mixer.LoadSnapshots(Mock::GetMixerSnapshots());
	mixer.ApplySnapshot("GameSnapshot");
	mixer.ApplySnapshot("MenuSnapshot");

	return 0;
}

/*
auto root = Group::Create("ROOT");
auto copy = Group::Create("copy");;

{
	auto n1 = Group::Create("A");
	auto n2 = Group::Create("B");
	auto n3 = Group::Create("C");
	auto n4 = Group::Create("D");
	auto n5 = Group::Create("N5");
	auto n6 = Group::Create("N6");

	root->AddChild(n1);

	n1->AddChild(n2);
	n1->AddChild(n3);

	n2->AddChild(n4);
	n2->AddChild(n5);

	n5->AddChild(n6);

	copy = root->Copy();
}

auto name = copy->GetName();

auto n0 = copy->GetChild("ROOT");

auto n1 = copy->GetChild("A")->GetName();
auto n2 = copy->GetChild("B")->GetName();
auto n3 = copy->GetChild("C")->GetName();
auto n5 = copy->GetChild("D")->GetName();

auto r1 = copy->GetChild("not_found");  //->GetName();
*/