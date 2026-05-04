#include <iostream>
#include <cstring>
#include "stackQueue.h"

using namespace std;

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
        default: return 0;  //nem muvelet
    }
}

void convertInfixToPostfix(char infix[], char postfix[])
{
    Stack verem;
    Queue sor;

    for(int i = 0; infix[i] != 0; i++)
    {
        if(isdigit(infix[i]))
        {
            sor.push(infix[i]);
        }
        else if(infix[i] == '(')
        {
            verem.push(infix[i]);
        }
        else if(infix[i] == ')')
        {
            char c;
            do
            {
                c = verem.pop();
                if(c != '(')
                    sor.push(c);
            }while(c != '(');
        }
        else    //muvelet
        {
            if(verem.isEmpty())
                verem.push(infix[i]);
            else
            {
                int prior = prioritas(infix[i]);
                int veremPrior;
                while(!verem.isEmpty() && prior <= prioritas(verem.onTop()))
                {
                    sor.push(verem.pop());
                }
                verem.push(infix[i]);
            }
        }
    }
    while(!verem.isEmpty())
        sor.push(verem.pop());

    int i = 0;
    while(!sor.isEmpty())
    {
        postfix[i] = sor.pop();
        i++;
    }
    postfix[i] = 0;
}

int main()
{
    char infix[100];
    char postfix[100];
    strcpy(infix, "(1+(2+3)*4)^(3-2*1)/3");
    cout << "infix" << endl << infix << endl;
    convertInfixToPostfix(infix, postfix);
    cout << "postfix" << endl << postfix << endl;

    return 0;
}
