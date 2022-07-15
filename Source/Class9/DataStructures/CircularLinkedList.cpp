// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "CircularLinkedList.h"

/*#include <stack>

#include "Kismet/KismetSystemLibrary.h"

FCircularLinkedNode::FCircularLinkedNode()
	:Now(nullptr),
	Left(nullptr),
	Right(nullptr)
{
	
}

FCircularLinkedNode::FCircularLinkedNode(AActor* NowActor, FCircularLinkedNode* LeftNode, FCircularLinkedNode* RightNode)
	:Now(NowActor),
	Left(LeftNode),
	Right(RightNode)
{
	
}

FCircularLinkedList::FCircularLinkedList()
	:Node(nullptr)
{
	
}

FCircularLinkedList::FCircularLinkedList(FCircularLinkedNode* InNode)
	:Node(InNode)
{
	
}

FCircularLinkedList::FCircularLinkedList(AActor* NowActor, FCircularLinkedNode* LeftNode, FCircularLinkedNode* RightNode)
	:FCircularLinkedList(new FCircularLinkedNode(NowActor, LeftNode, RightNode))
{
	
}

bool FCircularLinkedList::ToLeft()
{
	if (!Node)
	{
		return false;
	}
	Node = Node->Left;
	return true;
}

bool FCircularLinkedList::ToRight()
{
	if (!Node)
	{
		return false;
	}
	Node = Node->Right;
	return true;
}

void FCircularLinkedList::AddLeft(AActor* NowActor)
{
	Node->Left = new FCircularLinkedNode(NowActor, nullptr, Node);
}

void FCircularLinkedList::AddRight(AActor* NowActor)
{
	Node->Right = new FCircularLinkedNode(NowActor, Node, nullptr);
}

AActor* FCircularLinkedList::Value() const
{
	return Node->Now;
}*/

/*FCircularLinkedList::~FCircularLinkedList()
{
	FCircularLinkedNode* Nodes[100]{nullptr};
	int Index = 0;
	FCircularLinkedNode* Now = Node->Left;
	while (Now && Now != Node)
	{
		Nodes[Index] = Now;
		Index++;
		Now = Now->Left;
	}
	Index--;
	
	while (Index >= 0)
	{
		FCircularLinkedNode* Top = Nodes[Index];
		UKismetSystemLibrary::PrintString(Dependency, GetNameSafe(Top->Now), true, true, FLinearColor::Red, 5.f);
		delete Top;
		Index--;
	}
}*/
