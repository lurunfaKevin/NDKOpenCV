#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <com_lurunfa_test_OpenCVHelper.h>

//#include <vector>

using namespace std;
using namespace cv;
//-----------------------------------------------------------
//***********----------class Img-----------***********
#include <vector>
#include "iostream"
#include "stdio.h"
/*IMPORTANT*/
using namespace std;
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
typedef unsigned char byte;
#pragma comment(lib,"cxcore.lib")
#pragma comment(lib,"cv.lib")
#pragma comment(lib,"highgui.lib")
//"cvaux.lib" "cvcam.lib"  "ml.lib"
//class Color-----
class Color {
public:
    static CvScalar red;
    static CvScalar green;
    static CvScalar blue;
    static CvScalar black;
    static CvScalar white;

};
CvScalar Color::green = CV_RGB(0, 255, 0);
CvScalar Color::red = CV_RGB(255, 0, 0);
CvScalar Color::blue = CV_RGB(0, 0, 255);
CvScalar Color::black = CV_RGB(0, 0, 0);
CvScalar Color::white = CV_RGB(255, 255, 255);
//  --- End Class Color------

// ----  CvMat  ˝æ›π•»°------
class CImg {
public:
    IplImage *img;
    IplImage *img_32FC1;
    IplImage *img_RGBA_C3;

    CImg() {
        img = NULL;
        img_32FC1 = NULL;
        img_RGBA_C3=NULL;
    }

    //-----------------------------------Function here;
    //---static Functions declaration ---------
    static IplImage* CreateImg(int h = 3, int w = 3, int typeOfData = 8,
                               int nChannels = 1) {
        IplImage *retImg = cvCreateImage(cvSize(w, h), typeOfData, nChannels);
        return retImg;
    } //end createImg()

    static void ShowImg(int win_num, IplImage *src) {

        char windowName[22];
        sprintf(windowName, "Õ‚≤øimg_%d\0", win_num);
        cvNamedWindow(windowName, 1);
        cvShowImage(windowName, src);

    } //end showImg;

    void ReSizeToFrame(int Frame_size = 128 * 2) {
        int k = Frame_size;

        int h = img->height;
        int w = img->width;

        int max = h > w ? h : w;
        float rate = (float) (max * 1.0 / k);
        float w1 = w / rate;
        float h1 = h / rate;
        CvSize sz = cvSize((int) w1, (int) h1);

        IplImage *tempimg = cvCreateImage(sz, 8, 1);
        cvResize(img, tempimg, CV_INTER_LINEAR); //CV_INTER_CUBIC CV_INTER_LINEAR
        img = tempimg;

    } //end Resize();

    void LoadToGrayImg(char *FilePath) {

        IplImage *openImg = cvLoadImage(FilePath, -1);
        if (openImg->nChannels == 3) {
            IplImage *retGrayImage = cvCreateImage(cvGetSize(openImg), 8, 1);
            cvCvtColor(openImg, retGrayImage, CV_BGR2GRAY);
            img = retGrayImage;

        } else if (openImg->nChannels == 1)
            img = openImg;
        else
            cout << "Image DataType Not supported!\n";

    } //end LoadToGrayImg()

    void ShowImg(int win_num = 0) {

        char windowName[22];
        sprintf(windowName, "img_%d\0", win_num);
        cvNamedWindow(windowName, 1);
        cvShowImage(windowName, img);

    } //end showImg;
    void GetImg_32FC1() {
        img_32FC1 = cvCreateImage(cvGetSize(img), 32, 1);
        cvConvertScale(img, img_32FC1, 1.0);
    } //end GetImg_32FC1()

    void AdaptiveThreshold(void) {
        assert(img->nChannels == 1);
        cvAdaptiveThreshold(img, img, 255);
    }
    ;
    void Smooth(int Temp_Size = 5) {
        cvSmooth(img, img, CV_GAUSSIAN, Temp_Size);
    } // End Smooth
    void Threshold(int thresh = 119) {
        cvThreshold(img, img, thresh, 255, CV_THRESH_BINARY);
    } //End Threshold
    void EqualizeHist() {
        cvEqualizeHist(img, img);

    }
    void Canny(int param1 = 50, int param2 = 200) {
        IplImage *image0 = img;
        cvCanny(image0, image0, param1, param1, 3);
    }
    //

