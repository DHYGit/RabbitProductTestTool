#include "stdafx.h"
#include "FFmpegTool.h"
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

HANDLE hMutex = CreateMutex(NULL,FALSE,NULL);

#define CLOCK_TIME_BASE     90000

static AVFrame *picture, *tmp_picture;  
static uint8_t *video_outbuf;  
static int frame_count, video_outbuf_size;  

static int num = 0;
static int index = 0;
FILE *pYUVFile;
FILE *outputFile;
static char* fileName[5] = {"opencvyuv1.yuv", "opencvyuv2.yuv", "opencvyuv3.yuv", "opencvyuv4.yuv", "opencvyuv5.yuv"};

//ʱ���
clock_t tick1, tick2;

void FFmpegClass::FFmpeg_Init(){
	av_register_all();
	avformat_network_init();
	pFormatCtx_In = avformat_alloc_context();
	pFrameDec = av_frame_alloc();
	pFrameYUV = av_frame_alloc(); 
	pFrameEnc = av_frame_alloc();	
	packet = (AVPacket *)malloc(sizeof(AVPacket));
	av_init_packet(packet);
	packetData = (uint8_t*)malloc(BUFFLENGTH);
}

FFmpegClass::FFmpegClass()
{

}

int FFmpegClass::FFmpeg_openFile(char *fileName) {
	int t = avformat_open_input(&pFormatCtx_In, fileName, NULL, NULL);
	if (t != 0) {
		printf("���ļ�ʧ��\n");
		return -1;
	}
	if (avformat_find_stream_info(pFormatCtx_In, NULL)<0){
		printf("�Ҳ�������Ϣ");
		return -2;
	}
	videoindex = -1;
	//������е�����������������ΪAVMEDIA_TYPE_VIDEO
	for (int i = 0; i < pFormatCtx_In->nb_streams; i++){
		if (pFormatCtx_In->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)//�������Ƶ
		{
			videoindex = i;
			break;
		}
	}
	audioindex = -1;
	//������е�����������������ΪAVMEDIA_TYPE_AUDIO
	for (int i = 0; i < pFormatCtx_In->nb_streams; i++){
		if (pFormatCtx_In->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)//�������Ƶ
		{
			audioindex = i;
			break;
		}
	}
	if (videoindex == -1) {
		printf("û�з�����Ƶ��\n");
		return -3;
	}
	if(audioindex == -1){
		printf("û�з�����Ƶ��\n");
	}
	pCodecCtx_In = pFormatCtx_In->streams[videoindex]->codec;
	pCodec_In = avcodec_find_decoder(pCodecCtx_In->codec_id);//���Ҷ�Ӧ�Ľ�����
	if (pCodec_In == NULL) {
		printf("���ҽ�����ʧ��\r\n");
		return -4;
	}
	//�򿪽�����
	if (avcodec_open2(pCodecCtx_In,pCodec_In, NULL) < 0) {
		printf("�򿪽�����ʧ��\r\n");
		return -5;
	}
	
	y_size = pCodecCtx_In->width * pCodecCtx_In->height;

	out_buffer = (uint8_t*)malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx_In->width, pCodecCtx_In->height));
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, pCodecCtx_In->width, pCodecCtx_In->height);
	yuvImg = new Mat(pCodecCtx_In->height * 3 / 2, pCodecCtx_In->width, CV_8UC1);
	rgbImg  = new Mat(pCodecCtx_In->height, pCodecCtx_In->width, CV_8UC3);
	img_convert_ctx = sws_getContext(pCodecCtx_In->width, pCodecCtx_In->height, pCodecCtx_In->pix_fmt, pCodecCtx_In->width, pCodecCtx_In->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
	return 0;
}

