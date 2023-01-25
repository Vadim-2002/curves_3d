#pragma once

#include "Curves.h"


class Ellipse : public Curves
{
    protected:
        double x_0, y_0;
        double a;
        double b;
        double t;

    public:
        Ellipse(double a, double b)
        {
            x_0 = 0; y_0 = 0;
            this->a = a;
            this->b = b;
        }

        Ellipse(double x_0, double y_0, double a, double b)
        {
            this->x_0 = x_0;
            this->y_0 = y_0;
            this->a = a;
            this->b = b;
        }

        Ellipse(const Ellipse &object)
        {
            x_0 = object.x_0;
            y_0 = object.y_0;
            a = object.a;
            b = object.b;
        }

        ~Ellipse() {}

        std::tuple<double, double, double> get_point(double t) override
        {
            double x = x_0 + a*cos(t);
            double y = y_0 + b*sin(t);
            double z = 0.0;

            return std::make_tuple(x, y, z);
        }

        std::tuple<double, double, double> get_first_derivative(double t) override
        {
            double x = x_0 + a*cos(t);
            double y = -b*x / (a*a*sqrt(1 - (x*x / (a*a))));

            return std::make_tuple(x, y, 0);
        }

        bool isA(std::string name) override
        {
            if ("Ellipse" == name)
                return true;
            else
                return false;
        }
};
