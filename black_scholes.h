#pragma once
#include <cmath>    // std::exp, std::sqrt, std::log
#include <stdexcept>
 
// Cumulative standard normal distribution using the Horner method approximation.
// In production you would use std::erfc from <cmath> — shown here for clarity.
inline double normalCDF(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}
 
// d1 and d2 are the core BSM intermediate values.
// Think of d1 as a standardised measure of how far in-the-money the option is.
inline double bsD1(double S, double K, double T, double r, double sigma) {
    if (T <= 0.0 || sigma <= 0.0) throw std::invalid_argument("T and sigma must be > 0");
    return (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
}
 
inline double bsD2(double d1, double sigma, double T) {
    return d1 - sigma * std::sqrt(T);
}
 
// European Call price: C = S*N(d1) - K*e^(-rT)*N(d2)
inline double bsCall(double S, double K, double T, double r, double sigma) {
    double d1 = bsD1(S, K, T, r, sigma);
    double d2 = bsD2(d1, sigma, T);
    return S * normalCDF(d1) - K * std::exp(-r * T) * normalCDF(d2);
}
 
// European Put price via put-call parity: P = C - S + K*e^(-rT)
// This is how production code does it — avoids duplicating the formula.
inline double bsPut(double S, double K, double T, double r, double sigma) {
    return bsCall(S, K, T, r, sigma) - S + K * std::exp(-r * T);
}
