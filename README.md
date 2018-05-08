# OpenCV_source
OpenCVに関するプログラムをまとめたもの。
なお、各サンプルコードの実行手順を以下に示す。

```
rm -rf ~/(path to source directory)/build
mkdir build
cd build
cmake ../
make
./main
```


## aruco
ARマーカー認識のためのOpenCVの拡張モジュール。
C言語のライブラリのように、includeすることで使えるようになる。

## camera calibration
aruco/pose_estimationを実行する前にカメラキャリブレーションを行う必要があり、
本プログラムを用いてカメラ外縁部の歪みを補正する。
補正後のカメラデータはcalibration.ymlに保存されるので、これをaruco/pose_estimation/buildの中に入れてプログラムを実行する。

## sample
OpenCVのサンプルプログラム。
もっといろいろ知りたい方は以下のURLを参照。
http://nn-hokuson.hatenablog.com/entry/2017/05/31/210808