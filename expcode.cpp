#include "expcode.h"
#include <iostream>
#include <time.h>
#include <math.h>
#define PI 3.14159

using namespace std;

//统计直方图, 返回长度为256的1维数组
int* histogram(int** pixelmat, int mheight, int mwidth)
{
	//注意:函数内分配数组必须使用动态分配;
	int *zft = new int[256];
	for (int i = 0; i<256; i++){
		zft[i] = 0;
	}
	for (int i = 0; i<mheight; i++){
		for (int j = 0; j<mwidth; j++){
			zft[pixelmat[i][j]]++;
		}
	}
	return zft;
}

//示例,将灰度图转化为二值图像,返回处理后的图像
int** binaryimg(int** pixelmat, int mheight, int mwidth)
{
	for (int i = 0; i < mheight; i++)
	{
		for (int j = 0; j < mwidth; j++)
		{
			//从左上角开始遍历整幅图像, 实现二值化;
			pixelmat[i][j] = pixelmat[i][j] > 128 ? 255 : 0;
		}
	}
	//根据实验要求返回对应的值;
	return pixelmat;
}

//直方图均衡, 返回处理后的图像
int** histogramequ(int** pixelmat, int mheight, int mwidth)
{
	int *souce_zft = new int[256];
	float *sum_zft = new float[256];
	int *final_zft = new int[256];
	souce_zft = histogram(pixelmat, mheight, mwidth);
	sum_zft[0] = souce_zft[0] / (float)(mheight*mwidth);
	for (int i = 1; i<256; i++){
		sum_zft[i] = souce_zft[i] / (float)(mheight*mwidth) + sum_zft[i - 1];
	}

	for (int i = 0; i<256; i++){
		final_zft[i] = (int)(sum_zft[i] * 255 + 0.5);
	}
	for (int i = 0; i<mheight; i++){
		for (int j = 0; j<mwidth; j++){
			pixelmat[i][j] = final_zft[pixelmat[i][j]];
		}
	}


	return pixelmat;
}

//灰度拉伸, 返回处理后的图像
int** graystretch(int** pixelmat, int mheight, int mwidth)
{
	int min = minvalue(pixelmat, mheight, mwidth);
	int max = maxvalue(pixelmat, mheight, mwidth);
	//g(x,y)=(255/(B-A))[f(x,y)-A];
	for (int i = 0; i<mheight; i++)
	{
		for (int j = 0; j<mwidth; j++)
		{
			pixelmat[i][j] = (255.0 / (max - min))*(pixelmat[i][j] - min);
		}
	}
	return pixelmat;
}


int GetMedianNum(int * aArray, int iFilterLen)
{
	int i, j;// 循环变量
	int bTemp;
	int * bArray = new int[iFilterLen];
	for (i = 0; i<iFilterLen; i++)
		bArray[i] = aArray[i];

	// 用冒泡法对数组进行排序
	for (int i = 0; i<iFilterLen; i++)
	{
		for (int j = iFilterLen - 1; j>i; j--)
		{
			if (bArray[j]<bArray[j - 1])
			{
				bTemp = bArray[j];
				bArray[j] = bArray[j - 1];
				bArray[j - 1] = bTemp;
			}
		}
	}
	// 计算中值
	if ((iFilterLen & 1) > 0)
		// 数组有奇数个元素，返回中间一个元素
		bTemp = bArray[(iFilterLen + 1) / 2];
	else
		// 数组有偶数个元素，返回中间两个元素平均值
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	return bTemp;
}


