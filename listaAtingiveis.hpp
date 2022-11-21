#ifndef LISTAATINGIVEIS_HPP
#define LISTAATINGIVEIS_HPP

#include "atingivel.hpp"

#include <memory>
#include <vector>

class listaAtingiveis : public atingivel{
    public:
        std::vector<std::shared_ptr<atingivel>> objetos;

        listaAtingiveis() {}
        listaAtingiveis(std::shared_ptr<atingivel> objeto) { add(objeto); }
        
        void limpar() { objetos.clear(); }
        void add(std::shared_ptr<atingivel> objeto) { objetos.push_back(objeto); }

        virtual bool atingiu(
            const raioDeLuz& r, double tMin, double tMax, registroImpacto& reg) const override;
};

bool listaAtingiveis::atingiu(const raioDeLuz& r, double tMin, double tMax, registroImpacto& reg) const{
    registroImpacto regTemp;
    bool atingiuAlgo = false;
    auto maisProximoAteAgora = tMax;

    for(const auto& objeto : objetos){
        if(objeto->atingiu(r, tMin, maisProximoAteAgora, regTemp)){
            atingiuAlgo = true;
            maisProximoAteAgora = regTemp.t;
            reg = regTemp;
        }
    }

    return atingiuAlgo;
}

#endif