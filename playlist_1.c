#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Track
{
    char title[100];
    struct Track* prev;
    struct Track* next;
} Track;

Track* createTrack(const char* title)
{
    Track* track = (Track*)malloc(sizeof(Track));
    strcpy(track->title, title);
    track->prev = NULL;
    track->next = NULL;
    return track;
}

void addToPlaylist(Track** head, Track** tail, const char* title)
{
    Track* newTrack = createTrack(title);
    if (*head == NULL)
        *head = *tail = newTrack;
    else
	{
        (*tail)->next = newTrack;
        newTrack->prev = *tail;
        *tail = newTrack;
    }
}

void deleteFromPlaylist(Track** head, Track** tail, const char* title)
{
    Track* current = *head;
    while (current != NULL)
	{
        if (strcmp(current->title, title) == 0)
		{
            if (current->prev == NULL)// Deleting the head
			{ 
                *head = current->next;
                if (*head != NULL)
                    (*head)->prev = NULL;
                else	// The playlist becomes empty
                	*tail = NULL;
				else if (current->next == NULL) // Deleting the tail
                {
					*tail = current->prev;
                	(*tail)->next = NULL;
				}
            	else	// Deleting a track in the middle
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
    }
    printf("Track not found in the playlist.\n");
}

void insertInPlaylist(Track** head, Track** tail, const char* title, int position) {
    if (position <= 0) { // Insert at the beginning
        addToPlaylist(head, tail, title);
    } else {
        Track* current = *head;
        int count = 0;
        while (current != NULL) {
            if (count == position - 1) { // Found the position
                Track* newTrack = createTrack(title);
                newTrack->prev = current;
                newTrack->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = newTrack;
                }
                current->next = newTrack;
                if (current == *tail) { // Insert at the end
                    *tail = newTrack;
                }
                return;
            }
            count++;
            current = current->next;
        }
        printf("Invalid position for inserting the track.\n");
    }
}

void shufflePlaylist(Track** head, Track** tail) {
    // Count the number of tracks in the playlist
    int count = 0;
    Track* current = *head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // Create an array to store the pointers to the tracks
    Track** trackArray = (Track**)malloc(count * sizeof(Track*));
    current = *head;
    int i = 0;
    while (current != NULL) {
        trackArray[i] = current;
        current = current->next;
        i++;
    }

    // Shuffle the array using Fisher-Yates algorithm
    srand(time(NULL));
    for (int j = count - 1; j > 0; j--) {
        int k = rand() % (j + 1);
        Track* temp = trackArray[j];
        trackArray[j] = trackArray[k];
        trackArray[k] = temp;
    }

    // Reconnect the shuffled tracks
    for (int j = 0; j < count; j++) {
        if (j == 0) {
            *head = trackArray[j];
            trackArray[j]->prev = NULL;
        } else {
            trackArray[j]->prev = trackArray[j - 1];
            trackArray[j - 1]->next = trackArray[j];
        }
        if (j == count - 1) {
            *tail = trackArray[j];
            trackArray[j]->next = NULL;
        } else {
            trackArray[j]->next = trackArray[j + 1];
            trackArray[j + 1]->prev = trackArray[j];
        }
    }

    free(trackArray);
}

void printPlaylistForward(Track* head) {
    printf("Playlist (forward order):\n");
    while (head != NULL) {
        printf("%s\n", head->title);
        head = head->next;
    }
    printf("\n");
}

void freePlaylist(Track* head) {
    while (head != NULL) {
        Track* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Track* head = NULL;
    Track* tail = NULL;

    // Adding tracks to the playlist
    addToPlaylist(&head, &tail, "Track 1");
    addToPlaylist(&head, &tail, "Track 2");
    addToPlaylist(&head, &tail, "Track 3");

    printf("Original Playlist:\n");
    printPlaylistForward(head);

    // Deleting a track from the playlist
    deleteFromPlaylist(&head, &tail, "Track 2");

    printf("Playlist after deleting 'Track 2':\n");
    printPlaylistForward(head);

    // Inserting a track into the playlist
    insertInPlaylist(&head, &tail, "Track X", 1);

    printf("Playlist after inserting 'Track X' at position 1:\n");
    printPlaylistForward(head);

    // Shuffling the playlist
    shufflePlaylist(&head, &tail);

    printf("Shuffled Playlist:\n");
    printPlaylistForward(head);

    // Freeing the memory allocated for the playlist
    freePlaylist(head);

    return 0;
}