//中值滤波, 返回处理后的图像
int** medianfit(int** pixelmat, int mheight, int mwidth)
{

	int winsize = 5;
	int *temp = new int[winsize*winsize];
	int **p = pixelmat;
	int pp = 0, mid = 0;
	int temp_mat[256][256];
	int s1, s2, s3, s4, s5, s6, s7, s8, s9;

	for (int i = 0; i<mheight; i++){
		for (int j = 0; j<mwidth; j++){
			temp_mat[i][j] = pixelmat[i][j];
		}
	}

	for (int i = winsize / 2; i<mheight - winsize / 2; ++i){
		for (int j = winsize / 2; j<mwidth - winsize / 2; ++j)
		{
			temp[0] = p[(i)][j - 1];
			temp[1] = p[(i)][j - 2];
			temp[2] = p[(i)][j + 1];
			temp[3] = p[i][j + 2];
			temp[4] = p[i][j];
			temp[5] = p[i - 1][j];
			temp[6] = p[i - 2][j];
			temp[7] = p[(i + 1)][j];
			temp[8] = p[(i + 2)][j];
			temp_mat[i][j] = GetMedianNum(temp, 9);

		}
	}
	for (int i = 0; i<mheight; i++){
		for (int j = 0; j<mwidth; j++){
			pixelmat[i][j] = temp_mat[i][j];
		}
	}
	return pixelmat;
}



int average(int * num, int length)
{
	int ave = 0, sum = 0;
	for (int i = 0; i<length; i++)	sum += num[i];
	ave = sum / length;
	return ave;
}



//均值滤波, 返回处理后的图像
int** averagefit(int** pixelmat, int mheight, int mwidth)
{
	int winsize = 5;
	int *temp = new int[winsize*winsize];
	int **p = pixelmat;
	int pp = 0;
	int temp_mat[256][256];
	int s1, s2, s3, s4, s5, s6, s7, s8, s9;

	for (int i = 0; i<mheight; i++){
		for (int j = 0; j<mwidth; j++){
			temp_mat[i][j] = pixelmat[i][j];
		}
	}

	for (int i = winsize / 2; i<mheight - winsize / 2; ++i){
		for (int j = winsize / 2; j<mwidth - winsize / 2; ++j)
		{
			s1 = p[(i)][j - 1];
			s2 = p[(i)][j - 2];
			s3 = p[(i)][j + 1];
			s4 = p[i][j + 2];
			s6 = p[i - 1][j];
			s7 = p[i - 2][j];
			s8 = p[(i + 1)][j];
			s9 = p[(i + 2)][j];
			temp_mat[i][j] = (s1 + s2 + s3 + s4 + s6 + s7 + s8 + s9) / 8;
		}
	}

	for (int i = 0; i<mheight; i++){
		for (int j = 0; j<mwidth; j++){
			pixelmat[i][j] = temp_mat[i][j];
		}
	}

	return pixelmat;
}

class Tnode
{
public:
	float re;
	float im;
};


void fft1D(Tnode x[], int nn)       //一维快速Fourier变换
{
	int N, i, n, s, pn, ys, pp;
	float pi = 3.14;
	Tnode ox[256], X[256], c[256];

	N = nn;
	while (N>1) {
		for (i = 0; i<nn; i++)
			ox[i] = x[i];
		for (n = 0; n<nn; n++)
		if (n%N<N / 2)
		{
			x[n].re = ox[n].re + ox[n + N / 2].re;
			x[n].im = ox[n].im + ox[n + N / 2].im;
		}
		else
		{
			float w = -2.0*pi*(n - N / 2) / N;
			c[n].re = ox[n - N / 2].re - ox[n].re;
			c[n].im = ox[n - N / 2].im - ox[n].im;
			x[n].re = c[n].re*cos(w) - c[n].im*sin(w);
			x[n].im = c[n].re*sin(w) + c[n].im*cos(w);
		}
		N /= 2;
	}

	float x1, x2;
	x1 = log(nn*1.0);
	x2 = log(2.0);
	pp = (int)(x1 / x2 + 0.5);
	for (n = 0; n<nn; n++) {
		s = 0;
		pn = n;
		for (i = 1; i <= pp; i++) {
			ys = pn % 2;
			s = s * 2 + ys;
			pn /= 2;
		}
		X[s] = x[n];
	}

	for (n = 0; n<nn; n++)
		x[n] = X[n];
}

