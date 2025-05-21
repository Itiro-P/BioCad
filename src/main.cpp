#include <iostream>
#include <iomanip>
#include <limits>
#include <sistemaManager.hpp>
#include <dadosTeste.hpp>
#include <stdio.h>


void exibirMenuPrincipal();
void pausarTela();
std::string lerString(const std::string& prompt);
int lerInteiro(const std::string& prompt);
tm lerData(const std::string& prompt);
void colocarDados(SistemaManager &sistema);


int main() {
    SistemaManager sistema;
    colocarDados(sistema);
    int opcao;
    
    do {
        exibirMenuPrincipal();
        opcao = lerInteiro("Escolha uma opcao: ");
        
        try {
            switch(opcao) {
                case 1: {
                    std::cout << "\n=== CADASTRAR CLIENTE ===\n";
                    std::string cpf = lerString("CPF (xxx.xxx.xxx-xx): ");
                    std::string nome = lerString("Nome completo: ");
                    std::string telefone = lerString("Telefone: ");
                    std::string endereco = lerString("Endereco: ");
                    
                    tm dataNasc = lerData("Data de nascimento (DD MM AAAA): ");
                    ClienteBean novoCliente(
                        cpf, nome, telefone, endereco,
                        dataNasc.tm_mday, dataNasc.tm_mon + 1, dataNasc.tm_year + 1900
                    );
                    
                    sistema.clienteManager->adicionarCliente(novoCliente);
                    std::cout << "Cliente cadastrado com sucesso!\n";
                    break;
                }
                
                case 2: {
                    std::string cpf = lerString("CPF do cliente: ");
                    sistema.checkInCliente(cpf);
                    std::cout << "Check-in registrado!\n";
                    break;
                }
                
                case 3: {
                    std::string cpf = lerString("CPF do cliente: ");
                    int id = lerInteiro("ID da mensalidade: ");
                    sistema.pagarMensalidade(id, cpf);
                    std::cout << "Mensalidade marcada como paga!\n";
                    break;
                }
                
                case 4: {
                    tm inicio = lerData("Data inicial (DD MM AAAA): ");
                    tm fim = lerData("Data final (DD MM AAAA): ");
                    
                    RelatorioBean relatorio = sistema.gerarRelatorioFrequencia(inicio, fim);
                    std::cout << "\n=== RELATORIO ==="
                         << "\nPeriodo: " << std::put_time(&inicio, "%d/%m/%Y")
                         << " - " << std::put_time(&fim, "%d/%m/%Y")
                         << "\nTotal check-ins: " << relatorio.getCheckInsPeriodo().size()
                         << "\nTotal check-outs: " << relatorio.getCheckoutsPeriodo().size()
                         << "\n";
                    int opcao = lerInteiro("Deseja exportar o relatorio? (1/0)");
                    if(opcao == 1) {
                        sistema.exportar("arquivo.txt");
                        std::cout << "Relatorio exportado com sucesso.\n";
                    }
                    break;
                }
                
                case 5: {
                    std::string cpf = lerString("CPF do cliente: ");
                    ClienteBean cliente = sistema.pesquisarClienteCadastrado(cpf);
                    
                    std::cout << "\n=== DADOS DO CLIENTE ==="
                         << "\nCPF: " << cliente.getCpf()
                         << "\nNome: " << cliente.getNomeCompleto()
                         << "\nTelefone: " << cliente.getTelefone()
                         << "\nEndereco: " << cliente.getEndereco() << "\n";
                    break;
                }
                
                case 6: {
                    int id = lerInteiro("ID da mensalidade: ");
                    sistema.emitirReciboPagamento(id);
                    break;
                }
                
                case 7: {
                    std::string cpf = lerString("CPF do cliente: ");
                    ContratoBean contrato = sistema.selecionarContrato(cpf);
                    
                    std::cout << "\n=== OPCOES DE CONTRATO ==="
                         << "\n1 - Cancelar contrato"
                         << "\n2 - Renovar contrato"
                         << "\n3 - Imprimir contrato\n";
                         
                    int op = lerInteiro("Escolha: ");
                    switch(op) {
                        case 1:
                            sistema.cancelarContrato(contrato);
                            std::cout << "Contrato cancelado!\n";
                            break;
                        case 2: {
                            tm novaData = lerData("Nova data final (DD MM AAAA): ");
                            sistema.renovarContrato(contrato, novaData);
                            std::cout << "Contrato renovado!\n";
                            break;
                        }
                        case 3:
                            sistema.imprimirContrato(contrato);
                            break;
                        default:
                        std::cout << "Opcao invalida!\n";
                    }
                    break;
                }
                
                case 8: {
                    std::string cpf = lerString("CPF do cliente: ");
                    DescontoBean desconto = sistema.calcularDescontoFidelidade(cpf);
                    std::cout << "Desconto acumulado: R$" << std::fixed << std::setprecision(2) 
                         << desconto.getValor() << "\n";
                    break;
                }
                
                case 0:
                std::cout << "Saindo do sistema...\n";
                    break;
                    
                default:
                std::cout << "Opcao invalida!\n";
            }
        } catch(const std::exception& e) {
            std::cerr << "\nErro: " << e.what() << std::endl;
        }
        
        pausarTela();
        
    } while(opcao != 0);

    return 0;
}

