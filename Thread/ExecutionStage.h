#pragma once
#include "ForwardDeclarations.h"

class ExecutionStage
{
public:
    ExecutionStage(void);
    virtual ~ExecutionStage(void);

    virtual void Execute(FrameParam & fp) = 0;

    void SetNextStage(ExecutionStage * stage);
private:
    ExecutionStage * NextStage;
};