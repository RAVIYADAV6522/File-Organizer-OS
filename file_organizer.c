#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int main() {
    char directoryPath[256];
    struct dirent *entry;
    DIR *dp;

    printf("Enter the directory path to organize: ");
    scanf("%255s", directoryPath);

    dp = opendir(directoryPath);
    if (dp == NULL) {
        printf("Error: Cannot open directory.\n");
        return 1;
    }

    // Folder paths
    char documents[300], images[300], audio[300], videos[300], others[300];

    sprintf(documents, "%s/Documents", directoryPath);
    sprintf(images, "%s/Images", directoryPath);
    sprintf(audio, "%s/Audio", directoryPath);
    sprintf(videos, "%s/Videos", directoryPath);
    sprintf(others, "%s/Others", directoryPath);

    // Create folders
    mkdir(documents, 0777);
    mkdir(images, 0777);
    mkdir(audio, 0777);
    mkdir(videos, 0777);
    mkdir(others, 0777);

    while ((entry = readdir(dp)) != NULL) {

        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        // Skip directories
        if (entry->d_type == DT_DIR)
            continue;

        char oldPath[300], newPath[300];
        char *ext = strrchr(entry->d_name, '.');

        sprintf(oldPath, "%s/%s", directoryPath, entry->d_name);

        // DOCUMENTS
        if (ext &&
            (strcmp(ext, ".txt") == 0 ||
             strcmp(ext, ".pdf") == 0 ||
             strcmp(ext, ".docx") == 0)) {

            sprintf(newPath, "%s/%s", documents, entry->d_name);
        }
        // IMAGES
        else if (ext &&
                (strcmp(ext, ".jpg") == 0 ||
                 strcmp(ext, ".jpeg") == 0 ||
                 strcmp(ext, ".png") == 0)) {

            sprintf(newPath, "%s/%s", images, entry->d_name);
        }
        // AUDIO
        else if (ext &&
                (strcmp(ext, ".mp3") == 0 ||
                 strcmp(ext, ".wav") == 0 ||
                 strcmp(ext, ".aac") == 0)) {

            sprintf(newPath, "%s/%s", audio, entry->d_name);
        }
        // VIDEO
        else if (ext &&
                (strcmp(ext, ".mp4") == 0 ||
                 strcmp(ext, ".mkv") == 0 ||
                 strcmp(ext, ".avi") == 0)) {

            sprintf(newPath, "%s/%s", videos, entry->d_name);
        }
        // OTHERS
        else {
            sprintf(newPath, "%s/%s", others, entry->d_name);
        }

        rename(oldPath, newPath);
    }

    closedir(dp);
    printf("Files organized successfully.\n");
    return 0;
}
