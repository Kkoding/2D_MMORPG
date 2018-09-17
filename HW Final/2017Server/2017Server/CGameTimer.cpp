#include "stdafx.h"
#include "CGameTimer.h"



//���� Ÿ�̸��� ���ļ��� ��ȸ�ؼ� ƽ�� �� ���� �����Ѵ�
GameTimer::GameTimer()
	: mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),
	mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

// Returns the total time elapsed since Reset() was called, NOT counting anyhb
// time when the clock is stopped.
float GameTimer::TotalTime()const
{
	// Ÿ�̸Ӱ� ���� ���¸�, ������ �������� �帥 �ð��� ����ϸ� �ȵȴ�
	// ����, ������ �̹� �Ͻ� ������ ���� �ִٸ� �ð��� stop-base ���� 
	// �Ͻ� ���� ���� �ð��� ���ԵǾ� �ִµ�, �� ���� �ð��� ��ü �ð��� ��������
	// ���ƾ� �Ѵ�. �̸� �ٷ���� ����, stop���� �Ͻ� ���� ���� �ð��� ����
	//
	//                     |<--paused time-.|
	// ----*---------------*-----------------*------------*------------*-----. time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime

	if (mStopped)
	{
		return (float)(((mStopTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	}

	// �ð��� cur - base ���� �Ͻ� ���� ���� �ð��� ���ԵǾ� �ִ�.
	// �̸� ��ü �ð��� �����ϸ� �� �ǹǷ�, �� �ð��� cur���� ����
	//
	//  (mCurrTime - mPausedTime) - mBaseTime 
	//
	//                     |<--paused time-.|
	// ----*---------------*-----------------*------------*-----. time
	//  mBaseTime       mStopTime        startTime     mCurrTime

	else
	{
		return (float)(((mCurrTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	}
}

float GameTimer::DeltaTime()const
{
	return (float)mDeltaTime;
}

void GameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);


	// ������ ���� ���̿� �帥 �ð��� ����
	//
	//                     |<-------d------.|
	// ----*---------------*-----------------*-----------. time
	//  mBaseTime       mStopTime        startTime     

	if (mStopped)
	{
		mPausedTime += (startTime - mStopTime);
		//Ÿ�̸Ӹ� �ٽ� �����ϴ� ���̱� ������, ������ ���� �ð��� ��ȿ���� �ʴ�
		// ���� ���� �ð����� �ٽ� �����Ѵ�
		mPrevTime = startTime;
		//������ ���� ���°� �ƴϹǷ� ���� ������� �����Ѵ�
		mStopTime = 0;
		mStopped = false;
	}
}

void GameTimer::Stop()
{
	//�������¸� �ƹ��ϵ�����
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		//���� �ð��� Ÿ�̸� ���� ���� �ð����� ����, �������� ���� �� �÷��� ����
		mStopTime = currTime;
		mStopped = true;
	}
}

void GameTimer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}
	//�̹� �������� �ð��� ��´�.
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	//�̹� �������� �ð��� ���� �������� �ð��� ���̸� ���Ѵ�.
	mDeltaTime = (mCurrTime - mPrevTime)*mSecondsPerCount;

	//���� �������� �غ��Ѵ�.
	mPrevTime = mCurrTime;

	// ������ ���� �ʰ� �Ѵ�. 
	// ���μ����� ���� ���� ���ų� 
	// ������ �ٸ� ���μ����� ��Ű�� ���
	// mDeltaTime�� ������ �� �� �ִ�.
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}