int FFmpegClass::FFmpeg_openOutPutFile2(char *path, char *type)
{
	frame_count = 0;
	ofmt = NULL;
    avformat_alloc_output_context2(&pFormatCtx_Out, ofmt, type, path);
    if(!pFormatCtx_Out){
        cprintf("create output context failed \r\n");
        return -1;
    }
    cprintf("create output context success \n");
	pFormatCtx_Out->video_codec_id =  AV_CODEC_ID_H264;
    ofmt = pFormatCtx_Out->oformat;
    video_st = NULL;
    if(ofmt->video_codec != AV_CODEC_ID_NONE){
		video_st = avformat_new_stream(pFormatCtx_Out, NULL);
		if(!video_st){
			cprintf("alloc video_st failed \n");
			return -3;
		}
		pCodec_Out = avcodec_find_encoder(AV_CODEC_ID_H264);
		if(pCodec_Out == NULL){
			cprintf("find encoder failed \n");
			return -4;
		}
		cprintf("find encoder success \n");
		AVStream *instream = pFormatCtx_In->streams[videoindex];
		video_st->codec->pix_fmt = instream->codec->pix_fmt;
		video_st->codec->width = pCodecCtx_In->width;
		video_st->codec->height = pCodecCtx_In->height;
		video_st->codec->time_base.den = 30;
		video_st->codec->time_base.num = 1;
		video_st->codec->gop_size = instream->codec->gop_size;
		video_st->codec->bit_rate = instream->codec->bit_rate;
		video_st->codec->codec_type = AVMEDIA_TYPE_VIDEO;
		video_st->codec->codec_tag = 0;
		video_st->codec->codec_id = AV_CODEC_ID_H264;
		video_st->codec->keyint_min = 30;
		video_st->codec->me_range = 16;
		video_st->codec->max_qdiff = 4;
		video_st->codec->qcompress = 0.6;
		video_st->codec->max_b_frames = 0;
		video_st->codec->b_frame_strategy = true;
		video_st->codec->qmin = 16;
		video_st->codec->qmax = 24;
		pCodecCtx_Out = video_st->codec;
		int n = CLOCK_TIME_BASE;
		av_opt_set(pCodecCtx_Out->priv_data, "preset", "superfast", 0);
	    av_opt_set(pCodecCtx_Out->priv_data, "tune", "zerolatency", 0);
		if(pFormatCtx_Out->oformat->flags&AVFMT_GLOBALHEADER){
			pCodecCtx_Out->flags |= CODEC_FLAG_GLOBAL_HEADER;
		}
		if (avcodec_open2(pCodecCtx_Out, pCodec_Out, NULL)<0) {
			cprintf("open encoder failed \n");
			return -5;
		}
		cprintf("open encoder success \n");
	}
    //av_dump_format(pFormatCtx_Out, 0, path, 1);
    if(!(ofmt->flags & AVFMT_NOFILE)){
        ret = avio_open(&pFormatCtx_Out->pb, path, AVIO_FLAG_WRITE);
        if(ret < 0){
            cprintf("Could not open output URL '%s'", path);
            return -2;
        }
    }
    printf("will write header \n");
    //д�ļ�ͷ
    ret = avformat_write_header(pFormatCtx_Out, NULL);
    if(ret < 0){
        printf("Error occurred when write header to output URL\n");
        return -6;
    }
    return 0;
}

int FFmpegClass::FFmpeg_openOutPutFile(char *path, char *type)
{
	frame_count = 0;
	ofmt = NULL;
	avformat_alloc_output_context2(&pFormatCtx_Out, ofmt, type, path);
	if(!pFormatCtx_Out){
		cprintf("create output context failed \r\n");
		return -1;
	}
	cprintf("create output context success \n");
	//pFormatCtx_Out->video_codec_id =  AV_CODEC_ID_H264;
	ofmt = pFormatCtx_Out->oformat;
	video_st = NULL;
	for (int i = 0; i < pFormatCtx_In->nb_streams; i++)
	{
		//���������������������Create output AVStream according to input AVStream��
		
		AVStream *in_stream = pFormatCtx_In->streams[i];
		AVStream *out_stream = avformat_new_stream(pFormatCtx_Out, NULL);
		if (!out_stream)
		{
			printf("Failed allocating output stream\n");
			ret = AVERROR_UNKNOWN;
			return -2;
		}
		
		if(i == videoindex){
			pCodec_Out = avcodec_find_encoder(AV_CODEC_ID_H264);
			if(pCodec_Out == NULL){
				cprintf("find AV_CODEC_ID_H264 encoder failed \n");
				return -4;
			}
			ret = avcodec_parameters_copy(out_stream->codecpar, in_stream->codecpar);
			if (ret < 0)
			{
				printf("Failed to copy context from input to output stream codec context\n");
				return -3;
			}  
			out_stream->codecpar->codec_tag = 0;
		}else if(i == audioindex){
			pCodec_Out = avcodec_find_encoder(AV_CODEC_ID_AAC);
			if(pCodec_Out == NULL){
				cprintf("find AV_CODEC_ID_AAC encoder failed \n");
				return -4;
			}
			ret = avcodec_parameters_copy(out_stream->codecpar, in_stream->codecpar);
			if (ret < 0)
			{
				printf("Failed to copy context from input to output stream codec context\n");
				return -3;
			}  
			out_stream->codecpar->codec_tag = 0;
		}
		
		if(pFormatCtx_Out->oformat->flags & AVFMT_GLOBALHEADER){
		    out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
			if(in_stream->codec->extradata_size > 0){
				int extra_size = (uint64_t)in_stream->codec->extradata_size + FF_INPUT_BUFFER_PADDING_SIZE;
                out_stream->codec->extradata = (uint8_t*)malloc(extra_size);
                memcpy(out_stream->codec->extradata, in_stream->codec->extradata, in_stream->codec->extradata_size);
                out_stream->codec->extradata_size = in_stream->codec->extradata_size;
			}
		}
	}
	//av_dump_format(pFormatCtx_Out, 0, path, 1);
	if(!(ofmt->flags & AVFMT_NOFILE)){
		ret = avio_open(&pFormatCtx_Out->pb, path, AVIO_FLAG_WRITE);
		if(ret < 0){
			cprintf("Could not open output URL '%s'", path);
			return -4;
		}
	}
	printf("will write header \n");
	//д�ļ�ͷ
	ret = avformat_write_header(pFormatCtx_Out, NULL);
	if(ret < 0){
		printf("Error occurred when write header to output URL\n");
		return -6;
	}
	return 0;
}

