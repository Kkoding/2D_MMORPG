#pragma once
class CObjectPool
{
private:
	list<CLIENT*> m_obj;

public:
	CLIENT * getObject();
	void ReleaseObject(CLIENT* obj);


	static CObjectPool* Instance;
public:
	static CObjectPool * getInstance()
	{
		if (nullptr == Instance)
			Instance = new CObjectPool();
		return Instance;
	}

	void Release()
	{
		if (nullptr != Instance)
			delete Instance;
		Instance = nullptr;
	}
private:
	CObjectPool();
public:
	~CObjectPool();
};


#define OBJPOOL CObjectPool::getInstance()