#include <cliente.hpp>
#include <string>
#include <chrono>
#include <algorithm>

ClienteBean::ClienteBean(const std::string &cpf, const std::string &nomeCompleto, const std::string &telefone, const std::string &endereco, int diaNascimento, int mesNascimento, int anoNascimento)
 : cpf(cpf), nomeCompleto(nomeCompleto), telefone(telefone), endereco(endereco) {
    std::tm tmp = {};
    this->cpf.resize(14);
    this->telefone.resize(11);
    this->nomeCompleto.resize(150);
    this->endereco.resize(150);
    tmp.tm_year = anoNascimento - 1900;
    tmp.tm_mon = mesNascimento - 1;
    tmp.tm_mday = diaNascimento;

    dataNascimento = std::chrono::system_clock::from_time_t(std::mktime(&tmp));
}

void ClienteBean::setCpf(const std::string novoCpf) {
    cpf = novoCpf;
    cpf.resize(14);
}

void ClienteBean::setNomeCompleto(const std::string novoNome) {
    nomeCompleto = novoNome;
    nomeCompleto.resize(150);
}

void ClienteBean::setTelefone(const std::string novotelefone) {
    telefone = novotelefone;
    telefone.resize(11);
}

void ClienteBean::setEndereco(const std::string novoEndereco) {
    endereco = novoEndereco;
    endereco.resize(150);
}

void ClienteBean::setDataNascimento(int dia, int mes, int ano) {
    std::tm tmp = {};
    tmp.tm_year = ano - 1900;
    tmp.tm_mon = mes - 1;
    tmp.tm_mday = dia;
    dataNascimento = std::chrono::system_clock::from_time_t(std::mktime(&tmp));
}

ClienteDAO::ClienteDAO(std::vector<ClienteBean> &clientes) {
    for(auto &it: clientes) {
        this->clientes.push_back(std::make_unique<ClienteBean>(std::move(it)));
    }
}

void ClienteDAO::create(const ClienteBean &cliente) {
    clientes.push_back(std::make_unique<ClienteBean>(std::move(cliente)));
}

void ClienteDAO::update(const ClienteBean &cliente) {
    for(auto &&it: clientes) {
        if(it->getCpf() == cliente.getCpf()) {
            it = std::make_unique<ClienteBean>(std::move(cliente));
            break;
        }
    }
}

void ClienteDAO::remover(const ClienteBean &cliente) {
    clientes.erase(std::remove_if(clientes.begin(), clientes.end(),
    [&cliente](const std::unique_ptr<ClienteBean>& it) { return it->getCpf() == cliente.getCpf(); }), clientes.end());
}

ClienteBean ClienteDAO::getClienteBean(const std::string& cpfCliente) const& {
    for(auto &&it: clientes) {
        if(it->getCpf() == cpfCliente) {
            return *it;
            break;
        }
    }
    return ClienteBean();
}

ClienteManager::ClienteManager(ClienteDAO &&clienteDAO) {
    this->clienteDAO = std::make_unique<ClienteDAO>(std::move(clienteDAO));
}

ClienteBean ClienteManager::getClienteBean(const std::string &cpfCliente) const& {
    return clienteDAO->getClienteBean(cpfCliente);
}

bool ClienteManager::validarCpf(const std::string &cpf) {
    bool existe = true;
    if(cpf.size() != 14) existe = false;
    if(clienteDAO->getClienteBean(cpf).getCpf().empty()) existe = false;
    return existe;
}

void ClienteManager::adicionarCliente(ClienteBean &cliente) {
    if(!cliente.getCpf().empty()) clienteDAO->create(cliente);
}

void ClienteManager::atualizarCliente(ClienteBean &cliente) {
    if(!cliente.getCpf().empty()) clienteDAO->update(cliente);
}

void ClienteManager::removerCliente(ClienteBean &cliente) {
    if(!cliente.getCpf().empty()) clienteDAO->remover(cliente);
}