#include "orientation.h"

Orientation::Orientation()
{
}
Orientation::ORIENTATION Orientation::getOri() const
{
    return ori;
}

void Orientation::setOri(const ORIENTATION &value)
{
    ori = value;
}

