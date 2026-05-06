#ifndef STACKQUEUE_H_INCLUDED
#define STACKQUEUE_H_INCLUDED

#include "Token.h"
#include <iostream>

using namespace std;

struct ListNode
{
    Token *adat;
    ListNode *next;
    ListNode(Token *adat)
    {
        this->adat = adat;
        this->next = NULL;
    }
    ListNode(Token *adat, ListNode *next)
    {
        this->adat = adat;
        this->next = next;
    }
    ~ListNode()
    {
        if(this->next) delete this->next;
    }
    void felfuz(Token *adat)
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
    void push(Token *adat)
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
    Token *front()
    {
        return first ? first->adat : NULL;
    }
    Token *pop()
    {
        if(!first) return NULL;

        Token *adat = first->adat;
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
     void kiir() {
        ListNode *l=first;
        while(l) {
            switch(l->adat->type) {
            case 1: cout << (((Szam *)l->adat)->szam); break;
            case 2: cout << (((Zarojel *)l->adat)->c); break;
            case 3: cout << (((Muvelet *)l->adat)->c); break;
            }
            cout << " ";
            l = l->next;
        }
        cout << endl;
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
    void push(Token *adat)
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
    Token *onTop()
    {
        return first ? first->adat : NULL;
    }
    Token *pop()
    {
        if(!first) return NULL;

        Token *adat = first->adat;
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
    void kiir() {
        ListNode *l = first;
        while(l) {
            switch(l->adat->type) {
            case 1: cout << (((Szam *)l->adat)->szam); break;
            case 2: cout << (((Zarojel *)l->adat)->c); break;
            case 3: cout << (((Muvelet *)l->adat)->c); break;
            }
            cout << " ";
            l = l->next;
        }
        cout << endl;
    }
};

#endif // STACKQUEUE_H_INCLUDED
