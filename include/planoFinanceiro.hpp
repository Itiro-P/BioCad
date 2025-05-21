#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <enums.hpp>

class PlanoFinanceiroBean {
    std::string nomePlano = "";
    TipoPlanoFinanceiro tipoPlano = TipoPlanoFinanceiro::MENSAL;
    public:
    PlanoFinanceiroBean() = default;
    PlanoFinanceiroBean(const std::string &nomePlano, const TipoPlanoFinanceiro &tipoPlano) : nomePlano(nomePlano), tipoPlano(tipoPlano) {};

    std::string getNomePlano() const& { return nomePlano; };
    TipoPlanoFinanceiro getTipoPlano() const& { return tipoPlano; };

    void setNomePlano(const std::string &novoNome) { nomePlano = novoNome; }
    void setTipoPlano(const TipoPlanoFinanceiro &novoTipoPlano) { tipoPlano = novoTipoPlano; }
};

class PlanoFinanceiroDAO {
    std::vector<std::unique_ptr<PlanoFinanceiroBean>> planos = {}; 
    public:
    PlanoFinanceiroDAO() = default;
    PlanoFinanceiroDAO(std::vector<PlanoFinanceiroBean> &planos);
    void create(PlanoFinanceiroBean &plano);
    void update(PlanoFinanceiroBean &plano);
    void remover(PlanoFinanceiroBean &plano);
    PlanoFinanceiroBean getPlanoFinanceiroBean(const std::string &nome);
};

class PlanoFinanceiroManager {
    std::unique_ptr<PlanoFinanceiroDAO> planoFinanceiroDAO = nullptr;
    public:
    PlanoFinanceiroManager() = default;
    PlanoFinanceiroManager(PlanoFinanceiroDAO &&planoFinanceiroDAO) : planoFinanceiroDAO(std::make_unique<PlanoFinanceiroDAO>(std::move(planoFinanceiroDAO))) {};
    void adicionarPlano(PlanoFinanceiroBean &plano);
    void atualizarPlano(PlanoFinanceiroBean &plano);
    void removerPlano(PlanoFinanceiroBean &plano);
    PlanoFinanceiroBean getPlanoFinanceiroBean(const std::string &nome) const& ;
};