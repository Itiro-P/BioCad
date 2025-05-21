#pragma once

#include <string>
#include <vector>
#include <memory>
#include <chrono>

class ClienteBean {
    std::string cpf = "";
    std::string nomeCompleto = "";
    std::string telefone = "";
    std::string endereco = "";
    std::chrono::system_clock::time_point dataNascimento = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point dataCadastro = std::chrono::system_clock::now();

    public:
    ClienteBean() = default;
    ClienteBean(const std::string &cpf, const std::string &nomeCompleto, const std::string &telefone, const std::string &endereco, int diaNascimento, int mesNascimento, int anoNascimento);

    std::string getCpf() const& { return cpf; };
    std::string getNomeCompleto() const& { return nomeCompleto; };
    std::string getTelefone() const& { return telefone; };
    std::string getEndereco() const& { return endereco; };
    std::chrono::system_clock::time_point getDataNascimento() const& { return dataNascimento; };
    std::chrono::system_clock::time_point getDataCadastro() const& { return dataCadastro; };

    void setCpf(const std::string novoCpf);
    void setNomeCompleto(const std::string novoNome);
    void setTelefone(const std::string novotelefone);
    void setEndereco(const std::string novoEndereco);
    void setDataNascimento(int dia, int mes, int ano);
};

class ClienteDAO {
    std::vector<std::unique_ptr<ClienteBean>> clientes = {};
    public:
    ClienteDAO() = default;
    ClienteDAO(std::vector<ClienteBean> &clientes);
    void create(const ClienteBean &cliente);
    void update(const ClienteBean &cliente);
    void remover(const ClienteBean &cliente);
    ClienteBean getClienteBean(const std::string& cpfCliente) const&;
};

class ClienteManager {
    std::unique_ptr<ClienteDAO> clienteDAO = nullptr;
    public:
    ClienteManager() = default;
    ClienteManager(ClienteDAO &&clienteDAO);
    ClienteBean getClienteBean(const std::string &cpfCliente) const&;
    bool validarCpf(const std::string &cpf);
    void adicionarCliente(ClienteBean &cliente);
    void removerCliente(ClienteBean &cliente);
    void atualizarCliente(ClienteBean &cliente);
};