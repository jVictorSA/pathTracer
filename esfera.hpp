#ifndef ESFERA_HPP
#define ESFERA_HPP

#include "vec3.hpp"
#include "atingivel.hpp"

class esfera : public atingivel{
    ponto3D centro;
    double raio;
    std::shared_ptr<material> matPtr;
    public:
        esfera() {}
        esfera(ponto3D cen, double r, std::shared_ptr<material> m) : centro(cen), raio(r), matPtr(m) {}

        virtual bool atingiu(
            const raioDeLuz& r, double tMin, double tMax, registroImpacto& reg) const override;
};

bool esfera::atingiu(const raioDeLuz& r, double tMin, double tMax, registroImpacto& reg) const{
    vec3 oc = r.origem() - centro;
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
    vec3 normalParaFora = (reg.p - centro) / raio;
    reg.setFaceNormal(r, normalParaFora);
    reg.matPtr = matPtr;

    return true;
}

#endif
