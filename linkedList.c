#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define EXIT_SUCCESS 0

typedef struct Node
{
  int32_t data;
  struct Node* next;
}Node;


struct Node* CreateNode(int32_t data)
{
  struct Node* newNode = ((struct Node*)malloc(sizeof(struct Node)));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void AddNode(Node** first, Node* new)
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

void RemoveNode(Node** first, int32_t target)
{
  Node* current = *first;
  Node* previousNode = NULL;

  while(current != NULL && current->data != target)
  {
    previousNode = current;
    current = current->next;
  }

  if(current != NULL)
  {
    if(previousNode == NULL)
    {
      *first = current->next;
    }
    else
    {
      previousNode->next = current->next;
    }

    free(current);
  }
}

void ReverseList(Node** node)
{
  Node* previousNode, *currentNode, *nextNode; 
  previousNode = NULL;
  currentNode = *node;

  while(currentNode != NULL)
  {
    nextNode = currentNode->next;
    currentNode->next = previousNode;
    previousNode = currentNode;
    currentNode = nextNode;
  }

  *node = previousNode;
}

static void PrintList(Node* node)
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
  Node* nodeList = NULL;

  Node* firstNode = CreateNode(1);
  AddNode(&nodeList, firstNode);

  Node* secondNode = CreateNode(2);
  AddNode(&nodeList, secondNode);

  Node* thirdNode = CreateNode(3);
  AddNode(&nodeList, thirdNode);

  PrintList(nodeList);

  RemoveNode(&nodeList, 2);

  PrintList(nodeList);

  printf("reversing..\n");

  ReverseList(&nodeList);

  PrintList(nodeList);

  return EXIT_SUCCESS;
}


