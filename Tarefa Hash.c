/* 
Construa uma aplicação que permita a leitura de números inteiros do teclado e a inserção dos mesmos em uma estrutura Hash de comprimento 7. A função de transformação de chave a ser utilizada é a mesma dos exemplos passados em sala de aula: h(x) = x mod 7.
  
Sua aplicação deve possuir também um procedimento para exibir o conteúdo do Hash, após o seu preenchimento. Sugestão para criação do Hash: crie um vetor de "Listas" de tamanho 7, cada nodo das listas deve guardar um número inteiro e um ponteiro para o próximo elemento da lista. 
*/

#include <stdio.h>
#include <stdlib.h>

#define HASH_KEY 7

// Estrutura para um nó da lista
typedef struct node {
  int value;
  struct node *next;
} Node;

// Estrutura para o Hash
typedef struct Hash {
  Node **buckets; // Vetor de listas (buckets)
  int size;    // Tamanho do Hash (7)
} Hash;

// Função de hash
int hashFunction(int key) {
  return key % HASH_KEY;
}

// Cria um novo nó
Node *createNode(int value) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

// Cria o Hash
Hash *createHash(int size){
  Hash *hash = (Hash *)malloc(sizeof(Hash));
  hash->size = size;
  hash->buckets = (Node **)malloc(size * sizeof(Node *));
  for (int i = 0; i < size; i++){
    hash->buckets[i] = NULL;
  }
  return hash;
}

// Insere um elemento no Hash
void insertHash(Hash *hash, int value) {
  int index = hashFunction(value);

  // Insere na lista encadeada do índice
  Node *newNode = createNode(value);
  newNode->next = hash->buckets[index];
  hash->buckets[index] = newNode;
}

// Exibe o conteúdo do Hash
void displayHash(Hash *hash) {
  for (int i = 0; i < hash->size; i++) {
    printf("Índice %d: ", i);

    Node *current = hash->buckets[i];
    while (current != NULL) {
      printf("%d ", current->value);
      current = current->next;
    }
    printf("\n");
  }
}

// Função principal --------------------------------------------------------
int main() {
  Hash *hash = createHash(HASH_KEY);
  
  // Lê números inteiros do teclado e insere no Hash
  int value;
  printf("Digite números inteiros (0 para sair): ");
  while (scanf("%d", &value) && value != 0) {
    insertHash(hash, value);
  }

  // Exibe o conteúdo do Hash
  printf("\nConteúdo do Hash:\n");
  displayHash(hash);

  // Libera memória alocada
  for (int i = 0; i < hash->size; i++) {
    Node *current = hash->buckets[i];
    while (current != NULL) {
      Node *next = current->next;
      free(current);
      current = next;
    }
  }
  free(hash->buckets);

  return 0;
}