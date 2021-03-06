#pragma once
#include "ForwardDeclarations.h"

class FrameParam
{
public:
    FrameParam(void);
    ~FrameParam(void);

    GETSET_AUTO(Uint64, FrameNumber);


public:
    Uint64 mFrameNumber;

    LinearAllocator         mAllocator;
    //std::vector<Vector3f *> Positions;
};
