#pragma once

#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <chrono>
#include <enums.hpp>

class CheckInBean {
    std::string cpfCliente = "";
    std::tm dataHora;
    public:
    CheckInBean() =  default;
    CheckInBean(const std::string &cpfCliente);
    std::string getCpfCliente() { return cpfCliente; };
    std::tm getDataHora() const&;
};

class CheckInDAO {
    std::vector<std::unique_ptr<CheckInBean>> checkIns;
    public:
    CheckInDAO() = default;
    void create(const std::string &cpfCliente);
    std::vector<CheckInBean> getCheckInsBean() const&;
};

class CheckInManager {
    std::unique_ptr<CheckInDAO> checkInDAO = nullptr;
    public:
    CheckInManager() = default;
    CheckInManager(CheckInDAO &&checkIn) : checkInDAO(std::make_unique<CheckInDAO>(std::move(checkIn))) {};
    void adicionarCheckIn(const std::string &cpfCliente) { if(!cpfCliente.empty()) checkInDAO->create(cpfCliente); };
    std::vector<CheckInBean> getCheckInsPeriodo(const std::tm &dataInicio, const std::tm &dataFim);
};