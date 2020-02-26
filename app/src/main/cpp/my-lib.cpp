//
// Created by renault on 2/21/20.

#include <jni.h>
#include <string>

#include <stdlib.h>
#include <android/bitmap.h>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>



using namespace cv;



extern "C" {

    JNIEXPORT void JNICALL
    Java_com_renault_mylibraryinclusion_MainActivity_rotatePic(
            JNIEnv *env,
            jobject /* this */,
            jobject bitmap,
            jstring destination,
            jint angle) {


        // Get information about format and size
        AndroidBitmapInfo info;
        AndroidBitmap_getInfo(env, bitmap, &info);

        // Get pointer to pixel buffer
        void *pixels = 0;
        AndroidBitmap_lockPixels(env, bitmap, &pixels);

        // I create separate scope for input Mat here
        // to make sure it is destroyed before unlocking
        // pixels
        {

            // Now create the mat
            cv::Mat input(info.height, info.width, CV_8UC4, pixels);
            cv::cvtColor(input, input, COLOR_BGR2RGB);

            cv::Mat rotation = cv::getRotationMatrix2D(cv::Point2f((info.width / 2), (info.height / 2)),
                                                       angle, 1.0);

            cv::Mat destMat;

            cv::warpAffine(input, destMat, rotation, input.size(), cv::INTER_LANCZOS4);


            // Save to destination
            const char *dest = env->GetStringUTFChars(destination, 0);
            cv::imwrite(dest, destMat);
            env->ReleaseStringUTFChars(destination, dest);
        }

        // Release the Bitmap buffer once we have it inside our Mat
        AndroidBitmap_unlockPixels(env, bitmap);
    }



    JNIEXPORT jstring JNICALL
    Java_com_renault_mylibraryinclusion_MainActivity_sayHello(
            JNIEnv *env,
            jobject /* this */,
            jint i) {

        char * concatened = (char *)malloc(strlen("Hi from my-lib :) (  )") + sizeof(i));
        strcpy(concatened, "Hi from my-lib :) ( ");
        char buffer[sizeof(i)];
        sprintf(buffer, "%d", i);

        strcat(concatened, buffer);
        strcat(concatened, " )");

        jstring jstr = (*env).NewStringUTF(concatened);


        return jstr;
    }


    JNIEXPORT void JNICALL
    Java_com_renault_mylibraryinclusion_MainActivity_drawChessboard(
            JNIEnv *env,
            jobject /* this */,
            jobject bitmap,
            jstring destination
            ) {

        // Get information about format and size
        AndroidBitmapInfo info;
        AndroidBitmap_getInfo(env, bitmap, &info);

        // Get pointer to pixel buffer
        void *pixels = 0;
        AndroidBitmap_lockPixels(env, bitmap, &pixels);

        // I create separate scope for input Mat here
        // to make sure it is destroyed before unlocking
        // pixels
        {

            // Now create the mat
            cv::Mat img(info.height, info.width, CV_8UC4, pixels);
            cv::cvtColor(img, img, COLOR_BGR2RGB);

            std::vector<cv::Point2f> cornersCamera;
            bool patternFound = cv::findChessboardCorners(img, cv::Size(9,6), cornersCamera, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

            drawChessboardCorners(img, cv::Size(9, 6), cornersCamera, patternFound);

            // Save to destination
            const char *dest = env->GetStringUTFChars(destination, 0);
            cv::imwrite(dest, img);
            env->ReleaseStringUTFChars(destination, dest);
        }

        // Release the Bitmap buffer once we have it inside our Mat
        AndroidBitmap_unlockPixels(env, bitmap);

    }



}