    static void ShowMatrixData(CvMat *mat) {
#define CV_MAT_PElem(mat__,mytype,I,J) ((mytype*)cvPtr2D(mat__,I,J))
        int type = CV_MAT_TYPE(mat->type);
        int i, j;
        int t;

        int h = mat->height;
        int w = mat->width;

        int nchannels = 1;
        if (type == CV_64FC3 || type == CV_64FC2 || type == CV_64FC1) {
            if (type == CV_64FC3) {

                nchannels = 3;
            } else if (type == CV_64FC2) {
                nchannels = 2;
            } else if (type == CV_64FC1) {
                nchannels = 1;
            }

            for (i = 0; i < h; i++) {
                for (j = 0; j < w; j++) {
                    if (nchannels != 1)
                        printf("[");

                    for (t = 0; t < nchannels; t++) {
                        double *dp = CV_MAT_PElem(mat,double,i,j);
                        printf(" %4.2f ", dp[t]);
                    }
                    if (nchannels != 1)
                        printf("]");
                }
                cout << "\n";
            }
        } //end double

        else if (type == CV_32FC3 || type == CV_32FC2 || type == CV_32FC1) {
            if (type == CV_32FC3) {

                nchannels = 3;
            } else if (type == CV_32FC2) {
                nchannels = 2;
            } else if (type == CV_32FC1) {
                nchannels = 1;
            }

            for (i = 0; i < h; i++) {
                for (j = 0; j < w; j++) {
                    if (nchannels != 1)
                        printf("[");
                    for (t = 0; t < nchannels; t++) {
                        float *dp = CV_MAT_PElem(mat,float,i,j);
                        //	cout<<" "<<dp[t]<<" ";
                        printf(" %4.2f ", dp[t]);
                    }
                    if (nchannels != 1)
                        printf("]");
                }
                cout << "\n";
            }
        } //end float
        else if (type == CV_32SC3 || type == CV_32SC2 || type == CV_32SC1) {
            if (type == CV_32SC3) {

                nchannels = 3;
            } else if (type == CV_32SC2) {
                nchannels = 2;
            } else if (type == CV_32SC1) {
                nchannels = 1;
            }

            for (i = 0; i < h; i++) {
                for (j = 0; j < w; j++) {
                    if (nchannels != 1)
                        printf("[");
                    for (t = 0; t < nchannels; t++) {
                        int *dp = CV_MAT_PElem(mat,int,i,j);
                        printf(" %3d ", dp[t]);
                    }
                    if (nchannels != 1)
                        printf("]");
                }
                cout << "\n";
            }
        } //end int
        else if (type == CV_8UC3 || type == CV_8UC2 || type == CV_8UC1) {
            if (type == CV_8UC3) {

                nchannels = 3;
            } else if (type == CV_8UC2) {
                nchannels = 2;
            } else if (type == CV_8UC1) {
                nchannels = 1;
            }

            for (i = 0; i < h; i++) {
                for (j = 0; j < w; j++) {
                    if (nchannels != 1)
                        printf("[");
                    for (t = 0; t < nchannels; t++) {
                        byte *dp = CV_MAT_PElem(mat,byte,i,j);
                        printf(" %3d ", dp[t]);
                    }
                    if (nchannels != 1)
                        printf("]");
                }
                cout << "\n";
            }
        } //end uchar
        else
            cout << "unsupported dataType!!--\n";

    } // End SHowMatData----------------------

    IplImage *GetImg_8UC3_Gray() {
        IplImage *imgC3 = CreateImg(img->height, img->width, 8, 3);
        cvZero(imgC3);
        IplImage *imgC1 = img;
        cvMerge(imgC1, imgC1, imgC1, NULL, imgC3);
        return imgC3;
    } //End Get Img3Channels()
    static void ShowMatrixData(IplImage *src) {
        CvMat header; //ΩˆΩˆ¥¥Ω®Õ∑£¨≤ª∑÷≈‰ ˝æ›ø’º‰
        CvMat *mat = cvGetMat(src, &header); // share the data Area
        ShowMatrixData(mat);
    } //end show imgData
    static CvMat* Transpose(CvMat* _mat) {
        int h = _mat->width;
        int w = _mat->height;
        int type = CV_MAT_TYPE(_mat->type);
        CvMat *ret_mat = cvCreateMat(h, w, type);
        cvT(_mat, ret_mat);
        return ret_mat;
    } //End Transpose() --
    static CvMat* Transpose(IplImage* _img) {
        CvMat header; //ΩˆΩˆ¥¥Ω®Õ∑£¨≤ª∑÷≈‰ ˝æ›ø’º‰
        CvMat *mat = cvGetMat(_img, &header); // share the data Area
        return Transpose(mat);

    } //End Transpose() --
    void MergeTo_BGRA_C4(IplImage *in_out_imgC3){
        //¥”“ªÕ®µ¿µƒgrayImg -- >> ÀƒÕ®µ¿µƒ RGBA Õº£ª

        IplImage *mgray=img; //gray is img
        IplImage *c_B=mgray;
        IplImage *c_G=mgray;
        IplImage *c_R=mgray;
        IplImage *c_A=cvCloneImage(mgray);cvZero(c_A);
        cvNot(c_A,c_A);


        cvMerge(c_B,c_G,c_R,c_A,in_out_imgC3);

    }// end Get_BGRA_C4


