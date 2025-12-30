<div _ngcontent-ng-c2984736400="" class="immersive-editor markdown stronger" id="extended-response-markdown-content"><div contenteditable="true" translate="no" class="ProseMirror"><h1>Linkedlist - C++ 模板链表实现</h1><p>一个基于 C++ 模板类实现的单向链表，支持通用数据类型（<code>T_ELE</code>），并针对 Windows 环境下的 <code>DWORD</code> 和 <code>BOOL</code> 类型进行了适配。该实现提供了基础的增删改查功能，并支持索引操作。</p><h2>🚀 特性</h2><ul><li><p><strong>泛型支持</strong>：使用 <code>template &lt;class T_ELE&gt;</code>，可存储任意数据类型。</p></li><li><p><strong>高效尾插</strong>：维护了 <code>m_pList_END</code> 指针，实现 <math-inline class="math-inline math-node" data-math="O(1)" title="" contenteditable="false"><span class="math-render"><span class="katex"><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal" style="margin-right: 0.0278em;">O</span><span class="mopen">(</span><span class="mord">1</span><span class="mclose">)</span></span></span></span></span><span class="math-src" spellcheck="false"></span></math-inline> 时间复杂度的尾部插入。</p></li><li><p><strong>安全检查</strong>：内置索引越界检查及状态返回宏。</p></li><li><p><strong>内存管理</strong>：完整的析构逻辑与 <code>Clear()</code> 函数，防止内存泄漏。</p></li></ul><h2>🛠️ API 参考</h2><h3>宏定义状态码</h3><table><tbody><tr><td><p><strong>宏名</strong></p></td><td><p><strong>值</strong></p></td><td><p><strong>说明</strong></p></td></tr><tr><td><p><code>SUCCESS</code></p></td><td><p><code>1</code></p></td><td><p>操作成功</p></td></tr><tr><td><p><code>ERROR</code></p></td><td><p><code>-1</code></p></td><td><p>通用错误</p></td></tr><tr><td><p><code>INDEX_IS_ERROR</code></p></td><td><p><code>-2</code></p></td><td><p>索引越界或无效</p></td></tr><tr><td><p><code>BUFFER_IS_EMPTY</code></p></td><td><p><code>-3</code></p></td><td><p>缓冲区/链表为空</p></td></tr></tbody></table><h3>核心方法</h3><h4>1. 基础状态</h4><ul><li><p><code>BOOL IsEmpty()</code>: 判断链表是否为空。</p></li><li><p><code>DWORD GetSize()</code>: 获取当前链表中的元素数量。</p></li></ul><h4>2. 插入操作</h4><ul><li><p><code>DWORD Insert(const T_ELE&amp; Element)</code>: 在链表<strong>末尾</strong>插入数据。</p></li><li><p><code>DWORD Insert(DWORD dwIndex, const T_ELE&amp; Element)</code>: 在<strong>指定索引</strong>位置插入数据。</p></li></ul><h4>3. 删除与清空</h4><ul><li><p><code>DWORD Delete(DWORD dwIndex)</code>: 删除指定索引位置的节点。</p></li><li><p><code>VOID Clear()</code>: 清空链表所有数据并释放内存。</p></li></ul><h4>4. 查询操作</h4><ul><li><p><code>DWORD GetElement(DWORD dwIndex, T_ELE&amp; Element)</code>: 获取指定索引的数据（通过引用返回）。</p></li><li><p><code>DWORD GetElementIndex(const T_ELE&amp; Element)</code>: 查找数据在链表中的第一个匹配索引。</p></li></ul><h2>💻 使用示例</h2><pre><code>#include "LinkList.h"
#include &lt;iostream&gt;

int main() {
    Linkedlist&lt;int&gt; myList;

    // 1. 插入数据
    myList.Insert(100);
    myList.Insert(200);
    myList.Insert(0, 50); // 在头部插入 50

    // 2. 获取长度
    std::cout &lt;&lt; "Size: " &lt;&lt; myList.GetSize() &lt;&lt; std::endl; // 输出 3

    // 3. 遍历查询
    int val;
    for (DWORD i = 0; i &lt; myList.GetSize(); i++) {
        if (myList.GetElement(i, val) == SUCCESS) {
            std::cout &lt;&lt; "Index " &lt;&lt; i &lt;&lt; ": " &lt;&lt; val &lt;&lt; std::endl;
        }
    }

    // 4. 删除索引为1的元素
    myList.Delete(1);

    // 5. 清空链表
    myList.Clear();

    return 0;
}
<br class="ProseMirror-trailingBreak"></code></pre><h2>⚠️ 注意事项</h2><ol><li><p><strong>内存拷贝</strong>：本项目内部使用 <code>memcpy</code> 和 <code>memcmp</code> 进行数据操作。</p><ul><li><p>适用于基本数据类型（int, char, double）或 POD (Plain Old Data) 结构体。</p></li><li><p><strong>不建议</strong> 直接用于包含复杂对象（如 <code>std::string</code> 或带有虚函数的类），否则可能会导致深拷贝失效或内存错误。</p></li></ul></li><li><p><strong>环境要求</strong>：代码依赖 <code>&lt;Windows.h&gt;</code>，主要针对 Windows 平台开发。