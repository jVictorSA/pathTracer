#ifndef ATINGIVEL_HPP
#define ATINGIVEL_HPP

#include "raioDeLuz.hpp"
#include "rayTracing.hpp"

class material;

struct registroImpacto{
    ponto3D p;
    vec3 normal;
    std::shared_ptr<material> matPtr;
    double t;
    bool faceFrontal;

    inline void setFaceNormal(const raioDeLuz& r, const vec3& normalParaFora){
        faceFrontal = prodEscalar(r.direcao(), normalParaFora) < 0;
        normal = faceFrontal ? normalParaFora : -normalParaFora;
    }
};

class atingivel{
    public:
        virtual bool atingiu(const raioDeLuz& r, double tMin, double tMax, registroImpacto& reg) const = 0;
};

#endif