    ~CImg() {
        if (img != NULL)
            cvReleaseImage(&img);
        img_32FC1 = NULL;

        cvDestroyAllWindows();
    }
};
// *****----  STRUCT_2D_to_3D-----************************************************************************
class C_2D_to_3D {
public:
    CvMat *_2D_pt; //Matrix 2D Point

    CvMat *intrinsic_matrix; //Matrix A
    CvMat *rotation_vectors; //Matrix R  -->(1,1,CV_32FC3)
    CvMat *translation_vectors; //Matrix t

    CvMat *_3D_pt; //Matrix 3D point
//	int image_count;
    C_2D_to_3D() {
        _2D_pt = NULL; //Matrix 2D Point

        intrinsic_matrix = NULL; //Matrix A
        rotation_vectors = NULL; //Matrix R  -->(1,1,CV_32FC3)
        translation_vectors = NULL; //Matrix t

        _3D_pt = NULL; //Matrix 3D point
        //	image_count=-1;
    }
    void showAllVals(int valNum = 6) {
        CImg idcImg;
        int i, j;

        CvMat *p[5] = { _2D_pt, intrinsic_matrix, rotation_vectors,
                        translation_vectors, _3D_pt };
        char *pName[5] = { "_2D_pt", "intrinsic_matrix", "rotation_vectors",
                           "translation_vectors", "_3D_pt" };
        for (i = 0; i < 5; i++)
            if (p[i] == NULL) {
                printf(pName[i]);
                printf(" is NULL pointer!\n");
                return;
            } //end reg Null

        //---------	show All 6 Vals------------------
        cout << " image_count-------\n";
        cout << rotation_vectors->width << endl;
        cout << "idcImg.ShowMatrixData(_2D_pt)\n";
        idcImg.ShowMatrixData(_2D_pt);
        cout << endl;
        cout << "idcImg.ShowMatrixData(intrinsic_matrix)\n";
        idcImg.ShowMatrixData(intrinsic_matrix);
        cout << endl;
        cout << "idcImg.ShowMatrixData(rotation_vectors)\n";
        idcImg.ShowMatrixData(rotation_vectors);
        cout << endl;
        cout << "idcImg.ShowMatrixData(translation_vectors)\n";
        idcImg.ShowMatrixData(translation_vectors);
        cout << endl;
        cout << "idcImg.ShowMatrixData(_3D_pt)\n";
        idcImg.ShowMatrixData(_3D_pt);
        cout << endl;

    } //end Show(vals= 6);
    void do_2D_to_3D(CvPoint2D32f input_pt2D = cvPoint2D32f(333, 24)) {
        CvPoint2D32f inPt2D = input_pt2D;
        CV_MAT_PElem(_2D_pt,float,0,0)[0] = inPt2D.x;
        CV_MAT_PElem(_2D_pt,float,1,0)[0] = inPt2D.y;
        CV_MAT_PElem(_2D_pt,float,2,0)[0] = 1;

        int i, j;

        CvMat *p[5] = { _2D_pt, intrinsic_matrix, rotation_vectors,
                        translation_vectors, _3D_pt };
        char *pName[5] = { "_2D_pt", "intrinsic_matrix", "rotation_vectors",
                           "translation_vectors", "_3D_pt" };
        for (i = 0; i < 5; i++)
            if (p[i] == NULL) {
                printf(pName[i]);
                printf(" is NULL pointer!\n");
                return;
            } //end reg Null

        // get the right six vals-------------------
        for (i = 0; i < 1; i++) //image_count=tr~.width--
        {

            CvMat* rotation_vector_per = cvCreateMat(1, 1, CV_32FC3);
            CvMat* rotation_matrix = cvCreateMat(3, 3, CV_32FC1); // 3 x 3

            rotation_vector_per->data.ptr = cvPtr2D(rotation_vectors, 0, i);
            cvRodrigues2(rotation_vector_per, rotation_matrix);

            CvMat *A = intrinsic_matrix;

            CvMat *R = rotation_matrix;

            CvMat *B = cvCreateMat(3, 3, CV_32FC1);
            CvMat *t = cvCreateMat(3, 1, CV_32FC1);

            B = cvCloneMat(R);

            // Initial [t]--  //ªÒµ√µ•∏ˆÕºœÒµƒt(3x1)æÿ’Û “‘º∞ [R3+t]
            for (j = 0; j < 3; j++) {
                float t_i_j = (CV_MAT_PElem(t,float,j,0)[0] =
                                       CV_MAT_PElem(translation_vectors,float,0,i)[j]); //Translat_vectors->(T)
                CV_MAT_PElem(B,float,j,2)[0] += t_i_j; ////  ( A B=[R1,R,R3+t] )^(-1) [x1,x2,x3](T)

            } //end for(j)

            cvGEMM(A, B, 1, 0, 1, B);
            cvInvert(B, B, CV_LU);
            cvGEMM(B, _2D_pt, 1, 0, 0, _3D_pt, 0);

            float _z;
            _z = CV_MAT_PElem(_3D_pt,float,2,0)[0];
            for (j = 0; j < 3; j++) {
                CV_MAT_PElem(_3D_pt,float,j,0)[0] /= _z;
            }

            //	idCImg.ShowMatrixData(_3D_pt);

        } //end for(i:image_count)---

    } //end do2D - > 3D
    void do_3D_to_2D(CvPoint3D32f intputpt_3d = cvPoint3D32f(0, 0, 1)) {
        CvPoint3D32f inPt3D = intputpt_3d;
        CV_MAT_PElem(_3D_pt,float,0,0)[0] = inPt3D.x;
        CV_MAT_PElem(_3D_pt,float,1,0)[0] = inPt3D.y;
        CV_MAT_PElem(_3D_pt,float,2,0)[0] = 1;

        int i, j;

        CvMat *p[5] = { _2D_pt, intrinsic_matrix, rotation_vectors,
                        translation_vectors, _3D_pt };
        char *pName[5] = { "_2D_pt", "intrinsic_matrix", "rotation_vectors",
                           "translation_vectors", "_3D_pt" };
        for (i = 0; i < 5; i++)
            if (p[i] == NULL) {
                printf(pName[i]);
                printf(" is NULL pointer!\n");
                return;
            } //end reg Null

        // get the right six vals
        for (i = 0; i < 1; i++) //image_count=1
        {
            // C_2D_to_3D id_2d3d;

            CvMat* rotation_vector_per = cvCreateMat(1, 1, CV_32FC3);
            CvMat* rotation_matrix = cvCreateMat(3, 3, CV_32FC1); // 3 x 3

            rotation_vector_per->data.ptr = cvPtr2D(rotation_vectors, 0, i);
            cvRodrigues2(rotation_vector_per, rotation_matrix);

            CvMat *A = intrinsic_matrix;

            CvMat *R = rotation_matrix;

            CvMat *B = cvCreateMat(3, 3, CV_32FC1);
            CvMat *t = cvCreateMat(3, 1, CV_32FC1);

            B = cvCloneMat(R);

            // Initial [t]--  //ªÒµ√µ•∏ˆÕºœÒµƒt(3x1)æÿ’Û
            for (j = 0; j < 3; j++) {

                float t_i_j = (CV_MAT_PElem(t,float,j,0)[0] =
                                       CV_MAT_PElem(translation_vectors,float,0,i)[j]); //Translat_vectors->(T)
                CV_MAT_PElem(B,float,j,2)[0] += t_i_j; ////  ( A B=[R1,R,R3+t] )^(-1) [x1,x2,x3](T)

            } //end for(j)

            cvGEMM(R, _3D_pt, 1, t, 1, _2D_pt);
            cvGEMM(A, _2D_pt, 1, 0, 1, _2D_pt);

            // 3D ->2D _z=1 ---

            float _z;

            _z = CV_MAT_PElem(_2D_pt,float,2,0)[0];

            for (j = 0; j < 3; j++) {

                CV_MAT_PElem(_2D_pt,float,j,0)[0] /= _z;
            }

        } //end for(i:image_count)---

    } //end do_3D_to_2D---

};
// End struct C_2D_3D-------

