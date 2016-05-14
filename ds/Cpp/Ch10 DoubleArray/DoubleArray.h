#ifndef DoubleArray_h
#define DoubleArray_h
class DoubleArray{
private:
    int low;
    int high;
    double *storage;
public:
    DoubleArray(int lh,int rh):low(lh),high(rh)
    {storage=new double [high-low+1];}
    bool insert(int index, double value);
    bool fatch(int index, double &value);
    ~DoubleArray(){delete []storage;}
};
#endif // DoubleArray
