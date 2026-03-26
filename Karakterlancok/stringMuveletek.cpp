#include <iostream>
#include <cstring>
using namespace std;
void kiir(char s[]){
    for(char *p=s;*p!=0;p++)
    {
        cout<<*p;
    }
    cout<<endl;
}
int stringLenght(char s[]){
    int len = 0;
    for(char *p=s;*p!=0;p++){
        len++;
    }
    return len;
}
void stringCopy(char source[],char dest[]){

    //while(*dest++==*source++);

    while(*source!=0)
    {
        //*dest++=*source++;

        *dest=*source;
        dest++;
        source++;
    }
    *dest = 0;
}

void stringConcatenate(char source[], char dest[])
{
    while(*dest!=0)
    {
        dest++;
    }//amikor eleri a ,most jelenleg a 'szia' esteben, az 5. betut akkor kezdi utana masolni a source-ot

    while(*source!=0)
    {
        *dest=*source;
        dest++;
        source++;
    }
    *dest = 0;
}

void toppercase(char s[])//kis betubol nagyot csinal
{
    for(char *p=s; *p!=0; p++)
    {
        if(*p>='a' && *p<='z')
        {
            *p=*p-'a'+'A';

        }
    }
}

int stringcompare(char a[], char b[])//strcmp
{
    char *p=a; char *q=b;
    while(*p!=0 && *q!=0)
    {
        if(*p!=*q)
            return *p-*q;
            p++;
            q++;
    }
    return *p-*q;
}

void lowercase(char s[])//nagy betubol kicsit csinal
{
    for(char *p=s; *p!=0; p++)
    {
        if(*p>='A' && *p<='Z')
        {
            *p=*p+'a'-'A';

        }
    }
}

char *findStringChar(char source[], char what)
{
    for(char *p=source; *p !=0; p++)
    {
        if(*p==what )
            return p;
    }
    return 0;
}

char *findStringString(char source[], char what[])
{
    for(char *p=source; *p !=0; p++)
    {
        int i=0;
        while(*(p + i)!= 0 && what[i] !=0 && *(p + i)==what[i])
        {
            i++;
        }
        if(what[i]==0)
            return p;
    }

    return 0;
}
void replaceCharChar(char source[], char match, char target)
{
    for(char *p = source; *p != 0; p++)
    {
        if(*p == match)
            *p = target;
    }
}

void replaceCharString(char source[], char match, char target[])
{
    char tmp[100];
    stringCopy(source, tmp);
    char *q = source;
    for(char *p = tmp; *p != 0; p++)
    {
        if(*p == match)
        {
            for(char *t = target; *t != 0; t++)
            {
               *q = *t;
                q++;
            }
        }
        else
        {
            *q = *p;
            q++;
        }
    }
    *q = 0;
}

void replaceCharString(char source[], char match, char target[])
{
    char tmp[100];
    stringCopy(source, tmp);
    char *q = source;
    for(char *p = tmp; *p != 0; p++)
    {
        if(*p == match)
        {
            for(char *t = target; *t != 0; t++)
            {
               *q = *t;
                q++;
            }
        }
        else
        {
            *q = *p;
            q++;
        }
    }
    *q = 0;
}

void replaceStringString(char source[], char match[], char target[])
{
    char tmp[10000];
    stringCopy(source, tmp);
    char *q = source;
    for(char *p = tmp; *p != 0; p++)
    {
        int i=0;
        while(*(p + i) != 0 && match[i]!=0 && match[i] == *(p + i)){
            i++;}
        if(match[i]==0){
            for(char *t = target; *t != 0; t++)
            {
               *q = *t;
                q++;

            }
            for(char *t = match; *t != 0; t++)
            {
               p++;
            }
            p--;
        }
        else
        {
            *q = *p;
            q++;
        }
    }
    *q = 0;
}

int main()
{
   char s[100]="alma alma piros alma odafenn a fan";
   /*
   cout << s[4] << endl;
   for(int i=0;s[i]!=0;i++){
        cout << s[i] << endl;
   }
    char *p=s;
    cout<< s[1]<<endl;
    cout<< (s+2)<<endl;
    cout<< (p+2)<<endl;
char s2[100] = "geza kek az eg";
    kiir(s2);
    cout<<stringLenght(s2)<<endl;
char s3[100];
    stringCopy("szia", s3);
    cout<<s3;
    cout<<endl;
    stringConcatenate(s2, s3);
    cout<<s3;
cout<<endl;
    toppercase(s2);
    cout<<s2<<endl;
cout<<endl;
    lowercase(s2);
    cout<<s2<<endl;
cout<<endl;
    cout<<stringcompare("alma", "alma")<<endl;*/

    //cout<<findStringChar(s, 'l')<<endl;
    //cout<<findStringString(s, "lm")<<endl;
    replaceCharChar(s, 'a', '@');
    cout<<s<<endl;
    replaceCharString(s, '@', "ALMA");
    cout<<s<<endl;

    return 0;
}
