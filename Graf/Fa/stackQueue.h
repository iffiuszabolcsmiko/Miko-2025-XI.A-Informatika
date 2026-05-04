#ifndef STACKQUEUE_H_INCLUDED
#define STACKQUEUE_H_INCLUDED

struct ListNode
{
    int adat;
    ListNode *next;

    ListNode(int adat)
    {
        this->adat = adat;
        this->next = NULL;
    }

    ListNode(int adat, ListNode *next)
    {
        this->adat = adat;
        this->next = next;
    }

    ~ListNode()
    {
        if(this->next) delete this->next;
    }

    void felfuz(int adat)
    {
        if(this->next) this->next->felfuz(adat);
        else this->next = new ListNode(adat);
    }
};

class Queue
{
    ListNode *first;
    ListNode *last;

public:

    Queue()
    {
        first = NULL;
        last = NULL;
    }

    ~Queue()
    {
        if(first) delete first;
        first = NULL;
        last = NULL;
    }

    void push(int adat)
    {
        if(first)
        {
            last->next = new ListNode(adat);
            last = last->next;
        }
        else
        {
            first = new ListNode(adat);
            last = first;
        }
    }

    int elso()
    {
        return first ? first->adat : NULL;
    }

    int front()
    {
        return first ? first->adat : NULL;
    }

    int utolso()
    {
        return last ? last->adat : NULL;
    }

    int pop()
    {
        if(!first) return NULL;

        int adat = first->adat;
        ListNode *tmp = first;
        first = first->next;
        tmp->next = NULL;
        delete tmp;
        return adat;
    }

    bool isEmpty()
    {
        return first == NULL;
    }
};

class Stack
{
    ListNode *first;
    ListNode *last;

public:

    Stack()
    {
        first = NULL;
        last = NULL;
    }

    ~Stack()
    {
        if(first) delete first;
        first = NULL;
        last = NULL;
    }

    void push(int adat)
    {
        if(first)
        {
            ListNode* tmp = new ListNode(adat);
            tmp->next = first;
            first = tmp;
        }
        else
        {
            first = new ListNode(adat);
            last = first;
        }
    }

    int elso()
    {
        return first ? first->adat : NULL;
    }

    int utolso()
    {
        return last ? last->adat : NULL;
    }

    int onTop()
    {
        return first ? first->adat : NULL;
    }

    int pop()
    {
        if(!first) return NULL;

        int adat = first->adat;
        ListNode *tmp = first;
        first = first->next;
        tmp->next = NULL;
        delete tmp;
        return adat;
    }
    bool isEmpty()
    {
        return first == NULL;
    }
};

#endif // STACKQUEUE_H_INCLUDED
