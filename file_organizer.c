#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

// Function to create directory and files (Option 1)
void create_directory_and_files() {
    char dirName[256];
    char fileName[256];
    char filePath[300];

    printf("Enter new directory name: ");
    scanf("%255s", dirName);

    // Create directory
    if (mkdir(dirName, 0777) == 0) {
        printf("Directory '%s' created successfully.\n", dirName);
    } else {
        printf("Directory already exists or cannot be created.\n");
    }

    // Create 5 files
    for (int i = 1; i <= 5; i++) {
        printf("Enter name for file %d: ", i);
        scanf("%255s", fileName);

        sprintf(filePath, "%s/%s", dirName, fileName);
        FILE *fp = fopen(filePath, "w");

        if (fp != NULL) {
            fclose(fp);
            printf("File '%s' created.\n", fileName);
        } else {
            printf("Error creating file '%s'.\n", fileName);
        }
    }

    printf("Directory and files created successfully.\n");
}

// Function to organize files (Option 2)
void organize_directory(char directoryPath[]) {
    struct dirent *entry;
    DIR *dp = opendir(directoryPath);

    if (dp == NULL) {
        printf("Error: Cannot open directory.\n");
        return;
    }

    char documents[300], images[300], audio[300], videos[300], others[300];

    sprintf(documents, "%s/Documents", directoryPath);
    sprintf(images, "%s/Images", directoryPath);
    sprintf(audio, "%s/Audio", directoryPath);
    sprintf(videos, "%s/Videos", directoryPath);
    sprintf(others, "%s/Others", directoryPath);

    mkdir(documents, 0777);
    mkdir(images, 0777);
    mkdir(audio, 0777);
    mkdir(videos, 0777);
    mkdir(others, 0777);

    while ((entry = readdir(dp)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        if (entry->d_type == DT_DIR)
            continue;

        char oldPath[300], newPath[300];
        char *ext = strrchr(entry->d_name, '.');

        sprintf(oldPath, "%s/%s", directoryPath, entry->d_name);

        if (ext &&
            (strcmp(ext, ".txt") == 0 ||
             strcmp(ext, ".pdf") == 0 ||
             strcmp(ext, ".docx") == 0)) {

            sprintf(newPath, "%s/%s", documents, entry->d_name);
        }
        else if (ext &&
                (strcmp(ext, ".jpg") == 0 ||
                 strcmp(ext, ".jpeg") == 0 ||
                 strcmp(ext, ".png") == 0)) {

            sprintf(newPath, "%s/%s", images, entry->d_name);
        }
        else if (ext &&
                (strcmp(ext, ".mp3") == 0 ||
                 strcmp(ext, ".wav") == 0 ||
                 strcmp(ext, ".aac") == 0)) {

            sprintf(newPath, "%s/%s", audio, entry->d_name);
        }
        else if (ext &&
                (strcmp(ext, ".mp4") == 0 ||
                 strcmp(ext, ".mkv") == 0 ||
                 strcmp(ext, ".avi") == 0)) {

            sprintf(newPath, "%s/%s", videos, entry->d_name);
        }
        else {
            sprintf(newPath, "%s/%s", others, entry->d_name);
        }

        rename(oldPath, newPath);
    }

    closedir(dp);
    printf("Files organized successfully.\n");
}

int main() {
    int choice;
    char directoryPath[256];

    while (1) {
        printf("\n===== FILE ORGANIZER MENU =====\n");
        printf("1. Create a new directory and add 5 files\n");
        printf("2. Organize an existing directory\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_directory_and_files();
                break;

            case 2:
                printf("Enter the directory path to organize: ");
                scanf("%255s", directoryPath);
                organize_directory(directoryPath);
                break;

            case 3:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}


