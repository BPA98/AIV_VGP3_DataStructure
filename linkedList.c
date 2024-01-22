#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define EXIT_SUCCESS 0

typedef struct Node
{
  int32_t data;
  struct Node* next;
}Node;


struct Node* create_node(int32_t data)
{
  struct Node* new_node = ((struct Node*)malloc(sizeof(struct Node)));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

void add_node(Node** first, Node* new)
{
  if(*first == NULL)
  {
    *first = new;
  }
  else
  {
    Node* current = *first;
    while(current->next != NULL)
    {
      current = current->next;
    }
    current->next = new;
  }
}

void remove_node(Node** first, int32_t target)
{
  Node* current = *first;
  Node* previous_node = NULL;

  while(current != NULL && current->data != target)
  {
    previous_node = current;
    current = current->next;
  }

  if(current != NULL)
  {
    if(previous_node == NULL)
    {
      *first = current->next;
    }
    else
    {
      previous_node->next = current->next;
    }

    free(current);
  }
}

void reverse_list(Node** node)
{
  Node* previous_node, *current_node, *next_node; 
  previous_node = NULL;
  current_node = *node;

  while(current_node != NULL)
  {
    next_node = current_node->next;
    current_node->next = previous_node;
    previous_node = current_node;
    current_node = next_node;
  }

  *node = previous_node;
}

static void print_list(Node* node)
{
  Node* current = node;

  while(node != NULL)
  {
    printf("%d -> " ,node->data);
    node = node->next;
  }

  printf("NULL\n");
}

int main(int argc, char *argv[])
{
  Node* node_list = NULL;

  Node* first_node = create_node(1);
  add_node(&node_list, first_node);

  Node* second_node = create_node(2);
  add_node(&node_list, second_node);

  Node* third_node = create_node(3);
  add_node(&node_list, third_node);

  print_list(node_list);

  remove_node(&node_list, 2);

  print_list(node_list);

  printf("reversing..\n");

  reverse_list(&node_list);

  print_list(node_list);

  free(first_node);
  free(second_node);
  free(third_node);
  free(node_list);

  return EXIT_SUCCESS;
}