void ifft1D(Tnode x[], int nn)          //一维快速Fourier反变换
{
	int N, i, n, s, pn, ys, pp;
	float pi = 3.14;
	Tnode ox[256], X[256], c[256];

	N = nn;
	while (N>1) {
		for (i = 0; i<nn; i++)
			ox[i] = x[i];
		for (n = 0; n<nn; n++)
		if (n%N<N / 2)
		{
			x[n].re = ox[n].re + ox[n + N / 2].re;
			x[n].im = ox[n].im + ox[n + N / 2].im;
		}
		else
		{
			float w = 2.0*pi*(n - N / 2) / N;
			c[n].re = ox[n - N / 2].re - ox[n].re;
			c[n].im = ox[n - N / 2].im - ox[n].im;
			x[n].re = c[n].re*cos(w) - c[n].im*sin(w);
			x[n].im = c[n].re*sin(w) + c[n].im*cos(w);
		}
		N /= 2;
	}

	float x1, x2;
	x1 = log(nn*1.0);
	x2 = log(2.0);
	pp = (int)(x1 / x2 + 0.5);
	for (n = 0; n<nn; n++) {
		s = 0;
		pn = n;
		for (i = 1; i <= pp; i++) {
			ys = pn % 2;
			s = s * 2 + ys;
			pn /= 2;
		}
		X[s] = x[n];
	}

	for (n = 0; n<nn; n++)
		x[n] = X[n];
}


//理想低通滤波, 返回处理后的图像
int** lowpassfit(int** pixelmat, int mheight, int mwidth)
{
	int i, j;
	int m_nHeight = mheight;
	int m_nWidth = mwidth;
	int size = 30;
	double mid_height = double(mheight / 2);
	double mid_width = double(mwidth / 2);

	Tnode value[256][256];
	Tnode tem[256];

	for (i = 0; i<mheight; ++i)
	{
		for (j = 0; j<mwidth; ++j)
		{
			value[i][j].re = pixelmat[i][j] * pow(-1.0, i + j);
			value[i][j].im = 0;
		}
	}
	//dft
	for (i = 0; i<m_nHeight; i++) {
		for (j = 0; j<m_nWidth; j++) {//对每一行做一维变换
			tem[j] = value[i][j];
		}
		fft1D(tem, m_nWidth);
		for (j = 0; j<m_nWidth; j++) {
			value[i][j] = tem[j];
		}
	}

	for (j = 0; j<m_nWidth; j++) {//对每一列做一维变换
		for (i = 0; i<m_nHeight; i++)
			tem[i] = value[i][j];
		fft1D(tem, m_nHeight);
		for (i = 0; i<m_nHeight; i++)
			value[i][j] = tem[i];
	}

	//lowpass_filter
	for (i = 0; i<m_nHeight; ++i)
	{
		for (j = 0; j<m_nWidth; ++j)
		{
			double distance = sqrt((i - mid_height)*(i - mid_height) + (j - mid_width)*(j - mid_width));
			if (distance>size)
			{
				value[i][j].re = 0;
				value[i][j].im = 0;
			}
		}
	}

	for (i = 0; i<m_nHeight; ++i)
	{
		for (j = 0; j<m_nWidth; ++j)
		{
			value[i][j].re /= 256;
			value[i][j].im /= 256;
		}
	}
	//idft
	for (i = 0; i<m_nHeight; i++) {//对每一列做反变换
		for (j = 0; j<m_nWidth; j++) {
			tem[j] = value[i][j];
		}
		ifft1D(tem, m_nWidth);
		for (j = 0; j<m_nWidth; j++) {
			value[i][j] = tem[j];
		}
	}

	for (j = 0; j<m_nWidth; j++) {//对每一行做变换
		for (i = 0; i<m_nHeight; i++)
			tem[i] = value[i][j];
		ifft1D(tem, m_nHeight);
		for (i = 0; i<m_nHeight; i++)
			value[i][j] = tem[i];
	}

	for (i = 0; i<m_nHeight; ++i)	
		for (j = 0; j<m_nWidth; ++j)
		{
			value[i][j].re /= 256;
			value[i][j].im /= 256;
		}
	

	for (i = 0; i<m_nHeight; ++i)	
		for (j = 0; j<m_nWidth; ++j)
		{
			float d1, d2, f;
			d1 = value[i][j].re*value[i][j].re;
			d2 = value[i][j].im*value[i][j].im;
			f = sqrt(d1 + d2);
			if (f>255) pixelmat[i][j] = 255;
			else pixelmat[i][j] = (int)(f + 0.5);
		}
	return pixelmat;
}

