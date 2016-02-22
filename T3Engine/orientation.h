#ifndef ORIENTATION_H
#define ORIENTATION_H


class Orientation
{
public:
    enum ORIENTATION{empty,up,down,left,right,
                     upLeft,upRight,downLeft,downRight};
    Orientation();
    ORIENTATION getOri() const;
    void setOri(const ORIENTATION &value);

protected:
    ORIENTATION ori;
};

#endif // ORIENTATION_H
