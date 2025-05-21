#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <algorithm>
#include <planoFinanceiro.hpp>

PlanoFinanceiroDAO::PlanoFinanceiroDAO(std::vector<PlanoFinanceiroBean> &planos) {
    for(auto &it: planos) {
        this->planos.push_back(std::make_unique<PlanoFinanceiroBean>(std::move(it)));
    }
}

void PlanoFinanceiroDAO::create(PlanoFinanceiroBean &plano) {
    planos.push_back(std::make_unique<PlanoFinanceiroBean>(std::move(plano)));
}

void PlanoFinanceiroDAO::update(PlanoFinanceiroBean &plano) {
    for(auto &&it: planos) {
        if(it->getNomePlano() == plano.getNomePlano()) {
            it->setTipoPlano(plano.getTipoPlano());
        }
    }
}

void PlanoFinanceiroDAO::remover(PlanoFinanceiroBean &plano) {
    planos.erase(std::remove_if(planos.begin(), planos.end(),
    [&plano](const std::unique_ptr<PlanoFinanceiroBean>& it) { return it->getNomePlano() == plano.getNomePlano(); }), planos.end());
}

PlanoFinanceiroBean PlanoFinanceiroDAO::getPlanoFinanceiroBean(const std::string &nome) {
    for(auto &it: planos) {
        if(it->getNomePlano() == nome) {
            return *it;
        }
    }
    return PlanoFinanceiroBean();
}

void PlanoFinanceiroManager::adicionarPlano(PlanoFinanceiroBean &plano) {
    if(!plano.getNomePlano().empty()) {
        planoFinanceiroDAO->create(plano);
    }
}

void PlanoFinanceiroManager::atualizarPlano(PlanoFinanceiroBean &plano) {
    if(!plano.getNomePlano().empty()) {
        planoFinanceiroDAO->update(plano);
    }
}

void PlanoFinanceiroManager::removerPlano(PlanoFinanceiroBean &plano) {
    if(!plano.getNomePlano().empty()) {
        planoFinanceiroDAO->remover(plano);
    }
}
