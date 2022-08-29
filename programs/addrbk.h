#ifndef ADDRBK_H
#define ADDRBK_H
#define ADDRBK_FILE "addrbk.txt"
#define MAX_NAME_LEN 20

typedef struct
{
  char name[MAX_NAME_LEN];
  char address[MAX_NAME_LEN];
} address_book;

int save_address();
int find_address();
int delete_address();
int list_address();
int edit_address();
void menu();
void read_addr_from_stdin(address_book *addr);
int read_line(char *str);
void create_address_book();
void clear_buffer();

#endif /* ADDRBK_H */
