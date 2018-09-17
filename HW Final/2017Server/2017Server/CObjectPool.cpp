#include "stdafx.h"
#include "CObjectPool.h"



CLIENT * CObjectPool::getObject()
{
	{
		if (m_obj.empty()) return new CLIENT;
		else {
			CLIENT* newObj = m_obj.front();
			m_obj.pop_front();
			return newObj;
		}
	}
}

void CObjectPool::ReleaseObject(CLIENT * obj)
{
	obj->Reset();
	m_obj.push_back(obj);
}

CObjectPool::CObjectPool()
{
}


CObjectPool::~CObjectPool()
{
	while (m_obj.size())
	{
		auto& delete_obj = m_obj.front();
		m_obj.pop_front();
		delete delete_obj;
	}

	m_obj.clear();
}
