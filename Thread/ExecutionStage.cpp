#include "stdafx.h"
#include "ExecutionStage.h"
ExecutionStage::ExecutionStage(void)
{
}

ExecutionStage::~ExecutionStage(void)
{
}

void ExecutionStage::SetNextStage(ExecutionStage * stage)
{
    NextStage = stage;
}
