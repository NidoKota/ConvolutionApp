#include "SignalConsoleRenderer.hpp"

void SignalConsoleRenderer::draw(const Signal target)
{
    using namespace std;

    //値同士の間にある幅
    const int hSpace = 5;

    cout << right << fixed << setprecision(1);

    //横線を出力
    for (int x = target.getStartN(); x <= target.getLastN(); x++) cout << "-----";
    cout << "-----" << endl;

    int upY = target.getMaxValue() < 0 ? 1 : target.getMaxValue() + 1;
    int downY = target.getMinValue() > 0 ? -1 : target.getMinValue() - 1;

    //マイナスの値も考慮しつつ、縦線と値の大きさを出力
    for (int y = upY; y >= downY; y--)
    {
        for (int x = target.getStartN(); x <= target.getLastN(); x++)
        {
            if(y == 0) continue;
            
            int intData = target.getData(x);
            if(intData >= 0)
            {
                if(0 < y && y <= intData) cout << setw(hSpace) << "|";
                else
                {
                    if (y == intData + 1) cout << setw(hSpace) << target.getData(x);
                    else cout << setw(hSpace) << "";
                }
            }
            else
            {
                if(0 > y && y >= intData) cout << setw(hSpace) << "|";
                else
                {
                    if (y == intData - 1) cout << setw(hSpace) << target.getData(x);
                    else cout << setw(hSpace) << "";
                }
            }
        }
        if(y != 0) cout << endl;
    }

    //横線を出力
    for (int x = target.getStartN(); x <= target.getLastN(); x++) cout << "-----";
    cout << "-----" << endl;

    //位置(n)を出力
    for (int x = target.getStartN(); x <= target.getLastN(); x++) cout << setw(hSpace) << x;
    cout << endl;
    
    //横線を出力
    for (int x = target.getStartN(); x <= target.getLastN(); x++) cout << "-----";
    cout << "-----";
}
