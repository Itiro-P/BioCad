#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include <contrato.hpp>
#include <planoFinanceiro.hpp>

ContratoBean::ContratoBean(const std::string &cpfCliente, const std::string &nomeCliente, const CondicaoContrato &condicao, const PlanoFinanceiroBean &planoBean, int dia, int mes, int ano) 
 : cpfCliente(cpfCliente), nomeCliente(nomeCliente), condicao(condicao), plano(std::make_shared<PlanoFinanceiroBean>(planoBean)) {
    this->cpfCliente.resize(14);
    this->nomeCliente.resize(150);
    std::tm tmp = {};
    tmp.tm_year = ano - 1900;
    tmp.tm_mon = mes - 1;
    tmp.tm_mday = dia;
    dataFim = std::chrono::system_clock::from_time_t(std::mktime(&tmp));
}

void ContratoBean::setCpfCliente(const std::string &novoCpf) {
    if(!novoCpf.empty()) cpfCliente = novoCpf;
}

void ContratoBean::setNomeCliente(const std::string &novoNome) {
    if(!novoNome.empty()) nomeCliente = novoNome;
}

void ContratoBean::setCondicao(const CondicaoContrato &novaCondicao) {
    condicao = novaCondicao;
}

void ContratoBean::setDataFim(int dia, int mes, int ano) {
    std::tm tmp = {};
    tmp.tm_year = ano - 1900;
    tmp.tm_mon = mes - 1;
    tmp.tm_mday = dia;
    dataFim = std::chrono::system_clock::from_time_t(std::mktime(&tmp));
}

ContratoDAO::ContratoDAO(std::vector<ContratoBean> &contratos) {
    for(auto &it: contratos) {
        this->contratos.push_back(std::make_unique<ContratoBean>(std::move(it)));
    }
}

void ContratoDAO::create(ContratoBean &contrato) {
    if(!contrato.getCpfCliente().empty()) {
        contratos.push_back(std::make_unique<ContratoBean>(std::move(contrato)));
    }
}

void ContratoDAO::update(ContratoBean &contrato) {
    if(!contrato.getCpfCliente().empty()) {
        for(auto &&it: contratos) {
            if(it->getCpfCliente() == contrato.getCpfCliente()  &&it->getCondicao() == CondicaoContrato::ATIVO) {
                it = std::make_unique<ContratoBean>(std::move(contrato));
                break;
            }
        }
    }
}

ContratoBean ContratoDAO::getContratoBean(const std::string &cpfCliente) const& {
    for(auto &&it: contratos) {
        if(it->getCpfCliente() == cpfCliente) return *it;
    }
    return ContratoBean();
}

bool ContratoManager::validarCpf(const std::string &cpf) {
    bool existe = false;
    if(!contratoDAO->getContratoBean(cpf).getCpfCliente().empty()) existe = true;
    return existe;
}

bool ContratoManager::validarContrato(const ContratoBean &contrato) {
    bool existe = false;
    if(!contratoDAO->getContratoBean(contrato.getCpfCliente()).getCpfCliente().empty()) existe = true;
    return existe;
}

void ContratoManager::salvarContrato(ContratoBean &contrato) {
    if(!contrato.getCpfCliente().empty()) {
        contratoDAO->create(contrato);
    }
}

void ContratoManager::atualizarContrato(ContratoBean &contrato) {
    if(!contrato.getCpfCliente().empty()) {
        contratoDAO->update(contrato);
    }
}

bool ContratoManager::setContratoCancelado(ContratoBean &contrato) {
    ContratoBean temp = contratoDAO->getContratoBean(contrato.getCpfCliente());
    if(!temp.getCpfCliente().empty()) {
        temp.setCondicao(CondicaoContrato::CANCELADO);
        contratoDAO->update(temp);
        return true;
    }
    return false;
}

ContratoBean ContratoManager::renovarContrato(ContratoBean &contrato, const std::tm novaDataFim) const& {
    ContratoBean temp = contratoDAO->getContratoBean(contrato.getCpfCliente());
    if(!temp.getCpfCliente().empty()) {
        temp.setDataFim(novaDataFim.tm_mday, novaDataFim.tm_mon, novaDataFim.tm_year + 1900);
        contratoDAO->update(temp);
    }
    return temp;
}

ContratoBean ContratoManager::getContratoBean(const std::string &cpfCliente) const& {
    return contratoDAO->getContratoBean(cpfCliente);
}
