#pragma once

#include <ios>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "../src/lib/Signal.hpp"
#include "../src/lib/SignalConsoleRenderer.hpp"

//コマンドライン入力から信号を取得する
void inputSignal(Signal* signalP);