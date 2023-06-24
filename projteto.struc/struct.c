#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

#define MaxUsers 3

typedef struct {
  int id;
  char nome[20];
  double altura;
  int vacinado;
  char email[50];
  char sexo[15];
} Usuario;

void cadastrarUsuario(Usuario usuarios[], int *numUsuarios) {
  if (*numUsuarios >= MaxUsers) {
    printf("Número máximo de usuários atingido.\n");
    return;
  }

  usuarios[*numUsuarios].id = rand() % 3 + 1; // Gera um ID aleatório entre 1 e 3
  printf("ID gerado: %d\n", usuarios[*numUsuarios].id);

  printf("Digite o nome: ");
  scanf("%s", usuarios[*numUsuarios].nome);

  do {
    printf("Digite o sexo (feminino, masculino ou indiferente): ");
    scanf("%s", usuarios[*numUsuarios].sexo);

    if (strcmp(usuarios[*numUsuarios].sexo, "feminino") == 0 || strcmp(usuarios[*numUsuarios].sexo, "masculino") == 0 || strcmp(usuarios[*numUsuarios].sexo, "indiferente") == 0) {
      printf("Sexo válido.\n");
    } else {
      printf("Sexo inválido. Digite novamente.\n");
    }
  } while (!(strcmp(usuarios[*numUsuarios].sexo, "feminino") == 0 || strcmp(usuarios[*numUsuarios].sexo, "masculino") == 0 || strcmp(usuarios[*numUsuarios].sexo, "indiferente") == 0));

  do {
    printf("Digite a altura: ");
    scanf("%lf", &usuarios[*numUsuarios].altura);

    if (usuarios[*numUsuarios].altura >= 1 && usuarios[*numUsuarios].altura <= 2) {
      printf("Altura válida.\n");
    } else {
      printf("Altura inválida. Digite novamente.\n");
    }
  } while (!(usuarios[*numUsuarios].altura >= 1 && usuarios[*numUsuarios].altura <= 2));

  do {
    printf("Digite 1 se você estiver vacinado ou 2 se não estiver: ");
    scanf("%d", &usuarios[*numUsuarios].vacinado);

    switch (usuarios[*numUsuarios].vacinado) {
    case 1:
      printf("Você está vacinado!\n");
      break;
    case 2:
      printf("Você não está vacinado.\n");
      break;
    default:
      printf("Opção inválida. Digite novamente.\n");
      break;
    }
  } while (usuarios[*numUsuarios].vacinado != 1 && usuarios[*numUsuarios].vacinado != 2);

  do {
    printf("Digite o seu email: ");
    scanf("%s", usuarios[*numUsuarios].email);

    // Verificar se o caractere '@' está presente no email
    if (strstr(usuarios[*numUsuarios].email, "@") == NULL) {
      printf("Email inválido. Digite novamente.\n");
    } else {
      printf("Email válido.\n");
      break; // Sai do loop quando o email for válido
    }
  } while (1);

  (*numUsuarios)++;
  printf("Usuário cadastrado com sucesso!\n");
}

void buscarUsuario(Usuario usuarios[], int numUsuarios) {
  int i, idBusca;
  printf("Digite o ID do usuário que deseja buscar: ");
  scanf("%d", &idBusca);

  for (i = 0; i < numUsuarios; i++) {
    if (idBusca == usuarios[i].id) {
      printf("----- Informações do Usuário -----\n");
      printf("ID: %d\n", usuarios[i].id);
      printf("Nome: %s\n", usuarios[i].nome);
      printf("Sexo: %s\n", usuarios[i].sexo);
      printf("Altura: %lf\n", usuarios[i].altura);
      printf("E-mail: %s\n", usuarios[i].email);
      printf("Vacina: %d\n", usuarios[i].vacinado);
      return;
    }
  }

  printf("Usuário não encontrado.\n");
}

void deletarUsuario(Usuario usuarios[], int *numUsuarios) {
  int i, idDeletar;
  printf("Digite o ID do usuário que deseja deletar: ");
  scanf("%d", &idDeletar);

  for (i = 0; i < *numUsuarios; i++) {
    if (idDeletar == usuarios[i].id) {
      // Deslocar os usuários para preencher o espaço do usuário deletado
      for (int j = i; j < *numUsuarios - 1; j++) {
        usuarios[j] = usuarios[j + 1];
      }

      (*numUsuarios)--;
      printf("Usuário deletado com sucesso!\n");
      return;
    }
  }

  printf("Usuário não encontrado.\n");
}

void fazerBackup(Usuario usuarios[], int numUsuarios, Usuario backupUsuarios[]) {
  int i;
  for (i = 0; i < numUsuarios; i++) {
    backupUsuarios[i] = usuarios[i];
  }

  printf("Backup realizado com sucesso!\n");
}

void restaurarBackup(Usuario usuarios[], int *numUsuarios, Usuario backupUsuarios[]) {
  int i;
  for (i = 0; i < *numUsuarios; i++) {
    usuarios[i] = backupUsuarios[i];
  }

  printf("Backup restaurado com sucesso!\n");
}

void imprimirUsuarios(Usuario usuarios[], int numUsuarios) {
  if (numUsuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  printf("----- Usuários Cadastrados -----\n");
  for (int i = 0; i < numUsuarios; i++) {
    printf("ID: %d\n", usuarios[i].id);
    printf("Nome: %s\n", usuarios[i].nome);
    printf("Sexo: %s\n", usuarios[i].sexo);
    printf("Altura: %lf\n", usuarios[i].altura);
    printf("E-mail: %s\n", usuarios[i].email);
    printf("Vacina: %d\n", usuarios[i].vacinado);
    printf("-----------------------------\n");
  }
}

void limparTela() {
  system(CLEAR_SCREEN);
}

int main() {
  Usuario usuarios[MaxUsers];
  Usuario backupUsuarios[MaxUsers];
  int numUsuarios = 0;

  int opcao;

  srand(time(NULL));

  do {
    printf("----- Sistema de Cadastro -----\n");
    printf("1 - Cadastrar usuário\n");
    printf("2 - Buscar usuário\n");
    printf("3 - Deletar usuário\n");
    printf("4 - Fazer backup\n");
    printf("5 - Restaurar backup\n");
    printf("6 - Imprimir usuários\n");
    printf("7 - Limpar tela\n");
    printf("0 - Sair\n");
    printf("Digite a opção desejada: ");
    scanf("%d", &opcao);

    limparTela(); // Limpa a tela antes de exibir o resultado

    switch (opcao) {
    case 1:
      cadastrarUsuario(usuarios, &numUsuarios);
      break;
    case 2:
      buscarUsuario(usuarios, numUsuarios);
      break;
    case 3:
      deletarUsuario(usuarios, &numUsuarios);
      break;
    case 4:
      fazerBackup(usuarios, numUsuarios, backupUsuarios);
      break;
    case 5:
      restaurarBackup(usuarios, &numUsuarios, backupUsuarios);
      break;
    case 6:
      imprimirUsuarios(usuarios, numUsuarios);
      break;
    case 7:
      limparTela();
      break;
    case 0:
      printf("Encerrando o programa...\n");
      break;
    default:
      printf("Opção inválida. Digite novamente.\n");
      break;
    }

    printf("\n");
  } while (opcao != 0);

  return 0;
}
