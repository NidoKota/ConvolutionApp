#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "Signal.hpp"

class SignalConsoleRenderer : public Signal::Renderer
{
public:
    virtual void draw(Sample* sampleArray, int sampleArrayCount) override;
};