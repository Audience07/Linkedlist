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
	BOOL IsEmpty();												//判断链表是否为空
	VOID Clear();												//循环释放链表分配的内存
	DWORD GetElement(IN DWORD dwIndex, OUT T_ELE& Element);		//获取指定索引数据
	DWORD GetElementIndex(const IN T_ELE& Element);				//获取指定数据索引
	DWORD Insert(IN const T_ELE& Element);						//在尾部插入
	DWORD Insert(IN DWORD dwIndex, IN const T_ELE& Element);	//在指定索引插入
	DWORD Delete(IN DWORD dwIndex);								//删除指定索引
	DWORD GetSize();											//获取大小
private:
	typedef struct _NODE{
		T_ELE Data;				//数据
		_NODE* pNext;			//下一个结构的指针
	}NODE,*PNODE;
	/*PNODE GetIndexPreviousNode(DWORD dwIndex);
	PNODE GetIndexCurrentNode(DWORD dwIndex);					
	PNODE GetIndexNextNode(DWORD dwIndex);*/


private:
	PNODE m_pList;												//链表头部指针
	PNODE m_pList_END;											//链表局部指针
	DWORD m_dwLenth;											//链表存有数据长度
};

//构造函数
template <class T_ELE>
Linkedlist<T_ELE>::Linkedlist() :m_pList(NULL),m_pList_END(NULL), m_dwLenth(0) {};

//析构函数
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
	//判断链表是否为空
	if (this->IsEmpty()) {
		return;
	}
	//定义一个指针，指向链表首位
	p = m_pList;
	//判断链表中的地址是否为空，如果为空，则停止循环，如果不为空，则删除下一个元素
	while (p)
	{
		//将指针指向下一个元素，然后将当前内存释放
		temp = p;
		p = p->pNext;
		delete temp;
	}
	//给p赋为空指针
	p = nullptr;

	//设置链表的头和尾
	m_pList = nullptr;
	m_pList_END = nullptr;
	//将链表长度设置为0
	m_dwLenth = 0;

}


template<class T_ELE>
DWORD Linkedlist<T_ELE>::Insert(IN const T_ELE& Element) {
	//判断链表是否为空，如果为空，则在起始指针分配内存
	if (!m_pList) {
		//分配内存
		m_pList = new NODE{};
		//将元素填入分配的内存的data
		memcpy(m_pList, &Element, sizeof(T_ELE));
		//长度加一
		m_dwLenth++;
		//设置链表尾
		m_pList_END = m_pList;
		return SUCCESS;
	}
	//在尾部分配内存
	m_pList_END->pNext = new NODE{};
	//将尾部指针挪如下一块内存
	m_pList_END = m_pList_END->pNext;
	//往这块内存中存入值
	memcpy(&m_pList_END->Data, &Element, sizeof(T_ELE));
	//链表长度加一
	m_dwLenth++;

	return SUCCESS;
}



template <class T_ELE>
DWORD Linkedlist<T_ELE>::GetElement(IN DWORD dwIndex, OUT T_ELE& Element) {
	NODE* p = m_pList;
	//如果越界，返回INDEX_IS_ERROR
	if (dwIndex >= m_dwLenth || dwIndex < 0) {
		return INDEX_IS_ERROR;
	}
	//如果是链表中最后一个数，则根据m_pList_END返回数据
	if (dwIndex == m_dwLenth-1) {
		memcpy(&Element, &m_pList->Data, sizeof(T_ELE));
		return SUCCESS;
	}
	//循环查找
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
	//循环找出对应的元素
	for (int i = 0; i < m_dwLenth; i++) {
		if (!memcmp(&p->Data,&Element,sizeof(T_ELE))) {
			return i;
		}
		p = p->pNext;
	}
	//找不到返回error
	return ERROR;
}



template<class T_ELE>
DWORD Linkedlist<T_ELE>::Insert(IN DWORD dwIndex, IN const T_ELE& Element) {
	PNODE p = m_pList;
	//如果插入的是第一个,且指定索引为0的话,则直接插入,如果容器里还没有数据,想插入索引为非0则返回错误的索引值
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


	//如果越界，返回错误的索引值
	if (dwIndex > m_dwLenth || dwIndex < 0) {
		return INDEX_IS_ERROR;
	}
	//如果要插入的地方刚好是下一个地方，则直接插入
	if (dwIndex == m_dwLenth) {
		m_pList_END->pNext = new NODE{};
		m_pList_END = m_pList_END->pNext;
		memcpy(&m_pList_END->Data, &Element, sizeof(T_ELE));
		m_dwLenth++;
		return SUCCESS;
	}
	//定位到指定索引前一个结构
	dwIndex--;
	while (dwIndex--)
		p = p->pNext;
	//记录原本指定索引的指针
	DWORD temp = (DWORD)p->pNext;
	//更改将指定索引上一个结构的指针指向新分配的内存
	p->pNext = new NODE{};
	p = p->pNext;
	//将数据填入新分配的内存
	memcpy(&p->Data, &Element, sizeof(T_ELE));
	//将指针改为下一个结构
	p->pNext = (PNODE)temp;
	//因为插入了新的数据，长度加一
	m_dwLenth++;
	return SUCCESS;
}


template<class T_ELE>
DWORD Linkedlist<T_ELE>::Delete(IN DWORD dwIndex) {
	PNODE pl = m_pList;
	
	//判断是否越界
	if (dwIndex >= m_dwLenth || dwIndex < 0) {
		return INDEX_IS_ERROR;
	}
	//找到指定索引的上一个索引值
	while (dwIndex-1) {
		pl = pl->pNext;
		dwIndex--;
	}
	//找到指定索引值的下一个索引，并保存地址
	PNODE p = pl->pNext;
	DWORD tempr = (DWORD)p->pNext;
	//释放指定索引的内存
	delete pl->pNext;
	//将下一个索引指向下下个
	pl->pNext = (PNODE)tempr;
	//长度减一
	m_dwLenth--;
	return SUCCESS;


}


template <class T_ELE>
DWORD Linkedlist<T_ELE>::GetSize() {
	return m_dwLenth;
}
