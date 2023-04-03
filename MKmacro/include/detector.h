#ifndef DETECTOR_H
#define DETECTOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <gdiplus.h>
#include <fstream>
#include <vector>

class Detector{
private:
    //Background image
    cv::Mat img;

    //Background image but gray
    cv::Mat imgGray;

    //Target image
    cv::Mat templ;

    //Mask
    cv::Mat result;

    //Storage for matches object data
    std::vector<cv::Point> matches;

    //ScreenShot rectangle data
    int x, y, width, height;

    //Data load validator
    bool load;

public:
    //Accessors
    bool Load();

    //Init
    void getData();

    //Functions
    void getImages();
    bool findCaptcha();
    void printResult();
    int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
    cv::Mat gdiscreen(int x, int y, int width, int height);

};

#endif