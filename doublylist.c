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

Node* CreateNode(int32_t data)
{
  Node* newNode = ((Node*)malloc(sizeof(Node)));
  newNode->data = data;
  newNode->next = NULL;
  newNode->previous = NULL;

  return newNode;
}

void AddNode(Node** first ,Node* newNode)
{
  if (*first== NULL)
  {
    *first = newNode;
  }
  else
  {
    Node* node = *first;
    while(node->next != NULL)
    {
      node = node->next;
    }
    node->next = newNode;
    newNode->previous = node;
  }
}

void RemoveNode(Node** origin, int32_t data)
{
  Node* nodeToRemove = *origin;

  //finding the node desired throught while loop
  while(nodeToRemove != NULL && nodeToRemove->data != data)
  {
    nodeToRemove = nodeToRemove->next;
  }

  //if found
  if(nodeToRemove != NULL)
  {
    if(nodeToRemove ->previous != NULL)
    {
      nodeToRemove->previous->next = nodeToRemove->next;
    }
    else
    {
      *origin = nodeToRemove;
    }

    if(nodeToRemove->next != NULL)
    {
      nodeToRemove->next->previous = nodeToRemove->previous;
    }

    free(nodeToRemove);
  }

}

void PushNodeAfter(Node* previousNode, Node* newNode)
{
  if(previousNode == NULL)
  {
    return; //no use
  }
  
  newNode->next = previousNode->next; //adds the new node after the previous one
  newNode->previous = previousNode; //set the pointer to the previous node

  if(previousNode->next != NULL)
  {
    previousNode->next->previous = newNode;
  }

  previousNode->next = newNode;
}

void PushNodeBefore(Node** first, Node* nextNode, Node* nodeToPush)
{
  if(nextNode == NULL)
  {
    return;
  }

  nodeToPush->next = nextNode;
  nodeToPush->previous = nextNode->previous;

  if(nextNode->previous == NULL)
  {
    nextNode->previous->next = nodeToPush;
  }
  else
  {
    *first = nodeToPush;
  }
  nextNode->previous = nodeToPush;
}


static void PrintList(Node* nodeList)
{
  Node* node = nodeList;
  while(node != NULL)
  {
    printf("%d -> ", node->data);
    node = node->next;
  }
  printf("done");

  printf("\n");

  node = nodeList;

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
  Node* a = CreateNode(1);
  Node* b = CreateNode(2);
  Node* c = CreateNode(3);
  Node* d = CreateNode(4);

  Node* nodeList = NULL;
  AddNode(&nodeList, a);
  AddNode(&nodeList, b);
  AddNode(&nodeList, c);
  AddNode(&nodeList, d);

  PrintList(nodeList);

  printf("remove b node \n");

  RemoveNode(&nodeList, 2); //removing b node

  PrintList(nodeList);

  printf("\n");
  printf("push node after list \n");

  Node* e = CreateNode(5);
  Node* nodeEToList = nodeList->next->next;
  PushNodeAfter(nodeEToList, e);
  PrintList(nodeList);

  printf("\npush node before\n");
  Node* f = CreateNode(6);

  Node* pushFtoList = nodeList->next->next;
  PushNodeBefore(&nodeList, pushFtoList, f);
  PrintList(nodeList);

  return EXIT_SUCCESS;
}