//sobel算子, 返回处理后的图像
int** sobel(int** pixelmat, int mheight, int mwidth)
{
	int **p = pixelmat;

	int i, j, x, xx, yy;
	int s1, s2, s3, s4, s6, s7, s8, s9;

	int lpDst[256][256];

	for (i = 1; i<mheight - 1; ++i)
	{
		for (j = 1; j<mwidth - 1; ++j)
		{
			s1 = p[(i - 1)][j - 1];
			s2 = p[(i - 1)][j];
			s3 = p[(i - 1)][j + 1];
			s4 = p[i][j - 1];
			s6 = p[i][j + 1];
			s7 = p[(i + 1)][j - 1];
			s8 = p[(i + 1)][j];
			s9 = p[(i + 1)][j + 1];
			xx = abs(s3 - s1 + 2 * s6 - 2 * s4 + s9 - s7);
			yy = abs(s1 - s7 + 2 * s2 - 2 * s8 + s3 - s9);
			lpDst[i][j] = xx + yy;
			if (lpDst[i][j]>255) lpDst[i][j] = 0;
		}
	}
	for (i = 1; i<mheight - 1; ++i)
	{
		for (j = 1; j<mwidth - 1; ++j)
		{
			p[i][j] = lpDst[i][j];
		}
	}
	return pixelmat;

}



//laplace算子, 返回处理后的图像
int** laplace(int** pixelmat, int mheight, int mwidth)
{
	int **p = pixelmat;

	int i, j, x;
	int s1, s2, s3, s4, s6, s7, s8, s9;

	int lpDst[256][256];

	for (i = 1; i<mheight - 1; ++i)
	{
		for (j = 1; j<mwidth - 1; ++j)
		{
			s1 = p[(i - 1)][j - 1];
			s2 = p[(i - 1)][j];
			s3 = p[(i - 1)][j + 1];
			s4 = p[i][j - 1];
			s6 = p[i][j + 1];
			s7 = p[(i + 1)][j - 1];
			s8 = p[(i + 1)][j];
			s9 = p[(i + 1)][j + 1];
			lpDst[i][j] = abs(s1 + s2 + s3 + s4 + s6 + s7 + s8 + s9 - 8 * p[i][j]);
			if (lpDst[i][j]>255) lpDst[i][j] = 0;
		}
	}
	for (i = 1; i<mheight - 1; ++i)
	{
		for (j = 1; j<mwidth - 1; ++j)
		{
			p[i][j] = lpDst[i][j];
		}
	}
	return pixelmat;
}

