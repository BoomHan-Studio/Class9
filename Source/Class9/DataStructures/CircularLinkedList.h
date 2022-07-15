// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


/*struct CLASS9_API FCircularLinkedNode
{
public:

	TObjectPtr<AActor> Now;
	
	FCircularLinkedNode* Left;
	
	FCircularLinkedNode* Right;

	FCircularLinkedNode();
	
	FCircularLinkedNode(AActor* NowActor, FCircularLinkedNode* LeftNode, FCircularLinkedNode* RightNode);

	FORCEINLINE operator AActor*() const
	{
		return Now;
	}
};

USTRUCT()
struct CLASS9_API FCircularLinkedList
{
	GENERATED_BODY()
public:

	FCircularLinkedNode* Node;

	FCircularLinkedList();

	FCircularLinkedList(FCircularLinkedNode* InNode);

	FCircularLinkedList(AActor* NowActor, FCircularLinkedNode* LeftNode, FCircularLinkedNode* RightNode);

	//~FCircularLinkedList();

	bool ToLeft();

	bool ToRight();

	void AddLeft(AActor* NowActor);

	void AddRight(AActor* NowActor);

	AActor* Value() const;
};*/