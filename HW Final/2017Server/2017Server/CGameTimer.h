#pragma once
#ifndef GAMETIMER_H
#define GAMETIMER_H

class GameTimer
{
public:
	GameTimer();

	float TotalTime()const; // �� ����
	float DeltaTime()const; // �� ����

	void Reset(); // �޽��� ���� ������ ȣ��
	void Start(); // Ÿ�̸Ӹ� ���� �Ǵ� �簳
	void Stop();  // Ÿ�̸Ӹ� ����
	void Tick();  // �� ������ ȣ���Ѵ�

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;   //���� ȣ��� ���� �ð����� �ʱ�ȭ
	__int64 mPausedTime; //����� ����
	__int64 mStopTime;    // ���� ������ �ð�
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};

#endif // GAMETIMER_H