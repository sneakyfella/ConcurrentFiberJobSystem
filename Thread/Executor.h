#pragma once
#include "ForwardDeclarations.h"
#include "ExecutionStage.h"
class Executor
{
public:
    Executor(void);
    ~Executor(void);

    void Execute(FrameParam & curr);

private:
    ExecutionStage * Head;
};