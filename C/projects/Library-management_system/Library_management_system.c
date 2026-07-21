#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
    char title[50];
    char author[20];
    int year;
    float price;
    bool isCheckedOut;
} Book;

Book library[100] = {0};
size_t size = 0;
int title_length = sizeof(library[size].title);
int author_length = sizeof(library[size].author);

void clear_buffer();
void null_terminator(char string[]);
void to_lower(char string[]);
void search_found(char input[], int found[101], int *found_count, bool check);
void add_book();
void print_book();
void search_book();
void checkout_book();
void return_book();
void save_data(Book library[], size_t size);
void load_data(Book library[], size_t *count);

int main()
{
    printf("************************************\n");
    printf("Welcome to library management system\n");
    printf("************************************\n");

    bool running = true;
    char choice = 0;

    typedef enum
    {
        Add = '1',
        List = '2',
        Search = '3',
        Checkout = '4',
        Return = '5',
        Save = '6',
        Load = '7'
    } Choice;

    while (running)
    {
        printf("\nWhat do you want to do:\n1. Add book\n2. List whole library\n3. Search for book\n4. Checkout book\n5. Return book\n6. Save to file\n7. Load existing file\nPress q to quit\n");
        printf("Choice: ");
        scanf("%c", &choice);
        clear_buffer();
        printf("\n");

        switch (choice)
        {
        case Add:
            add_book();
            break;
        case List:
            print_book();
            break;
        case Search:
            search_book();
            break;
        case Checkout:
            checkout_book();
            break;
        case Return:
            return_book();
            break;
        case Save:
            save_data(library, size);
            break;
        case Load:
            load_data(library, &size);
            break;
        case 'q':
        case 'Q':
            running = false;
            break;
        default:
            printf("Invalid input");
            break;
        }
    }

    return 0;
}

