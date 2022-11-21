#ifndef ESFERAEMMOV_HPP
#define ESFERAEMMOV_HPP

#include "rayTracing.hpp"
#include "atingivel.hpp"

class esferaEmMov : public atingivel{
    public:
        ponto3D centro0, centro1;
        double t0, t1, raio;
        std::shared_ptr<material> matPtr;

        esferaEmMov(){}
        esferaEmMov(
            ponto3D c0, ponto3D c1, double _t0, double _t1, double r, std::shared_ptr<material> mat)
            : centro0(c0), centro1(c1), t0(_t0), t1(_t1), raio(r), matPtr(mat) {};

        virtual bool atingiu(
            const raioDeLuz& r, double tMin, double tMax, registroImpacto& reg
        ) const override;

        ponto3D centro(double time) const;
};

ponto3D esferaEmMov::centro(double tempo) const {
    return centro0 + (((tempo - t0) / (t1 - t0)) * (centro1 - centro0));
}

bool esferaEmMov::atingiu(const raioDeLuz& r, double tMin, double tMax, registroImpacto& reg) const{
    vec3 oc = r.origem() - centro(r.tempo);
    auto a = r.direcao().comprimentoAoQuadrado();
    auto bSObre2 = prodEscalar(oc, r.direcao());
    auto c = oc.comprimentoAoQuadrado() - raio * raio;

    auto discriminante = bSObre2 * bSObre2 - a*c;
    if(discriminante < 0) { return false; }
    auto raizQuadDiscr = std::sqrt(discriminante);

    //Achar a raiz mais proxima que esteja em uma distancia aceitavel
    auto raiz = (-bSObre2 - raizQuadDiscr) / a;
    if(raiz < tMin || tMax < raiz){
        raiz = (-bSObre2 + raizQuadDiscr) / a;
        if(raiz < tMin || tMax < raiz){
            return false;
        }
    }

    reg.t = raiz;
    reg.p = r.em(reg.t);
    auto normalParaFora = (reg.p - centro(r.tempo)) / raio;
    reg.setFaceNormal(r, normalParaFora);
    reg.matPtr = matPtr;

    return true;
}

#endif