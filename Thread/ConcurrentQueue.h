#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include "ThreadTypeDefs.h"


#include "ForwardDeclarations.h"

template<typename T>
class ConcurrentQueue
{
public:
	ConcurrentQueue()
	{
		//mMutex = CreateMutex(
		//					NULL,              // default security attributes
		//					FALSE,             // initially not owned
		//					NULL);             // name
	}
	~ConcurrentQueue()
	{
		//ReleaseMutex(mMutex);
	}
	void Push(const T& job)
	{
		std::unique_lock<std::mutex> lock(mMutex);

		mQueue.push(job);
		lock.unlock();
		mCV.notify_one();
	}
	void Push(T&& job)
	{
		std::unique_lock<std::mutex> lock(mMutex);
		mQueue.push(std::move(job));
		lock.unlock();
		mCV.notify_one();
	}
	T Pop(void)
	{
		std::unique_lock<std::mutex> lock(mMutex);

		while (mQueue.empty())
		{
			mCV.wait(lock);
		}

		auto job = mQueue.front();
		mQueue.pop();
		lock.unlock();
		
		return job;
	}
	void Pop(T& item)
	{
		std::unique_lock<std::mutex> lock(mMutex);

		while (mQueue.empty())
		{
			mCV.wait(lock);
		}
		T job = mQueue.front();
		mQueue.pop();
		lock.unlock();
	}

	size_t Size(void) const
	{
		std::unique_lock<std::mutex> lock(mMutex);
		size_t size = mQueue.size();
		lock.unlock();
		return size;
	}

	bool Empty(void) const
	{
		std::unique_lock<std::mutex> lock(mMutex);
		bool ret = mQueue.empty();
		lock.unlock();
		return ret;
	}
private:
	std::queue<T>   mQueue;
	std::condition_variable mCV;
	mutable std::mutex       mMutex;
};