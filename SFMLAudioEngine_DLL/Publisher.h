#pragma once

#include "GroupProperty.h"

#include <functional>
#include <map>

using TokenId = int;

struct Token
{
	Token(const PropertyType& propertyType, const TokenId& Id) : mPropertyType{ propertyType }, mId{ Id } { }

	const PropertyType mPropertyType;
	const TokenId mId;
};

template <typename Payload>
class Publisher
{
public:
	template <typename Callback>
	Token RegisterObserver(const PropertyType& propertyType, Callback&& callbackToRegister);
	bool UnregisterObserver(Token&& token);
	void Notify(const PropertyType& propertyType, const Payload& value) const;

private:
	std::map<PropertyType, std::map<TokenId, std::function<void(Payload)>>> mObservers;
	inline static TokenId mTokenId { 0 };
};

// Inline template implementation

template <typename Payload>
template <typename Callback>
Token Publisher<Payload>::RegisterObserver(const PropertyType& propertyType, Callback&& callbackToRegister)
{
	mObservers[propertyType].emplace(mTokenId, std::forward<Callback>(callbackToRegister));
	return Token(propertyType, mTokenId++);
}

template <typename Payload>
bool Publisher<Payload>::UnregisterObserver(Token&& token)
{
	// Lookup PropertyType
	if (auto callbackMap = mObservers.find(token.mPropertyType); callbackMap != mObservers.end())
	{
		// Lookup TokenId
		if (auto callback = callbackMap->second.find(token.mId); callback != callbackMap->second.end())
		{
			callbackMap->second.erase(callback);
			return true;
		}
	}
	return false;
}

template <typename Payload>
void Publisher<Payload>::Notify(const PropertyType& propertyType, const Payload& value) const
{
	if (auto callbackMap = mObservers.find(propertyType); callbackMap != mObservers.end())
	{
		for (const auto& [tokenId, callback] : callbackMap->second)
		{
			(void)tokenId;
			callback(value);
		}
	}
}