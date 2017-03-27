typedef struct {
     unsigned char red,green,blue;
} ppmPixel;

typedef struct {
     int x, y;
     ppmPixel *data;
} ppmImage;
