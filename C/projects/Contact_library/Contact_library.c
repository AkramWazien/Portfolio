#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
        char *name;
        char *phone;
        char *email;
} Contact;

void clear_buffer();
void null_terminator(char *name);
void toLowerCase(char *name);
void searchForFound(size_t **founds, Contact **contacts, size_t count, char *inputBuffer, size_t *found_count, size_t *found_capacity);
void add_contact(Contact **contacts, size_t *count, size_t *capacity);
void list_contact(Contact **contacts, size_t count);
void search_contact(Contact **contacts, size_t count);
void delete_contact(Contact **contacts, size_t *count, size_t *capacity);
void load_file(Contact **contacts, size_t *count, size_t *capacity);
void save_file(Contact **contacts, size_t count);

int main()
{
        Contact *contacts = NULL;
        size_t count = 0;
        size_t capacity = 0;
        bool running = true;
        char choice;

        typedef enum
        {
                Add = '1',
                List = '2',
                Search = '3',
                Delete = '4',
                Load = '5',
                Save = '6'
        } Action;

        // Welcome sentence
        printf("*******************\n");
        printf("Contact library\n");
        printf("*******************\n");

        while (running)
        {
                // Giving choice
                printf("Choose action:\n");
                printf("1. Add new contact\n2. List all contacts\n3. Search contact\n4. Delete contact\n5. Load file\n6. Save file\nPress q to quit\n");
                scanf(" %c", &choice);
                clear_buffer();

                // All of the action available
                switch (choice)
                {
                case Add:
                        add_contact(&contacts, &count, &capacity);
                        break;
                case List:
                        list_contact(&contacts, count);
                        break;
                case Search:
                        search_contact(&contacts, count);
                        break;
                case Delete:
                        delete_contact(&contacts, &count, &capacity);
                        break;
                case Load:
                        load_file(&contacts, &count, &capacity);
                        break;
                case Save:
                        save_file(&contacts, count);
                        break;
                case 'q':
                case 'Q':
                        running = false;
                        break;
                default:
                        printf("Invalid choice\n");
                        break;
                }
        }

        if (contacts != NULL)
        {
                for (int i = 0; i < count; i++)
                {
                        free(contacts[i].name);
                        free(contacts[i].email);
                        free(contacts[i].phone);
                }
                free(contacts);
        }

        return 0;
}

