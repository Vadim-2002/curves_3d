#include <iostream>
#include <tuple>
#include <cmath>
#include <vector>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <omp.h>

#include "Curves.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Helix.h"


double sum_of_radii(std::vector<Curves*> curv_2)
{
    double sum_r = 0;
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        double local_sum = 0;
        #pragma omp for
        for (int i = 0; i < curv_2.size(); i++)
        {
            local_sum += ((Circle*)curv_2[i])->get_R();
        }
        #pragma omp atomic
        sum_r += local_sum;
    }

    return sum_r;
}


void output_of_points(std::vector<Curves*> curv, double t)
{
    for (int i = 0; i < curv.size(); i++)
    {
        std::cout << std::get<0> (curv[i]->get_point(t)) << "  ";
        std::cout << std::get<1> (curv[i]->get_point(t)) << "  ";
        std::cout << std::get<2> (curv[i]->get_point(t)) << "\n";
    }
}


void output_of_first_derivatives(std::vector<Curves*> curv, double t)
{
    for (int i = 0; i < curv.size(); i++)
    {
        std::cout << std::get<0> (curv[i]->get_first_derivative(t)) << "  ";
        std::cout << std::get<1> (curv[i]->get_first_derivative(t)) << "  ";
        std::cout << std::get<2> (curv[i]->get_first_derivative(t)) << "\n";
    }
}


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
            curv.push_back(new Circle(rand() % 25));
        else
           if (rand() % 3 == 0)
               curv.push_back(new Ellipse(rand() % 20, i % 15));
           else
               curv.push_back(new Helix(i + rand() % 15));
    }

    /*output of coordinates of points and first derivatives of all curves in the container*/
    output_of_points(curv, t);
    std::cout << "\n\n";
    output_of_first_derivatives(curv, t);

    /*filling the second container with okrazhnosty*/
    std::vector<Curves*> curv_2;
    
    for (int i = 0; i < curv.size(); i++)
        if (curv[i]->isA("Circle"))
            curv_2.push_back(curv[i]);
    
    /*sorting circles by increasing radius*/
    std::sort(curv_2.begin(), curv_2.end(), 
        [] (Curves const *obj_1, Curves const *obj_2) {return ((Circle*)obj_1)->get_R() < ((Circle*)obj_2)->get_R();}
    );
    
    /*the sum of the radii of all circles from the second container*/
    std::cout << sum_of_radii(curv_2) << "\n";
    
    /*freeing up memory*/
    for (int i = 0; i < curv.size(); i++)
        delete curv[i];

    for (int i = 0; i < curv_2.size(); i++)
        delete curv_2[i];

    return 0;
}
