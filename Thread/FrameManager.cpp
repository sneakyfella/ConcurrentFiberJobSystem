#include "stdafx.h"
#include "FrameManager.h"
FrameManager::FrameManager(void)
{
}

FrameManager::~FrameManager(void)
{
}

void FrameManager::Initialise(void)
{
    for (; mCurrFrameNumber < 3; ++mCurrFrameNumber)
    {
        FrameParam *fp = new FrameParam();
        fp->SetFrameNumber(mCurrFrameNumber);
        mFrames.emplace(mCurrFrameNumber, fp);
    }
}

void FrameManager::Shutdown(void)
{

}

void FrameManager::Update(Float32 dt)
{
    for (;; ++mCurrFrameNumber)
    {
        //Begin frame
        //Allocate frame resources
        //mExecutor.Execute()
        //Dispatch Jobs
        //End Frame
        //Free Frame Memory
    }
   
}

void FrameManager::GenerateNewFrame(void)
{
    FrameParam *fp = new FrameParam();
    fp->SetFrameNumber(++mCurrFrameNumber);

    mFrames.emplace(mCurrFrameNumber, fp);
}

void FrameManager::DumpOldestFrame(void)
{
    if (mCurrFrameNumber > 16)
        mFrames.erase(mCurrFrameNumber - 16);
}

FrameParam * FrameManager::GetCurrentFrame(void)
{
    //mFrames[mCurrFrameNumber];
    return mFrames[mCurrFrameNumber];
}
