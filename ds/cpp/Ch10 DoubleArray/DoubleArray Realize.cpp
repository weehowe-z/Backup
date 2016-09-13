#include "DoubleArray.h"
bool DoubleArray::insert(int index, double value)
{
    if (index<low||index>high) return false;
    storage[index-low]=value;
    return true;
}
bool DoubleArray::fatch(int index,double &value)
{
    if (index<low||index>high) return false;
    value=storage[index-low];
    return true;
}
