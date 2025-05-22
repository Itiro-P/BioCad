## Lei de Demeter

Esta lei diz que um objeto deve falar **apenas** com seus vizinhos diretos.

Isto é:
- Chamar apenas seus atributos.
- Usar variáveis locais.
- Objetos passados como parâmetro.

---

Exemplo:

```cpp
    // Violação clara
    obj.getA().getB().getC().facaAlgo();

    // Lei de Demeter aplicada
    std::vector<std::unique_ptr<ICheckInBean>> CheckInDAO::getCheckInsBean() {
        std::vector<std::unique_ptr<ICheckInBean>> res;
        res.reserve(checkIns.size());
        for(const auto &it: checkIns) {
            // it é conhecido localmente
            res.push_back(std::make_unique<ICheckInBean>(std::move(it)));
        }
        return res;
    }

```