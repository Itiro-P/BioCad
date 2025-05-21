#include <ctime>
#include <dadosTeste.hpp>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <limits>
#include <vector>
#include <sistemaManager.hpp>


namespace TestData {

    // ----- CheckInBean -----
    CheckInBean checkIn1("111.111.111-11");
    CheckInBean checkIn2("222.222.222-22");
    CheckInBean checkIn3("333.333.333-33");
    CheckInBean checkIn4("444.444.444-44");
    CheckInBean checkIn5("555.555.555-55");
    CheckInBean checkIn6("666.666.666-66");

    // ----- CheckOutBean -----
    CheckOutBean checkOut1("111.111.111-11");
    CheckOutBean checkOut2("222.222.222-22");
    CheckOutBean checkOut3("333.333.333-33");
    CheckOutBean checkOut4("444.444.444-44");
    CheckOutBean checkOut5("555.555.555-55");
    CheckOutBean checkOut6("666.666.666-66");

    // ----- ClienteBean -----
    ClienteBean cliente1("111.111.111-11", "Alice Silva", "(11) 91234-1111", "Rua das Acácias, 100", 5, 3, 1980);
    ClienteBean cliente2("222.222.222-22", "Bruno Costa", "(21) 92345-2222", "Avenida Central, 200", 12, 7, 1985);
    ClienteBean cliente3("333.333.333-33", "Carla Souza", "(31) 93456-3333", "Rua dos Lírios, 300", 23, 9, 1990);
    ClienteBean cliente4("444.444.444-44", "Daniel Pereira", "(41) 94567-4444", "Av. dos Pinheiros, 400", 15, 5, 1992);
    ClienteBean cliente5("555.555.555-55", "Elisa Ramos", "(51) 95678-5555", "Rua das Orquídeas, 500", 8, 11, 1988);
    ClienteBean cliente6("666.666.666-66", "Fábio Lima", "(61) 96789-6666", "Avenida das Palmeiras, 600", 30, 1, 1995);

    // ----- PlanoFinanceiroBean -----
    PlanoFinanceiroBean plano1("Básico", TipoPlanoFinanceiro::MENSAL);
    PlanoFinanceiroBean plano2("Premium", TipoPlanoFinanceiro::ANUAL);
    PlanoFinanceiroBean plano3("Executivo", TipoPlanoFinanceiro::MENSAL);
    PlanoFinanceiroBean plano4("Avançado", TipoPlanoFinanceiro::ANUAL);
    PlanoFinanceiroBean plano5("Standard", TipoPlanoFinanceiro::MENSAL);
    PlanoFinanceiroBean plano6("Especial", TipoPlanoFinanceiro::ANUAL);

    // ----- ContratoBean -----
    ContratoBean contrato1("111.111.111-11", "Alice Silva", CondicaoContrato::ATIVO, plano1, 1, 1, 2023);
    ContratoBean contrato2("222.222.222-22", "Bruno Costa", CondicaoContrato::ATIVO, plano2, 2, 2, 2023);
    ContratoBean contrato3("333.333.333-33", "Carla Souza", CondicaoContrato::ATIVO, plano3, 3, 3, 2023);
    ContratoBean contrato4("444.444.444-44", "Daniel Pereira", CondicaoContrato::ATIVO, plano4, 4, 4, 2023);
    ContratoBean contrato5("555.555.555-55", "Elisa Ramos", CondicaoContrato::ATIVO, plano5, 5, 5, 2023);
    ContratoBean contrato6("666.666.666-66", "Fábio Lima", CondicaoContrato::ATIVO, plano6, 6, 6, 2023);

    // ----- MensalidadeBean -----
    MensalidadeBean mensalidade1("111.111.111-11", 101);
    MensalidadeBean mensalidade2("222.222.222-22", 102);
    MensalidadeBean mensalidade3("333.333.333-33", 103);
    MensalidadeBean mensalidade4("444.444.444-44", 104);
    MensalidadeBean mensalidade5("555.555.555-55", 105);
    MensalidadeBean mensalidade6("666.666.666-66", 106);

    // ----- PlanoDeTreinoBean -----
    PlanoDeTreinoBean treino1("111.111.111-11", "Alice Silva", {"Hipertrofia", "Resistência"}, {"Nenhuma"}, "Funcional");
    PlanoDeTreinoBean treino2("222.222.222-22", "Bruno Costa", {"Emagrecimento"}, {"Diabetes"}, "Aeróbico");
    PlanoDeTreinoBean treino3("333.333.333-33", "Carla Souza", {"Flexibilidade", "Equilíbrio"}, {"Nenhuma"}, "Alongamento");
    PlanoDeTreinoBean treino4("444.444.444-44", "Daniel Pereira", {"Força", "Resistência"}, {"Lesão no joelho"}, "Treino de Força");
    PlanoDeTreinoBean treino5("555.555.555-55", "Elisa Ramos", {"Cardio"}, {"Hipertensão"}, "Circuito");
    PlanoDeTreinoBean treino6("666.666.666-66", "Fábio Lima", {"Definição muscular"}, {"Nenhuma"}, "Crossfit");

    // ----- RelatorioBean -----

    std::tm inicio1 = []{
        std::tm t = {}; 
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;      // Janeiro (0-indexado)
        t.tm_mday = 1;
        return t;
    }();
    std::tm fim1 = []{
        std::tm t = {}; 
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 1;
        t.tm_hour = 23;
        t.tm_min  = 59;
        t.tm_sec  = 59;
        return t;
    }();
    RelatorioBean relatorio1(inicio1, fim1, { checkIn1 }, { checkOut1 });

    std::tm inicio2 = []{
        std::tm t = {};
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 2;
        return t;
    }();
    std::tm fim2 = []{
        std::tm t = {};
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 2;
        t.tm_hour = 23;
        t.tm_min  = 59;
        t.tm_sec  = 59;
        return t;
    }();
    RelatorioBean relatorio2(inicio2, fim2, { checkIn2 }, { checkOut2 });

    std::tm inicio3 = []{
        std::tm t = {};
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 3;
        return t;
    }();
    std::tm fim3 = []{
        std::tm t = {};
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 3;
        t.tm_hour = 23;
        t.tm_min  = 59;
        t.tm_sec  = 59;
        return t;
    }();
    RelatorioBean relatorio3(inicio3, fim3, { checkIn3 }, { checkOut3 });

    std::tm inicio4 = []{
        std::tm t = {};
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 4;
        return t;
    }();
    std::tm fim4 = []{
        std::tm t = {};
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 4;
        t.tm_hour = 23;
        t.tm_min  = 59;
        t.tm_sec  = 59;
        return t;
    }();
    RelatorioBean relatorio4(inicio4, fim4, { checkIn4 }, { checkOut4 });

    std::tm inicio5 = []{
        std::tm t = {};
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 5;
        return t;
    }();
    std::tm fim5 = []{
        std::tm t = {};
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 5;
        t.tm_hour = 23;
        t.tm_min  = 59;
        t.tm_sec  = 59;
        return t;
    }();
    RelatorioBean relatorio5(inicio5, fim5, { checkIn5 }, { checkOut5 });

    std::tm inicio6 = []{
        std::tm t = {};
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 6;
        return t;
    }();
    std::tm fim6 = []{
        std::tm t = {};
        t.tm_year = 2025 - 1900;
        t.tm_mon  = 0;
        t.tm_mday = 6;
        t.tm_hour = 23;
        t.tm_min  = 59;
        t.tm_sec  = 59;
        return t;
    }();
    RelatorioBean relatorio6(inicio6, fim6, { checkIn6 }, { checkOut6 });
}