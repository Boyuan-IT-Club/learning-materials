template <typename __Tp>
class node
{
public:
    __Tp data;
    class node *pre;
    class node *next;
};

template <typename __Tp>
node<__Tp> *newNode()
{
    node<__Tp> *newNode = (node<__Tp> *)malloc(sizeof(node<__Tp>));
    newNode->pre = NULL;
    newNode->next = NULL;
    return newNode;
}

template <typename __Tp>
class list
{
public:
    node<__Tp> *head;
    bool empty() { return (head->next == head); }

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

protected:
    list()
    {
        head = newNode<__Tp>();
        head->pre = head;
        head->next = head;
    }
};

template <typename __Tp>
class stack : virtual public list<__Tp>
{
public:
    void push_front(__Tp data)
    {
        node<__Tp> *pushNode = newNode<__Tp>();
        pushNode->data = data;
        pushNode->pre = this->head;
        pushNode->next = this->head->next;
        pushNode->pre->next = pushNode;
        pushNode->next->pre = pushNode;
    }

    virtual void swap(stack<__Tp> another)
    {
        node<__Tp> *swapNode = another.head;
        another.head = this->head;
        this->head = swapNode;
        return;
    }
};

template <typename __Tp>
class queue : virtual public list<__Tp>
{
public:
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

    virtual void swap(queue<__Tp> another)
    {
        node<__Tp> *swapNode = another.head;
        another.head = this->head;
        this->head = swapNode;
        return;
    }
};

template <typename __Tp>
class deque : public stack<__Tp>, public queue<__Tp>
{
public:
    void pop_back()
    {
        if (this->empty())
            return;
        node<__Tp> *popNode = this->head->pre;
        popNode->pre->next = popNode->next;
        popNode->next->pre = popNode->pre;
        free(popNode);
    }
    virtual void swap(deque<__Tp> another)
    {
        node<__Tp> *swapNode = another.head;
        another.head = this->head;
        this->head = swapNode;
        return;
    }
};

template <typename __Tp>
class linkList : public deque<__Tp>
{
public:
    node<__Tp> *begin() { return this->head->next; }
    node<__Tp> *end() { return this->head; }
    node<__Tp> *rbegin() { return this->head->pre; }
    node<__Tp> *rend() { return this->head; }

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

    __Tp at(int pos)
    {
        node<__Tp> *now = find(pos);
        if (now != NULL)
            return find(pos)->data;
    }

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
    virtual void swap(linkList<__Tp> another)
    {
        node<__Tp> *swapNode = another.head;
        swapNode = this->head;
        this->head = another.head;
        return;
    }
};