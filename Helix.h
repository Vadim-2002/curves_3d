#pragma once

#include "Curves.h"
#include "Ellipse.h"
#include "Circle.h"


class Helix : public Circle
{
    public:
        Helix(double r) : Circle(r) {}

        Helix(double x_0, double y_0, double r) : Circle(x_0, y_0, r) {}

        ~Helix() {}

        std::tuple<double, double, double> get_point(double t) override
        {
            double x = x_0 + r*cos(t);
            double y = y_0 + r*sin(t);
            double z = t;

            return std::make_tuple(x, y, z);
        }

        std::tuple<double, double, double> get_first_derivative(double t) override
        {
            double x = x_0 + r*cos(t);
            double y = -x / sqrt(1 - (r*r - x*x));

            return std::make_tuple(x, y, t);
        }

        bool isA(std::string name) override
        {
            if ("Helix" == name)
                return true;
            else
                return false;
        }
};
