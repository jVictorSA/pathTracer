#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "rayTracing.hpp"

class camera{
    private:
        ponto3D origem;
        ponto3D cantoInfEsq;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double raioLente;
        double t0, t1;

    public:
        camera(double fovVert, double aspecto, ponto3D orig, ponto3D olharPara,
               vec3 vup, double abertura, double distFoco,
               double tempo0 = 0, double tempo1 = 0){
            auto theta = degrees_to_radians(fovVert);
            auto h = tan(theta/2);
            auto alturaViewport = 2.0 * h;
            auto larguraViewport = aspecto * alturaViewport;

            w = vetorUnitario(orig - olharPara);
            u = vetorUnitario(prodVetorial(vup, w));
            v = prodVetorial(w, u);

            auto distanciaFocal = 1.0;

            origem = orig;
            horizontal = distFoco * larguraViewport * u;
            vertical = distFoco * alturaViewport * v;
            cantoInfEsq = origem - horizontal/2 - vertical/2 - distFoco * w;
            raioLente = abertura / 2;
            t0 = tempo0;
            t0 = tempo0;
        }

        raioDeLuz raio(double s, double t) const{
            vec3 rd = raioLente * aleatorioNoDiscoUnit();
            vec3 offset = u * rd.x() + v * rd.y();
            return raioDeLuz(origem + offset, cantoInfEsq + s*horizontal + t*vertical
                             - origem - offset, doubleAleatorio(t0, t1));
        }        
};

#endif