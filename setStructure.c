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

//rappresenting item
typedef struct Item
{
  const char* key;
  size_t len;
  struct Item* next;

} Item;

//create item
Item* create_item(const char* key_value, size_t lenght)
{
  Item* new_item = ((Item*)malloc(sizeof(Item)));
  new_item->key = key_value;
  new_item->len = lenght;
  return new_item;
}

void add_item(Item** item_list, const char* key, size_t lenght)
{
  Item* item = create_item(key, lenght);
  item->next = *item_list;
  *item_list = item;
}

void remove_item(Item** item_list, const char* key)
{
  Item* list = *item_list;
  Item* previous_item = NULL;

  while(list != NULL)
  {
    if(strcmp(list->key, key) == 0)
    {
      if(previous_item == NULL)
      {
        *item_list = list->next;
      }
      else
      {
        previous_item->next = list->next;
      }

      free(list);
      return;
    }

    previous_item = list;
    list = list->next;
  }


}

// Function to find an item with the given key in the linked list

int find(const Item* item_list, const char* key)  
{
  const Item* item = item_list;

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


void print_list(Item** item_list)
{
  const Item* item = *item_list;

  while(item != NULL)
  {
    printf("KEY -> %s Lenght -> %zu\n", item->key, item->len);
    item = item->next;
  }
}

//  Function to add a unique key to the linked list

void add_unique_key(Item** item_list, const char* key, size_t key_size)
{
  if(!find(*item_list, key))
  {
    printf("key %s already exists return..\n", key);
    return;
  }

  Item* new_item = create_item(key, key_size);
  new_item->next = *item_list;
  *item_list = new_item;

}


int main(int argc, char *argv[])
{
  Item* itemList = NULL;
  add_item(&itemList, "first", 0);
  add_item(&itemList, "second", 1);
  add_item(&itemList, "third", 2);;

  print_list(&itemList);

  find(itemList, "third");
  find(itemList, "fourth");

  printf("removing item\n");

  remove_item(&itemList, "first");
  print_list(&itemList);
  printf("\n");
  add_unique_key(&itemList, "fift", 3);
  print_list(&itemList);

  free(itemList);

  return EXIT_SUCCESS;
}