//****-------- End Class CImg ---------------******
CImg idCImg;




//-----------------------------------------------------------
//--------------------------------------start MHI-------
// ≤ø∑÷∏˙◊Ÿ≤Œ ˝(√Î)
#include <math.h>
#include <ctype.h>
const double MHI_DURATION = 0.5;
const double MAX_TIME_DELTA = 0.5;
const double MIN_TIME_DELTA = 0.05;
const int N = 3;

//
const int CONTOUR_MAX_AERA = 200;

// ring image buffer
IplImage **buf = 0;
int last = 0;

// µ±«∞ ”∆µ÷°
IplImage *mhi = 0; // MHI: motion history image

//CvFilter filter ;
CvConnectedComp *cur_comp, min_comp;
CvConnectedComp comp;
CvMemStorage *storage;
CvPoint pt[4];
//FILE *fp;
//FILE *fp2;

//  ≤Œ ˝£∫
//  img ®C  ‰»Î ”∆µ÷°
//  dst ®C ºÏ≤‚Ω·π˚
void  update_mhi( IplImage* img, IplImage* dst, int diff_threshold )
{
    double timestamp = clock()/100.; // get current time in seconds
    CvSize size = cvSize(img->width,img->height); // get current frame size
    int i, j, idx1, idx2;
    IplImage* silh;
    uchar val;
    float temp;
    IplImage* pyr = cvCreateImage( cvSize((size.width & -2)/2, (size.height & -2)/2), 8, 1 );
    CvMemStorage *stor;
    CvSeq *cont, *result, *squares;
    CvSeqReader reader;
//	int m=r.x + r.width/2;


    if( !mhi || mhi->width != size.width || mhi->height != size.height )
    {
        if( buf == 0 )
        {
            buf = (IplImage**)malloc(N*sizeof(buf[0]));
            memset( buf, 0, N*sizeof(buf[0]));
        }

        for( i = 0; i < N; i++ )
        {
            cvReleaseImage( &buf[i] );
            buf[i] = cvCreateImage( size, IPL_DEPTH_8U, 1 );
            cvZero( buf[i] );
        }
        cvReleaseImage( &mhi );
        mhi = cvCreateImage( size, IPL_DEPTH_32F, 1 );
        cvZero( mhi ); // clear MHI at the beginning
    } // end of if(mhi)

    cvCvtColor( img, buf[last], CV_BGR2GRAY ); // convert frame to grayscale

    idx1 = last;
    idx2 = (last + 1) % N; // index of (last - (N-1))th frame
    last = idx2;

    // ◊ˆ÷°≤Ó
    silh = buf[idx2];
    cvAbsDiff( buf[idx1], buf[idx2], silh ); // get difference between frames

    // ∂‘≤ÓÕºœÒ◊ˆ∂˛÷µªØ
    cvThreshold( silh, silh, 30, 255, CV_THRESH_BINARY ); // and threshold it

    cvUpdateMotionHistory( silh, mhi, timestamp, MHI_DURATION ); // update MHI
    cvCvtScale( mhi, dst, 255./MHI_DURATION,
                (MHI_DURATION - timestamp)*255./MHI_DURATION );
    cvCvtScale( mhi, dst, 255./MHI_DURATION, 0 );

    // ÷–÷µ¬À≤®£¨œ˚≥˝–°µƒ‘Î…˘
    cvSmooth( dst, dst, CV_MEDIAN, 3, 0, 0, 0 );

    // œÚœ¬≤…—˘£¨»•µÙ‘Î…˘
    cvPyrDown( dst, pyr, CV_GAUSSIAN_5x5 );
    cvDilate( pyr, pyr, 0, 1 );  // ◊ˆ≈Ú’Õ≤Ÿ◊˜£¨œ˚≥˝ƒø±Íµƒ≤ª¡¨–¯ø’∂¥
    cvPyrUp( pyr, dst, CV_GAUSSIAN_5x5 );
    //
    // œ¬√Êµƒ≥Ã–Ú∂Œ”√¿¥’“µΩ¬÷¿™
    //
    // Ω®¡¢µ„’Û–Ú¡–,±£¥Ê¬÷¿™µ„’Û.
    stor = cvCreateMemStorage(0);
    cont = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint) , stor);

    // ’“µΩÀ˘”–¬÷¿™
    cvFindContours( dst, stor, &cont, sizeof(CvContour),
                    CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

    // ÷±Ω” π”√CONTOUR÷–µƒæÿ–Œ¿¥ª≠¬÷¿™
//	int mx[2]={0};
//	int ny[2]={0};
    for(;cont;cont = cont->h_next)
    {
        CvRect r = ((CvContour*)cont)->rect;
        CvRect r2;
        CvSeq *cont_ne=cont->h_next;
        if(cont_ne)
            r2 = ((CvContour*)cont_ne)->rect;

        if(r.height * r.width > CONTOUR_MAX_AERA) // √Êª˝–°µƒ∑Ω–Œ≈◊∆˙µÙ
        {
            cvRectangle( img, cvPoint(r.x,r.y),
                         cvPoint(r.x + r.width, r.y + r.height),
                         CV_RGB(0,0,255), 1, CV_AA,0);

            // fprintf(fp,"%d\t%d\n",r.x + r.width/2,r.y + r.height/2);



        }
        if(r2.height * r2.width > CONTOUR_MAX_AERA) // √Êª˝–°µƒ∑Ω–Œ≈◊∆˙µÙ
        {
            cvRectangle( img, cvPoint(r2.x,r2.y),
                         cvPoint(r2.x + r2.width, r2.y + r2.height),
                         CV_RGB(0,0,255), 1, CV_AA,0);
            // fprintf(fp,"%d\t%d\n",r2.x + r2.width/2,r2.y + r2.height/2);
        }


        //mx[0]=(int)(r.x + r.width/2);  ny[0]=r.y + r.height/2;

        //mx[1]=(int)(r2.x + r2.width/2);  ny[1]=r2.y + r2.height/2;
        //int comX;int comY;
        // comX=mx[0]-mx[1];
        // comY=ny[0]-ny[1];

        //	printf("%d,%d\n",comX,comY);
        //cont=cont->h_prev;



    }
    //  Õ∑≈ƒ⁄¥Ê
    cvReleaseMemStorage(&stor);
    cvReleaseImage( &pyr );
}
//-----------------------------------------------------End MHI---