int FFmpegClass::Encoder_Init(){
	pCodec_Enc = avcodec_find_encoder(AV_CODEC_ID_H264);
	if(pCodec_Enc == NULL){
		cprintf("find encoder failed \n");
		return -4;
	}
	cprintf("find encoder success \n");
	pCodecCtx_Enc = avcodec_alloc_context3(pCodec_Enc);
	AVStream *instream = pFormatCtx_In->streams[videoindex];
	pCodecCtx_Enc->pix_fmt = instream->codec->pix_fmt;//���ظ�ʽ
	pCodecCtx_Enc->width = pCodecCtx_In->width;
	pCodecCtx_Enc->height = pCodecCtx_In->height;
	pCodecCtx_Enc->time_base.den = 30;//֡��
	pCodecCtx_Enc->time_base.num = 1;
	pCodecCtx_Enc->gop_size = 60;//I֡�������
	pCodecCtx_Enc->keyint_min = 30;//I֡��С�����
	pCodecCtx_Enc->bit_rate = instream->codec->bit_rate;//Ŀ�����ʣ�����Խ����ƵԽ��
	pCodecCtx_Enc->rc_max_rate = instream->codec->rc_max_rate;
	pCodecCtx_Enc->codec_type = AVMEDIA_TYPE_VIDEO;//��������������
	pCodecCtx_Enc->codec_id = AV_CODEC_ID_H264;//������ID
	pCodecCtx_Enc->me_range = 16;//�˶����뾶
	pCodecCtx_Enc->max_qdiff = 4;//������֡��֮֡������б���������ӵı仯����
	pCodecCtx_Enc->qcompress = 0.6;//������ѹ������0-1.ԽС�������Խ���ڹ̶���Խ��Խʹ�������������ڹ̶�
	pCodecCtx_Enc->max_b_frames = 0;//��ʹ��b֡
	pCodecCtx_Enc->b_frame_strategy = false;//���Ϊtrue�����Զ�����ʲôʱ����Ҫ����B֡����ߴﵽ���õ����B֡�����������Ϊfalse,��ô����B֡����ʹ�á�
	pCodecCtx_Enc->lmin = 1;//��С�������ճ��� 
	pCodecCtx_Enc->lmax = 5;//����������ճ���
	pCodecCtx_Enc->qmin = 10;//��С�������� ȡֵ��Χ1~51 һ��ȡֵ10~30
	pCodecCtx_Enc->qmax = 50;//����������� ȡֵ��Χ1~51 һ��ȡֵ10~30
	pCodecCtx_Enc->qblur = 0.0;//��ʾ�������������仯�̶ȣ�ȡֵ��Χ0.0~1.0��0.0��ʾ������
	pCodecCtx_Enc->spatial_cplx_masking = 0.3;//�ռ临�Ӷ�
	pCodecCtx_Enc->thread_count = 4;
	av_opt_set(pCodecCtx_Enc->priv_data, "preset", "superfast", 0);
	av_opt_set(pCodecCtx_Enc->priv_data, "tune", "zerolatency", 0);
	if (avcodec_open2(pCodecCtx_Enc, pCodec_Enc, NULL)<0){
		cprintf("open encoder failed \n");
		return -5;
	}
	cprintf("open encoder success \n");
	return 0;
}

