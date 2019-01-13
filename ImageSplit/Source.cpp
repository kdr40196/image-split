#include<iostream>
#include<string>
#include<opencv2/opencv.hpp>

// image_split.exe <image_name> <width> <height>
int main(int argc, char** argv) {

    if (argc != 4) {
        std::cerr << "Usage: ./image_split.exe <image_name> <width> <height>" << std::endl;
        return -1;
    }

    std::string fileName = argv[1];
    std::string baseFileName = fileName.substr(0, fileName.find_last_of('.'));
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);

    cv::Mat image = cv::imread(fileName);

    cv::Rect rect(0, 0, width, height);

    int counter = 1;
    while (rect.y < image.rows) {
        while (rect.x < image.cols) {

            if (rect.x + width > image.cols) {
                rect.width = image.cols - rect.x;
            }

            std::cout << rect << std::endl;
            std::string imageName = baseFileName + '_' + std::to_string(counter) + ".png";
            cv::imwrite(std::string(imageName), cv::Mat(image, rect));

            rect.x += width;
            counter++;
        }

        rect.x = 0;
        rect.y += height;
    }

    return 0;
}