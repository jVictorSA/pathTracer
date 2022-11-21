#ifndef VEC3_HPP
#define VEC3_HPP

#include<cmath>
#include <iostream>
#include "rayTracing.hpp"

class vec3{
    public:
        /*  Atributo da classe. 
            Pode representar as coordenadas geométricas ou 
            representar os valores RGB de uma cor
        */
        double e[3];

        //Construtores
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        //Getters
        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}
        double comprimento() const{
            return std::sqrt(comprimentoAoQuadrado());
        }
        double comprimentoAoQuadrado() const{
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        vec3 operator-() const {return vec3(-e[0],-e[1], -e[2]);}
        double operator[](int i) const { return e[i];}
        double& operator[](int i) {return e[i];}

        vec3& operator+= (const vec3 &v){
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this; 
        }

        vec3& operator*= (const double t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this; 
        }

        vec3& operator/= (const double t) {return *this *= 1/t;}

        inline static vec3 aleatorio(){
            return vec3(doubleAleatorio(), doubleAleatorio(), doubleAleatorio());
        }

        inline static vec3 aleatorio(double min, double max){
            return vec3(doubleAleatorio(min, max), doubleAleatorio(min, max), doubleAleatorio(min, max));
        }


        bool proximoDeZero() const{
            const auto s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }
};

//Aliases de tipo

//Coordenada tridimensional
using ponto3D = vec3;   
//Valores RGB de uma cor
using cor = vec3;       

//Funções utilitárias da classe vec3

inline std::ostream& operator<<(std::ostream &out, const vec3 &v){
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v){
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v){
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v){
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &u){
    return vec3(t *u.e[0], t * u.e[1], t * u.e[2]);
}

inline vec3 operator*(const vec3 &u, double t){
    return t * u;
}

inline vec3 operator/(vec3 v, double t){
    return (1/t) * v;
}

//produto escalar - dot product
inline double prodEscalar(const vec3 &u, const vec3 &v){
    return u.e[0] * v.e[0] +
           u.e[1] * v.e[1] +
           u.e[2] * v.e[2];
}

//produto vetorial - cross product
inline vec3 prodVetorial(const vec3 &u, const vec3 &v){
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 vetorUnitario(vec3 v){
    return v / v.comprimento();
}

//Ponto aleatorio dentro de uma esfera unitarop
vec3 aleatorioNaEsfUnit(){
    while(true){
        auto p = vec3::aleatorio(-1,1);
        if(p.comprimentoAoQuadrado() >= 1) continue;
        return p;
    }
}

vec3 vetorUnitarioAleat(){
    return vetorUnitario(aleatorioNaEsfUnit());
}

vec3 aleatorioNoHemisferio(const vec3& normal){
    vec3 pontoNaEsferaUnitaria = aleatorioNaEsfUnit();

    if(prodEscalar(pontoNaEsferaUnitaria, normal) > 0.0){
        return pontoNaEsferaUnitaria;
    }else{
        return -pontoNaEsferaUnitaria;
    }
}

vec3 aleatorioNoDiscoUnit(){
    while(true){
        auto p = vec3(doubleAleatorio(-1,1), doubleAleatorio(-1,1), 0);
        if(p.comprimentoAoQuadrado() >= 1) continue;
        return p;
    }
}

vec3 refletir(const vec3& v, const vec3& n){
    return v - 2 * prodEscalar(v,n) * n;
}

vec3 refratar(const vec3& uv, const vec3& n, double etaSobreEtaLinha){
    auto cosTheta = fmin(prodEscalar(-uv, n), 1.0);
    vec3 raioPerp = etaSobreEtaLinha * (uv + cosTheta * n);
    vec3 raioPara = -sqrt(fabs(1.0 - raioPerp.comprimentoAoQuadrado())) * n;
    return raioPerp + raioPara;
}

#endif