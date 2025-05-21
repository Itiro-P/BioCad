# O Princípio da Responsabilidade Única

Este princípio SOLID diz que um objeto precisa ter apenas uma responsabilidade.
Tomamos como exemplo.

```cpp
    // Código resumido em certas partes para melhor leitura.

    class CheckInBean {
        std::string cpfCliente = "";
        std::tm dataHora;
        public:
        CheckInBean() =  default;
        CheckInBean(const std::string &cpfCliente);
        std::string getCpfCliente();
        std::tm getDataHora():
    }

    class CheckInDAO {
        std::vector<std::unique_ptr<CheckInBean>> checkIns;
        public:
        CheckInDAO() = default;
        void create(const std::string &cpfCliente);
        std::vector<CheckInBean> getCheckInsBean();
    }

    class CheckInManager {
        std::unique_ptr<CheckInDAO> checkInDAO = nullptr;
        public:
        CheckInManager() = default;
        CheckInManager(CheckInDAO &checkIn);
        void adicionarCheckIn(const std::string &cpfCliente);
        std::vector<CheckInBean> getCheckInsPeriodo(const std::tm &dataInicio, const std::tm &dataFim);
    }
```

Aqui fica explícito que todas as classes desempenham uma função:

* CheckInBean é um dado bruto
* CheckInDAO é o banco de dados. Realiza operações CRUD
* CheckInManager faz a lógica de projeto para gerencia o CheckInDAO

Assim, a manutenção do pojeto fica mais fácil:

* Alterações em `CheckInDao` não afetam `CheckInManager`, por exemplo.
* Elaborar testes unitários fica mais simples.