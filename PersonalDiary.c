#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int id;
    char date[20];
    char content[200];
};

void addRecord(struct Record diary[], int *count) {
    if (*count >= 100) {
        printf("Diary is full. Cannot add more records.\n");
        return;
    }

    struct Record newRecord;
    printf("Enter date: ");
    scanf("%s", newRecord.date);
    printf("Enter content: ");
    scanf(" %[^\n]s", newRecord.content);

    newRecord.id = *count + 1;
    diary[*count] = newRecord;
    (*count)++;

    printf("Record added successfully.\n");
}

void deleteRecord(struct Record diary[], int *count, int id) {
    if (id <= 0 || id > *count) {
        printf("Invalid record ID.\n");
        return;
    }

    for (int i = id - 1; i < *count - 1; i++) {
        diary[i] = diary[i + 1];
        diary[i].id--;
    }

    (*count)--;
    printf("Record deleted successfully.\n");
}

void updateRecord(struct Record diary[], int count, int id) {
    if (id <= 0 || id > count) {
        printf("Invalid record ID.\n");
        return;
    }

    printf("Enter new date: ");
    scanf("%s", diary[id - 1].date);
    printf("Enter new content: ");
    scanf(" %[^\n]s", diary[id - 1].content);

    printf("Record updated successfully.\n");
}

void saveRecordsToFile(struct Record diary[], int count) {
    FILE *file = fopen("diary.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s\n", diary[i].id, diary[i].date, diary[i].content);
    }

    fclose(file);
    printf("Records saved to file.\n");
}

void viewRecords(struct Record diary[], int count) {
    printf("\n-- Diary Records --\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d\nDate: %s\nContent: %s\n\n", diary[i].id, diary[i].date, diary[i].content);
    }
}

int main() {
    struct Record diary[100];
    int recordCount = 0;

    // Load records from file (if available)
    FILE *file = fopen("diary.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%d %s %[^\n]s", &diary[recordCount].id, diary[recordCount].date, diary[recordCount].content) != EOF) {
            recordCount++;
        }
        fclose(file);
    }

    int choice, id;
    while (1) {
        printf("\n1. Add Record\n2. Delete Record\n3. Update Record\n4. View Records\n5. Save Records\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord(diary, &recordCount);
                break;
            case 2:
                printf("Enter record ID to delete: ");
                scanf("%d", &id);
                deleteRecord(diary, &recordCount, id);
                break;
            case 3:
                printf("Enter record ID to update: ");
                scanf("%d", &id);
                updateRecord(diary, recordCount, id);
                break;
            case 4:
                viewRecords(diary, recordCount);
                break;
            case 5:
                saveRecordsToFile(diary, recordCount);
                break;
            case 6:
                saveRecordsToFile(diary, recordCount);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please select again.\n");
        }
    }

    return 0;
}