extern "C" {
int itest=0;
IplImage *Zero=NULL;
JNIEXPORT jint JNICALL Java_com_lurunfa_test_OpenCVHelper_FindFeatures(
        JNIEnv* env, jobject thiz, jint width, jint height, jbyteArray yuv,
        jintArray bgra) {
    if(itest==0&&Zero==NULL)
        Zero=idCImg.CreateImg(height,width,8,1);



    jbyte* _yuv = env->GetByteArrayElements(yuv, 0);
    jint* _bgra = env->GetIntArrayElements(bgra, 0);

    Mat myuv(height + height / 2, width, CV_8UC1, (unsigned char *) _yuv);
    Mat mbgra(height, width, CV_8UC4, (unsigned char *) _bgra);
    Mat mgray(height, width, CV_8UC1, (unsigned char *) _yuv);

    cvtColor(myuv, mbgra, CV_YUV420sp2BGR, 4);

    //Please make attention about BGRA byte order
    IplImage img = mbgra;
    IplImage *m_bgra = &img;

    IplImage img2 = mgray;
    IplImage *m_gray = &img2;
    IplImage *gray = cvCloneImage(m_gray);

    //cvZero(m_bgra);

    int nc = m_bgra->nChannels;
    idCImg.img = gray;
//	idCImg.Canny();


    //cvMerge(gray,gray,gray,NULL,m_bgra);


//Zero=cvCloneImage(idCImg.img);
    IplImage*im3c=	idCImg.GetImg_8UC3_Gray(); //Get C=3 Image for CImg.img

    update_mhi(im3c,Zero,33);
    cvCvtColor(im3c,idCImg.img,CV_BGR2GRAY);


    idCImg.MergeTo_BGRA_C4(m_bgra);


//while()







    int diff__=11;

//update_mhi(imgC3_,grayCopy,diff__);


    env->ReleaseIntArrayElements(bgra, _bgra, 0);
    env->ReleaseByteArrayElements(yuv, _yuv, 0);

    //ARGB stored in java as int array becomes BGRA at native level
    //cvtColor(myuv, mbgra, CV_YUV420sp2BGR, 4);

//	vector<KeyPoint> v;

//	FastFeatureDetector detector(50);
//	detector.detect(mgray, v);
//	for( size_t i = 0; i < v.size(); i++ )
//	circle(mbgra, Point(v[i].pt.x, v[i].pt.y), 10, Scalar(0,0,255,255));
    return itest;
} //end Fun--

}