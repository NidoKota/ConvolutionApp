#pragma once

#include <ios>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "../src/lib/Signal.hpp"

class SignalConsoleRenderer : public Signal::Renderer
{
public:
    virtual void draw(const Signal target) override;
};