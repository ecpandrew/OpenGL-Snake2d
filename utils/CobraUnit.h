#ifndef COBRAUNIT_LIBRARY_H
#define COBRAUNIT_LIBRARY_H

class CobraUnit
{

public:

    void setPosicaoX(int x);
    void setPosicaoY(int y);
    int getPosicaoX();
    int getPosicaoY();

    void setSize(int x);
    int getSize();

private:
    int x;
    int y;
    int size;

};
#endif //COBRAUNIT_LIBRARY_H