//理想高通滤波, 返回处理后的图像
int** highpassfit(int** pixelmat, int mheight, int mwidth)
{
	int i, j;
	int m_nHeight = mheight;
	int m_nWidth = mwidth;
	int size = 20;
	double mid_height = double(mheight / 2);
	double mid_width = double(mwidth / 2);

	Tnode value[256][256];
	Tnode tem[256];

	for (i = 0; i<mheight; ++i)
	{
		for (j = 0; j<mwidth; ++j)
		{
			value[i][j].re = pixelmat[i][j] * pow(-1.0, i + j);
			value[i][j].im = 0;
		}
	}
	//dft
	for (i = 0; i<m_nHeight; i++) {
		for (j = 0; j<m_nWidth; j++) {
			tem[j] = value[i][j];
		}
		fft1D(tem, m_nWidth);
		for (j = 0; j<m_nWidth; j++) {
			value[i][j] = tem[j];
		}

	}

	for (j = 0; j<m_nWidth; j++) {
		for (i = 0; i<m_nHeight; i++)
			tem[i] = value[i][j];
		fft1D(tem, m_nHeight);
		for (i = 0; i<m_nHeight; i++)
			value[i][j] = tem[i];
	}

	for (i = 0; i<m_nHeight; ++i)
	{
		for (j = 0; j<m_nWidth; ++j)
		{
			value[i][j].re /= 256;
			value[i][j].im /= 256;
		}
	}
	//highpass_filter
	for (i = 0; i<m_nHeight; ++i)
	{
		for (j = 0; j<m_nWidth; ++j)
		{
			double distance = sqrt((i - mid_height)*(i - mid_height) + (j - mid_width)*(j - mid_width));
			if (distance<size)
			{
				value[i][j].re = 0;
				value[i][j].im = 0;
			}
		}
	}
	//idft
	for (i = 0; i<m_nHeight; i++) {
		for (j = 0; j<m_nWidth; j++) {
			tem[j] = value[i][j];
		}
		ifft1D(tem, m_nWidth);
		for (j = 0; j<m_nWidth; j++) {
			value[i][j] = tem[j];
		}
	}

	for (j = 0; j<m_nWidth; j++) {
		for (i = 0; i<m_nHeight; i++)
			tem[i] = value[i][j];
		ifft1D(tem, m_nHeight);
		for (i = 0; i<m_nHeight; i++)
			value[i][j] = tem[i];
	}

	for (i = 0; i<m_nHeight; ++i)
	{
		for (j = 0; j<m_nWidth; ++j)
		{
			value[i][j].re /= 256;
			value[i][j].im /= 256;
		}
	}


	for (i = 0; i<m_nHeight; ++i)
	{
		for (j = 0; j<m_nWidth; ++j)
		{
			float d1, d2, f;
			d1 = value[i][j].re*value[i][j].re;
			d2 = value[i][j].im*value[i][j].im;
			f = sqrt(d1 + d2);
			if (f>255) pixelmat[i][j] = 255;
			else pixelmat[i][j] = (int)(f + 0.5);
		}
	}

	return pixelmat;
}

//示例, 将图像平移到显示区域的中心
int** centralize(int** framemat, int** pixelmat, int mheight, int mwidth)
{
	//framemat为指向显示区域(画板)的二维数组指针, 大小为FRAME_HEIGHT x FRAMEWIDTH = 800 x 800
	int xpt = (FRAME_HEIGHT - mheight) / 2;
	int ypt = (FRAME_WIDTH - mwidth) / 2;
	for (int i = 0; i < mheight; i++)
	{
		for (int j = 0; j < mwidth; j++)
		{
			framemat[i + xpt][j + ypt] = pixelmat[i][j];
		}
	}
	return framemat;
}


//旋转图像, 返回显示区域(画板)指针
int** rotation(int** framemat, int** pixelmat, int mheight, int mwidth)
{
	int i, j;
	int newx, newy;
	float angle = PI / 4.0;
	float m, n;
	//得到旋转之后的图像的边界newx、newy，即旋转之后的大小
	newx = int((sin(angle)*mheight + cos(angle)*mwidth) / 2);
	newy = int((cos(angle)*mheight + sin(angle)*mwidth) / 2);
	//遍历旋转之后的所有pixel，映射回原图
	for (i = -newx; i<newx; i++){
		for (j = -newy; j<newy; j++){
			//m、n为旋转之后对应到原图的坐标
			m = i*cos(angle) + j*sin(angle);
			n = i*sin(angle) - j*cos(angle);
			if (abs(int(m))<mwidth / 2 && abs(int(n))<mheight / 2)
				framemat[newx + j][newy + i] = pixelmat[mheight / 2 + int(m)][mwidth / 2 + int(n)];
		}
	}
	return framemat;
}



//平移图像, 返回显示区域(画板)指针
int** moveimage(int** framemat, int** pixelmat, int mheight, int mwidth)
{
	int xpt = 200;
	int ypt = 200;
	for (int i = 0; i < mheight; i++)
	{
		for (int j = 0; j < mwidth; j++)
		{
			framemat[i + xpt][j + ypt] = pixelmat[i][j];
		}
	}
	return framemat;
}

//缩放图像, 返回显示区域(画板)指针
int** scaling(int** framemat, int** pixelmat, int mheight, int mwidth)
{
	float scale_rate = 2;
	for (int i = 0; i < mheight / scale_rate; i++)
	{
		for (int j = 0; j < mwidth / scale_rate; j++)
		{
			framemat[i][j] = pixelmat[int(i*scale_rate)][int(j*scale_rate)];
		}
	}
	return framemat;
}

