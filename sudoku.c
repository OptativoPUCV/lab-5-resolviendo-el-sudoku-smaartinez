#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  for (int k = 0; k < 9 ; k++)
  {
    int column[10] = {0};
    int fila[10] = {0};
    
    for (int j = 0; j < 9; j++)
    {
      if (n-> sudo[k][j] != 0)
      {
        if (fila[n->sudo[k][j]] == 1)
        {
          return 0;
        }
        fila[n->sudo[k][j]] = 1;
      }
      if (n-> sudo[j][k] != 0)
      {
        if (column[n->sudo[j][k]] == 1)
        {
          return 0;
        }
        column[n->sudo[j][k]] = 1;
      }
    }
  }
  for (int k = 0; k < 9 ; k+=3)
  {
    for (int j = 0 ; j < 9 ; j+=3)
    {
      int fila_aux [10] = {0};
      int column_aux [10] = {0};
      for (int i = 0; i < 3; i++)
      {
        for (int z = 0; z < 3 ; z++)
        {
          if (n->sudo[k+i][j+z] != 0)
          {
            if (fila_aux[n->sudo[k+i][j+z]] == 1)
            {
              return 0;
            }
            fila_aux[n->sudo[k+i][j+z]] = 1;
          }
          if (n->sudo[j+z][k+i] != 0)
          {
            if (column_aux[n->sudo[j+z][k+i]] == 1)
            {
              return 0;
            }
            column_aux[n->sudo[j+z][k+i]] = 1;
          }
        }
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n)
{
    List* list=createList();
    for (int k = 0; k < 9; k++)
    {
      for (int j = 0; j < 9; j++)
      {
        if (n->sudo[k][j]== 0)
        {
          for (int numero = 1; numero <= 9; numero++)
          {
            Node *actual = copy(n);
            actual->sudo[k][j] = numero;
            if (is_valid(actual))
            {
              pushBack(list, actual);
            }
          }
          return list;
        }
      }
    }
    return list;
}


int is_final(Node* n)
{
  for (int k = 0; k < 9; k++)
  {
    for (int j = 0 ; j < 9; j++)
    {
      if (n->sudo[k][j] == 0)
      {
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack* stack = createStack();
  push(stack, initial);
  while (!is_empty(stack))
  
  {
    Node* actual = top(stack);
    pop(stack);
    (*cont)++;
    if (is_final(actual))
    {
      return actual;
    }
    List* adj = get_adj_nodes(actual);
    Node* auxiliar = first(adj);
    while (auxiliar != NULL)
    {
      push(stack, auxiliar);
      auxiliar = next(adj);
    }
    free(actual);
    free(adj);
  }
  free(stack);
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/