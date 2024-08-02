#include <stdio.h>
#include <iostream>
#include <Windows.h>

#define SUCCESS 1
#define ERROR -1
#define INDEX_IS_ERROR -2
#define BUFFER_IS_EMPTY -3

template <class T_ELE>
class Linkedlist {
public:
	Linkedlist();
	~Linkedlist();

public:
	BOOL IsEmpty();												//�ж������Ƿ�Ϊ��
	VOID Clear();												//ѭ���ͷ����������ڴ�
	DWORD GetElement(IN DWORD dwIndex, OUT T_ELE& Element);		//��ȡָ����������
	DWORD GetElementIndex(const IN T_ELE& Element);				//��ȡָ����������
	DWORD Insert(IN const T_ELE& Element);						//��β������
	DWORD Insert(IN DWORD dwIndex, IN const T_ELE& Element);	//��ָ����������
	DWORD Delete(IN DWORD dwIndex);								//ɾ��ָ������
	DWORD GetSize();											//��ȡ��С
private:
	typedef struct _NODE{
		T_ELE Data;				//����
		_NODE* pNext;			//��һ���ṹ��ָ��
	}NODE,*PNODE;
	/*PNODE GetIndexPreviousNode(DWORD dwIndex);
	PNODE GetIndexCurrentNode(DWORD dwIndex);					
	PNODE GetIndexNextNode(DWORD dwIndex);*/


private:
	PNODE m_pList;												//����ͷ��ָ��
	PNODE m_pList_END;											//����ֲ�ָ��
	DWORD m_dwLenth;											//����������ݳ���
};

//���캯��
template <class T_ELE>
Linkedlist<T_ELE>::Linkedlist() :m_pList(NULL),m_pList_END(NULL), m_dwLenth(0) {};

//��������
template <class T_ELE>
Linkedlist<T_ELE>::~Linkedlist() {
	this->Clear();
}

template <class T_ELE>
BOOL Linkedlist<T_ELE>::IsEmpty() {
	if (!m_pList || !m_dwLenth) {
		return TRUE;
	}
	return FALSE;
}

template <class T_ELE>
VOID Linkedlist<T_ELE>::Clear() {
	PNODE p;
	PNODE temp;
	//�ж������Ƿ�Ϊ��
	if (this->IsEmpty()) {
		return;
	}
	//����һ��ָ�룬ָ��������λ
	p = m_pList;
	//�ж������еĵ�ַ�Ƿ�Ϊ�գ����Ϊ�գ���ֹͣѭ���������Ϊ�գ���ɾ����һ��Ԫ��
	while (p)
	{
		//��ָ��ָ����һ��Ԫ�أ�Ȼ�󽫵�ǰ�ڴ��ͷ�
		temp = p;
		p = p->pNext;
		delete temp;
	}
	//��p��Ϊ��ָ��
	p = nullptr;

	//���������ͷ��β
	m_pList = nullptr;
	m_pList_END = nullptr;
	//������������Ϊ0
	m_dwLenth = 0;

}


template<class T_ELE>
DWORD Linkedlist<T_ELE>::Insert(IN const T_ELE& Element) {
	//�ж������Ƿ�Ϊ�գ����Ϊ�գ�������ʼָ������ڴ�
	if (!m_pList) {
		//�����ڴ�
		m_pList = new NODE{};
		//��Ԫ�����������ڴ��data
		memcpy(m_pList, &Element, sizeof(T_ELE));
		//���ȼ�һ
		m_dwLenth++;
		//��������β
		m_pList_END = m_pList;
		return SUCCESS;
	}
	//��β�������ڴ�
	m_pList_END->pNext = new NODE{};
	//��β��ָ��Ų����һ���ڴ�
	m_pList_END = m_pList_END->pNext;
	//������ڴ��д���ֵ
	memcpy(&m_pList_END->Data, &Element, sizeof(T_ELE));
	//�����ȼ�һ
	m_dwLenth++;

	return SUCCESS;
}



