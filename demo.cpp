#include <iostream>
#include <opencv2/opencv.hpp>
#include <zbar.h>

int main()
{
    cv::Mat demo_image = cv::imread("/home/lu/work/crow_barcode/test/3.png");
    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
    cv::Mat gray;
    cv::cvtColor(demo_image, gray, cv::COLOR_RGB2GRAY);
    zbar::Image imageZbar(gray.cols, gray.rows, "Y800", gray.data, gray.cols * gray.rows);
    int n=scanner.scan(imageZbar);
    zbar::Image::SymbolIterator symbol = imageZbar.symbol_begin();
    if (imageZbar.symbol_begin() == imageZbar.symbol_end())
    {
        std::cout << "查询条码失败，请检查图片！" << std::endl;
    }
    for (; symbol != imageZbar.symbol_end(); ++symbol)
    {
        std::cout << "类型：" << std::endl << symbol->get_type_name() << std::endl;
        std::cout << "内容：" << std::endl << symbol->get_data() << std::endl;
    }
}