void clear_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}
void null_terminator(char string[])
{
    string[strcspn(string, "\n")] = '\0';
}
void to_lower(char string[])
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        string[i] = tolower(string[i]);
    }
}
void search_found(char input[], int found[101], int *found_count, bool check)
{
    for (int i = 0; i < size; i++)
    {
        if (library[i].title[0] == '\0')
            continue;

        char temp[100] = {0};
        strcpy(temp, library[i].title);
        to_lower(temp);
        char *result = strstr(temp, input);

        if (result != NULL && library[i].isCheckedOut == check)
        {
            found[*found_count] = i;
            (*found_count)++;
        }
    }
}
void add_book()
{
    if (size < 100)
    {
        printf("Title: ");
        fgets(library[size].title, title_length, stdin);
        null_terminator(library[size].title);
        printf("Author: ");
        fgets(library[size].author, author_length, stdin);
        null_terminator(library[size].author);
        printf("Year: ");
        scanf("%d", &library[size].year);
        clear_buffer();
        printf("Price :");
        scanf("%f", &library[size].price);
        clear_buffer();
        library[size].isCheckedOut = 0;
        printf("Book %s has been added\n", library[size].title);
        size++;
    }
}
void print_book()
{
    if (size == 0)
    {
        printf("Library is empty\n");
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            printf("%d. %s\n", i + 1, library[i].title);
        }
    }
}
void search_book()
{
    typedef enum
    {
        title = 1,
        author = 2,
        price = 3
    } Find;
    char find_by[15] = {0};
    char find[30] = {0};
    int count = 0;
    printf("Find by (title/author/price): ");
    fgets(find_by, sizeof(find_by), stdin);
    null_terminator(find_by);
    to_lower(find_by);

    if (size == 0)
    {
        printf("Library is empty\n");
        return;
    }

    Find searchBy = 0;

    if (strcmp(find_by, "title") == 0)
    {
        searchBy = 1;
    }
    else if (strcmp(find_by, "author") == 0)
    {
        searchBy = 2;
    }
    else if (strcmp(find_by, "price") == 0)
    {
        searchBy = 3;
    }

    switch (searchBy)
    {
    case title:
        printf("Enter the title of the book: ");
        fgets(find, sizeof(find), stdin);
        null_terminator(find);
        to_lower(find);

        for (int i = 0; i < 100; i++)
        {
            if (library[i].title[0] == '\0')
                continue;

            char temp[100] = {0};
            strcpy(temp, library[i].title);
            to_lower(temp);
            char *result = strstr(temp, find);

            if (result != NULL)
            {
                printf("%d. %s\n", count + 1, library[i].title);
                count++;
            }
        }
        if (!count)
        {
            printf("No book titled '%s' is found\n", find);
        }
        break;

    case author:
        printf("Enter the author of the book: ");
        fgets(find, sizeof(find), stdin);
        null_terminator(find);
        to_lower(find);

        for (int i = 0; i < 100; i++)
        {
            if (library[i].title[0] == '\0')
                continue;

            char temp[100] = {0};
            strcpy(temp, library[i].author);
            to_lower(temp);
            char *result = strstr(temp, find);

            if (result != NULL)
            {
                printf("%d. %s\n", count + 1, library[i].title);
                count++;
            }
        }
        if (!count)
        {
            printf("No book by author '%s' is found\n", find);
        }
        break;

    case price:
        char price[10] = {0};
        printf("Enter the price of the book: ");
        fgets(find, sizeof(find), stdin);
        null_terminator(find);
        to_lower(find);

        for (int i = 0; i < 100; i++)
        {
            if (library[i].title[0] == '\0')
                continue;

            snprintf(price, sizeof(price), "%.2f", library[i].price);

            int result = strcmp(price, find);

            if (result == 0)
            {
                printf("%d. %s\n", count + 1, library[i].title);
                count++;
            }
            else
            {
                printf("Book with price %s does not exist", find);
            }
        }
        if (!count)
        {
            printf("No book priced %.2f is found\n", find);
            break;
        }
    default:
        break;
    }
}
void checkout_book()
{
    int found[101] = {0};
    int found_count = 0;
    int choice = 0;
    char title[50] = {0};
    char big_title[50] = {0};
    int title_size = sizeof(title) / sizeof(char);
    printf("Enter the title of the book: ");
    fgets(big_title, title_size, stdin);
    null_terminator(big_title);
    strcpy(title, big_title);
    to_lower(title);

    if (size == 0)
    {
        printf("Library is empty\n");
        return;
    }
    search_found(title, found, &found_count, false);

    if (found_count >= 2)
    {
        for (int f = 0; f < found_count; f++)
        {
            printf("%d. %s\n", f + 1, library[found[f]].title);
        }
        printf("Choose the book: ");
        scanf("%d", &choice);
        int c;
        clear_buffer();
        if (choice > found_count || choice <= 0)
        {
            printf("Choice is not valid\n");
        }
        else if (choice > 0 && choice <= found_count)
        {
            library[found[choice - 1]].isCheckedOut = true;
            printf("Book '%s' is checked out\n", library[found[choice - 1]].title);
        }
    }
    else if (found_count == 1)
    {
        char choice;
        printf("Do you want to checkout '%s'? (Y/N): ", library[found[found_count - 1]].title);
        scanf("%c", &choice);
        clear_buffer();

        if (choice == 'Y' || choice == 'y')
        {
            library[found[found_count - 1]].isCheckedOut = true;
            printf("Book '%s' is checked out\n", library[found[found_count - 1]].title);
        }
        else if (choice == 'N' || choice == 'n')
        {
            return;
        }
        else
        {
            printf("Choice was not valid\n");
        }
    }
    else if (found_count == 0)
    {
        printf("No book titled '%s' is found\n", big_title);
    }
}
void return_book()
{
    int choice = 0;
    int checkedOut_book[101] = {0};
    int checkedOut_count = 0;
    char book_name[50] = {0};
    int length_title = sizeof(book_name) / sizeof(char);
    char lowercase_name[50] = {0};
    char temp[50] = {0};
    printf("Enter the name of book: ");
    fgets(book_name, length_title, stdin);
    null_terminator(book_name);
    strcpy(lowercase_name, book_name);
    to_lower(lowercase_name);

    if (size == 0)
    {
        printf("Library is empty\n");
        return;
    }

    search_found(lowercase_name, checkedOut_book, &checkedOut_count, true);

    if (checkedOut_count >= 2)
    {
        for (int i = 0; i < checkedOut_count; i++)
        {
            printf("%d. %s", i + 1, library[checkedOut_book[i]].title);
        }
        printf("Choose the book: ");
        scanf("%d", &choice);
        int c;
        clear_buffer();

        if (choice < 1 || choice > checkedOut_count)
        {
            printf("Option is not valid\n");
        }
        else if (choice > 0 && choice <= checkedOut_count)
        {
            library[checkedOut_book[choice - 1]].isCheckedOut = false;
            printf("Book '%s' is returned\n", library[checkedOut_book[choice - 1]].title);
        }
    }
    else if (checkedOut_count == 1)
    {
        char choice;
        printf("Do you want to return book '%s'? (Y/N): ", library[checkedOut_book[0]].title);
        scanf("%c", &choice);
        clear_buffer();

        if (choice == 'Y' || choice == 'y')
        {
            library[checkedOut_book[0]].isCheckedOut = false;
            printf("Book '%s' is returned\n", library[checkedOut_book[0]].title);
        }
        else if (choice == 'N' || choice == 'n')
        {
            return;
        }
        else
        {
            printf("Choice %c was not valid\n", choice);
        }
    }
    else if (checkedOut_count == 0)
    {
        printf("Book '%s' is not found\n", book_name);
    }
}
void save_data(Book library[], size_t size)
{
    FILE *file = fopen("book_library.csv", "w");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%s,%s,%d,%.2f,%d\n",
                library[i].title,
                library[i].author,
                library[i].year,
                library[i].price,
                library[i].isCheckedOut);
    }
    fclose(file);
    printf("Saved %d books into file\n", size);
}
void load_data(Book library[], size_t *count)
{
    FILE *file = fopen("book_library.csv", "r");

    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    *count = 0;
    while (fscanf(file, "%99[^,],%99[^,],%d,%f,%d\n",
                  library[*count].title,
                  library[*count].author,
                  &library[*count].year,
                  &library[*count].price,
                  &library[*count].isCheckedOut) == 5)
    {
        (*count)++;

        if ((*count) >= 100)
            break;
    }

    fclose(file);
}