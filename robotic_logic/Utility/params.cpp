#include "../Include/params.h"

using namespace params ;

string params::getColorName(Color color){
    switch (color) {
        case red:
            return "red";
            break;
        case blue:
            return "blue";
            break;
        case green:
            return "green";
            break;
        case yellow:
            return "yellow";
            break;
        case violet:
            return "violet";
            break;
        case black:
            return "black";
            break;
        default:
            break;
    }
}

Scalar params::getColorRGB(Color color)
{
    switch (color) {
        case red:
            return Scalar(0,0,255);
            break;
        case blue:
            return Scalar(255,0,0);
            break;
        case green:
            return Scalar(0,255,0);
            break;
        case yellow:
            return Scalar(0,255,255);
            break;
        case violet:
            return Scalar(205,0,205);
            break;
        case black:
            return Scalar(0,0,255);
            break;
        default:
            break;
    }

    return Scalar(0,0,0);
}