template <class T_ELE>
DWORD Linkedlist<T_ELE>::GetElement(IN DWORD dwIndex, OUT T_ELE& Element) {
	NODE* p = m_pList;
	//���Խ�磬����INDEX_IS_ERROR
	if (dwIndex >= m_dwLenth || dwIndex < 0) {
		return INDEX_IS_ERROR;
	}
	//��������������һ�����������m_pList_END��������
	if (dwIndex == m_dwLenth-1) {
		memcpy(&Element, &m_pList->Data, sizeof(T_ELE));
		return SUCCESS;
	}
	//ѭ������
	while (dwIndex) {
		p = p->pNext;
		dwIndex--;
	}
	memcpy(&Element, &p->Data, sizeof(T_ELE));
	return SUCCESS;

}

template <class T_ELE>
DWORD Linkedlist<T_ELE>::GetElementIndex(const IN T_ELE& Element) {
	PNODE p = m_pList;
	//ѭ���ҳ���Ӧ��Ԫ��
	for (int i = 0; i < m_dwLenth; i++) {
		if (!memcmp(&p->Data,&Element,sizeof(T_ELE))) {
			return i;
		}
		p = p->pNext;
	}
	//�Ҳ�������error
	return ERROR;
}



template<class T_ELE>
DWORD Linkedlist<T_ELE>::Insert(IN DWORD dwIndex, IN const T_ELE& Element) {
	PNODE p = m_pList;
	//���������ǵ�һ��,��ָ������Ϊ0�Ļ�,��ֱ�Ӳ���,��������ﻹû������,���������Ϊ��0�򷵻ش��������ֵ
	if (!m_dwLenth || !m_pList) {
		if (dwIndex) {
			return INDEX_IS_ERROR;
		}
		this->Insert(Element);
		return SUCCESS;
	}
	if (!dwIndex) {
		PNODE Temp = new NODE{};
		memcpy(&Temp->Data, &Element, sizeof(T_ELE));
		Temp->pNext = m_pList;
		m_pList = Temp;
		return SUCCESS;
	}


	//���Խ�磬���ش��������ֵ
	if (dwIndex > m_dwLenth || dwIndex < 0) {
		return INDEX_IS_ERROR;
	}
	//���Ҫ����ĵط��պ�����һ���ط�����ֱ�Ӳ���
	if (dwIndex == m_dwLenth) {
		m_pList_END->pNext = new NODE{};
		m_pList_END = m_pList_END->pNext;
		memcpy(&m_pList_END->Data, &Element, sizeof(T_ELE));
		m_dwLenth++;
		return SUCCESS;
	}
	//��λ��ָ������ǰһ���ṹ
	dwIndex--;
	while (dwIndex--)
		p = p->pNext;
	//��¼ԭ��ָ��������ָ��
	DWORD temp = (DWORD)p->pNext;
	//���Ľ�ָ��������һ���ṹ��ָ��ָ���·�����ڴ�
	p->pNext = new NODE{};
	p = p->pNext;
	//�����������·�����ڴ�
	memcpy(&p->Data, &Element, sizeof(T_ELE));
	//��ָ���Ϊ��һ���ṹ
	p->pNext = (PNODE)temp;
	//��Ϊ�������µ����ݣ����ȼ�һ
	m_dwLenth++;
	return SUCCESS;
}


template<class T_ELE>
DWORD Linkedlist<T_ELE>::Delete(IN DWORD dwIndex) {
	PNODE pl = m_pList;
	
	//�ж��Ƿ�Խ��
	if (dwIndex >= m_dwLenth || dwIndex < 0) {
		return INDEX_IS_ERROR;
	}
	//�ҵ�ָ����������һ������ֵ
	while (dwIndex-1) {
		pl = pl->pNext;
		dwIndex--;
	}
	//�ҵ�ָ������ֵ����һ���������������ַ
	PNODE p = pl->pNext;
	DWORD tempr = (DWORD)p->pNext;
	//�ͷ�ָ���������ڴ�
	delete pl->pNext;
	//����һ������ָ�����¸�
	pl->pNext = (PNODE)tempr;
	//���ȼ�һ
	m_dwLenth--;
	return SUCCESS;


}


template <class T_ELE>
DWORD Linkedlist<T_ELE>::GetSize() {
	return m_dwLenth;
}
