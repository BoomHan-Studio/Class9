// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "EnemyPropertiesNode.h"

FEnemyPropertiesNode::FEnemyPropertiesNode(AMapNode* Node, FVector Vector, float Angle, bool bMonitor, uint8 Code)
	:BoundNode(Node), Location(Vector), ViewAngle(Angle), bIsToMonitor(bMonitor), MonitorDirectionCode(Code)
{
	
}
