#pragma once

#include <string>
#include <vector>
#include <memory>
#include <enums.hpp>


class PlanoDeTreinoBean {
    std::string cpfCliente = "";
    std::string nomeCliente = "";
    std::vector<std::string> objetivosCliente = {"Ganho de massa"};
    std::vector<std::string> condicaoMedicaCliente = { "Nenhuma" };
    std::string tipoTreino = "Flexao a rodo";
    public:
    PlanoDeTreinoBean() = default;
    PlanoDeTreinoBean(const std::string &cpfCliente, const std::string &nomeCliente, const std::vector<std::string> &objetivosCliente, const std::vector<std::string> &condicaoMedicacliente, const std::string &tipoTreino);
    std::string getCpfCliente() const& { return cpfCliente; };
    std::string getNomeCliente() const& { return nomeCliente; };
    std::vector<std::string> getObjetivosCliente() const& { return objetivosCliente; };
    std::vector<std::string> getCondicaoMedicaCliente() const& { return condicaoMedicaCliente; };
    std::string getTipoTreino() const& { return tipoTreino; };

    void setCpfCliente(const std::string &novoCpf) { if(novoCpf.size() == 14) cpfCliente = novoCpf; };
    void setNomeCliente(const std::string &novoNome) { if(novoNome.size() <= 150) nomeCliente = novoNome; };
    void setObjetivosCliente(const std::vector<std::string> &novosObjetivos) { objetivosCliente = novosObjetivos; };
    void setCondicaoMedicaCliente(const std::vector<std::string> &novasCondicoes) { condicaoMedicaCliente = novasCondicoes; };
    void setTipoTreino(const std::string &novoTipo) { tipoTreino = novoTipo; };
};

class PlanoDeTreinoDAO {
    std::vector<std::unique_ptr<PlanoDeTreinoBean>> planosDeTreino;
    public:
    PlanoDeTreinoDAO() = default;
    PlanoDeTreinoDAO(std::vector<PlanoDeTreinoBean> &planos);
    void create(PlanoDeTreinoBean &plano);
    void remover(PlanoDeTreinoBean &plano);
    void update(PlanoDeTreinoBean &plano);
    PlanoDeTreinoBean getPlanoDeTreinoBean(const std::string &cpfCliente) const&;
};

class PlanoDeTreinoManager {
    std::unique_ptr<PlanoDeTreinoDAO> planoDeTreinoDAO = nullptr;
    public:
    PlanoDeTreinoManager(PlanoDeTreinoDAO &&planoDeTreinoDAO) : planoDeTreinoDAO(std::make_unique<PlanoDeTreinoDAO>(std::move(planoDeTreinoDAO))) {};
    bool validarCpf(const std::string &cpf);
    void adicionarPlanoDeTreino(PlanoDeTreinoBean &plano);
    void removerPlanoDeTreino(PlanoDeTreinoBean &plano);
    void atualizarPlanoDeTreino(PlanoDeTreinoBean &plano);
    PlanoDeTreinoBean getPlanoDeTreinoBean(const std::string &cpf) const&;
};