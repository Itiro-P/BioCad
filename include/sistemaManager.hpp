#pragma once
#include <memory>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cliente.hpp>
#include <checkIn.hpp>
#include <checkOut.hpp>
#include <contrato.hpp>
#include <mensalidade.hpp>
#include <desconto.hpp>
#include <relatorio.hpp>
#include <planoDeTreino.hpp>
#include <planoFinanceiro.hpp>

class SistemaManager {
public:
    std::unique_ptr<ClienteManager> clienteManager;
    std::unique_ptr<CheckInManager> checkInManager;
    std::unique_ptr<CheckOutManager> checkOutManager;
    std::unique_ptr<ContratoManager> contratoManager;
    std::unique_ptr<MensalidadeManager> mensalidadeManager;
    std::unique_ptr<PlanoDeTreinoManager> planoTreinoManager;
    std::unique_ptr<PlanoFinanceiroManager> planoFinanceiroManager;
    std::unique_ptr<DescontoManager> descontoManager;
    std::unique_ptr<RelatorioManager> relatorioManager;

    SistemaManager()
        : clienteManager(std::make_unique<ClienteManager>(ClienteDAO{}))
        , checkInManager(std::make_unique<CheckInManager>(CheckInDAO{}))
        , checkOutManager(std::make_unique<CheckOutManager>(CheckOutDAO{}))
        , contratoManager(std::make_unique<ContratoManager>(ContratoDAO{}))
        , mensalidadeManager(std::make_unique<MensalidadeManager>(MensalidadeDAO{}))
        , planoTreinoManager(std::make_unique<PlanoDeTreinoManager>(PlanoDeTreinoDAO{}))
        , planoFinanceiroManager(std::make_unique<PlanoFinanceiroManager>(PlanoFinanceiroDAO{}))
        , descontoManager(std::make_unique<DescontoManager>())
        , relatorioManager(std::make_unique<RelatorioManager>()) {}

    ClienteBean pesquisarClienteCadastrado(const std::string& cpfCliente) {
        return clienteManager->getClienteBean(cpfCliente);
    }

    ContratoBean selecionarContrato(const std::string& cpfCliente) {
        return contratoManager->getContratoBean(cpfCliente);
    }

    void imprimirContrato(const ContratoBean& contrato) {
        const auto plano = contrato.getPlano();
        std::cout << "=== Contrato ===\n"
                  << "Cliente: " << contrato.getNomeCliente() << "\n"
                  << "CPF: " << contrato.getCpfCliente() << "\n"
                  << "Plano: " << plano.getNomePlano() << "\n"
                  << "Tipo: " << static_cast<int>(plano.getTipoPlano()) << "\n"
                  << "Status: " << static_cast<int>(contrato.getCondicao()) << "\n";
    }

    ContratoBean digitalizarContrato(ContratoBean contrato) {
        contratoManager->atualizarContrato(contrato);
        return contratoManager->getContratoBean(contrato.getCpfCliente());
    }

    void cancelarContrato(ContratoBean& contrato) {
        contratoManager->setContratoCancelado(contrato);
    }

    ContratoBean renovarContrato(ContratoBean& contrato, const std::tm& novaDataFim) {
        return contratoManager->renovarContrato(contrato, novaDataFim);
    }

    MensalidadeBean exibirMensalidade(const std::string& cpfCliente) {
        auto mensalidades = mensalidadeManager->getMensalidades(cpfCliente);
        return !mensalidades.empty() ? mensalidades.back() : MensalidadeBean();
    }

    DescontoBean calcularDescontoFidelidade(const std::string& cpfCliente) {
        float total = 0.0f;
        for (const auto& mensalidade : mensalidadeManager->getMensalidades(cpfCliente)) {
            if (descontoManager->validarDesconto(mensalidade)) {
                total += descontoManager->calcularDesconto(mensalidade);
            }
        }
        return DescontoBean(total);
    }

    void pagarMensalidade(int idMensalidade, const std::string& cpfCliente) {
        if (mensalidadeManager->validarId(idMensalidade, cpfCliente)) {
            auto mensalidade = mensalidadeManager->getMensalidadeBean(idMensalidade);
            mensalidade.setStatus(Status::PAGO);
            mensalidadeManager->atualizarMensalidade(mensalidade);
        }
    }

    void emitirReciboPagamento(int idMensalidade) {
        std::cout << mensalidadeManager->getRecibo(idMensalidade) << std::endl;
    }

    void checkInCliente(const std::string& cpfCliente) {
        checkInManager->adicionarCheckIn(cpfCliente);
    }

    void checkOutCliente(const std::string& cpfCliente) {
        checkOutManager->adicionarCheckOut(cpfCliente);
    }

    RelatorioBean gerarRelatorioFrequencia(const std::tm& inicio, const std::tm& fim) {
        auto checkIns = checkInManager->getCheckInsPeriodo(inicio, fim);
        auto checkOuts = checkOutManager->getCheckOutsPeriodo(inicio, fim);
        return relatorioManager->gerarRelatorioFrequencia(inicio, fim, checkIns, checkOuts);
    }

    static void exportar(const std::string& conteudo) {
        std::ofstream("conteudo.txt") << conteudo;
    }

    static void imprimir(const std::string& conteudo) {
        std::cout << conteudo << '\n';
    }
};