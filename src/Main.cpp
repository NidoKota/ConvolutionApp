#include "Main.hpp"

//2つの信号
Signal x1 = Signal();
Signal x2 = Signal();
SignalConsoleRenderer renderer = SignalConsoleRenderer();
int tmpInput = 0;

int main()
{
    using namespace std;

    //x1の信号を入力した後、グラフを出力
    cout << "Input n where the X1 signal starts" << endl;
    cin >> tmpInput;
    x1.setStartN(tmpInput);
    cout << "Input the signals of X1 in order (Input \"end\" when finished inputting)" << endl;
    inputSignal(x1);

    cout << endl;
    cout << "X1" << endl;
    
    x1.draw(renderer);
    cout << endl;

    //x2の信号を入力した後、グラフを出力
    cout << "Input n where the X2 signal starts" << endl;
    cin >> tmpInput;
    x2.setStartN(tmpInput);
    cout << "Input the signals of X2 in order (Input \"end\" when finished inputting)" << endl;
    inputSignal(x2);
    
    cout << endl;
    cout << "X2" << endl;
    x2.draw(renderer);
    cout << endl;

    //x1 * x2の計算をした後、左右の余計な値を消し、グラフを出力
    Signal result = x1 * x2;
    result.normalize();

    cout << endl;
    cout << "x1 * x2" << endl;

    result.draw(renderer);
    cout << endl;
    
    return 0;
}

void inputSignal(Signal& signal)
{
    using namespace std;

    string tmpStr;
    ostringstream oss;
    int dataCount = 0;

    //endが入力されるまでossに値を格納し続ける
    while(true)
    {
        cin >> tmpStr;
        if(tmpStr == "end") break;

        oss << tmpStr << " ";
        dataCount += 1;
    }

    //何も入力されなかった場合、0の値だけ格納する
    if(dataCount == 0)
    {
        oss << 0 << " ";
        dataCount = 1;
    }

    signal.setDataArrayCount(dataCount);
    istringstream dataIss = istringstream(oss.str());

    //dataIssに格納された値をSignalに移す
    for (int n = signal.getStartN(); n <= signal.getLastN(); n++)
    {
        double tmpData = 0;
        dataIss >> tmpData;
        signal.setData(n, tmpData);
    }
}