#include <stdio.h>
#include <limits.h>

#define MAX_PAGES 100
#define MAX_FRAMES 50

void display_frames_state(int frame_history[][MAX_PAGES], int totalFrames, int totalPages)
{
    for (int i = 0; i < totalFrames; i++)
    {
        for (int j = 0; j < totalPages; j++)
        {
            if (frame_history[i][j] == -1)
            {
                printf("    ");
            }
            else
            {
                printf("|%d| ", frame_history[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void fifo(int pages[], int n, int frames)
{
    int frame[MAX_FRAMES];
    int frame_history[MAX_FRAMES][MAX_PAGES];
    int faults = 0;
    int pos = 0;

    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        for (int j = 0; j < n; j++)
        {
            frame_history[i][j] = -1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            frame[pos] = pages[i];
            pos = (pos + 1) % frames;
            faults++;
        }

        for (int k = 0; k < frames; k++)
        {
            frame_history[k][i] = frame[k];
        }
    }

    display_frames_state(frame_history, frames, n);
    printf("Total Page Faults (FIFO): %d\n\n", faults);
}

void lru(int pages[], int n, int frames)
{
    int frame[MAX_FRAMES];
    int used[MAX_FRAMES];
    int frame_history[MAX_FRAMES][MAX_PAGES];
    int faults = 0;

    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        used[i] = -1;
        for (int j = 0; j < n; j++)
        {
            frame_history[i][j] = -1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                used[j] = i;
                break;
            }
        }

        if (!found)
        {
            int min = -1;
            for (int j = 0; j < frames; j++)
            {
                if (frame[j] == -1)
                {
                    min = j;
                    break;
                }
            }
            if (min == -1)
            {
                min = 0;
                for (int j = 1; j < frames; j++)
                {
                    if (used[j] < used[min])
                    {
                        min = j;
                    }
                }
            }
            frame[min] = pages[i];
            used[min] = i;
            faults++;
        }

        for (int k = 0; k < frames; k++)
        {
            frame_history[k][i] = frame[k];
        }
    }

    display_frames_state(frame_history, frames, n);
    printf("Total Page Faults (LRU): %d\n\n", faults);
}

void opt(int pages[], int n, int frames)
{
    int frame[MAX_FRAMES];
    int frame_history[MAX_FRAMES][MAX_PAGES];
    int faults = 0;

    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        for (int j = 0; j < n; j++)
        {
            frame_history[i][j] = -1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            int replace = -1;
            for (int j = 0; j < frames; j++)
            {
                if (frame[j] == -1)
                {
                    replace = j;
                    break;
                }
            }

            if (replace == -1)
            {
                int farthest = -1;
                int idx = -1;
                for (int j = 0; j < frames; j++)
                {
                    int next_use = INT_MAX;
                    for (int k = i + 1; k < n; k++)
                    {
                        if (frame[j] == pages[k])
                        {
                            next_use = k;
                            break;
                        }
                    }
                    if (next_use > farthest)
                    {
                        farthest = next_use;
                        idx = j;
                    }
                }
                replace = (idx == -1) ? 0 : idx;
            }

            frame[replace] = pages[i];
            faults++;
        }

        for (int k = 0; k < frames; k++)
        {
            frame_history[k][i] = frame[k];
        }
    }

    display_frames_state(frame_history, frames, n);
    printf("Total Page Faults (OPT): %d\n\n", faults);
}

int main()
{
    int pages[MAX_PAGES] = {3,2,1,3,4,1,6,2,4,3,4,2,1,4,5,2,1,3,4,6,4,1};
    int n = 22;
    int frames = 3;

    printf("Manual Input:\n\n");
    fifo(pages, n, frames);
    lru(pages, n, frames);
    opt(pages, n, frames);

    printf("User Input:\nEnter number of pages: ");
    if (scanf("%d", &n) != 1) return 0;
    printf("Enter page reference string: ");
    for (int i = 0; i < n && i < MAX_PAGES; i++)
    {
        if (scanf("%d", &pages[i]) != 1) return 0;
    }
    printf("Enter number of frames: ");
    if (scanf("%d", &frames) != 1) return 0;
    if (frames > MAX_FRAMES) frames = MAX_FRAMES;

    fifo(pages, n, frames);
    lru(pages, n, frames);
    opt(pages, n, frames);

    return 0;
}
