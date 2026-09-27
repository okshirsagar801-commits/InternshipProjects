#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Book
{
    int id;
    char title[100];
    char author[100];
    int issued;
};

struct Member
{
    int id;
    char name[100];
};

struct Book books[MAX];
struct Member members[MAX];

int bookCount = 0;
int memberCount = 0;

void saveBooks()
{
    FILE *fp = fopen("books.dat", "wb");

    if (fp == NULL)
    {
        printf("Error opening book file!\n");
        return;
    }

    fwrite(&bookCount, sizeof(int), 1, fp);
    fwrite(books, sizeof(struct Book), bookCount, fp);

    fclose(fp);
}

void loadBooks()
{
    FILE *fp = fopen("books.dat", "rb");

    if (fp == NULL)
        return;

    fread(&bookCount, sizeof(int), 1, fp);
    fread(books, sizeof(struct Book), bookCount, fp);

    fclose(fp);
}

void saveMembers()
{
    FILE *fp = fopen("members.dat", "wb");

    if (fp == NULL)
    {
        printf("Error opening member file!\n");
        return;
    }

    fwrite(&memberCount, sizeof(int), 1, fp);
    fwrite(members, sizeof(struct Member), memberCount, fp);

    fclose(fp);
}

void loadMembers()
{
    FILE *fp = fopen("members.dat", "rb");

    if (fp == NULL)
        return;

    fread(&memberCount, sizeof(int), 1, fp);
    fread(members, sizeof(struct Member), memberCount, fp);

    fclose(fp);
}

void addBook()
{
    if (bookCount >= MAX)
    {
        printf("Book limit reached!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &books[bookCount].id);

    printf("Enter Book Title: ");
    scanf(" %[^\n]", books[bookCount].title);

    printf("Enter Author Name: ");
    scanf(" %[^\n]", books[bookCount].author);

    books[bookCount].issued = 0;

    bookCount++;

    saveBooks();

    printf("Book added successfully!\n");
}

void displayBooks()
{
    int i;

    if (bookCount == 0)
    {
        printf("No books available.\n");
        return;
    }

    printf("\n----- BOOK RECORDS -----\n");

    for (i = 0; i < bookCount; i++)
    {
        printf("\nBook ID: %d", books[i].id);
        printf("\nTitle: %s", books[i].title);
        printf("\nAuthor: %s", books[i].author);

        if (books[i].issued)
            printf("\nStatus: Issued\n");
        else
            printf("\nStatus: Available\n");
    }
}

void searchBook()
{
    int id, i, found = 0;

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < bookCount; i++)
    {
        if (books[i].id == id)
        {
            printf("\nBook Found!");
            printf("\nID: %d", books[i].id);
            printf("\nTitle: %s", books[i].title);
            printf("\nAuthor: %s\n", books[i].author);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found!\n");
}

void addMember()
{
    if (memberCount >= MAX)
    {
        printf("Member limit reached!\n");
        return;
    }

    printf("Enter Member ID: ");
    scanf("%d", &members[memberCount].id);

    printf("Enter Member Name: ");
    scanf(" %[^\n]", members[memberCount].name);

    memberCount++;

    saveMembers();

    printf("Member added successfully!\n");
}

void displayMembers()
{
    int i;

    if (memberCount == 0)
    {
        printf("No members found.\n");
        return;
    }

    printf("\n----- MEMBER RECORDS -----\n");

    for (i = 0; i < memberCount; i++)
    {
        printf("\nMember ID: %d", members[i].id);
        printf("\nMember Name: %s\n", members[i].name);
    }
}

void issueBook()
{
    int id, i;

    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    for (i = 0; i < bookCount; i++)
    {
        if (books[i].id == id)
        {
            if (books[i].issued)
            {
                printf("Book is already issued.\n");
            }
            else
            {
                books[i].issued = 1;
                saveBooks();
                printf("Book issued successfully!\n");
            }

            return;
        }
    }

    printf("Book not found!\n");
}

void returnBook()
{
    int id, i;

    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    for (i = 0; i < bookCount; i++)
    {
        if (books[i].id == id)
        {
            if (!books[i].issued)
            {
                printf("Book is already available.\n");
            }
            else
            {
                books[i].issued = 0;
                saveBooks();
                printf("Book returned successfully!\n");
            }

            return;
        }
    }

    printf("Book not found!\n");
}

int main()
{
    int choice;

    loadBooks();
    loadMembers();

    do
    {
        printf("\n==============================");
        printf("\n LIBRARY MANAGEMENT SYSTEM");
        printf("\n==============================");
        printf("\n1. Add Book");
        printf("\n2. Display Books");
        printf("\n3. Search Book");
        printf("\n4. Add Member");
        printf("\n5. Display Members");
        printf("\n6. Issue Book");
        printf("\n7. Return Book");
        printf("\n8. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                addMember();
                break;

            case 5:
                displayMembers();
                break;

            case 6:
                issueBook();
                break;

            case 7:
                returnBook();
                break;

            case 8:
                printf("Thank you!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 8);

    return 0;
}