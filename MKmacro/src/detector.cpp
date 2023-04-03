#include "detector.h"

//Accessors
bool Detector::Load () {return load;}

//Init
void Detector::getData(){

    std::string dummy;

    //Load background image rectangle data from info.txt
    std::ifstream infile ("../data/info.txt");

    if(infile.is_open()){
        
        for(int line = 1; line <= 9; line++){

            if(line  == 9 ){
                infile>>x>>y>>width>>height;
            }
            else{
                getline(infile, dummy);
            }
        }
        infile.close();
        load = true;
    }
}

//Functions
void Detector::getImages(){

    //Screenshot background image
    img = gdiscreen(x, y, width, height);
    
    //Load target image
    templ = cv::imread("../data/temp.png", cv::IMREAD_GRAYSCALE);

    //Convert background image to gray
    cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

}

bool Detector::findCaptcha(){

    //Scan all pixels
    cv::matchTemplate(imgGray, templ, result, cv::TM_CCOEFF_NORMED);

    //Set threshold for accepted similarity
    double threshold = 0.7;  //--> must be 70% similar
    cv::Mat mask = (result >= threshold);

    //Find all non zero value in mask and store it in vector
    cv::findNonZero(mask, matches);

    //Check if matches has any elements
    if(matches.size() > 0){

        return true;
    }

    return false;

}

void Detector::printResult(){

    //Draw rectangle on Captchaed object
    for(int i = 0; i < matches.size(); i++){
        cv::Rect roi (matches[i].x, matches[i].y, templ.cols, templ.rows);
        rectangle(img, roi, cv::Scalar(0,255,0), 3);
    }

    //DisplayImage
    cv::imshow("Image", img);
    cv::waitKey(0);

}

int Detector::GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    using namespace Gdiplus;
    UINT  num = 0;
    UINT  size = 0;

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if(size == 0)
        return -1;

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if(pImageCodecInfo == NULL)
        return -1;

    GetImageEncoders(num, size, pImageCodecInfo);
    for(UINT j = 0; j < num; ++j)
    {
        if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }    
    }
    free(pImageCodecInfo);
    return 0;
}

cv::Mat Detector::gdiscreen(int x, int y, int width, int height) {
    using namespace Gdiplus;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    {
        HDC scrdc, memdc;
        HBITMAP membit;
        scrdc = ::GetDC(0);
        memdc = CreateCompatibleDC(scrdc);
        membit = CreateCompatibleBitmap(scrdc, width, height);
        HBITMAP hOldBitmap = (HBITMAP) SelectObject(memdc, membit);
        BitBlt(memdc, 0, 0, width, height, scrdc, x, y, SRCCOPY);

        // Get the bitmap data
        Bitmap bitmap(membit, NULL);
        BitmapData bitmapData;
        Rect rect(0, 0, width, height);
        bitmap.LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);

        // Create a Mat object from the bitmap data
        cv::Mat img(height, width, CV_8UC4);
        std::memcpy(img.data, bitmapData.Scan0, bitmapData.Stride * height);

        // Release resources
        bitmap.UnlockBits(&bitmapData);
        SelectObject(memdc, hOldBitmap);
        DeleteDC(memdc);
        DeleteObject(membit);
        ::ReleaseDC(0, scrdc);

        return img;
    }
    GdiplusShutdown(gdiplusToken);
}

