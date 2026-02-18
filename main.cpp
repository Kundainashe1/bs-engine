#include <iostream>
#include <iomanip>
#include "black_scholes.h"

int main() {
    double S = 7500.0;
    double K = 7600.0;
    double T = 0.25;
    double r = 0.0525;
    double sigma = 0.18;

   std::cout << std::fixed << std::setprecision(4);
   std::cout << "Call price: " << bsCall(S, K, T, r,sigma) << "\n";
   std::cout << "Put Price: " << bsPut(S, K, T, r, sigma) << "\n";

   return 0;



   
}


