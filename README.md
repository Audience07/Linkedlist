# Linkedlist (C++ 模板链表)

这是一个基于 C++ 模板类实现的单向链表，支持多种数据类型，并提供了丰富的链表操作接口。

## 🚀 特性

* **模板化设计**：支持 `int`, `float`, 自定义结构体等多种数据类型。
* **内存管理**：内置 `Clear` 函数，在析构时自动释放所有动态分配的节点。
* **操作便捷**：支持尾部插入、指定索引插入、按索引删除、按值查找等常用功能。
* **Win32 兼容**：代码使用了 `Windows.h` 类型定义（如 `DWORD`, `BOOL`），适合在 Windows 开发环境中使用。

## 📋 接口说明

### 公有方法

| 方法 | 描述 | 
| ----- | ----- | 
| `IsEmpty()` | 判断链表是否为空 | 
| `Clear()` | 释放链表分配的所有节点内存 | 
| `Insert(Element)` | 在链表尾部插入新元素 | 
| `Insert(dwIndex, Element)` | 在指定的索引位置插入新元素 | 
| `Delete(dwIndex)` | 删除指定索引位置的元素 | 
| `GetElement(dwIndex, &Element)` | 获取指定索引位置的数据 | 
| `GetElementIndex(Element)` | 获取指定数据所在的索引（线性搜索） | 
| `GetSize()` | 获取当前链表中存储的数据长度 | 

### 返回值定义

* `SUCCESS (1)`：操作成功
* `ERROR (-1)`：常规错误（如未找到元素）
* `INDEX_IS_ERROR (-2)`：索引越界或无效索引
* `BUFFER_IS_EMPTY (-3)`：缓冲区/链表为空

## 💻 快速开始

```cpp
#include "LinkList.h"

int main() {
    Linkedlist<int> list;

    // 1. 插入数据
    list.Insert(10);
    list.Insert(20);
    list.Insert(0, 5); // 在索引0处插入5 -> [5, 10, 20]

    // 2. 获取大小
    printf("Size: %d\n", list.GetSize());

    // 3. 获取元素
    int value;
    if (list.GetElement(1, value) == SUCCESS) {
        printf("Index 1 value: %d\n", value);
    }

    // 4. 删除元素
    list.Delete(1); // 删除 10

    // 5. 清空链表
    list.Clear();

    return 0;
}
```
## 🛠 实现细节节点结构：
```C++
struct _NODE {
    T_ELE Data;       // 数据域
    _NODE* pNext;     // 指针域
};
```
- **内存拷贝**：内部使用 memcpy 进行数据复制，确保了对简单结构体及基本类型的兼容。
- **尾指针优化**：维护了 m_pList_END 指针，使得尾部插入操作的时间复杂度为 $O(1)$。
## ⚠️ 注意事项
- 本链表实现依赖于 `Windows.h`。
- GetElementIndex 使用 `memcmp` 进行值比较，因此对于包含复杂对象（如带指针的类）的类型，请确保其内存布局可被安全比较。