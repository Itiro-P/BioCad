## Princípio Aberto–Fechado (OCP)

Este princípio diz que “software deve estar aberto para extensão, mas fechado para modificação”.  
Ou seja, você não deve alterar código já testado para adicionar novas funcionalidades — em vez disso, estenda-o.

---

Exemplo
  
- Definimos a interface `ICheckInDAO`, que declara os métodos de persistência:
    ```cpp
        class ICheckInDAO {
            public:
            virtual ~ICheckInDAO() = default;
            virtual void create(const std::string &cpfCliente) = 0;
            virtual std::vector<std::unique_ptr<ICheckInBean>> getCheckInsBean() = 0;
        };
    ```

- `CheckInManager` só depende dessa interface, nunca de `CheckInDAO` diretamente:
    ```cpp
        class CheckInManager : public ICheckInManager {
            std::unique_ptr<ICheckInDAO> checkInDAO;
        public:
            CheckInManager(std::unique_ptr<ICheckInDAO> dao): checkInDAO(std::move(dao)) {}
            // ...
        };
    ```

- Suponha que agora você queira salvar check-ins em arquivo JSON em vez de memória.  
- Basta criar nova implementação de `ICheckInDAO`:

    ```cpp
    #include <fstream>
    #include <nlohmann/json.hpp> // exemplo de biblioteca JSON

    class FileCheckInDAO : public ICheckInDAO {
        std::string filename;
        public:
        FileCheckInDAO(std::string file) : filename(std::move(file)) {}
        void create(const std::string &cpf) override {
            // abre o arquivo e adiciona registro em JSON
            nlohmann::json j{ {"cpf", cpf}, {"timestamp", /*...*/} };
            std::ofstream os(filename, std::ios::app);
            os << j.dump() << "\n";
        }
            std::vector<std::unique_ptr<ICheckInBean>> getCheckInsBean() override {
            // lê o JSON do arquivo, converte em CheckInBean, retorna vetor
            // ...
        }
    };
    ```

   ```cpp
   #include "CheckInManager.hpp"
   #include "FileCheckInDAO.hpp"

   int main() {
       // Em vez de InMemory (ou CheckInDAO), agora injeta FileCheckInDAO:
       auto dao = std::make_unique<FileCheckInDAO>("checkins.json");
       CheckInManager manager(std::move(dao));

       manager.adicionarCheckIn("123.456.789-00");
       // ...
   }
    ```