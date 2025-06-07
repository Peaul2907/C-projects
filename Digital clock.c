#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void digital_clock(int format);
void set_alarm();
void stopwatch();

int main() {
    int choice, format;

    while (1) {
        printf("\n==== DIGITAL CLOCK MENU ====\n");
        printf("1. Digital Clock\n");
        printf("2. Set Alarm\n");
        printf("3. Stopwatch\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nChoose format:\n1. 12-hour\n2. 24-hour\nEnter choice: ");
                scanf("%d", &format);
                digital_clock(format);
                break;
            case 2:
                set_alarm();
                break;
            case 3:
                stopwatch();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

void digital_clock(int format) {
    while (1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        system("clear"); // use "cls" for Windows
        printf("\n\tDIGITAL CLOCK\n\n");

        if (format == 1) {
            int hour = t->tm_hour % 12;
            if (hour == 0) hour = 12;
            printf("\t%02d:%02d:%02d %s\n",
                hour, t->tm_min, t->tm_sec,
                (t->tm_hour >= 12) ? "PM" : "AM");
        } else {
            printf("\t%02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);
        }

        sleep(1);
    }
}

void set_alarm() {
    int h, m, s;
    printf("Set alarm time (HH MM SS): ");
    scanf("%d %d %d", &h, &m, &s);

    printf("Alarm set for %02d:%02d:%02d\n", h, m, s);

    while (1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        if (t->tm_hour == h && t->tm_min == m && t->tm_sec == s) {
            printf("\n\n*** ALARM! Time matched! ***\n");
            for (int i = 0; i < 5; i++) {
                printf("\a"); // beep sound
                sleep(1);
            }
            break;
        }

        sleep(1);
    }
}

void stopwatch() {
    int h = 0, m = 0, s = 0;
    char ch;

    printf("Press 's' to start stopwatch: ");
    scanf(" %c", &ch);

    if (ch != 's' && ch != 'S') return;

    while (1) {
        system("clear");
        printf("\n\tSTOPWATCH\n\n");
        printf("\t%02d:%02d:%02d\n", h, m, s);
        printf("Press 'q' to stop, 'r' to reset: ");

        sleep(1);
        s++;
        if (s == 60) { s = 0; m++; }
        if (m == 60) { m = 0; h++; }

        if (kbhit()) {
            ch = getchar();
            if (ch == 'q' || ch == 'Q') break;
            if (ch == 'r' || ch == 'R') { h = m = s = 0; }
        }
    }
}

// Function to detect key press (Linux only)
#include <termios.h>
#include <fcntl.h>

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}