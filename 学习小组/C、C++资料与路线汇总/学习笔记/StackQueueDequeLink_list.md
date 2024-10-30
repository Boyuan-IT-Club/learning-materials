# 基于C++面向对象与模板以带有头节点的环形双向链表为基础，对链表、栈、队列和双向队列的实现

作者：10234507025张春晓

 <p xmlns:cc="http://creativecommons.org/ns#" >本文及代码文件遵循 <a href="https://creativecommons.org/licenses/by/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC BY 4.0共享协议<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1" alt=""></a></p>

注：尚在更新，下一步

1. 代码部分讲解
2. 额外功能实现
3. 荣誉代码优化

## 采用带有头节点的环形双向链表的原因？

```mermaid
flowchart LR；
    head-->|next|node_0-->|next|node_1-.->|next|node_n-->|next|head;
    head-->|pre|node_n-.->|pre|node_1-->|pre|node_0-->|pre|head;   
```

此为**带有头节点的环形双向链表**的结构示意图，不难看出，在已知头节点的情况下，找到第一个节点、尾节点的时间复杂度均为O(1)，寻找任意节点的前节点与后节点的时间复杂度也为O(1)，处理部分操作时速率更快，便于后续结构的实现。

## 明确需求

参考[OI Wiki中对于STL中序列式容器的介绍](https://oi-wiki.org/lang/csl/sequence-container/#list-%E7%9A%84%E4%BD%BF%E7%94%A8%E6%96%B9%E6%B3%95)，结合自身能力，大致实现如下功能：

### 栈

- `empty()`：`true`为空，`false`为非空。
- `pop_front()`：弹出栈顶元素。
- `push_front()`：将元素压入栈顶。
- `size()`：返回栈的元素个数。
- `swap()`：与另一个栈交换。
- `front()`：返回栈顶元素。

### 队列

- `back()`：返回队尾元素
- `front()`：返回队首元素
- `empty()`：`true`为空，`false`为非空。
- `pop_front()`：删除队首元素
- `push_back()`：在队尾插入一个元素
- `size()`：返回元素个数
- `swap()`：交换两个队列

### 双向队列

- `front()`：返回队首元素
- `back()`：返回队尾元素
- `empty()`：`true`为空，`false`为非空
- `push_front()`：在队首插入一个元素
- `pop_front()`：删除队首的元素
- `push_back()`：在队尾插入一个元素
- `pop_back()`：删除队尾的元素
- `size()`：返回元素个数
- `swap()`：交换两个双向队列

### 链表

- `at()`：返回指定位置元素的引用
- `front()`：返回首元素的引用
- `back()`：返回尾元素的引用
- `begin()`：返回指向首元素的指针
- `end()`：返回指向尾端占位符元素的指针，在该实现方案中，返回的是指向头节点的指针
- `rbegin()`：返回指向末元素的指针
- `rend()`：返回指向首元素前一位置的指针，在该实现方案中，返回的是指向头节点的指针
- `empty()`：`true`为空，`false`为非空
- `size()`：返回元素数量
- `clear()`：清除所有元素
- `insert()`：在指定位置插入元素并返回指向插入元素的指针
- `erase()`：删除指定位置的元素
- `push_front()`：在开头插入一个元素
- `pop_front()`：删除开头的元素
- `push_back()`：在末尾插入一个元素
- `pop_back()`：删除末尾的元素
- `swap()`：交换两个链表

不难看出，以上四个结构相似的函数有`empty()`、`pop_front()`、`size()`、`front()`。

## 造轮子 Time

### 定义节点模板

```cpp
template <typename __Tp>
class node
{
public:
    __Tp data;
    class node *pre;
    class node *next;
};
```

### 定义新建节点模板函数

```cpp
template <typename __Tp>
node<__Tp> *newNode()
{
    node<__Tp> *newNode = (node<__Tp> *)malloc(sizeof(node<__Tp>));
    newNode->pre = NULL;
    newNode->next = NULL;
    return newNode;
}
```

### 定义表模板类

```cpp
template <typename __Tp>
class list
{
public:
    node<__Tp> *head;
    
protected:
    list()
    {
        head = newNode<__Tp>();
        head->pre = head;
        head->next = head;
    }
};
```

#### 实现`empty()`函数

```cpp
    bool empty() { return (head->next == head); }
```

#### 实现`size()`函数

```cpp
    int size()
    {
        node<__Tp> *now = this->head;
        int count = 0;
        while (now->next != this->head)
        {
            count++;
            now = now->next;
        }
        return count;
    }
```

#### 实现`front()`与`pop_front()`函数

```cpp
    __Tp front()
    {
        if (!this->empty())
            return this->head->next->data;
    }

    void pop_front()
    {
        if (empty())
            return;
        node<__Tp> *popNode = head->next;
        popNode->pre->next = popNode->next;
        popNode->next->pre = popNode->pre;
        free(popNode);
    }
```

### 定义栈模板类

```cpp
template <typename __Tp>
class stack : virtual public list<__Tp>
{
public:
    
};
```

#### 实现`push_front()`函数

```cpp
    void push_front(__Tp data)
    {
        node<__Tp> *pushNode = newNode<__Tp>();
        pushNode->data = data;
        pushNode->pre = this->head;
        pushNode->next = this->head->next;
        pushNode->pre->next = pushNode;
        pushNode->next->pre = pushNode;
    }
```

#### 实现`swap()`函数

```cpp
    virtual void swap(stack<__Tp> another)
    {
        node<__Tp> *swapNode = another.head;
        another.head = this->head;
        this->head = swapNode;
        return;
    }
```

### 定义队列模板类

```cpp
template <typename __Tp>
class queue : virtual public list<__Tp>
{
public:
    
};
```

#### 实现`back()`与`push_back()`函数

```cpp
    __Tp back()
    {
        if (!this->empty())
            return this->head->pre->data;
    }

    void push_back(__Tp data)
    {
        node<__Tp> *pushNode = newNode<__Tp>();
        pushNode->data = data;
        pushNode->next = this->head;
        pushNode->pre = this->head->pre;
        pushNode->pre->next = pushNode;
        pushNode->next->pre = pushNode;
    }
```

#### 实现`swap()`函数

```cpp
    virtual void swap(queue<__Tp> another)
    {
        node<__Tp> *swapNode = another.head;
        another.head = this->head;
        this->head = swapNode;
        return;
    }
```

### 定义双向队列模板类

```cpp
template <typename __Tp>
class deque : public stack<__Tp>, public queue<__Tp>
{
public:
    
};
```

#### 实现`pop_back()`函数

```cpp
    void pop_back()
    {
        if (this->empty())
            return;
        node<__Tp> *popNode = this->head->pre;
        popNode->pre->next = popNode->next;
        popNode->next->pre = popNode->pre;
        free(popNode);
    }
```

#### 实现`swap()`函数

```cpp
    virtual void swap(deque<__Tp> another)
    {
        node<__Tp> *swapNode = another.head;
        another.head = this->head;
        this->head = swapNode;
        return;
    }
```

### 定义链表模板类

```cpp
template <typename __Tp>
class linkList : public deque<__Tp>
{
public:

};
```

#### 实现`begin()`、`end()`、`rbegin()`、`rend()`函数

```cpp
    node<__Tp> *begin() { return this->head->next; }
    node<__Tp> *end() { return this->head; }
    node<__Tp> *rbegin() { return this->head->pre; }
    node<__Tp> *rend() { return this->head; }
```

#### 实现`swap()`函数

```cpp
    virtual void swap(linkList<__Tp> another)
    {
        node<__Tp> *swapNode = another.head;
        swapNode = this->head;
        this->head = another.head;
        return;
    }
```

#### 实现`clear()`函数
```cpp
    void clear()
    {
        node<__Tp> *now = this->head->next;
        node<__Tp> *del = now;
        while (now != this->head)
        {
            del = now;
            now = now->next;
            free(del);
        }
        this->head->pre = this->head;
        this->head->next = this->head;
        return;
    }
```

#### 实现`find()`函数

```cpp

    node<__Tp> *find(int pos)
    {
        int count = -1;
        node<__Tp> *now = this->head;
        while ((now != this->head || count == -1) && pos > count)
        {
            count++;
            now = now->next;
        }
        if (pos == count && now != this->head)
            return now;
        else
            return NULL;
    }
```

#### 实现`at()`函数

```cpp
    __Tp at(int pos)
    {
        node<__Tp> *now = find(pos);
        if (now != NULL)
            return find(pos)->data;
    }
```

#### 实现`insert()`函数

```cpp

    node<__Tp> *insert(int pos, __Tp data)
    {
        node<__Tp> *now = find(pos - 1);
        if (now != NULL)
        {
            node<__Tp> *insNode = newNode<__Tp>();
            insNode->data = data;
            insNode->pre = now;
            insNode->next = now->next;
            insNode->pre->next = insNode;
            insNode->next->pre = insNode;
            return insNode;
        }
    }
```

#### 实现`erase()`函数

```cpp
void erase(int pos)
    {
        node<__Tp> *now = find(pos);
        if (now != NULL)
        {
            now->pre->next = now->next;
            now->next->pre = now->pre;
            free(now);
            return;
        }
    }
```