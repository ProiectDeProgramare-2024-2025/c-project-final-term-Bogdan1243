#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
FILE *matches;
FILE *players;
FILE *match_no;

#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"

int counter = 0;
struct players {
  char player1[50];
  char player2[50];
  char score1[50];
  char score2[50];
};
int check_no() {
  match_no = fopen("matches", "r");
  if (match_no == NULL) {
    perror("Error opening file");
    return;
  }

  int line_count = 0;
  char buffer[256];


  while (fgets(buffer, sizeof(buffer), match_no)) {
    line_count++;
  }

  fclose(match_no);
  return line_count;
}

void menu() {
  system("cls");
  printf("======Table Tennis Results======\n");
  printf("========================\n");
  printf("1. Players\n");
  printf("2. Ranking\n");
  printf("3. History\n");
  printf("========================\n");
  printf("0. Exit\n");
}


void add_matches() {
  counter = check_no();
  players = fopen("players", "a");
  matches = fopen("matches", "a");
  struct players player;
  system("cls");
  int n;
  printf("Enter number of matches(" YELLOW "digits" RESET "): ");
  scanf("%d", &n);
  int count=0;
  for (int i = 0; i < n; i++) {
    printf("\n");
    printf("========Match %d========\n", i+1);
    printf("\n");
    printf("Enter player 1("YELLOW "string" RESET "): ");
    scanf("%s", player.player1);
    printf("\n");
    printf("Enter player 1 score("YELLOW "0-21" RESET "): ");
    while (1) {
      scanf("%s", player.score1);
      if (strspn(player.score1, "0123456789") == strlen(player.score1)) {
        int score = atoi(player.score1);
        if (score >= 0 && score <= 21) break;
        else {
          printf("\n");
          printf("Score cannot exceed "RED "21" RESET " points.\n");
          printf("Enter score again("YELLOW "0-21" RESET "): ");
        }
      } else {
        printf("\n");
        printf( RED "Invalid" RESET" input!\n");
        printf("Enter digits only("YELLOW "0-21" RESET"): ");
      }
    }
    printf("\n");
    printf("Enter player 2(" YELLOW "string" RESET"): ");
    scanf("%s", player.player2);
    printf("\n");
    printf("Enter player 2 score("YELLOW "0-21" RESET"): ");
    while (1) {
      scanf("%s", player.score2);
      if (strspn(player.score2, "0123456789") == strlen(player.score2)) {
        int score = atoi(player.score2);
        if (score >= 0 && score <= 21) break;
        else {
          printf("\n");
          printf("Score cannot exceed "RED "21" RESET " points.\n");
          printf("Enter score again("YELLOW "0-21" RESET "): ");
        }

      } else {
        printf("\n");
        printf( RED "Invalid" RESET" input!\n");
        printf("Enter digits only("YELLOW "0-21" RESET"): ");
      }
    }
    fprintf(matches, "%d. [%s%s%s] %s%s/%s%s [%s%s%s]\n",
        counter,
        GREEN, player.player1, RESET,        // Player 1 name in green
        YELLOW, player.score1, player.score2, RESET,  // Scores in yellow
        GREEN, player.player2, RESET         // Player 2 name in green
    );
    fprintf(players, "%s\n", player.player1);
    fprintf(players, "%s\n", player.player2);
    counter++;
    }
  fclose(players);
  fclose(matches);
  int choice=0;
  while (1) {
    system("cls");
    printf("========================\n");
    printf("1. To Enter More Matches\n");
    printf("========================\n");
    printf("9. Main page\n");
    scanf("%d", &choice);
    if (choice == 9) {
      fclose(players);
      fclose(matches);
      system("cls");
      menu();
      return;
    }
    if (choice==1){
      add_matches();
      break;
    }
  }
}


void ranking() {
    matches = fopen("matches", "r");
    if (matches == NULL) {
        perror("Error opening matches file");
        return;
    }

    struct stats {
        char name[50];
        int wins;
        int losses;
    } players[100];

    int player_count = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), matches)) {
        char player1[50], player2[50];
        int score1, score2;

        sscanf(buffer, "%*d. [%[^]]] %d / %d [%[^]]]", player1, &score1, &score2, player2);

        int found1 = -1, found2 = -1;
        for (int i = 0; i < player_count; i++) {
            if (strcmp(players[i].name, player1) == 0) found1 = i;
            if (strcmp(players[i].name, player2) == 0) found2 = i;
        }
        if (found1 == -1) {
            strcpy(players[player_count].name, player1);
            players[player_count].wins = 0;
            players[player_count].losses = 0;
            found1 = player_count++;
        }
        if (found2 == -1) {
            strcpy(players[player_count].name, player2);
            players[player_count].wins = 0;
            players[player_count].losses = 0;
            found2 = player_count++;
        }

        if (score1 > score2) {
            players[found1].wins++;
            players[found2].losses++;
        } else if (score2 > score1) {
            players[found2].wins++;
            players[found1].losses++;
        }
    }

    fclose(matches);

    system("cls");
    printf("========Ranking========\n");
    printf("=====[Name] "GREEN"[WINS]"RESET"/"BLUE"[LOSSES]"RESET"=====\n\n");
    for (int i = 0; i < player_count; i++) {
        printf("%s %s%d%s/%s%d%s\n", players[i].name, GREEN, players[i].wins, RESET, BLUE, players[i].losses, RESET);
    }

    int choice = 0;
    while (1) {
        printf("\n========================\n");
        printf("9. Main page\n");
        scanf("%d", &choice);
        if (choice == 9) {
            system("cls");
            menu();
            return;
        }
    }
}


void history() {
  system("cls");
  matches = fopen("matches", "r");
  char buffer[256];
  printf("========History========");
  printf("\n");
  while (fgets(buffer, 256, matches) != NULL) {
    printf("%s", buffer);
  }
  printf("\n");
  int choice=0;
  while (1) {
    printf("========================\n");
    printf("9. Main page\n");
    scanf("%d", &choice);
    if (choice == 9) {
      fclose(matches);
      system("cls");
      menu();
      return;
    }
    else {
      system("cls");
    }
    fclose(matches);
  }
}

void leave() {
  system("cls");
  printf("You exited the program");
}
int main() {
  fopen("matches", "r");
  fclose(matches);

  int a[3]={1,2,3};
  int input;
  menu();
  while (input!=0) {
    scanf("%d",&input);
    if (input==a[input-1] || input == 9) {
      if (input==1) {
        add_matches();
      }
      if (input==2) {
        ranking();
      }
      if (input==3) {
        history();
      }
      if (input==9){
        system("cls");
        menu();
      }
    }
    else {
      printf("This is the wrong option\n");
    }
  }
  leave();
  return 0;
}