void clear_buffer()
{
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
                ;
}
void null_terminator(char *name)
{
        name[strcspn(name, "\n")] = '\0';
}
void toLowerCase(char *name)
{
        for (int i = 0; name[i] != '\0'; i++)
        {
                name[i] = tolower(name[i]);
        }
}
void searchForFound(size_t **founds, Contact **contacts, size_t count, char *inputBuffer, size_t *found_count, size_t *found_capacity)
{
        toLowerCase(inputBuffer);
        for (size_t i = 0; i < count; i++)
        {
                size_t nameLength = strlen((*contacts)[i].name) + 1;
                char *temp = (char *)malloc(nameLength * sizeof(char));

                if (temp == NULL)
                {
                        printf("Failed to allocate memory for %s\n", (*contacts)[i].name);
                        continue;
                }
                strcpy(temp, (*contacts)[i].name);
                toLowerCase(temp);

                if (strstr(temp, inputBuffer) != NULL)
                {
                        if (*found_count == *found_capacity)
                        {
                                size_t new_capacity = (*found_capacity == 0) ? 4 : *found_capacity * 2;
                                size_t *new_memory = (size_t *)realloc(*founds, new_capacity * sizeof(size_t));
                                if (new_memory == NULL)
                                {
                                        printf("Memory allocation failed\n");
                                        free(temp);
                                        temp = NULL;
                                        return;
                                }
                                *founds = new_memory;
                                *found_capacity = new_capacity;
                        }
                        (*founds)[*found_count] = i;
                        (*found_count)++;
                }

                free(temp);
                temp = NULL;
        }
}
void add_contact(Contact **contacts, size_t *count, size_t *capacity)
{
        char inputBuffer[100];
        int bufferSize = sizeof(inputBuffer) / sizeof(char);

        // Checking if the array fits
        if (*count == *capacity)
        {
                size_t new_capacity = (*capacity == 0) ? 4 : *capacity * 2;
                Contact *new_memory = (Contact *)realloc(*contacts, new_capacity * sizeof(Contact));
                if (new_memory == NULL)
                {
                        printf("Memory allocation failed\n");
                        return;
                }
                *contacts = new_memory;
                *capacity = new_capacity;
        }

        Contact *current_contact = &((*contacts)[*count]);

        // Adding name
        printf("Name: ");
        fgets(inputBuffer, bufferSize, stdin);
        null_terminator(inputBuffer);
        size_t inputLength = strlen(inputBuffer) + 1;
        current_contact->name = (char *)malloc(inputLength * sizeof(char));
        if (current_contact->name == NULL)
        {
                printf("Failed to allocate memory for name\n");
                return;
        }
        strcpy(current_contact->name, inputBuffer);

        // Adding phone number
        printf("Phone number: ");
        fgets(inputBuffer, bufferSize, stdin);
        null_terminator(inputBuffer);
        inputLength = strlen(inputBuffer) + 1;
        current_contact->phone = (char *)malloc(inputLength * sizeof(char));
        if (current_contact->phone == NULL)
        {
                printf("Failed to allocate memory for phone number\n");
                return;
        }
        strcpy(current_contact->phone, inputBuffer);

        // Adding email
        printf("Email: ");
        fgets(inputBuffer, bufferSize, stdin);
        null_terminator(inputBuffer);
        inputLength = strlen(inputBuffer) + 1;
        current_contact->email = (char *)malloc(inputLength * sizeof(char));
        if (current_contact->email == NULL)
        {
                printf("Failed to allocate memory for email\n");
                return;
        }
        strcpy(current_contact->email, inputBuffer);
        (*count)++;
        printf("\n");
}
void list_contact(Contact **contacts, size_t count)
{
        if (count == 0)
        {
                printf("Library is empty\n");
                return;
        }
        for (size_t i = 0; i < count; i++)
        {
                printf("%zu. %s | %s | %s\n", i + 1, (*contacts)[i].name, (*contacts)[i].phone, (*contacts)[i].email);
        }
        printf("\n");
}
void search_contact(Contact **contacts, size_t count)
{
        char inputBuffer[100];
        size_t size = sizeof(inputBuffer) / sizeof(char);
        size_t found_count = 0;
        size_t found_capacity = 0;
        size_t *founds = NULL;

        if (count == 0)
        {
                printf("Library is empty\n");
                return;
        }

        printf("Name: ");
        fgets(inputBuffer, size, stdin);
        null_terminator(inputBuffer);

        searchForFound(&founds, contacts, count, inputBuffer, &found_count, &found_capacity);

        if (found_count == 0)
        {
                printf("No contact %s found\n", inputBuffer);
                return;
        }
        else
        {
                for (size_t i = 0; i < found_count; i++)
                {
                        printf("%zu. %s\n", i + 1, (*contacts)[founds[i]].name);
                }
        }
        printf("\n");
        free(founds);
        founds = NULL;
}
void delete_contact(Contact **contacts, size_t *count, size_t *capacity)
{
        char inputBuffer[100];
        size_t size = sizeof(inputBuffer) / sizeof(char);
        size_t found_count = 0;
        size_t found_capacity = 0;
        size_t *founds = NULL;

        if (count == 0)
        {
                printf("Library is empty\n");
                return;
        }

        printf("Name: ");
        fgets(inputBuffer, size, stdin);
        null_terminator(inputBuffer);

        searchForFound(&founds, contacts, *count, inputBuffer, &found_count, &found_capacity);

        if (found_count == 0)
        {

                printf("No contact %s found\n", inputBuffer);
                return;
        }
        else if (found_count == 1)
        {
                char choice;
                Contact found_person = (*contacts)[founds[0]];
                printf("Delete %s? (Y/N): ", found_person.name);
                choice = getchar();
                clear_buffer();

                if (choice == 'N' || choice == 'n')
                {
                        return;
                }
                else if (choice == 'Y' || choice == 'y')
                {
                        free(found_person.name);
                        free(found_person.phone);
                        free(found_person.email);

                        for (int i = founds[0]; i < *count - 1; i++)
                        {
                                (*contacts)[i] = (*contacts)[i + 1];
                        }
                        (*count)--;

                        if ((*count) < 0)
                        {
                                free(*contacts);
                                *capacity = 0;
                                *contacts = NULL;
                        }

                        if ((*count) <= (*capacity) / 2)
                        {
                                (*capacity) /= 2;
                                Contact *temp = (Contact *)realloc(*contacts, (*capacity) * sizeof(Contact));

                                if (temp == NULL)
                                {
                                        printf("Memory reallocation failed\n");
                                        return;
                                }

                                *contacts = temp;
                        }
                }
        }
        else
        {
                char choice;
                for (size_t i = 0; i < found_count; i++)
                {
                        printf("%zu. %ss\n", i + 1, (*contacts)[founds[i]].name);
                }
                printf("\nChoice #: ");
                scanf("%c", &choice);
                clear_buffer();

                int result = isdigit((unsigned char)choice);

                if (result == 0)
                {
                        printf("Invalid input\n");
                        return;
                }
                else if (choice >= '1' && choice <= '0' + found_count)
                {
                        Contact found_person = (*contacts)[founds[choice - 1]];
                        free(found_person.name);
                        free(found_person.phone);
                        free(found_person.email);

                        for (int i = founds[0]; i < *count - 1; i++)
                        {
                                (*contacts)[i] = (*contacts)[i + 1];
                        }
                        (*count)--;

                        if ((*count) < 0)
                        {
                                free(*contacts);
                                *capacity = 0;
                                *contacts = NULL;
                        }

                        if ((*count) <= (*capacity) / 2)
                        {
                                (*capacity) /= 2;
                                Contact *temp = (Contact *)realloc(*contacts, (*capacity) * sizeof(Contact));

                                if (temp == NULL)
                                {
                                        printf("Memory reallocation failed\n");
                                        return;
                                }

                                *contacts = temp;
                        }
                }
        }
}
void load_file(Contact **contacts, size_t *count, size_t *capacity)
{
        FILE *file = fopen("contact_library.csv", "r");

        if (file == NULL)
        {
                printf("Error: Fail to open file\n");
                return;
        }

        char name[100];
        char phone[20];
        char email[100];

        while (fscanf(file, "%99[^,],%19[^,],%99[^\n]\n", name, phone, email) == 3)
        {
                if (*count == *capacity)
                {
                        size_t new_capacity = (*capacity == 0) ? 4 : *capacity * 2;
                        Contact *tmp_ptr = (Contact *)realloc(*contacts, new_capacity * sizeof(Contact));
                        if (tmp_ptr == NULL)
                        {
                                printf("Memory allocation failed!\n");
                                fclose(file);
                                return;
                        }

                        *capacity = new_capacity;
                        *contacts = tmp_ptr;
                }

                (*contacts)[*count].name = (char *)malloc(strlen(name) + 1);
                if ((*contacts)[*count].name == NULL)
                {
                        printf("Memory allocation failed for name\n");
                        fclose(file);
                        return;
                }
                strcpy((*contacts)[*count].name, name);

                (*contacts)[*count].phone = (char *)malloc(strlen(phone) + 1);
                if ((*contacts)[*count].phone == NULL)
                {
                        printf("Memory allocation failed for phone\n");
                        fclose(file);
                        return;
                }
                strcpy((*contacts)[*count].phone, phone);

                (*contacts)[*count].email = (char *)malloc(strlen(email) + 1);
                if ((*contacts)[*count].email == NULL)
                {
                        printf("Memory allocation failed for email\n");
                        fclose(file);
                        return;
                }
                strcpy((*contacts)[*count].email, email);
                (*count)++;
        }
        printf("File loaded successfully\n");
        fclose(file);
}
void save_file(Contact **contacts, size_t count)
{
        FILE *file = fopen("contact_library.csv", "w");

        if (file == NULL)
        {
                printf("Error: Fail to open file\n");
                return;
        }

        for (size_t i = 0; i < count; i++)
        {
                fprintf(file, "%s,%s,%s\n", (*contacts)[i].name, (*contacts)[i].phone, (*contacts)[i].email);
        }
        printf("File saved successfully\n");

        fclose(file);
}