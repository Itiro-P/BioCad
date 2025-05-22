#pragma once

#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <chrono>
#include <enums.hpp>

class ICheckInBean {
    public:
    virtual ~ICheckInBean() = default;
    virtual std::string getCpfCliente() = 0;
    virtual std::tm getDataHora() = 0;
};


class ICheckInDAO {
    public:
    virtual ~ICheckInDAO() = default;
    virtual void create(const std::string &cpfCliente) = 0;
    virtual std::vector<std::unique_ptr<ICheckInBean>> getCheckInsBean() = 0;
};

class ICheckInManager {
    public:
    virtual ~ICheckInManager() = default;
    virtual void adicionarCheckIn(const std::string &cpfCliente) = 0;
    virtual std::vector<std::unique_ptr<ICheckInBean>> getCheckInsPeriodo(const std::tm &dataInicio, const std::tm &dataFim) = 0;
};

class CheckInBean: public ICheckInBean {
    std::string cpfCliente = "";
    std::tm dataHora;
    public:
    CheckInBean() = default;
    CheckInBean(const std::string &cpfCliente);
    std::string getCpfCliente() override { return cpfCliente; };
    std::tm getDataHora() override;
};

class CheckInDAO: public ICheckInDAO {
    std::vector<std::unique_ptr<CheckInBean>> checkIns;
    public:
    CheckInDAO() = default;
    void create(const std::string &cpfCliente) override;
    std::vector<std::unique_ptr<ICheckInBean>> getCheckInsBean() override;
};

class CheckInManager: public ICheckInManager{
    std::unique_ptr<ICheckInDAO> checkInDAO = nullptr;
    public:
    CheckInManager() = default;
    CheckInManager(CheckInDAO &&checkIn) : checkInDAO(std::make_unique<CheckInDAO>(std::move(checkIn))) {};
    void adicionarCheckIn(const std::string &cpfCliente) override { if(!cpfCliente.empty()) checkInDAO->create(cpfCliente); };
    std::vector<std::unique_ptr<ICheckInBean>> getCheckInsPeriodo(const std::tm &dataInicio, const std::tm &dataFim) override;
};