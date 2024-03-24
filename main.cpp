#include <iostream>
#include "include/crow_all.h"
#include <opencv2/opencv.hpp>
#include <zbar.h>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/qrcode_recognize").methods("GET"_method, "POST"_method)([](const crow::request& req){
        return req.body;
    });

    app.port(30006).run();
}