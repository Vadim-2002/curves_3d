#include <iostream>
#include <tuple>
#include <cmath>
#include <vector>
#include <cstring>
#include <ctime>
#include <algorithm>


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


int main()
{
    std::vector<Curves*> curv;

    int count_curves = 50;
    double t = 3.141592653 / 4;

    srand(time(NULL));
    
    /*filling the container with random curve objects*/
    for (int i = 0; i < count_curves; i++)
    {
        if (rand() % 2 == 0)
            curv.push_back(new Circle(i % 10));
        else
           if (rand() % 3 == 0)
               curv.push_back(new Ellipse(rand() % 10, i % 10));
           else
               curv.push_back(new Helix(i + rand() % 10));
    }

    /*output of coordinates of points and first derivatives of all curves in the container*/
    for (int i = 0; i < count_curves; i++)
    {
        std::cout << std::get<0> (curv[i]->get_point(t)) << ", " << std::get<1> (curv[i]->get_point(t)) << ", " << std::get<2> (curv[i]->get_point(t)) << "\n";
        std::cout << std::get<0> (curv[i]->get_first_derivative(t)) << ", " << std::get<1> (curv[i]->get_first_derivative(t)) << ", " << std::get<2> (curv[i]->get_first_derivative(t)) << "\n";
        std::cout << "\n";
    }

    /*filling the second container with okrazhnosty*/
    std::vector<Curves*> curv_2;
    int count_curves_2 = 0;
    
    for (int i = 0; i < count_curves; i++)
    {
        if (curv[i]->isA("Circle"))
        {
            curv_2.push_back(curv[i]);
            count_curves_2++;
        }
    }
    
    /*sorting circles by increasing radius*/
    std::sort(curv_2.begin(), curv_2.end(), 
        [] (Curves const *obj_1, Curves const *obj_2) {return ((Circle*)obj_1)->get_R() < ((Circle*)obj_2)->get_R();}
    );
    
    /*the sum of the radii of all circles from the second container*/
    double sum_r = 0;
    for (int i = 0; i < count_curves_2; i++)
        sum_r += ((Circle*)curv_2[i])->get_R();

    std::cout << sum_r << "\n";
    
    /*freeing up memory*/
    for (int i = 0; i < count_curves; i++)
        delete curv[i];

    for (int i = 0; i < count_curves_2; i++)
        delete curv_2[i];

    return 0;
}
