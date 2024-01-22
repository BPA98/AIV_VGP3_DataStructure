#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define EXIT_SUCCESS 0

typedef struct Node
{
  int32_t data;
  struct Node* next;
  struct Node* previous;
}Node;

Node* create_node(int32_t data)
{
  Node* new_node = ((Node*)malloc(sizeof(Node)));
  new_node->data = data;
  new_node->next = NULL;
  new_node->previous = NULL;

  return new_node;
}

void add_node(Node** first ,Node* new_node)
{
  if (*first== NULL)
  {
    *first = new_node;
  }
  else
  {
    Node* node = *first;
    while(node->next != NULL)
    {
      node = node->next;
    }
    node->next = new_node;
    new_node->previous = node;
  }
}

void remove_node(Node** origin, int32_t data)
{
  Node* node_to_remove = *origin;

  //finding the node desired throught while loop
  while(node_to_remove != NULL && node_to_remove->data != data)
  {
    node_to_remove = node_to_remove->next;
  }

  //if found
  if(node_to_remove != NULL)
  {
    if(node_to_remove ->previous != NULL)
    {
      node_to_remove->previous->next = node_to_remove->next;
    }
    else
    {
      *origin = node_to_remove;
    }

    if(node_to_remove->next != NULL)
    {
      node_to_remove->next->previous = node_to_remove->previous;
    }

    free(node_to_remove);
  }

}

void push_node_after(Node* previous_node, Node* new_node)
{
  if(previous_node == NULL)
  {
    return; //no use
  }
  
  new_node->next = previous_node->next; //adds the new node after the previous one
  new_node->previous = previous_node; //set the pointer to the previous node

  if(previous_node->next != NULL)
  {
    previous_node->next->previous = new_node;
  }

  previous_node->next = new_node;
}

void push_node_before(Node** first, Node* next_node, Node* node_to_push)
{
  if(next_node == NULL)
  {
    return;
  }

  node_to_push->next = next_node;
  node_to_push->previous = next_node->previous;

  if(next_node->previous == NULL)
  {
    next_node->previous->next = node_to_push;
  }
  else
  {
    *first = node_to_push;
  }
  next_node->previous = node_to_push;
}


void print_list(Node* node_list)
{
  Node* node = node_list;
  while(node != NULL)
  {
    printf("%d -> ", node->data);
    node = node->next;
  }
  printf("done");

  printf("\n");

  node = node_list;

  while(node->next != NULL)
  {
    node = node->next;
  }
  while(node != NULL)
  {
    printf("%d -> ", node->data);
    node = node->previous;
  }

  printf("done \n");
}

int main(int argc, char *argv[])
{
  Node* a = create_node(1);
  Node* b = create_node(2);
  Node* c = create_node(3);
  Node* d = create_node(4);

  Node* node_list = NULL;
  add_node(&node_list, a);
  add_node(&node_list, b);
  add_node(&node_list, c);
  add_node(&node_list, d);

  print_list(node_list);

  printf("remove b node \n");

  remove_node(&node_list, 2); //removing b node

  print_list(node_list);

  printf("\n");
  printf("push node after list \n");

  Node* e = create_node(5);
  Node* node_e_to_list = node_list->next->next;
  push_node_after(node_e_to_list, e);
  print_list(node_list);

  printf("\npush node before\n");
  Node* f = create_node(6);

  Node* push_f_to_list = node_list->next->next;
  push_node_before(&node_list, push_f_to_list, f);
  print_list(node_list);

  free(a); free(b); free(c); free(d); free(e); free(f);
  free(node_list);

  return EXIT_SUCCESS;
}
