#include <iostream>
#include "include/crow_all.h"
#include <opencv2/opencv.hpp>
#include <zbar.h>
#include <nlohmann_json/json.hpp>
#include <regex>

std::string getBarCode(cv::Mat &src_image)
{
    nlohmann::json ret = nlohmann::json::object();
    nlohmann::json data_list = nlohmann::json::array();
    ret["message"] = "response success";
    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
    cv::Mat gray;
    cv::cvtColor(src_image, gray, cv::COLOR_RGB2GRAY);
    zbar::Image imageZbar(gray.cols, gray.rows, "Y800", gray.data, gray.cols * gray.rows);
    int n=scanner.scan(imageZbar);
    zbar::Image::SymbolIterator symbol = imageZbar.symbol_begin();
    for (; symbol != imageZbar.symbol_end(); ++symbol)
    {
        nlohmann::json temp_data = nlohmann::json::object();
        temp_data["type"] = symbol->get_type_name();
        temp_data["content"] = symbol->get_data();
        data_list.push_back(temp_data);
    }
    ret["data_list"] = data_list;
    return ret.dump();
}

cv::Mat imageDecodeBinary(const crow::request& req)
{
    std::string imgData = req.body;
    std::vector<char> buf(imgData.c_str(), imgData.c_str() + imgData.size());
    cv::Mat img = cv::imdecode(buf, cv::IMREAD_UNCHANGED);
    return img;
}

cv::Mat imageDecodeForm(const crow::request& req)
{
    crow::multipart::message msg(req);
    auto part = msg.get_part_by_name("file");
    std::string imgData = part.body;
    std::vector<char> buf(imgData.c_str(), imgData.c_str() + imgData.size());
    cv::Mat img = cv::imdecode(buf, cv::IMREAD_UNCHANGED);
    return img;
}

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/qrcode_recognize").methods("GET"_method, "POST"_method)([](const crow::request& req){
        std::string imgData = req.body;
        std::string type = req.get_header_value("Content-Type");
        // if (req.get_header_value("Content-Type"))
        if (imgData.compare("") == 0)
        {
            nlohmann::json empty = nlohmann::json::object();
            empty["message"] = "empty http body";
            return empty.dump();
        }
        cv::Mat img;
        // multipart/form-data
        // application/x-www-form-urlencoded
        if (std::regex_search(type, std::regex("form\\-urlencoded")))
        {
            img = imageDecodeBinary(req);
        }
        else if (std::regex_search(type, std::regex("form\\-data")))
        {
            img = imageDecodeForm(req);
        }
        else
        {
            nlohmann::json empty = nlohmann::json::object();
            empty["message"] = "upload method not support";
            return empty.dump();
        }
        // std::vector<char> buf(imgData.c_str(), imgData.c_str() + imgData.size());
        // cv::Mat img = cv::imdecode(buf, cv::IMREAD_UNCHANGED);
        std::string res = getBarCode(img);
        return res;
    });

    app.port(30006).run();
}