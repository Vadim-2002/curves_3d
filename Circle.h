#pragma once

#include "Curves.h"
#include "Ellipse.h"


class Circle : public Ellipse
{
    protected:
        double r;

    public:
        Circle(double r) : Ellipse(r, r) 
        {
            this->r = r;
        }

        Circle(double x_0, double y_0, double r) : Ellipse(x_0, y_0, r, r) 
        {
            this->r = r;
        }

        Circle(const Circle &object) : Ellipse(object)
        {
            x_0 = object.x_0;
            y_0 = object.y_0;
            r = object.r;
        }

        ~Circle() {}

        bool isA(std::string name) override
        {
            if ("Circle" == name)
                return true;
            else
                return false;
        }

        double get_R()
        {
            return r;
        }
};
