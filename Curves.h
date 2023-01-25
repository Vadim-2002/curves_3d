#pragma once

class Curves
{
    public:
        virtual std::tuple<double, double, double> get_point(double t) = 0;
        virtual std::tuple<double, double, double> get_first_derivative(double t) = 0;

        virtual bool isA(std::string name)
        {
            if ("Curves" == name)
                return true;
            else
                return false;
        }
};