int FFmpegClass::FFmeg_PlayPacket(AVPacket *packet){
	//if(av_read_frame(pFormatCtx_In, packet)>=0){//��һ֡����
	if(packet->stream_index == videoindex){

		ret = avcodec_decode_video2(pCodecCtx_In, pFrameDec, &got_picture, packet);
		if(ret < 0){
			printf("�������\n");
			return -1;
		}
		if(got_picture){
			/*
			AVRational time_base = pFormatCtx_In->streams[videoindex]->time_base;
			AVRational time_base_q = {1, AV_TIME_BASE};
			int64_t pts_time = av_rescale_q(packet->dts, time_base, time_base_q);
			int64_t now_time = av_gettime() - start_time;
			if(pts_time > now_time){
			Sleep((pts_time - now_time)/1000.0);
			}*/
			sws_scale(img_convert_ctx, (const uint8_t* const*)pFrameDec->data, pFrameDec->linesize, 0, pCodecCtx_In->height, pFrameYUV->data, pFrameYUV->linesize);
			//cvRectangle(out_buffer,p1 ,p2, CV_RGB(0, 255, 0), 2); //��ɫ����
			//DrawFun(out_buffer);
			SDL_LockYUVOverlay(bmp);
			bmp->pixels[0]=pFrameYUV->data[0];
			bmp->pixels[2]=pFrameYUV->data[1];
			bmp->pixels[1]=pFrameYUV->data[2];
			bmp->pitches[0]=pFrameYUV->linesize[0];
			bmp->pitches[2]=pFrameYUV->linesize[1];
			bmp->pitches[1]=pFrameYUV->linesize[2];
			SDL_UnlockYUVOverlay(bmp);
			SDL_Rect *rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
			if (screen->clip_rect.w > pCodecCtx_In->width) {
				rect->x = (screen->clip_rect.w - pCodecCtx_In->width) / 2.0;
				rect->w = pCodecCtx_In->width;
			}
			else {
				rect->x = 0;
				rect->w = screen->clip_rect.w;
			}
			if (screen->clip_rect.h > pCodecCtx_In->height) {
				rect->y = (screen->clip_rect.h - pCodecCtx_In->height) / 2.0;
				rect->h = pCodecCtx_In->height;
			}
			else {
				rect->y = 0;
				rect->h = screen->clip_rect.h;
			}
			SDL_DisplayYUVOverlay(bmp, rect);
			free(rect);
		}
	}
	//}else{
	//	return -2;
	//}
	return 0;
}
int FFmpegClass::FFmpeg_PushMediaStream(){

	return 0;
}

int ANSIToUTF8(char* pszCode, char* UTF8code)
{
	WCHAR Unicode[100]={0,}; 
	char utf8[100]={0,};

	// read char Lenth
	int nUnicodeSize = MultiByteToWideChar(CP_ACP, 0, pszCode, strlen(pszCode), Unicode, sizeof(Unicode)); 
	memset(UTF8code, 0, nUnicodeSize+1);
	// read UTF-8 Lenth
	int nUTF8codeSize = WideCharToMultiByte(CP_UTF8, 0, Unicode, nUnicodeSize, UTF8code, sizeof(Unicode), NULL, NULL); 

	// convert to UTF-8 
	MultiByteToWideChar(CP_UTF8, 0, utf8, nUTF8codeSize, Unicode, sizeof(Unicode)); 
	UTF8code[nUTF8codeSize+1] = '\0';
	return nUTF8codeSize;
}
int FFmpegClass::DrawFun(unsigned char *yuv_data){
	memcpy(this->yuvImg->data, yuv_data, pCodecCtx_In->width * pCodecCtx_In->height * 3 / 2);
	cvtColor(*yuvImg, *rgbImg, COLOR_YUV2BGR_I420, 0);
	//IplImage img = (IplImage)*yuvImg;
	CvPoint center;
	center.x = pCodecCtx_In->width - 30;
	center.y = pCodecCtx_In->height - 30;
	int r = pCodecCtx_In->height - 100;
	//���ص�ͼ��Բ�ġ��뾶����ɫ����ϸ������ 
	circle(*rgbImg, center, r, cvScalar(100,100,200), 2, 8, 1);
	//������
	// cvRectangle���������� ͼƬ�� ���Ͻǣ� ���½ǣ� ��ɫ�� ������ϸ�� �������ͣ�������  
	CvPoint leftUpPoint, rightDownPoint;
	leftUpPoint.x = center.x - sqrt((r * r / 2.0));
	leftUpPoint.y = center.y - sqrt((r * r / 2.0));
	rightDownPoint.x = center.x + sqrt((r * r / 2.0));
	rightDownPoint.y = center.y + sqrt((r * r / 2.0));
	rectangle(*rgbImg, leftUpPoint, rightDownPoint, Scalar(100, 100, 200), 2, 8, 1);
	cvtColor(*rgbImg, *yuvImg, COLOR_BGR2YUV_I420, 0);
	memcpy(yuv_data, yuvImg->data, pCodecCtx_In->width * pCodecCtx_In->height * 3 / 2);
	return 0;
}