#pragma once

#include <string>
#include <vector>
#include <memory>
#include <enums.hpp>

class MensalidadeBean {
    int id = -1;
    std::string cpfCliente = "";
    float valor = 150.f;
    Status status = Status::PENDENTE;
    public:
    MensalidadeBean() = default;
    MensalidadeBean(const std::string &cpfCliente, int id) : cpfCliente(cpfCliente) { this->cpfCliente.resize(14); };
    std::string getCpfCliente() const& { return cpfCliente; };
    float getValor() const& { return valor; };
    Status getStatus() const& { return status; };
    int getId() const& { return id; };

    void setCpfCliente(const std::string &novoCpf) { if(novoCpf.size() == 14) cpfCliente = novoCpf; };
    void setValor(const float novoValor) { valor = novoValor; };
    void setStatus(const Status &novoStatus) { status = novoStatus; };
    void setId(int novoId) { id = novoId; };
};

class MensalidadeDAO {
    std::vector<std::unique_ptr<MensalidadeBean>> mensalidades = {};
    public:
    MensalidadeDAO() = default;
    MensalidadeDAO(std::vector<MensalidadeBean> &mensalidades);
    void create(MensalidadeBean &mensalidade);
    void update(MensalidadeBean &mensalidade);
    MensalidadeBean getMensalidadeBean(int idMensalidade);
    std::vector<MensalidadeBean> getMensalidades(const std::string &cpfCliente) const&;
};

class MensalidadeManager {
    std::unique_ptr<MensalidadeDAO> mensalidadeDAO = nullptr;
    public:
    MensalidadeManager() = default;
    MensalidadeManager(MensalidadeDAO &&mensalidadeDAO) : mensalidadeDAO(std::make_unique<MensalidadeDAO>(std::move(mensalidadeDAO))) {};
    bool validarId(int idMensalidade, const std::string &cpfCliente);
    bool validadrCpf(const std::string &cpfCliente);
    MensalidadeBean getMensalidadeBean(int idMensalidade) const&;
    std::vector<MensalidadeBean> getMensalidades(const std::string &cpfCliente) const&;
    std::string getRecibo(int idMensalidade);
    void atualizarMensalidade(MensalidadeBean &mensalidade);
    void adicionarMensalidade(MensalidadeBean &mensalidade);
};