//以下为DFT变换的代码
int ** DFT(int** pixelmat, int mheight, int mwidth)//DFT变换, 返回处理后的图像, 注意缩放到0~255的整型
{


	int i, j;
	int m_nHeight = mheight;
	int m_nWidth = mwidth;

	Tnode value[256][256];
	Tnode tem[256];

	for (i = 0; i<mheight; ++i)
	{
		for (j = 0; j<mwidth; ++j)
		{
			value[i][j].re = pixelmat[i][j] * pow(-1.0, (i + j));
			value[i][j].im = 0;
		}
	}

	for (i = 0; i<m_nHeight; i++) {
		for (j = 0; j<m_nWidth; j++) {
			tem[j] = value[i][j];
		}
		fft1D(tem, m_nWidth);
		for (j = 0; j<m_nWidth; j++) {
			value[i][j] = tem[j];
		}

	}

	for (j = 0; j<m_nWidth; j++) {
		for (i = 0; i<m_nHeight; i++)
			tem[i] = value[i][j];
		fft1D(tem, m_nHeight);
		for (i = 0; i<m_nHeight; i++)
			value[i][j] = tem[i];
	}

	for (i = 0; i<m_nHeight; ++i)
	{
		for (j = 0; j<m_nWidth; ++j)
		{
			float d1, d2, f;
			d1 = value[i][j].re*value[i][j].re;
			d2 = value[i][j].im*value[i][j].im;
			f = sqrt(d1 + d2) / 256;
			if (f>255) pixelmat[i][j] = 255;
			else pixelmat[i][j] = (int)(f + 0.5);
		}
	}
	return pixelmat;

}

void dct1D(float f[], int N)
{
	int u, x;
	float c[256];
	float pi = 3.14;
	for (u = 0; u<N; u++) {
		c[u] = 0.0;
		for (x = 0; x<N; x++)
			c[u] += f[x] * cos((2 * x + 1)*u*pi / (2 * N));

		if (u == 0) c[u] *= sqrt(1.0 / N);
		else c[u] *= sqrt(2.0 / N);
	}
	for (x = 0; x<N; x++)
		f[x] = c[x];
}

//DCT变换, 返回处理后的图像
int** DCT(int** pixelmat, int mheight, int mwidth)
{
	int**p;
	p = pixelmat;
	int i, j, x;
	float value[256][256];
	float tem[256];

	for (i = 0; i<mheight; ++i)
	{
		for (j = 0; j<mwidth; ++j)
		{
			value[i][j] = p[i][j];
		}
	}

	for (i = 0; i<mheight; i++) {
		for (j = 0; j<mwidth; j++) {
			tem[j] = value[i][j];
		}
		dct1D(tem, mwidth);
		for (j = 0; j<mwidth; j++) {
			value[i][j] = tem[j];
		}
	}

	for (j = 0; j<mwidth; j++) {
		for (i = 0; i<mheight; i++)
			tem[i] = value[i][j];
		dct1D(tem, mheight);
		for (i = 0; i<mheight; i++)
			value[i][j] = tem[i];
	}

	for (i = 0; i<mheight; ++i)
	{
		for (j = 0; j<mwidth; ++j)
		{

			if (value[i][j]<0) value[i][j] = 0 - value[i][j];
			int v = (int)(value[i][j] + 0.5);
			if (v>255) v = 255;
			p[i][j] = v;
		}
	}

	for (i = 0; i<mheight; ++i)
	{
		for (j = 0; j<mwidth; ++j)
		{
			pixelmat[i][j] = p[i][j];
		}
	}
	return pixelmat;
}


int b[256][8];

void walsh1D(int f[], int N)   //N=256
{

	int x, u, sum;
	int w[256];

	for (u = 0; u<N; u++)
	{
		w[u] = 0;
		for (x = 0; x<N; x++)
		{      //为增加运算速度，这里直接展开8次循环
			sum = 0;
			sum += b[x][0] * b[u][7] + b[x][1] * b[u][6] + b[x][2] * b[u][5] + b[x][3] * b[u][4];
			sum += b[x][4] * b[u][3] + b[x][5] * b[u][2] + b[x][6] * b[u][1] + b[x][7] * b[u][0];
			if (sum % 2 == 0) w[u] += f[x];
			else w[u] -= f[x];
		}
	}
	for (u = 0; u<N; u++)
		f[u] = w[u];
}

