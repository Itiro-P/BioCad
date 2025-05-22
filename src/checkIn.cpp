#include <checkIn.hpp>

#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <chrono>
#include <enums.hpp>

CheckInBean::CheckInBean(const std::string &cpfCliente) : cpfCliente(cpfCliente) {
    this->cpfCliente.resize(14);
    dataHora = [](std::time_t t) {
        std::tm tm;
    #if defined(_WIN32)
        localtime_s(&tm, &t);
    #else
        localtime_r(&t, &tm);
    #endif
        return tm;
    }(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
}

std::tm CheckInBean::getDataHora() {
    return dataHora;
}

void CheckInDAO::create(const std::string &cpfCliente) {
    checkIns.push_back(std::make_unique<CheckInBean>(std::move(CheckInBean(cpfCliente))));
}

std::vector<std::unique_ptr<ICheckInBean>> CheckInDAO::getCheckInsBean() {
    std::vector<std::unique_ptr<ICheckInBean>> res;
    res.reserve(checkIns.size());
    for(const auto &it: checkIns) {
        res.push_back(std::make_unique<ICheckInBean>(std::move(it)));
    }
    return res;
}

std::vector<std::unique_ptr<ICheckInBean>> CheckInManager::getCheckInsPeriodo(const std::tm &dataInicio, const std::tm &dataFim) {
    std::tm inicioCopia = dataInicio;
    std::tm fimCopia = dataFim;

    std::time_t tInicio = std::mktime(&inicioCopia);
    std::time_t tFim = std::mktime(&fimCopia);
    std::vector<std::unique_ptr<ICheckInBean>> res;
    for(const auto &it: checkInDAO->getCheckInsBean()) {
        std::tm checkData = it->getDataHora();
        std::time_t tCheck = std::mktime(&checkData);
        if (tCheck >= tInicio && tCheck <= tFim) {
            res.push_back(std::make_unique<ICheckInBean>(it));
        }
    }
    return res;
}
