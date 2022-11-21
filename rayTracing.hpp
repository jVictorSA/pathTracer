#ifndef RAYTRACING_HPP
#define RAYTRACING_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <cstdlib>

// Usings
// using std::shared_ptr;
// using std::make_shared;
// using std::sqrt;

//Constantes
const double infinito = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Funções utilitárias
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double doubleAleatorio() {
    return rand() / (RAND_MAX + 1.0);
    // static std::uniform_real_distribution<double> distribuicao(0.0, 1.0);
    // static std::mt19937 gerador;
    // return distribuicao(gerador);
}

// Returna um numero real aleatorio entre [min,max).
inline double doubleAleatorio(double min, double max) {
    return min + (max-min)*doubleAleatorio();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

//Includes comuns
#include "raioDeLuz.hpp"
#include "vec3.hpp"

#endif