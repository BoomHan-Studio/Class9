// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<typename T>
class CLASS9_API TUnrealSingleton
{
private:
	using ObjectType = T;
	
	static ObjectType* Singleton;

	TUnrealSingleton(const TUnrealSingleton&) = delete;
	TUnrealSingleton& operator =(const TUnrealSingleton&) = delete;

protected:

	TUnrealSingleton(){}

	virtual ~TUnrealSingleton(){}

	void InitSingleton()
	{
		OnInit();
	}

	void DestroySingleton()
	{
		OnDestroy();
	}

	virtual void OnInit() = 0;
	virtual void OnDestroy() = 0;

public:

	static T* CreateInstance(UObject* Outer)
	{
		if (!Singleton)
		{
			if (!Outer)
			{
				Singleton = NewObject<T>();
			}
			else
			{
				Singleton = NewObject<T>(Outer);
			}
			Singleton->InitSingleton();
			Singleton->AddToRoot();
		}
		return Singleton;
	}

	static void DestroyInstance()
	{
		if (Singleton)
		{
			Singleton->Destroy();
			Singleton->RemoveFromRoot();
		}
		Singleton = nullptr;
	}

	static FORCEINLINE T* GetInstance(bool bSkipCheck = false)
	{
		return Singleton;
	}
};

template<typename T>
typename TUnrealSingleton<T>::ObjectType* TUnrealSingleton<T>::Singleton;