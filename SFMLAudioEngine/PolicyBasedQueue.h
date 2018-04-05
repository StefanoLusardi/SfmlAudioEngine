#pragma once
#include <list>
#include <cassert>
#include <type_traits>
#include <utility>
#include <iostream>

template<typename Test, template<typename...> class Ref>
struct is_specialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

namespace Policy
{
	template <typename Container>
	struct IPolicy
	{
		IPolicy() { }

		virtual ~IPolicy()
		{
		}
				
		virtual bool ApplyPolicy(Container& container) const = 0;
	};

	template <typename Container>
	struct DiscardFirst : public IPolicy<Container>
	{
		bool ApplyPolicy(Container& container) const override
		{
			container.pop_front();
			return true;
		}
	};

	template <typename Container>
	struct DiscardLast : public IPolicy<Container>
	{
		bool ApplyPolicy(Container& container) const override
		{
			container.pop_back();
			return true;
		}
	};

	template <typename Container>
	struct DiscardNone : public IPolicy<Container>
	{
		bool ApplyPolicy(Container& container) const override { return false; }
	};
}

template <typename Container, template<typename> typename QueuePolicy = Policy::DiscardFirst>
class PolicyBasedQueue
{
public:

	PolicyBasedQueue(const size_t maxSize)
		: mMaxSize {maxSize}
	{
		assert((is_specialization<Container, std::list>::value));
		assert((std::is_base_of<Policy::IPolicy<Container>, QueuePolicy<Container>>::value));
	}

	size_t GetMaxSize() const { return mMaxSize; }
	size_t GetQueueSize() const { return mContainer.size(); }

	Container& GetContainer() { return mContainer; }
	const Container& GetContainer() const { return mContainer; }

	template <typename ContainerValue>
	bool Pop(ContainerValue& elem)
	{
		if (mContainer.empty())
			return false;

		elem = std::move(mContainer.front());
		mContainer.pop_front();
		return true;
	}

	template <typename ContainerValue>
	bool Push(ContainerValue&& elem)
	{
		if (mMaxSize == mContainer.size())
			if (!mQueuePolicy.ApplyPolicy(mContainer))
				return false;

		mContainer.push_back(std::move(elem));
		return true;
	}

private:
	Container mContainer;
	QueuePolicy<Container> mQueuePolicy;
	const size_t mMaxSize;
};
