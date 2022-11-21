#ifndef RAIODELUZ_HPP
#define RAIODELUZ_HPP

#include "vec3.hpp"

class raioDeLuz{
    public:
        ponto3D orig;
        vec3 dir;
        double tempo;

        //Construtores
        raioDeLuz() {}
        raioDeLuz(const ponto3D& origem, const vec3& direcao, double t = 0)
            : orig(origem), dir(direcao), tempo(t) {}
        
        //Getters
        ponto3D origem() const { return orig; }
        vec3 direcao() const { return dir; }
        double getTempo() const { return tempo; }

        ponto3D em(double t) const{
            return orig + t*dir;
        }

};

#endif