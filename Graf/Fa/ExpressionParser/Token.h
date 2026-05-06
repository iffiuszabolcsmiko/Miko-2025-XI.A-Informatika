#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

class Token
{
public:
    int type;
};

class Szam : public Token
{
    public:
    int szam;

    Szam(int szam) {
        this->szam = szam;
        type = 1;
    }

    Szam()
    {
        type = 1;
    }
};

class Zarojel : public Token
{
public:
    char c;

    Zarojel(char c) {
        this->c = c;
        type = 2;
    }
};

class Muvelet: public Token
{
public:
    char c;

    Muvelet(char c) {
        this->c = c;
        type = 3;
    }
};

#endif // TOKEN_H_INCLUDED
