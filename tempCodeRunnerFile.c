#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_DOCS 100
#define MAX_TITLE 100
#define MAX_CONTENT 1000

struct Document {
    int id;
    char title[MAX_TITLE];
    char content[MAX_CONTENT];
};

struct Document docs[MAX_DOCS];
int docCount = 0;

void toLowerCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

void addDocument() {
    if (docCount >= MAX_DOCS) {
        printf("Document storage full!\n");
        return;
    }

    docs[docCount].id = docCount + 1;

    printf("Enter document title: ");
    scanf(" %[^\n]", docs[docCount].title);

    printf("Enter document content: ");
    scanf(" %[^\n]", docs[docCount].content);

    docCount++;

    printf("Document added successfully!\n");
}

void displayDocuments() {
    if (docCount == 0) {
        printf("No documents available.\n");
        return;
    }

    printf("\n----- All Documents -----\n");

    for (int i = 0; i < docCount; i++) {
        printf("\nDocument ID: %d\n", docs[i].id);
        printf("Title: %s\n", docs[i].title);
        printf("Content: %s\n", docs[i].content);
    }
}

void searchDocument() {
    if (docCount == 0) {
        printf("No documents available.\n");
        return;
    }

    char keyword[100];
    char tempTitle[MAX_TITLE];
    char tempContent[MAX_CONTENT];
    char tempKeyword[100];

    int found = 0;

    printf("Enter keyword to search: ");
    scanf(" %[^\n]", keyword);

    strcpy(tempKeyword, keyword);
    toLowerCase(tempKeyword);

    printf("\n----- Search Results -----\n");

    for (int i = 0; i < docCount; i++) {
        strcpy(tempTitle, docs[i].title);
        strcpy(tempContent, docs[i].content);

        toLowerCase(tempTitle);
        toLowerCase(tempContent);

        if (strstr(tempTitle, tempKeyword) != NULL ||
            strstr(tempContent, tempKeyword) != NULL) {

            printf("\nDocument ID: %d\n", docs[i].id);
            printf("Title: %s\n", docs[i].title);
            printf("Content: %s\n", docs[i].content);

            found = 1;
        }
    }

    if (!found) {
        printf("No matching document found.\n");
    }
}

void deleteDocument() {
    int id, found = 0;

    if (docCount == 0) {
        printf("No documents available.\n");
        return;
    }

    printf("Enter document ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < docCount; i++) {
        if (docs[i].id == id) {
            for (int j = i; j < docCount - 1; j++) {
                docs[j] = docs[j + 1];
                docs[j].id = j + 1;
            }

            docCount--;
            found = 1;

            printf("Document deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Document not found.\n");
    }
}

void updateDocument() {
    int id, found = 0;

    if (docCount == 0) {
        printf("No documents available.\n");
        return;
    }

    printf("Enter document ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < docCount; i++) {
        if (docs[i].id == id) {
            printf("Enter new title: ");
            scanf(" %[^\n]", docs[i].title);

            printf("Enter new content: ");
            scanf(" %[^\n]", docs[i].content);

            found = 1;
            printf("Document updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Document not found.\n");
    }
}

void countKeywordOccurrences() {
    if (docCount == 0) {
        printf("No documents available.\n");
        return;
    }

    char keyword[100];
    char tempContent[MAX_CONTENT];
    char tempKeyword[100];

    printf("Enter keyword to count: ");
    scanf(" %[^\n]", keyword);

    strcpy(tempKeyword, keyword);
    toLowerCase(tempKeyword);

    printf("\n----- Keyword Frequency -----\n");

    for (int i = 0; i < docCount; i++) {
        strcpy(tempContent, docs[i].content);
        toLowerCase(tempContent);

        int count = 0;
        char *pos = tempContent;

        while ((pos = strstr(pos, tempKeyword)) != NULL) {
            count++;
            pos += strlen(tempKeyword);
        }

        printf("Document ID %d (%s): %d occurrence(s)\n",
               docs[i].id, docs[i].title, count);
    }
}

int main() {
    int choice;

    do {
        printf("\n===== Mini Search Engine =====\n");
        printf("1. Add Document\n");
        printf("2. Display All Documents\n");
        printf("3. Search Document by Keyword\n");
        printf("4. Update Document\n");
        printf("5. Delete Document\n");
        printf("6. Count Keyword Occurrences\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addDocument();
                break;

            case 2:
                displayDocuments();
                break;

            case 3:
                searchDocument();
                break;

            case 4:
                updateDocument();
                break;

            case 5:
                deleteDocument();
                break;

            case 6:
                countKeywordOccurrences();
                break;

            case 7:
                printf("Exiting Mini Search Engine...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 7);

    return 0;
}
