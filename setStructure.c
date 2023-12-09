#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define HASHPAP_SIZE 64
#define HASHMAP_SIZE_LIST 1

#define KEY_FOUND 0
#define KEY_NOT_FOUND 1

typedef struct Item
{
  const char* key;
  size_t len;
  struct Item* next;

} Item;

Item* CreateItem(const char* keyValue, size_t lenght)
{
  Item* newItem = ((Item*)malloc(sizeof(Item)));
  newItem->key = keyValue;
  newItem->len = lenght;
  return newItem;
}

void AddItem(Item** itemList, const char* key, size_t lenght)
{
  Item* item = CreateItem(key, lenght);
  item->next = *itemList;
  *itemList = item;
}

void RemoveItem(Item** itemList, const char* key)
{
  Item* list = *itemList;
  Item* previousItem = NULL;

  while(list != NULL)
  {
    if(strcmp(list->key, key) == 0)
    {
      if(previousItem == NULL)
      {
        *itemList = list->next;
      }
      else
      {
        previousItem->next = list->next;
      }

      free(list);
      return;
    }

    previousItem = list;
    list = list->next;
  }


}

int Find(const Item* itemList, const char* key)  
{
  const Item* item = itemList;

  while(item != NULL)
  {
    if(strcmp(item->key, key) == 0)
    {
      //found it
      printf("key found -> %s\n", key);
      return KEY_FOUND;
    }

    item = item->next;
  }

  printf("Key %s -> not found\n", key);
  return KEY_NOT_FOUND;
}


void PrintList(Item** itemList)
{
  const Item* item = *itemList;

  while(item != NULL)
  {
    printf("KEY -> %s Lenght -> %zu\n", item->key, item->len);
    item = item->next;
  }
}

void AddUniqueKey(Item** itemList, const char* key, size_t keySize)
{
  if(!Find(*itemList, key))
  {
    printf("key %s already exists return..\n", key);
    return;
  }

  Item* newItem = CreateItem(key, keySize);
  newItem->next = *itemList;
  *itemList = newItem;

}


int main(int argc, char *argv[])
{
  Item* itemList = NULL;
  AddItem(&itemList, "first", 0);
  AddItem(&itemList, "second", 1);
  AddItem(&itemList, "third", 2);;

  PrintList(&itemList);

  Find(itemList, "third");
  Find(itemList, "fourth");

  printf("removing item\n");

  RemoveItem(&itemList, "first");
  PrintList(&itemList);
  printf("\n");
  AddUniqueKey(&itemList, "fift", 3);
  PrintList(&itemList);

  return EXIT_SUCCESS;
}


