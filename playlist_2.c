#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for each track in the playlist
typedef struct Track {
    char title[100];
    struct Track* prev;
    struct Track* next;
} Track;

// Function to create a new track node
Track* createTrack(const char* title)
{
    Track* track = (Track*)malloc(sizeof(Track));
    strcpy(track->title, title);
    track->prev = NULL;
    track->next = NULL;
    return track;
}

// Function to add a track to the end of the playlist
void addToPlaylist(Track** head, Track** tail, const char* title)
{
    Track* newTrack = createTrack(title);
    if (*head == NULL) {
        *head = *tail = newTrack;
    } else {
        (*tail)->next = newTrack;
        newTrack->prev = *tail;
        *tail = newTrack;
    }
}

// Function to print the playlist in forward order
void printPlaylistForward(Track* head)
{
    printf("Playlist (forward order):\n");
    while (head != NULL) {
        printf("%s\n", head->title);
        head = head->next;
    }
    printf("\n");
}

// Function to print the playlist in reverse order
void printPlaylistReverse(Track* tail)
{
    printf("Playlist (reverse order):\n");
    while (tail != NULL) {
        printf("%s\n", tail->title);
        tail = tail->prev;
    }
    printf("\n");
}

// Function to free the memory allocated for the playlist
void freePlaylist(Track* head)
{
    while (head != NULL) {
        Track* temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    Track* head = NULL;
    Track* tail = NULL;

    // Adding tracks to the playlist
    addToPlaylist(&head, &tail, "Track 1");
    addToPlaylist(&head, &tail, "Track 2");
    addToPlaylist(&head, &tail, "Track 3");

    // Printing the playlist in forward and reverse order
    printPlaylistForward(head);
    printPlaylistReverse(tail);

    // Freeing the memory allocated for the playlist
    freePlaylist(head);

    return 0;
}
