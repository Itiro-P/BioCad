#include <relatorio.hpp>

#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <chrono>
#include <enums.hpp>

bool RelatorioManager::validarPeriodo(const std::tm &dataInicio, const std::tm &dataFim) {
    std::tm inicioCopia = dataInicio;
    std::tm fimCopia = dataFim;

    std::time_t tInicio = std::mktime(&inicioCopia);
    std::time_t tFim = std::mktime(&fimCopia);
    return tInicio < tFim;
}

RelatorioBean RelatorioManager::gerarRelatorioFrequencia(const std::tm &dataInicio, const std::tm &dataFim, const std::vector<CheckInBean> &checkInsPeriodo, const std::vector<CheckOutBean> &checkOutsPeriodo) {
    return RelatorioBean(dataInicio, dataFim, checkInsPeriodo, checkOutsPeriodo);
}