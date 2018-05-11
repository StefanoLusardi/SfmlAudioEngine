#pragma once
#include <memory>

namespace Policy
{
	template <typename Container>
	struct IPolicy
	{
		IPolicy() = default;
		virtual ~IPolicy() = default;
		IPolicy(const IPolicy& other) = delete;
		IPolicy(IPolicy&& other) noexcept = delete;
		IPolicy& operator=(const IPolicy& other) = delete;
		IPolicy& operator=(IPolicy&& other) noexcept = delete;

		virtual bool ApplyPolicy(Container& container, typename Container::value_type&& discardedElem) const = 0;
	};

	template <typename Container>
	struct DiscardFirst : public IPolicy<Container>
	{
		bool ApplyPolicy(Container& container, typename Container::value_type&& discardedElem) const override;
	};

	template <typename Container>
	struct DiscardLast : public IPolicy<Container>
	{
		bool ApplyPolicy(Container& container, typename Container::value_type&& discardedElem) const override;
	};

	template <typename Container>
	struct DiscardNone : public IPolicy<Container>
	{
		bool ApplyPolicy(Container& container, typename Container::value_type&& discardedElem) const override;
	};
}

template <typename Container>
class PolicyBasedQueue
{
public:

	PolicyBasedQueue(const size_t maxSize);

	size_t GetMaxSize() const;
	size_t GetQueueSize() const;

	Container& GetContainer();
	const Container& GetContainer() const;

	void SetPolicy(std::unique_ptr<Policy::IPolicy<Container>> policy);

	template <typename ContainerValue>
	bool Pop(ContainerValue& elem);

	template <typename ContainerValue, typename RemovedValue>
	bool Push(ContainerValue&& elem, RemovedValue&& discardedElem);

private:
	Container mContainer;
	std::unique_ptr<Policy::IPolicy<Container>> mQueuePolicy;
	const size_t mMaxSize;
};

// Inline template implementation

#include <list>
#include <cassert>
#include <type_traits>

template<typename Test, template<typename...> class Ref>
struct is_specialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

namespace Policy
{
	template <typename Container>
	bool DiscardFirst<Container>::ApplyPolicy(Container& container, typename Container::value_type&& discardedElem) const
	{
		discardedElem = std::move(container.front());
		container.pop_front();
		return true;
	}

	template <typename Container>
	bool DiscardLast<Container>::ApplyPolicy(Container& container, typename Container::value_type&& discardedElem) const
	{
		discardedElem = std::move(container.back());
		container.pop_back();
		return true;
	}

	template <typename Container>
	bool DiscardNone<Container>::ApplyPolicy(Container& container, typename Container::value_type&& discardedElem) const
	{
		return false;
	}
}

template <typename Container>
PolicyBasedQueue<Container>::PolicyBasedQueue(const size_t maxSize)
	: mMaxSize{maxSize}
{
	assert((is_specialization<Container, std::list>::value));
}

template <typename Container>
size_t PolicyBasedQueue<Container>::GetMaxSize() const
{
	return mMaxSize;
}

template <typename Container>
size_t PolicyBasedQueue<Container>::GetQueueSize() const
{
	return mContainer.size();
}

template <typename Container>
Container& PolicyBasedQueue<Container>::GetContainer()
{
	return mContainer;
}

template <typename Container>
const Container& PolicyBasedQueue<Container>::GetContainer() const
{
	return mContainer;
}

template <typename Container>
void PolicyBasedQueue<Container>::SetPolicy(std::unique_ptr<Policy::IPolicy<Container>> policy)
{
	mQueuePolicy = std::move(policy);
}

template <typename Container>
template <typename ContainerValue>
bool PolicyBasedQueue<Container>::Pop(ContainerValue& elem)
{
	if (mContainer.empty())
		return false;

	elem = std::move(mContainer.front());
	mContainer.pop_front();
	return true;
}

template <typename Container>
template <typename ContainerValue, typename RemovedValue>
bool PolicyBasedQueue<Container>::Push(ContainerValue&& elem, RemovedValue&& discardedElem)
{
	if (mMaxSize == mContainer.size())
	{
		if (!mQueuePolicy->ApplyPolicy(mContainer, std::move(discardedElem)))
			return false; // No element added. mContainer is unchanged
	}

	mContainer.push_back(std::move(elem));
	return true;
}