void exibirMenuPrincipal() {
    system("clear || cls");
    std::cout << "=== SISTEMA BioCad ==="
         << "\n1 - Cadastrar Cliente"
         << "\n2 - Realizar Check-in"
         << "\n3 - Pagar Mensalidade"
         << "\n4 - Gerar Relatorio"
         << "\n5 - Consultar Cliente"
         << "\n6 - Emitir Recibo"
         << "\n7 - Gerenciar Contratos"
         << "\n8 - Calcular Desconto"
         << "\n0 - Sair\n";
}

void pausarTela() {
    std::cout << "\nPressione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

std::string lerString(const std::string& prompt) {
    std::cout << prompt;
    std::string entrada;
    std::getline(std::cin >> std::ws, entrada);
    return entrada;
}

int lerInteiro(const std::string& prompt) {
    int valor;
    std::cout << prompt;
    while(!(std::cin >> valor)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada invalida. Digite um numero: ";
    }
    return valor;
}

tm lerData(const std::string& prompt) {
    tm data = {};
    std::cout << prompt;
    std::cin >> data.tm_mday >> data.tm_mon >> data.tm_year;
    data.tm_mon--;    // Ajuste para struct tm (0-11)
    data.tm_year -= 1900; // Ano desde 1900
    return data;
}

void colocarDados(SistemaManager &sistema) {
    sistema.checkInManager->adicionarCheckIn("111.111.111-11");
    sistema.checkInManager->adicionarCheckIn("222.222.222-22");
    sistema.checkInManager->adicionarCheckIn("333.333.333-33");
    sistema.checkInManager->adicionarCheckIn("444.444.444-44");
    sistema.checkInManager->adicionarCheckIn("555.555.555-55");
    sistema.checkInManager->adicionarCheckIn("666.666.666-66");
    sistema.checkOutManager->adicionarCheckOut("111.111.111-11");
    sistema.checkOutManager->adicionarCheckOut("222.222.222-22");
    sistema.checkOutManager->adicionarCheckOut("333.333.333-33");
    sistema.checkOutManager->adicionarCheckOut("444.444.444-44");
    sistema.checkOutManager->adicionarCheckOut("555.555.555-55");
    sistema.checkOutManager->adicionarCheckOut("666.666.666-66");

    sistema.clienteManager->adicionarCliente(TestData::cliente1);
    sistema.clienteManager->adicionarCliente(TestData::cliente2);
    sistema.clienteManager->adicionarCliente(TestData::cliente3);
    sistema.clienteManager->adicionarCliente(TestData::cliente4);
    sistema.clienteManager->adicionarCliente(TestData::cliente5);
    sistema.clienteManager->adicionarCliente(TestData::cliente6);

    sistema.planoFinanceiroManager->adicionarPlano(TestData::plano1);
    sistema.planoFinanceiroManager->adicionarPlano(TestData::plano2);
    sistema.planoFinanceiroManager->adicionarPlano(TestData::plano3);
    sistema.planoFinanceiroManager->adicionarPlano(TestData::plano4);
    sistema.planoFinanceiroManager->adicionarPlano(TestData::plano5);
    sistema.planoFinanceiroManager->adicionarPlano(TestData::plano6);

    sistema.contratoManager->salvarContrato(TestData::contrato1);
    sistema.contratoManager->salvarContrato(TestData::contrato2);
    sistema.contratoManager->salvarContrato(TestData::contrato3);
    sistema.contratoManager->salvarContrato(TestData::contrato4);
    sistema.contratoManager->salvarContrato(TestData::contrato5);
    sistema.contratoManager->salvarContrato(TestData::contrato6);

    sistema.mensalidadeManager->adicionarMensalidade(TestData::mensalidade1);
    sistema.mensalidadeManager->adicionarMensalidade(TestData::mensalidade2);
    sistema.mensalidadeManager->adicionarMensalidade(TestData::mensalidade3);
    sistema.mensalidadeManager->adicionarMensalidade(TestData::mensalidade4);
    sistema.mensalidadeManager->adicionarMensalidade(TestData::mensalidade5);
    sistema.mensalidadeManager->adicionarMensalidade(TestData::mensalidade6);

    sistema.planoTreinoManager->adicionarPlanoDeTreino(TestData::treino1);
    sistema.planoTreinoManager->adicionarPlanoDeTreino(TestData::treino2);
    sistema.planoTreinoManager->adicionarPlanoDeTreino(TestData::treino3);
    sistema.planoTreinoManager->adicionarPlanoDeTreino(TestData::treino4);
    sistema.planoTreinoManager->adicionarPlanoDeTreino(TestData::treino5);
    sistema.planoTreinoManager->adicionarPlanoDeTreino(TestData::treino6);
}