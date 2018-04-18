#pragma once

#include <functional>
#include <map>

using Token = std::pair<PropertyType, int>;

template <typename Payload>
class Publisher
{
public:
	template <typename Callback>
	Token RegisterObserver(const PropertyType& propertyType, Callback&& callbackToRegister)
	{
		auto tokenId = mObservers[propertyType].size();
		mObservers[propertyType].push_back(std::forward<Callback>(callbackToRegister));
		return std::make_pair(propertyType, tokenId);
	}

	bool UnregisterObserver(Token&& token)
	{
		if (auto callbackList = mObservers.find(token.first); callbackList != mObservers.end())
		{			
			callbackList->second.erase(callbackList->second.begin() + token.second);
			return true;
		}
		return false;
	}

	void Notify(const PropertyType& propertyType, const Payload& value) const
	{
		if (auto callbackList = mObservers.find(propertyType); callbackList != mObservers.end())
		{
			for (const auto& callback : callbackList->second)
			{
				callback(value);
			}
		}
	}

private:
	std::map<PropertyType, std::vector<std::function<void(Payload)>>> mObservers;
};