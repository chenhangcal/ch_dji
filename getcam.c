#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "djicam.h"


#define FRAME_SIZE              (1280*720*3/2)  /*format NV12*/
#define BLOCK_MODE                     1
using namespace cv;
int mode=GETBUFFER_MODE;
static unsigned char buffer[FRAME_SIZE+8] = {0};
static unsigned int nframe = 0;



void getframe(void)
{
int ret;
    manifold_cam_init(mode);
    while(1) /*Ctrl+c to break out*/
	{
		if(mode & GETBUFFER_MODE)
		{
#if BLOCK_MODE
			ret = manifold_cam_read(buffer, &nframe, CAM_BLOCK); /*blocking read*/
			if(ret >= 0)
				printf("frame_size = %d, nframe = %d\n", ret, nframe);
			else if(ret < 0)
				break;
#else
            		ret = manifold_cam_read(buffer, &nframe, CAM_NON_BLOCK); /*non_blocking read*/
            		if(ret > 0)
                		printf("frame_size = %d, nframe = %d\n", ret, nframe);
             		else if(0 == ret)
                		printf("no new frame, ret = %d\n",ret);
             		else
                		break;
#endif
		}

		if(manifold_cam_exit()) /*to check if threads stop working*/
			break;
		waitKey(10);
	}

	while(!manifold_cam_exit()) /*make sure all threads exit ok*/
	{
		waitKey(1);
	}}
