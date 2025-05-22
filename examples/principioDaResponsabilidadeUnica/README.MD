# O Princípio da Responsabilidade Única

Este princípio SOLID diz que um objeto precisa ter apenas uma responsabilidade.
Tomamos como exemplo.

```cpp
    // Código resumido em certas partes para melhor leitura.

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
```

Aqui fica explícito que todas as classes desempenham uma função:

* CheckInBean é um dado bruto
* CheckInDAO é o banco de dados. Realiza operações CRUD
* CheckInManager faz a lógica de projeto para gerencia o CheckInDAO

Assim, a manutenção do pojeto fica mais fácil:

* Alterações em `CheckInDao` não afetam `CheckInManager`, por exemplo.
* Elaborar testes unitários fica mais simples.