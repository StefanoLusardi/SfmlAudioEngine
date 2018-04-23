#pragma once

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
	Token RegisterObserver(const PropertyType& propertyType, Callback&& callbackToRegister)
	{
		mObservers[propertyType].emplace(mTokenId, std::forward<Callback>(callbackToRegister));
		return Token(propertyType, mTokenId++);
	}

	bool UnregisterObserver(Token&& token)
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

	void Notify(const PropertyType& propertyType, const Payload& value) const
	{
		if (auto callbackMap = mObservers.find(propertyType); callbackMap != mObservers.end())
		{
			for (const auto& [tokenId, callback] : callbackMap->second)
			{
				callback(value);
			}
		}
	}

private:
	std::map<PropertyType, std::map<TokenId, std::function<void(Payload)>>> mObservers;
	inline static TokenId mTokenId { 0 };
};