//walsh变换, 返回处理后的图像
int** walsh(int** pixelmat, int mheight, int mwidth)
{
	// 实验四  图像线性变换 3.walsh变换
	int **p;
	p = pixelmat;

	int i, j, location, xx, pp, N;
	int value[256][256];
	int tem[256];
	N = 256;

	for (i = 0; i<N; i++) {
		xx = i;
		pp = 0;
		while (xx >= 1) {
			b[i][pp] = xx % 2;
			xx = xx >> 1;
			pp++;
		}
	}

	for (i = 0; i<mheight; ++i)
	{
		for (j = 0; j<mwidth; ++j)
		{
			value[i][j] = p[i][j];
		}
	}

	for (i = 0; i<mheight; i++) {
		for (j = 0; j<mwidth; j++) {
			tem[j] = value[i][j];
		}
		walsh1D(tem, mwidth);
		for (j = 0; j<mwidth; j++) {
			value[i][j] = tem[j];
		}
	}

	for (j = 0; j<mwidth; j++) {
		for (i = 0; i<mheight; i++)
			tem[i] = value[i][j];
		walsh1D(tem, mheight);
		for (i = 0; i<mheight; i++)
			value[i][j] = tem[i];
	}

	float v;
	for (i = 0; i<mheight; ++i)
	{
		for (j = 0; j<mwidth; ++j)
		{
			v = value[i][j] * 1.0 / mheight;
			value[i][j] = (int)(v + 0.5);
			if (value[i][j]<0) value[i][j] = 0 - value[i][j];
			if (value[i][j]>255) value[i][j] = 255;
			p[i][j] = value[i][j];
		}
	}
	return pixelmat;

}

int getp(int k)
{
	int p;
	for (p = 0; p<10; p++)
	{
		if (pow(2.0, double(p))>k)
			return p - 1;
	}
}

int getq(int k)
{
	int q;
	q = k + 1 - pow(2.0, double(getp(k)));
	return q;
}

float Hk(float z, int k, float N)
{
	int p = getp(k);
	int q = getq(k);
	if (k == 0) return 1 / sqrt(N);
	else {
		float result;
		if ((z >= (float(q) - 1.0) / pow(2.0, double(p))) && (z<(float(q) - 0.5) / pow(2.0, double(p))))
			result = 1 / sqrt(N)*pow(2.0, double(p) / 2);
		else if ((z >= (float(q) - 0.5) / pow(2.0, double(p))) && (z<(float(q)) / pow(2.0, double(p))))
			result = -1 / sqrt(N)*pow(2.0, double(p) / 2);
		else result = 0;
		return result;
	}
}
/*
int** haar(int** pixelmat, int mheight, int mwidth)
{
float h[256][256];
int p, q;
float N = 256.0;
float tmp;
int temp1[256][256];
int temp2[256][256];
for (int i = 0; i<mheight; i++)
for (int j = 0; j<mwidth; j++) { temp1[i][j] = pixelmat[i][j]; temp2[i][j] = pixelmat[i][j]; }

for (int i = 0; i<mheight; i++)
for (int j = 0; j<mwidth; j++)
{
p = getp(i);
q = getq(i);
h[i][j] = Hk(j / N, i, N);
}

for (int j = 0; j<mheight; j++){
for (int i = 0; i<mwidth; i++){
for (int k = 0; k<mwidth; k++){
tmp += h[i][k] * temp1[k][j];
}
temp2[i][j] = int(tmp);
tmp = 0;
}
}


for (int j = 0; j<mheight; j++){
for (int i = 0; i<mwidth; i++){
for (int k = 0; k<mwidth; k++){
tmp += temp2[i][k] * h[j][k];
}
pixelmat[i][j] = int(tmp);
tmp = 0;
}
}

return pixelmat;

}
*/
//haar变换, 返回处理后的图像

