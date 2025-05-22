## Composição vs Herança

Este princípio diz que composição deve ser priorizado ao invés de herança para garantir flexibilidade.

---

Exemplo:

```cpp
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
```

- Aqui, `CheckInManager` não herda de `ICheckInDAO`, apenas tem como membro interno. Se eu quiser alterar como o DAO maneja as informações internamente, eu refatoro apenas `ICheckInDAO` e sua implementação `CheckInDAO`