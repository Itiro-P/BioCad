#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include <enums.hpp>
#include <mensalidade.hpp>

class DescontoBean {
    float valor = 0.f;
    public:
    DescontoBean() = default;
    DescontoBean(float valor) : valor(valor) {};
    float getValor() const& { return valor; };
    void setValor(float novoValor) { valor = novoValor; };
};

class DescontoManager {
    public:
    DescontoManager() = default;
    bool validarDesconto(const MensalidadeBean &mensalidade);
    float calcularDesconto(const MensalidadeBean &mensalidade);
};