int** haar(int** pixelmat, int mheight, int mwidth)
{
	float **h = new float *[mheight];
	float **haar = new float *[mheight];
	float tmp = 0, z, a, b, c;
	int p, q, cnt = mheight / 2;
	for (int i = 0; i<mheight; i++){
		haar[i] = (float*)malloc(sizeof(float)*mwidth);
		h[i] = (float*)malloc(sizeof(float)*mwidth);
	}
	for (int i = 0; i<mheight; i++)
	for (int j = 0; j<mwidth; j++){
		haar[i][j] = 0;
		h[i][j] = 1;
	}
	for (int i = 0; i<mheight; i++){
		for (int j = 0; j<mwidth; j++){
			if (i == 0)	h[i][j] = 1 / sqrt(double(mheight));
			else{
				for (int k = 0; k<9; k++){
					if (pow(2.0, double(k))>i){
						p = k - 1;
						break;
					}
				}
				q = i + 1 - pow(2.0, double(p));
				z = float(j) / mwidth; a = (q - 1) / pow(2.0, double(p)); b = (q - 0.5) / pow(2.0, double(p)); c = q / pow(2.0, double(p));
				if (a <= z && z<b)	h[i][j] = pow(2.0, p) / double(mheight);
				else if (b <= z && z<c) h[i][j] = -pow(2.0, p) / double(mheight);
				else h[i][j] = 0;
			}
		}
	}
	for (int i = 0; i<mheight; i++)
	for (int j = 0; j<mwidth; j++)
	for (int k = 0; k<mwidth; k++)
		haar[i][j] += pixelmat[i][k] * h[j][k];
	for (int j = 0; j<mheight; j++){
		for (int i = 0; i<mwidth; i++){
			for (int k = 0; k<mwidth; k++){
				tmp += haar[k][j] * h[i][k];
			}
			pixelmat[i][j] = int(tmp);
			tmp = 0;
		}
	}
	return pixelmat;
}


//生成随机噪声, 返回处理后的图像;
int** randomnoise(int** pixelmat, int mheight, int mwidth)
{

	int H = mheight, W = mwidth;
	int i, j, noisenum, num, noisevalue, x, y;
	bool noise[256][256];
	for (i = 0; i<H; ++i) //初始化噪声数组
	for (j = 0; j<W; ++j)
		noise[i][j] = 0;
	noisenum = H*W / 4;
	num = 0;
	srand((int)time(0));
	while (num<noisenum)
	{
		x = (int)(rand() % H);
		y = (int)(rand() % W);
		if (!noise[x][y])
		{
			noise[x][y] = 1;
			num++;
			noisevalue = -60 + (int)(rand() % 121);
			pixelmat[x][y] = pixelmat[x][y] + noisevalue;
			if (pixelmat[x][y]<0) pixelmat[x][y] = 0;
			if (pixelmat[x][y]>255) pixelmat[x][y] = 255;
		}
	}
	return pixelmat;
}



//生成椒盐噪声, 返回处理后的图像
int** impulsenoise(int** pixelmat, int mheight, int mwidth)
{
	int **p;
	p = pixelmat;

	int H = mheight, W = mwidth;
	int i, j, noisenum, minnum, maxnum, x, y;
	bool noise[256][256] = { 0 };
	for (i = 0; i<H; ++i)
	for (j = 0; j<W; ++j)
		noise[i][j] = 0;
	noisenum = H*W / 10;
	minnum = maxnum = 0;
	srand((int)time(0));
	while (minnum<noisenum / 2) {
		x = (int)(rand() % H);
		y = (int)(rand() % W);
		if (!noise[x][y]) {
			noise[x][y] = 1;
			p[x][y] = 0;
			minnum++;
		}
	}
	while (maxnum<noisenum / 2) {
		x = (int)(rand() % H);
		y = (int)(rand() % W);
		if (!noise[x][y]) {
			noise[x][y] = 1;
			p[x][y] = 255;
			maxnum++;
		}
	}
	return p;

}


//逆滤波复原
int** inversefit(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//维纳滤波
int** wienerfit(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}


//示例: JPEG压缩及解压缩
int** jpeg(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}