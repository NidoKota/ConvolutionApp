#include "Signal.hpp"

double Signal::getData(int n) const
{
    //登録された信号の範囲なら、位置(n)に対する値を返す
    if (startN <= n && n <= getLastN()) return dataArray[n - startN];
    return 0;
}

void Signal::setData(int n, double value)
{
    //登録された信号の範囲なら、位置(n)に値を格納する
    int index = n - startN;
    if (startN <= n && n <= getLastN()) dataArray[index] = value;
    else throw;
}

int Signal::getDataArrayCount() const
{
    return dataArrayCount;
}

void Signal::setDataArrayCount(int value)
{
    //信号に含まれる値の数を変更し、新しい配列を作る
    dataArrayCount = value;
    if(dataArray != nullptr) delete[] dataArray;
    dataArray = new double[getDataArrayCount()];
}

int Signal::getLastN() const
{
    return startN + getDataArrayCount() - 1;
}

double Signal::getMinValue() const
{
    //resultは信号の最初の値とし、それより小さな値を発見したら、resultを更新する
    double result = getData(startN);
    for (int n = startN; n <= getLastN(); n++) result = result < getData(n) ? result : getData(n);
    return result;
}

double Signal::getMaxValue() const
{
    //resultは信号の最初の値とし、それより大きな値を発見したら、resultを更新する
    double result = getData(startN);
    for (int n = startN; n <= getLastN(); n++) result = result < getData(n) ? getData(n) : result;
    return result;
}

void Signal::normalize()
{
    //信号中、初めて0以外の値を発見した場合、このフラグを立てる
    bool firstDataPassed = false;
    //最初の0以外の値の位置(n)
    int firstDataN = startN;
    //最後の0以外の値の位置(n)
    int lastDataN = startN;

    //上記3つの変数に格納する値を探す
    for(int n = startN; n <= getLastN(); n++)
    {
        if(getData(n) != 0) 
        {
            if(!firstDataPassed)
            {
                firstDataN = n;
                firstDataPassed = true;
            }
            lastDataN = n;
        }
    }

    //一時的な配列を作成し、信号から無駄な値を除いて、値を格納する
    int* tmpDataArray = new int[getDataArrayCount()];
    for(int n = firstDataN; n <= lastDataN; n++) tmpDataArray[n - firstDataN] = getData(n);

    //一時的な配列から値を戻す
    startN = firstDataN;
    setDataArrayCount(lastDataN - firstDataN + 1);
    for(int n = startN; n <= getLastN(); n++) setData(n, tmpDataArray[n - startN]);

    delete[] tmpDataArray;
}

std::string Signal::getStrGrouph() const
{
    using namespace std;

    //値同士の間にある幅
    const int hSpace = 5;

    ostringstream oss;
    oss << right << fixed << setprecision(1);

    //横線を出力
    for (int x = startN; x <= getLastN(); x++) oss << "-----";
    oss << "-----" << endl;

    int upY = getMaxValue() < 0 ? 1 : getMaxValue() + 1;
    int downY = getMinValue() > 0 ? -1 : getMinValue() - 1;

    //マイナスの値も考慮しつつ、縦線と値の大きさを出力
    for (int y = upY; y >= downY; y--)
    {
        for (int x = startN; x <= getLastN(); x++)
        {
            if(y == 0) continue;
            
            int intData = getData(x);
            if(intData >= 0)
            {
                if(0 < y && y <= intData) oss << setw(hSpace) << "|";
                else
                {
                    if (y == intData + 1) oss << setw(hSpace) << getData(x);
                    else oss << setw(hSpace) << "";
                }
            }
            else
            {
                if(0 > y && y >= intData) oss << setw(hSpace) << "|";
                else
                {
                    if (y == intData - 1) oss << setw(hSpace) << getData(x);
                    else oss << setw(hSpace) << "";
                }
            }
        }
        if(y != 0) oss << endl;
    }

    //横線を出力
    for (int x = startN; x <= getLastN(); x++) oss << "-----";
    oss << "-----" << endl;

    //位置(n)を出力
    for (int x = startN; x <= getLastN(); x++) oss << setw(hSpace) << x;
    oss << endl;
    
    //横線を出力
    for (int x = startN; x <= getLastN(); x++) oss << "-----";
    oss << "-----" << endl;
    
    return oss.str();
}

Signal operator*(const Signal l, const Signal r)
{
    Signal large;
    Signal small;

    //信号の値の数が多い方をlargeとし、少ない方をsmallとする
    //smallを固定して、largeを少しずつ動かしながら、畳み込みの計算を行う
    if(l.getDataArrayCount() > r.getDataArrayCount()) 
    {
        large = l;
        small = r;
    }
    else
    {
        large = r;
        small = l;
    }
    
    //largeの信号が、smallの信号と最初に重なる位置(n)
    int minN = small.startN - (-large.startN);
    //largeの信号が、smallの信号と最後に重なる位置(n)
    int maxN = small.getLastN() - (-large.getLastN() + minN);

    //結果の信号を入れるSignalを用意
    Signal result = Signal();
    result.startN = minN;
    result.setDataArrayCount(maxN - minN + 1);

    for (int n = minN; n <= maxN; n++)
    {
        double value = 0;
        
        //smallの信号にlargeをかけて、ループ回数を減らす
        for (int m = small.startN; m <= small.getLastN(); m++)
        {
            value += small.getData(m) * large.getData(n - m);
        }
        result.setData(n, value);
    }
    
    return result;
}