// Address book
// File: addrbk.c
// Compile: gcc addrkk.c -o addrbk
// Run: ./addrbk

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "addrbk.h"

int main(void)
{

  create_address_book();
  menu();
  return 0;
}

// Create address book if it doesn't exist
void create_address_book()
{
  FILE *fp;

  fp = fopen(ADDRBK_FILE, "r");
  if (fp == NULL)
  {
    fp = fopen(ADDRBK_FILE, "w");

    if (fp == NULL)
    {
      printf("Error: %s\n", strerror(errno));
      exit(1);
    }
  }

  fclose(fp);
}

void menu()
{
  printf("\n\n");
  printf("Address Book\n");
  printf("0. Save Address\n");
  printf("1. Find an address\n");
  printf("2. Delete an address\n");
  printf("3. List all addresses\n");
  printf("4. Edit an address\n");
  printf("5. Quit\n");

  printf("\nEnter your choice: ");

  int choice;

  scanf("%d", &choice);

  clear_buffer();

  switch (choice)
  {
  case 0:
    save_address();
    break;
  case 1:
    find_address();
    break;
  case 2:
    delete_address();
    break;
  case 3:
    list_address();
    break;
  case 4:
    edit_address();
    break;
  case 5:
    exit(0);
    break;
  default:
    printf("Invalid choice.\n");
    break;
  }
}

int save_address()
{
  address_book addr;
  read_addr_from_stdin(&addr);

  FILE *fp;
  fp = fopen(ADDRBK_FILE, "a+");

  if (fp == NULL)
  {
    printf("Error opening file\n");
    return -1;
  }

  fprintf(fp, "%s\t%s\n", addr.name, addr.address);
  fclose(fp);
  return 0;
}

int find_address()
{

  char *name;
  printf("Enter name: ");
  read_line(name);

  FILE *fp;
  char buf[100];
  int found = 0;

  fp = fopen(ADDRBK_FILE, "r");
  if (fp == NULL)
  {
    printf("File open error: %s\n", strerror(errno));
    exit(1);
  }

  // fscanf
  while (fscanf(fp, "%s\t%s", buf, buf) != EOF)
  {
    if (strcmp(name, buf) == 0)
    {
      found = 1;
      printf("%s\t%s\n", buf, buf);
    }
  }

  if (found == 0)
  {
    printf("Address not found.\n");
  }

  fclose(fp);
  return 0;
}

int delete_address()
{

  char *name;

  printf("Enter name: ");
  read_line(name);

  FILE *fp;
  FILE *fp2;
  char buf[100];
  int found = 0;

  fp = fopen(ADDRBK_FILE, "r");
  if (fp == NULL)
  {
    printf("File open error: %s\n", strerror(errno));
    exit(1);
  }

  fp2 = fopen("addrbk2.txt", "w");
  if (fp2 == NULL)
  {
    printf("File open error: %s\n", strerror(errno));
    exit(1);
  }

  while (fgets(buf, 100, fp) != NULL)
  {
    if (strstr(buf, name) != NULL)
    {
      found = 1;
      continue;
    }
    fputs(buf, fp2);
  }

  fclose(fp);
  fclose(fp2);

  if (found == 0)
    printf("No record found.\n");

  // remove old file
  remove(ADDRBK_FILE);

  // rename new file
  rename("addrbk2.txt", ADDRBK_FILE);

  return found;
}

int list_address()
{
  FILE *fp;

  fp = fopen(ADDRBK_FILE, "r");
  if (fp == NULL)
  {
    printf("File open error: %s\n", strerror(errno));
    exit(1);
  }

  printf("*****************************************************\n");
  printf("Address Book\n");
  printf("*****************************************************\n");

  printf("Name\t\t\tAddress\n");

  char buf[100];
  while (fgets(buf, 100, fp) != NULL)
  {
    // split the line into name and address
    char *name = strtok(buf, "\t");
    char *address = strtok(NULL, "\t");

    printf("------------------------------------------------------\n");
    printf("%s\t\t\t%s", name, address);
    printf("------------------------------------------------------\n");
  }

  fclose(fp);

  return 0;
}

int edit_address()
{

  address_book addr;
  read_addr_from_stdin(&addr);

  FILE *fp;

  fp = fopen(ADDRBK_FILE, "r");

  if (fp == NULL)
  {
    printf("File open error: %s\n", strerror(errno));
    exit(1);
  }

  char buf[100];
  int found = 0;

  while (fgets(buf, 100, fp) != NULL)
  {
    if (strstr(buf, addr.name) != NULL)
    {
      found = 1;
      break;
    }
  }

  fclose(fp);

  if (found == 0)
  {
    printf("No record found.\n");
    return 0;
  }

  // open file in write mode
  fp = fopen(ADDRBK_FILE, "w");

  if (fp == NULL)
  {
    printf("File open error: %s\n", strerror(errno));
    exit(1);
  }

  // write new address
  fprintf(fp, "%s\t%s\n", addr.name, addr.address);

  fclose(fp);

  return 0;
}

void read_addr_from_stdin(address_book *addr)
{

  printf("Enter name: ");
  read_line(addr->name);

  printf("Enter address: ");
  read_line(addr->address);
}

int read_line(char *str)
{
  // read name and address from stdin
  // up to the newline character or 20 characters

  int i = 0;
  char c;

  while ((c = getchar()) != '\n' && i < 20)
  {
    str[i] = c;
    i++;
  }

  str[i] = '\0';
}

void clear_buffer()
{
  while (getchar() != '\n')
    ;
}