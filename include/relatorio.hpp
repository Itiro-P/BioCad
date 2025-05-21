#pragma once

#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <chrono>
#include <checkIn.hpp>
#include <checkOut.hpp>
#include <enums.hpp>

class RelatorioBean {
    std::tm dataInicio;
    std::tm dataFim;
    std::vector<CheckInBean> checkInsPeriodo;
    std::vector<CheckOutBean> checkOutsPeriodo;
    public:
    RelatorioBean() = default;
    RelatorioBean(const std::tm &dataInicio, const std::tm &dataFim, const std::vector<CheckInBean> &checkInsPeriodo, const std::vector<CheckOutBean> &checkOutsPeriodo)
        : dataInicio(dataInicio), dataFim(dataFim), checkInsPeriodo(checkInsPeriodo), checkOutsPeriodo(checkOutsPeriodo) {};
    
    std::tm getDataInicio() const& { return dataInicio; };
    std::tm getDataFim() const& { return dataFim; };
    std::vector<CheckInBean> getCheckInsPeriodo() const& { return checkInsPeriodo; };
    std::vector<CheckOutBean> getCheckoutsPeriodo() const& { return checkOutsPeriodo; };
};

class RelatorioManager {
    public:
    bool validarPeriodo(const std::tm &dataInicio, const std::tm &dataFim);
    RelatorioBean gerarRelatorioFrequencia(const std::tm &dataInicio, const std::tm &dataFim, const std::vector<CheckInBean> &checkInsPeriodo, const std::vector<CheckOutBean> &checkOutsPeriodo);
};