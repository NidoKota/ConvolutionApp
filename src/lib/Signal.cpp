#include "Signal.hpp"

bool Signal::isInRange(int n) const
{
    return getStartN() <= n && n <= getLastN();
}

double Signal::getData(int n) const
{
    if(!isInRange(n)) return 0;

    //位置(n)に対する値を返す
    return dataArray[n - getStartN()];
}

void Signal::setData(int n, double value)
{
    if(!isInRange(n)) assert(!"OutOfRange");

    //位置(n)に値を格納する
    dataArray[n - getStartN()] = value;
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

int Signal::getStartN() const
{
    return startN;
}

void Signal::setStartN(int value)
{
    startN = value;
}

int Signal::getLastN() const
{
    return getStartN() + getDataArrayCount() - 1;
}

double Signal::getMinValue() const
{
    return *std::min_element(dataArray, dataArray + getDataArrayCount());
}

double Signal::getMaxValue() const
{
    return *std::max_element(dataArray, dataArray + getDataArrayCount());
}

void Signal::normalize()
{
    //信号中、初めて0以外の値を発見した場合、このフラグを立てる
    bool firstDataPassed = false;
    //最初の0以外の値の位置(n)
    int firstDataN = getStartN();
    //最後の0以外の値の位置(n)
    int lastDataN = getStartN();

    //上記3つの変数に格納する値を探す
    for(int n = getStartN(); n <= getLastN(); n++)
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
    setStartN(firstDataN);
    setDataArrayCount(lastDataN - firstDataN + 1);
    for(int n = getStartN(); n <= getLastN(); n++) setData(n, tmpDataArray[n - getStartN()]);

    delete[] tmpDataArray;
}

void Signal::draw(Renderer& renderer)
{
    renderer.draw(*this);
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
    int minN = small.getStartN() - (-large.getStartN());
    //largeの信号が、smallの信号と最後に重なる位置(n)
    int maxN = small.getLastN() - (-large.getLastN() + minN);

    //結果の信号を入れるSignalを用意
    Signal result = Signal();
    result.setStartN(minN);
    result.setDataArrayCount(maxN - minN + 1);

    for (int n = minN; n <= maxN; n++)
    {
        double value = 0;

        std::cout << "n(" << n << ") = ";

        //smallの信号にlargeをかけて、ループ回数を減らす
        for (int m = small.getStartN(); m <= small.getLastN(); m++)
        {
            if(m != small.getStartN()) std::cout << " + ";
            std::cout << small.getData(m) << "*" << large.getData(n - m);

            value += small.getData(m) * large.getData(n - m);
        }

        std::cout << " = " << value << std::endl;

        result.setData(n, value);
    }
    
    return result;
}