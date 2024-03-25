# crow_barcode
a cpp web application to recognize QRcode, using crowcpp as server and zbar as the recognizer of QRcode

推荐使用cmake编译

需要准备zbar和opencv库
``` bash
sudo apt install libzbar-dev
```

``` bash
sudo apt install libopencv-dev
```

编译过程
```bash
mkdir build
cd build
cmake ..
make -j4

./demo
```

默认端口30006，接口名称：/qrcode_recognize，可通过post/get请求传文件，请求体直接传二进制文件
示例
```bash
curl -X POST --data-binary @1.jpg 127.0.0.1:30006/qrcode_recognize
```
