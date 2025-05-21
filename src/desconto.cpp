#include <desconto.hpp>

#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include <enums.hpp>
#include <mensalidade.hpp>

bool DescontoManager::validarDesconto(const MensalidadeBean &mensalidade) {
    return mensalidade.getValor() > 130.f && mensalidade.getId()&1;
}

float DescontoManager::calcularDesconto(const MensalidadeBean &mensalidade) {
    return mensalidade.getValor()/10.f;
}
