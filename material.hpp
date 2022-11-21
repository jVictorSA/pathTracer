#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "rayTracing.hpp"
#include "atingivel.hpp"
#include "esferaEmMov.hpp"

class material{
    public:
        virtual bool dispersar(
            const raioDeLuz& rEntrada, const registroImpacto& reg, cor& atenuacao, raioDeLuz& dispersado
        ) const = 0;
        
};

class lambertian : public material{
    public:
        cor albedo;

    lambertian(const cor& a) : albedo(a) {}

    virtual bool dispersar(
        const raioDeLuz& rEntrada, const registroImpacto& reg, cor& atenuacao, raioDeLuz& dispersado
    ) const override{
        auto direcaoDispersao = reg.normal + vetorUnitarioAleat();

        if(direcaoDispersao.proximoDeZero()){
            direcaoDispersao = reg.normal;
        }

        dispersado = raioDeLuz(reg.p, direcaoDispersao, rEntrada.tempo);
        atenuacao = albedo;
        return true;
    }
};

class metal : public material{
    public:
        cor albedo;
        double reflexDifusa;

        metal(const cor& a, double rD) : albedo(a), reflexDifusa(rD < 1 ? rD : 1) {}

        virtual bool dispersar(
            const raioDeLuz& rEntrada, const registroImpacto& reg, cor& atenuacao, raioDeLuz& dispersado
        ) const override{
            vec3 refletido = refletir(vetorUnitario(rEntrada.direcao()), reg.normal);
            dispersado = raioDeLuz(reg.p, refletido + reflexDifusa * aleatorioNaEsfUnit(), rEntrada.tempo);
            atenuacao = albedo;
            return (prodEscalar(dispersado.direcao(), reg.normal) > 0);
        }
};

class dieletrico : public material{
    public:
        double iR; //Indice de Refação

        dieletrico(double indexRefra) : iR(indexRefra) {}

        virtual bool dispersar(
            const raioDeLuz& rEntrada, const registroImpacto& reg, cor& atenuacao, raioDeLuz& dispersado
        ) const override{
            atenuacao = cor(1.0, 1.0, 1.0);
            double razaoRefracao = reg.faceFrontal ? (1.0/iR) : iR;

            vec3 direcaoUnit = vetorUnitario(rEntrada.direcao());

            double cosTheta = fmin(prodEscalar(-direcaoUnit, reg.normal), 1.0);
            double senTheta = sqrt(1.0 - cosTheta * cosTheta);

            bool naoPodeRefratar = razaoRefracao * senTheta > 1.0;

            vec3 direcao;

            if(naoPodeRefratar || reflectancia(cosTheta, razaoRefracao) > doubleAleatorio()){
                direcao = refletir(direcaoUnit, reg.normal);
            }else{
                direcao = refratar(direcaoUnit, reg.normal, razaoRefracao);
            }

            dispersado = raioDeLuz(reg.p, direcao, rEntrada.tempo);
            return true;
        }

    private:
        static double reflectancia(double cosseno, double indexRefra){
            auto r0 = (1 - indexRefra) / (1 + indexRefra);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cosseno), 5);
        }
};

#endif