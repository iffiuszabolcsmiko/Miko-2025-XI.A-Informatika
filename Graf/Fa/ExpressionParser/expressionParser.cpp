#include <iostream>
#include <cstring>
#include "stackQueue.h"

using namespace std;

class ExpressionParser
{
private:
    char input[100];
    Queue infix;
    Queue postfix;

    int hatvany(int a, int k)
    {
        if(k == 0) return 1;
        if(k % 2 == 0)
        {
            int tmp = hatvany(a, k / 2);
            return tmp * tmp;
        }
        else
            return a * hatvany(a, k - 1);
    }

    int faktorialis(int k)
    {
        int prod = 1;
        for(int i = 1; i <= k; i++)
            prod = prod * i;
        return prod;
    }

    int prioritas(char muv)
    {
        switch(muv)
        {
            case '+': return 1;
            case '-': return 1;
            case '*': return 2;
            case '/': return 2;
            case '%': return 2;
            case '^': return 3;
            case '!': return 4;
            default: return 0;
        }
    }

    int aritas(char muv)
    {
        switch(muv)
        {
            case '+': return 2;
            case '-': return 2;
            case '*': return 2;
            case '/': return 2;
            case '%': return 2;
            case '^': return 2;
            case '!': return 1;
            default: return 0;
        }
    }

    bool muvelet(char muv)
    {
        return  muv == '+' ||
                muv == '-' ||
                muv == '*' ||
                muv == '/' ||
                muv == '%' ||
                muv == '^' ||
                muv == '!';
    }

    int olvasEgeszSzam(char **p) {
        int szam = 0;
        while(**p && isdigit(**p)) {
            szam *= 10;
            szam += **p - '0';
            (*p)++;
        }
        return szam;
    }

    void tokenize()  {
        char *p = input;
        while(*p)
        {
            if(isdigit(*p))
            {
                infix.push(new Szam(olvasEgeszSzam(&p)));
            }
            else if(muvelet(*p))
            {
                infix.push(new Muvelet(*p));
                p++;
            }
            else if(*p == '(' || *p == ')')
            {
                infix.push(new Zarojel(*p));
                p++;
            }
            else
            {
                p++;
            }
            //Itt lehet kiegesziteni fuggvenyekkel valtozokkal stb.
        }
    }

    void convertInfixToPostfix()
    {
        Stack verem;
        while(!infix.isEmpty())
        {
            Token *t = infix.pop();
            switch(t->type) {
            //Szam
            case 1: postfix.push(t); break;
            //Zarojel
            case 2:
                if(((Zarojel *)t)->c == '(')
                    verem.push(t);
                else
                {
                    Token *tmp;
                    while(true)
                    {
                        tmp = verem.pop();
                        if(!tmp) break;
                        if(tmp->type == 2 && ((Zarojel *)tmp)->c == '(')
                        {
                            delete tmp;
                            break;
                        }
                        postfix.push(tmp);
                    }
                    delete t;
                }
                break;
            //Muvelet
            case 3:
                int prior = prioritas(((Muvelet *)t)->c);
                int veremPrior;
                while(!verem.isEmpty() && prior <= prioritas(((Muvelet *)verem.onTop())->c))
                {
                    postfix.push(verem.pop());
                }
                verem.push(t);
                break;
            }
        }
        while(!verem.isEmpty())
            postfix.push(verem.pop());
    }
public:
    ExpressionParser(char input[])
    {
        strcpy(this->input, input);
    }
    int resolvePostfix()
    {
        tokenize();
        //infix.kiir();
        convertInfixToPostfix();
        //postfix.kiir();
        Stack verem;
        while(!postfix.isEmpty())
        {
            Token *t = postfix.pop();
            if(t->type == 1)
            {
                verem.push(t);
            }
            else //muvelet
            {
                Szam *a = 0, *b = 0;
                switch(((Muvelet *)t)->c)
                {
                    case '+':
                        b = (Szam *)verem.pop();
                        a = (Szam *)verem.pop();
                        verem.push(new Szam(a->szam + b->szam));
                        break;
                    case '-':
                        b = (Szam *)verem.pop();
                        a = (Szam *)verem.pop();
                        verem.push(new Szam(a->szam - b->szam));
                        break;
                    case '*':
                        b = (Szam *)verem.pop();
                        a = (Szam *)verem.pop();
                        verem.push(new Szam(a->szam * b->szam));
                        break;
                    case '/':
                        b = (Szam *)verem.pop();
                        a = (Szam *)verem.pop();
                        verem.push(new Szam(a->szam / b->szam));
                        break;
                    case '%':
                        b = (Szam *)verem.pop();
                        a = (Szam *)verem.pop();
                        verem.push(new Szam(a->szam % b->szam));
                        break;
                    case '^':
                        b = (Szam *)verem.pop();
                        a = (Szam *)verem.pop();
                        verem.push(new Szam(hatvany(a->szam, b->szam)));
                        break;
                    case '!':
                        a = (Szam *)verem.pop();
                        verem.push(new Szam(faktorialis(a->szam)));
                        break;
                }
                delete t;
                delete a;
                delete b;
            }
        }
        Szam *t = (Szam *)verem.pop();
        int eredmeny = t->szam;
        delete t;
        return eredmeny;
    }
};

int main()
{
    char input[100];
    while(true)
    {
        system("cls");
        cout << "irj egy muveletsort:" << endl;
        cin >> input;
        if(strcmp(input, "exit") == 0)
            break;
        ExpressionParser ep(input);
        cout << "eredmeny: " << ep.resolvePostfix() << endl;
        system("pause");
    }

    return 0;
}
