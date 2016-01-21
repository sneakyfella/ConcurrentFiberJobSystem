#pragma once
#include "ForwardDeclarations.h"
#include "Executor.h"


class FrameManager
{
public:

    FrameManager(void);
    virtual ~FrameManager(void);

    void Initialise(void);

    void Shutdown(void);

    void Update(Float32 dt);

    void GenerateNewFrame(void);

    void DumpOldestFrame(void);

    FrameParam * GetCurrentFrame(void);
   

    GETSET_AUTO(Uint64, CurrFrameNumber);

    
private:
    Executor        mExecutor;
    Uint64          mCurrFrameNumber;

    typedef Uint64 FrameCount;

    std::unordered_map<Uint64, FrameParam>   mFrames;

    DECLARE_SINGLETON(FrameManager);
};