#include <stdio.h>
#include <string.h>

enum Departamento {
    TI,
    VENDAS,
    LOGISTICA,
    OUTRO
    
};

const char *departamentos[] = {
    "TI",
    "Vendas",
    "Logistica",
    "OUTRO"
};

struct Funcionario {
    char nome[50];
    enum Departamento departamento;
    float salario;
};

const char *DepartamentoString(enum Departamento departamento) {
    return departamentos[departamento];
}

float MediaSalarial(struct Funcionario funcionarios[], int numFuncionarios, enum Departamento departamento) {
    float somaSalarios = 0.0;
    int count = 0;

    for (int i = 0; i < numFuncionarios; i++) {
        if (funcionarios[i].departamento == departamento) {
            somaSalarios += funcionarios[i].salario;
            count++;
        }
    }

    // Evitar a divisão por zero
    if (count > 0) {
        return somaSalarios / count;
    } else {
        return 0.0;
    }
}

int main() {
    struct Funcionario funcionarios[10];

    for (int i = 0; i < 10; i++) {
        printf("Digite o nome do funcionário %d: ", i + 1);
        fgets(funcionarios[i].nome, sizeof(funcionarios[i].nome), stdin);
        funcionarios[i].nome[strcspn(funcionarios[i].nome, "\n")] = '\0';  // Remover a quebra de linha do final

        printf("Digite o departamento do funcionário %d (TI, Vendas, Logistica, Outro): ", i + 1);
        char departamentoStr[20];
        fgets(departamentoStr, sizeof(departamentoStr), stdin);
        departamentoStr[strcspn(departamentoStr, "\n")] = '\0'; 

        // Mapear a string do departamento para o enum
        int j;
        for (j = 0; j < sizeof(departamentos) / sizeof(departamentos[0]); j++) {
            if (strcmp(departamentoStr, departamentos[j]) == 0) {
                funcionarios[i].departamento = j;
                break;
            }
        }

        // Se o departamento não foi encontrado, atribuir "Outro"
        if (j == sizeof(departamentos) / sizeof(departamentos[0])) {
            funcionarios[i].departamento = OUTRO;
        }

        printf("Digite o salário do funcionário %d: ", i + 1);
        scanf("%f", &funcionarios[i].salario);
        getchar(); 
    }

    printf("\nDados dos Funcionários:\n");
    for (int i = 0; i < 10; i++) {
        printf("Funcionário %d:\n", i + 1);
        printf("Nome: %s\n", funcionarios[i].nome);
        printf("Departamento: %s\n", DepartamentoString(funcionarios[i].departamento));
        printf("Salário: R$ %.2f\n", funcionarios[i].salario);
        printf("\n");
    }

    // Calcular e exibir a média salarial de um departamento específico
    char DepartEscolhido[20];
    printf("Digite o departamento para calcular a média salarial: ");
    fgets(DepartEscolhido, sizeof(DepartEscolhido), stdin);
    DepartEscolhido[strcspn(DepartEscolhido, "\n")] = '\0'; 

    enum Departamento departDesejado;
    for (int i = 0; i < sizeof(departamentos) / sizeof(departamentos[0]); i++) {
        if (strcmp(DepartEscolhido, departamentos[i]) == 0) {
            departDesejado = i;
            break;
        }
    }

    if (departDesejado == sizeof(departamentos) / sizeof(departamentos[0])) {
        departDesejado = OUTRO;
    }

    float mediaSalarial = MediaSalarial(funcionarios, 10, departDesejado);
    printf("A média salarial do departamento %s é: R$ %.2f\n", DepartamentoString(departDesejado), mediaSalarial);

    return 0;
}
