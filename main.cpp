#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define FRAME_SIZE              (1280*720*3/2)  /*format NV12*/

using namespace cv;
extern unsigned char buffer[FRAME_SIZE+8];
extern "C"{
extern int getframe(void);
}
int mymain2(int argc, char *argv[])
{
    printf("start\n");
    Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty())
       return -1;
    namedWindow( "lena", CV_WINDOW_AUTOSIZE );
    imshow("lena", img);
    Mat frame;
    VideoWriter chwriter("myvideo.avi",CV_FOURCC('M','J','P','G'),20,{1280,720});
    while(1)
    {
        if(getframe())
        {
            frame.create(720*3/2,1280,CV_8UC1);
            memcpy(frame.data,buffer,FRAME_SIZE*sizeof(unsigned char));
            Mat rgbimg;
            cvtColor(frame,rgbimg,CV_YUV2BGR_NV12);
            imshow("rgb",rgbimg);
            waitKey(1);
        }
        else printf("no cam\n");
        waitKey(1);
    }
    waitKey(0);
    return 0;
}



