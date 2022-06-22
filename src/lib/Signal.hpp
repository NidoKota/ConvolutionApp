#pragma once

#include <ios>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>


//離散信号を表す構造体
class Signal
{

public:
    //class Sample;

private:
    //信号を格納する配列
    double* dataArray;
    //信号に含まれる値の数
    int dataArrayCount;
    //最初の値の位置(n)
    int startN;

    bool isInRange(int n) const;

public:
    /*class Sample
    {
        int n;
        double data;
    };*/

    class Renderer
    {
        public:
            virtual void draw(const Signal target) = 0;
    };

    //nの位置にある値を取得
    double getData(int n) const;
    //位置(n)に値を格納
    void setData(int n, double value);
    //信号に含まれる値の数を取得
    int getDataArrayCount() const;
    //信号に含まれる値の数を変更
    void setDataArrayCount(int value);
    //最初の値の位置(n)を取得
    int getStartN() const;
    //最初の値の位置(n)を変更
    void setStartN(int value);
    //最後の値の位置(n)を取得
    int getLastN() const;
    //最小の値を取得
    double getMinValue() const;
    //最大の値を取得
    double getMaxValue() const;
    //配列の外側で値が0になっている部分を消す
    void normalize();

    //文字列で表現されたグラフを取得
    std::string getStrGrouph() const;

    void draw(Renderer& renderer);
};

//畳み込みの計算
Signal operator* (const Signal l, const Signal r);