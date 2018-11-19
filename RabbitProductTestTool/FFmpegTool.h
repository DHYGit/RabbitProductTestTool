#pragma once
 extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
	//�°����ͼ��ת���ṹ��Ҫ�����ͷ�ļ�
#include "libswscale/swscale.h"
#include "libavutil/time.h"
#include "libavutil/imgutils.h"
#include "libavutil/opt.h"
#include "sdl/SDL.h"
#include "sdl/SDL_thread.h"
}; 
 #include "opencv2/opencv.hpp"      
#include "imgproc/imgproc.hpp"  
#include <direct.h>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
#define BUFFLENGTH 1024 * 1024 * 20

using namespace cv;

struct EncoderStruct{
	AVCodecContext  *pCodecCtx;
	int used;
};

class FFmpegClass
{
public:
	FFmpegClass();
	void FFmpeg_Init();
	int Encoder_Init();
	int FFmpeg_openFile(char *fileName);
	int FFmpeg_openOutPutFile(char *path, char *type);
	int FFmpeg_openOutPutFile2(char *path, char *type);
	int FFmpeg_PushMediaStream();
	int FFmpegClass::FFmeg_PlayPacket(AVPacket *packet);
	int DrawFun(unsigned char *yuv_data);
	AVFrame *pFrameDec;
	AVFrame *pFrameYUV;
	AVFrame *pFrameEnc;
	
	AVFormatContext	*pFormatCtx_In;
	AVFormatContext	*pFormatCtx_Out;
	AVCodecContext  *pCodecCtx_In;
	AVCodecContext  *pCodecCtx_Out;
	AVCodecContext  *pCodecCtx_Enc;
	
	AVCodec         *pCodec_In;
	AVCodec         *pCodec_Out;
	AVCodec         *pCodec_Enc;
	AVOutputFormat *ofmt;
	AVStream *video_st;
	
	AVPicture src_picture, dst_picture;
	
	SDL_Surface *screen;
	SDL_Overlay *bmp;

	AVPacket *packet;

	Mat *yuvImg;
	Mat *rgbImg;

	int ret;
	int y_size;
    int got_picture;
	int got_packet;
	int64_t start_time;
	struct SwsContext *img_convert_ctx;

	uint8_t *packetData;
	uint8_t *out_buffer;
	int videoindex;
	int audioindex;
};
#define STREAM_DURATION   5.0  
#define STREAM_FRAME_RATE 25 /* 25 images/s */  
#define STREAM_NB_FRAMES  ((int)(STREAM_DURATION * STREAM_FRAME_RATE))  
int ANSIToUTF8(char* pszCode, char* UTF8code);


