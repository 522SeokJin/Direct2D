#pragma once
#include "GameEngineThread.h"
#include "GameEngineIocp.h"

// 설명 :
class GameEngineThreadQueue
{
private:
	class Job
	{
	public:
		std::function<void()> JobFunction;
	};

public:
	GameEngineThreadQueue(const std::string& _ThreadName, int _ThreadCount = 0)
	{

		ThreadCount_ = _ThreadCount;

		if (ThreadCount_ == 0)
		{
			SYSTEM_INFO Info;
			GetSystemInfo(&Info);
			ThreadCount_ = Info.dwNumberOfProcessors - 2;
		}

		if (ThreadCount_ <= 0)
		{
			ThreadCount_ = 1;
		}

		Iocp_.Start(ThreadCount_);
		for (size_t i = 0; i < ThreadCount_; i++)
		{
			GameEngineThread* NewThread = new GameEngineThread();
			std::string ThreadName = _ThreadName + std::to_string(static_cast<int>(i));
			NewThread->Start(ThreadName, std::bind(JobWorkThread, NewThread, &Iocp_));
			Threads_.push_back(NewThread);
		}


	}
	~GameEngineThreadQueue()
	{

		Destroy();
	}



	void JobPost(std::function<void()> _Job)
	{
		Job* NewJob = new Job();
		NewJob->JobFunction = _Job;
		Iocp_.Makework(-2, NewJob);
	}

	void Destroy()
	{
		for (size_t i = 0; i < ThreadCount_; i++)
		{
			Iocp_.Makework(-1, nullptr);
			Sleep(1);
		}

		for (size_t i = 0; i < Threads_.size(); i++)
		{
			delete Threads_[i];
			Threads_[i] = nullptr;
		}

		Threads_.clear();
	}

protected:

private:
	static void JobWorkThread(GameEngineThread* Thread, GameEngineIocp* _Iocp)
	{
		DWORD lpNumberOfBytesTransferred = 0;
		ULONG_PTR lpCompletionKey = 0;
		LPOVERLAPPED Ptr = nullptr;
		while (true)
		{

			// 윈도우가 
			//                    0                         

			_Iocp->WaitforWork(lpNumberOfBytesTransferred, lpCompletionKey, Ptr);

			switch (lpNumberOfBytesTransferred)
			{
			case -1:
			{
				return;
			}
			case -2:
			{
				Job* PostJob = reinterpret_cast<Job*>(lpCompletionKey);
				PostJob->JobFunction();
				delete PostJob;
				break;
			}
			default:
				break;
			}
		}
	}

	GameEngineIocp Iocp_;

	int ThreadCount_;
	std::vector<GameEngineThread*> Threads_;
};

