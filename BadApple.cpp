//@author Ezhidze https://github.com/Ezhidzee

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <windows.h>

using namespace cv;
using namespace std;

int countOfNeighbors(Mat, int, int);

int main() {
    VideoCapture compressedFile("BadAppleCompressed.mp4");
    VideoCapture originalFile("BadApple.mp4");
    vector<string> frames;

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 12;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    if (!compressedFile.isOpened()) {
        cout << "Cannot open file" << endl;
        return -1;
    }

    int counter = 0;

    cout << "Processing, please wait..." << endl;
    bool isFrame = 1;
    while (true) {
        Mat frame;
        isFrame = compressedFile.read(frame);

        if (!isFrame) {
            break;
        }

        String page;
        for (int i = 0; i < 60; i++) {
            for (int j = 0; j < 80; j++) {
                if (frame.at<Vec3b>(i, j)[0] > 240 &&
                    frame.at<Vec3b>(i, j)[1] > 240 &&
                    frame.at<Vec3b>(i, j)[2] > 240) {
                    if (countOfNeighbors(frame, i, j) < 8) {
                        page += 'I';
                    } else {
                        page += '@';
                    }
                } else {
                    page += ' ';
                }
            }
            page += '\n';
        }
        frames.push_back(page);
    }

    cout << "Processing done!";
    Sleep(1000);
    isFrame = 1;
    while (true) {
        Mat frame;
        isFrame = originalFile.read(frame);

        if (!isFrame) {
            break;
        }

        cout << string(100, '\n') << frames[0];
        frames.erase(frames.begin());

        imshow("Bad Apple", frame);

        if (waitKey(30) == 27) {
            cout << "Esc key is pressed by user" << endl;
            break;
        }
    }
}

inline int countOfNeighbors(Mat frame, int i, int j) {
    int counter = 8;
    if (frame.at<Vec3b>(i, j - 1)[0] < 40 &&
        frame.at<Vec3b>(i, j - 1)[1] < 40 &&
        frame.at<Vec3b>(i, j - 1)[2] < 40) {
        counter--;
    }
    if (frame.at<Vec3b>(i, j + 1)[0] < 40 &&
        frame.at<Vec3b>(i, j + 1)[1] < 40 &&
        frame.at<Vec3b>(i, j + 1)[2] < 40) {
        counter--;
    }
    if (frame.at<Vec3b>(i + 1, j - 1)[0] < 40 &&
        frame.at<Vec3b>(i + 1, j - 1)[1] < 40 &&
        frame.at<Vec3b>(i + 1, j - 1)[2] < 40) {
        counter--;
    }
    if (frame.at<Vec3b>(i + 1, j + 1)[0] < 40 &&
        frame.at<Vec3b>(i + 1, j + 1)[1] < 40 &&
        frame.at<Vec3b>(i + 1, j + 1)[2] < 40) {
        counter--;
    }
    if (frame.at<Vec3b>(i + 1, j)[0] < 40 &&
        frame.at<Vec3b>(i + 1, j)[1] < 40 &&
        frame.at<Vec3b>(i + 1, j)[2] < 40) {
        counter--;
    }
    if (frame.at<Vec3b>(i - 1, j)[0] < 40 &&
        frame.at<Vec3b>(i - 1, j)[1] < 40 &&
        frame.at<Vec3b>(i - 1, j)[2] < 40) {
        counter--;
    }
    if (frame.at<Vec3b>(i - 1, j + 1)[0] < 40 &&
        frame.at<Vec3b>(i - 1, j + 1)[1] < 40 &&
        frame.at<Vec3b>(i - 1, j + 1)[2] < 40) {
        counter--;
    }
    if (frame.at<Vec3b>(i - 1, j - 1)[0] < 40 &&
        frame.at<Vec3b>(i - 1, j - 1)[1] < 40 &&
        frame.at<Vec3b>(i - 1, j - 1)[2] < 40) {
        counter--;
    }
    return counter;
}