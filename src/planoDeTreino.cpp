#include <planoDeTreino.hpp>

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <enums.hpp>

PlanoDeTreinoBean::PlanoDeTreinoBean(const std::string &cpfCliente, const std::string &nomeCliente, const std::vector<std::string> &objetivosCliente, const std::vector<std::string> &condicaoMedicacliente, const std::string &tipoTreino)
 : cpfCliente(cpfCliente), nomeCliente(nomeCliente), objetivosCliente(objetivosCliente), condicaoMedicaCliente(condicaoMedicaCliente), tipoTreino(tipoTreino) {
    this->cpfCliente.resize(14);
    this->nomeCliente.resize(150);
    this->tipoTreino.resize(150);
}

PlanoDeTreinoDAO::PlanoDeTreinoDAO(std::vector<PlanoDeTreinoBean> &planos) {
    for(auto &it: planos) {
        this->planosDeTreino.push_back(std::make_unique<PlanoDeTreinoBean>(it));
    }
}

void PlanoDeTreinoDAO::create(PlanoDeTreinoBean &plano) {
    if(!plano.getCpfCliente().empty()) planosDeTreino.push_back(std::make_unique<PlanoDeTreinoBean>(std::move(plano)));
}

void PlanoDeTreinoDAO::remover(PlanoDeTreinoBean &plano) {
    planosDeTreino.erase(std::remove_if(planosDeTreino.begin(), planosDeTreino.end(),
    [&plano](const std::unique_ptr<PlanoDeTreinoBean>& it) { return it->getCpfCliente() == plano.getCpfCliente(); }), planosDeTreino.end());
}

void PlanoDeTreinoDAO::update(PlanoDeTreinoBean &plano) {
    for(auto &&it: planosDeTreino) {
        if(it->getCpfCliente() == plano.getCpfCliente()) {
            it = std::make_unique<PlanoDeTreinoBean>(std::move(plano));
            break;
        }
    }
}

PlanoDeTreinoBean PlanoDeTreinoDAO::getPlanoDeTreinoBean(const std::string &cpfCliente) const& {
    if(cpfCliente.size() == 14) {
        for(auto &&it: planosDeTreino) {
            if(it->getCpfCliente() == cpfCliente) {
                return *it;
            }
        }
    }
    return PlanoDeTreinoBean();
}

bool PlanoDeTreinoManager::validarCpf(const std::string &cpf) {
    bool existe = true;
    if(cpf.size() != 14) existe = false;
    if(planoDeTreinoDAO->getPlanoDeTreinoBean(cpf).getCpfCliente().empty()) existe = false;
    return existe;
}

void PlanoDeTreinoManager::adicionarPlanoDeTreino(PlanoDeTreinoBean &plano) {
    if(!plano.getCpfCliente().empty()) planoDeTreinoDAO->create(plano);
}

void PlanoDeTreinoManager::removerPlanoDeTreino(PlanoDeTreinoBean &plano) {
    if(!plano.getCpfCliente().empty()) planoDeTreinoDAO->remover(plano);
}

void PlanoDeTreinoManager::atualizarPlanoDeTreino(PlanoDeTreinoBean &plano) {
    if(!plano.getCpfCliente().empty()) planoDeTreinoDAO->update(plano);
}

PlanoDeTreinoBean PlanoDeTreinoManager::getPlanoDeTreinoBean(const std::string &cpf) const& {
    return planoDeTreinoDAO->getPlanoDeTreinoBean(cpf);
}
