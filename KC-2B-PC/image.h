/**
 *	Declaration of Struct & Class
 *	结构体与类声明
 */


#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

///////////		Define RgbImage & BwImage 	///////////
template<class T>
class Image {
private:
    IplImage* imgp;
public:
    Image(IplImage* img=0) { imgp=img; }
    ~Image() { imgp=0; }
    inline T*operator[](const int rowIndx) { return ((T*)(imgp->imageData+rowIndx*imgp->widthStep)); }
    inline int width() const { return imgp->width; }
    inline int height() const { return imgp->height; }
};

typedef struct {
    unsigned char b,g,r;
}RgbPixel;

typedef Image<RgbPixel> RgbImage;
typedef Image<unsigned char> BwImage;
///////////					End 			///////////

////////	Define Mouse Callback Param		////////
enum EVENT { SET_PERSPECTIVE };
struct MouseEvent {
	EVENT event;
    int counter;
    MouseEvent(int c=0, EVENT e=SET_PERSPECTIVE): counter(c), event(e) {}
};
////////				End					////////

#endif // IMAGE_H_INCLUDED
