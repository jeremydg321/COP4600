
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

#define MAXLENGTH 1000 
#define RESET "\x1B[0m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define RED   "\x1B[31m"

// Clear the Console - Akash Samlal
void clearConsole() {
    printf("\e[1;1H\e[2J");
}

// Gets Current Directory - Akash Samlal
void whereAmI(char currentDirectory[]) {
	//char cwd[MAXLENGTH]; 
	//printf("\n%s\n\n", getcwd(cwd, sizeof(cwd)));
	printf("\n%s\n\n", currentDirectory);
}

// Returns Current Directory - Akash Samlal
char * currentDir() {
	char cwd[MAXLENGTH]; 
	return getcwd(cwd, sizeof(cwd));
}


// Read History Text Files - Akash Samlal
void readHistory(int lengthCommand, char arrayStrings[lengthCommand][100]) {
	int i = 0; 
	char line[100];

	FILE * ofp = fopen("history.txt", "r"); 

	printf("\n\n"); 
	while(fgets(line, sizeof(line), ofp)) {
		strcpy(arrayStrings[i], line);  
		printf(arrayStrings[i], "\n");
		i++;
	} 
	fclose(ofp);
}

// Print History - Akash Samlal
void printHistory() {
	char line[100];
	FILE * anotha = fopen("reverse.txt", "r"); 
	int i = 0;
	printf("\n");
	while(fgets(line, sizeof(line), anotha)) {
		printf("%d: %s", i, line);
		i++;
	} 
	printf("\n");
	fclose(anotha);
}

// Main of Displaying History - Akash Samlal
int startHistory(int lengthCommand, char command[], char*parameters[]) {
		fclose(fopen("reverse.txt", "w")); 
		int i = 0;
		char line[100]; 
		char historyCommands[lengthCommand][100]; 
			
		FILE * ofp = fopen("history.txt", "r"); 

		while(fgets(line, sizeof(line), ofp)) {
			strcpy(historyCommands[i], line);  
			i++;
		} 
		fclose(ofp);

		FILE * ifp = fopen("reverse.txt", "w");

		for(i = lengthCommand - 1; i >= 0; i--) {
			fprintf(ifp, "%s", historyCommands[i]);
		}
		fclose(ifp);

		FILE * anotha = fopen("reverse.txt", "r"); 
		i = 0;
		printf("\n");
		while(fgets(line, sizeof(line), anotha)) {
			printf("%d: %s", i, line);
			i++;
		} 

		printf("\n");
		fclose(anotha);

		return lengthCommand;
	
}

// Replay Method - Akash Samlal
int replay(char* parameters[], char command[], int lengthCommand) {
	// + 1
	int n = atoi(parameters[1]);
 	int i = 0;
	int replayTrue = 0;
	char line[100]; 
	char historyCommands[lengthCommand][100]; 

	FILE * anotha = fopen("reverse.txt", "r"); 

	while(fgets(line, sizeof(line), anotha)) {
		strcpy(historyCommands[i], line);  
		i++;
	} 
	fclose(anotha);

	if((n > i)) {
		printf("Error: Command Don't Exists -- Out of bounds!\n");
		return replayTrue; 
	}
	printf("\nReplayed Command: %s\n", historyCommands[n]); 
	strcpy(command, historyCommands[n]); 
	replayTrue = 1;
	return replayTrue;
}

// Print History List - Akash Samlal
void appendHistory(int lengthCommand, char command[]) {
		if((strcmp(command, " ") != 0)){
			FILE *ifp = fopen("history.txt", "a");
			fprintf(ifp, "%s\n", command);
			fclose(ifp);
		}
}

//MovetoDirectory Command - Akash Samlal
void moveDir(char* parameters[], char currentDirectory[]) {
	struct stat stats; 

	stat(parameters[1], &stats);

	if(S_ISDIR(stats.st_mode)) {
		strcpy(currentDirectory, parameters[1]); 
	}
	else 
		printf("Error: Directory doesn't exists!\n"); 

}


//StartProgram - Jeremy Galvan
void startprogram(char *parameters[])
{	
	pid_t pid = fork();
	if(pid==0)
	{
		if((strcmp(parameters[1], "/") == 0)) 
		
		{
			//test start /usr/bin/xterm -bg green

			execl(parameters[1], parameters[1], parameters[2], parameters[3],(void*)NULL);

			printf("%s\n ",parameters[1]);
			printf("%s\n ",parameters[2]);
			printf("%s\n ",parameters[3]);

			printf("No program\n");
			return;
		}
		/*
		can run:
		pwd
		ls
		mkdir
		df
		touch
		rm
		cp
		locate(kind of)
		sudo apt something something

		can't run:
		cd?
		*/
		execvp(parameters[1],&parameters[1]);
		printf("No program\n");
		return;
	}
	fflush(stdout);
    waitpid(pid,NULL,0);
}

//BackgroundProgram - Jeremy Galvan
void backprogram(char *parameters[])
{
	
	pid_t pid = fork();
	if(pid==0)
	{
		if(parameters[1]=="/")
		{
			//test start /usr/bin/xterm -bg green

			execl(parameters[1], parameters[1], parameters[2], parameters[3],(void*)NULL);

			printf("%s\n ",parameters[1]);
			printf("%s\n ",parameters[2]);
			printf("%s\n ",parameters[3]);

			printf("No program\n");
			return;
		}
		/*
		can run:
		pwd
		ls
		mkdir
		df
		touch
		rm
		cp
		locate(kind of)
		sudo apt something something

		can't run:
		cd?
		
		*/

		execvp(parameters[1],&parameters[1]);
		printf("No program\n");
		return;
	}
	fflush(stdout);
    printf("\nPID: %d\n", pid);
}


//Dalek PID - Jeremy Galvan
void dalekPID(char *parameters[])
{
    int pid = atoi(parameters[1]);

 

		pid_t p = (pid_t)pid;
   
        if(!(kill(atoi(parameters[1]), SIGKILL )))
        {
			printf("Success!!!\n");
        
        }

		else
		{
			printf("Failure...\n");
		}
		

   
   
}

// All Commands for the Terminal - Akash Samlal & Jeremy Galvan
int commandList(char command[], char* parameters[], int lengthCommand, int * p, int sizeCommands, char currentDirectory[]) {
	int replayTrue = 0; 
	appendHistory(lengthCommand, command);

	// Clear Command
	if((strcmp(parameters[0], "clear") == 0)) 
		clearConsole();
	
	// Move to Directory Command
	else if((strcmp(parameters[0], "movetodir") == 0)) 
		moveDir(parameters, currentDirectory); 

	// Where am I command 
	else if((strcmp(parameters[0], "whereami") == 0)) 
		whereAmI(currentDirectory);
	
	// History Command 
	else if((strcmp(parameters[0], "history") == 0)) {
		if(sizeCommands > 1) {
			if(strcmp(parameters[1], "[-c]") == 0) {
				fclose(fopen("history.txt", "w")); 
				fclose(fopen("reverse.txt", "w")); 
				(*p) = 0; 
			}
		}
		else 
			lengthCommand = startHistory(lengthCommand, command, parameters);
	}
	
	// Replay Command
	else if((strcmp(parameters[0], "replay") == 0)) 
		replayTrue = replay(parameters, command, lengthCommand);
	
	// ByeBye Command
	else if((strcmp(parameters[0], "byebye") == 0)) 
		printf("\nSwitching back to normal terminal....\n\n");

	 else if((strcmp(parameters[0], "start") == 0)) 
		startprogram(parameters); 

    else if((strcmp(parameters[0], "background") == 0)) 
		backprogram(parameters);

    else if((strcmp(parameters[0], "dalek") == 0)) 
		dalekPID(parameters);

	// If the command doesn't exists report invalid 
	else 
		printf(RED "Invalid Command!\n" RESET);

 // Return lengthCommand, Replay Truth
 return lengthCommand, replayTrue; 
}

// Parser - Akash Samlal
int parser(char command[], char* parameters[], int replayTrue) {
	int i = 0; 
	int j = 0;
	int count = 0;

	char *copied; 
	char *array[100]; 
	char line[MAXLENGTH];
	char parseStrings[100][100]; 
	char *tmp; 

	// If user hit replay
	if(replayTrue == 1) {
		// Grab the entire line 
		while(1) {
			char c = command[count];
			line[count++] = c; 
			if(c == '\n') 
				break;
		} }
	else {
		// Grab the entire line 
		while(1) {
			int c = fgetc(stdin);
			line[count++] = (char)c; 
			if(c == '\n') 
				break;
		}
	}

	if(count == 1) 
		return 1; 
	
	copied = strtok(line, "\n"); 

	while(copied != NULL) {
		array[i++] = strdup(copied); 
		copied = strtok(NULL, "\n");
	}
	
	strcpy(command, array[0]); 

	i = 0;
	tmp = strtok(array[0], " ");

	// Fill in the parameters
	do {
		strcpy(parseStrings[i], tmp);
		parameters[i] = parseStrings[i];  
		i++;
   } while (tmp = strtok(NULL, " "));

	return i; 
}

// Prompt terminal with starting '#' line  - Akash Samlal
void initTerminal(char currentDirectory[]) {
	printf(BLUE "User@COP4600:" RESET YELLOW "%s# " RESET, currentDirectory);
}

// Main Function - Akash Samlal
int main() {  
  int lengthCommand = 0; 
  int sizeCommands = 0;
  int replayTrue = 0;
  char command[MAXLENGTH];  
  char * parameters[MAXLENGTH];
  char currentDirectory[MAXLENGTH];
	
   strcpy(currentDirectory, getcwd(currentDirectory, sizeof(currentDirectory)));

   clearConsole();

	FILE *histFile; 
	FILE *revFile; 

	if((histFile = fopen("history.txt", "r"))) {
		   remove("history.txt");
	}
	if((revFile = fopen("reverse.txt", "r"))) {
   		   remove("reverse.txt");
	}

   do { 	
	initTerminal(currentDirectory);
	sizeCommands = parser(command, parameters, replayTrue);
	lengthCommand++;
	lengthCommand, replayTrue = commandList(command, parameters, lengthCommand, &lengthCommand, sizeCommands, currentDirectory); 

	if(replayTrue == 1) 
		continue; 

  } while(!(strcmp(command, "byebye") == 0));
   
   remove("history.txt");
   remove("reverse.txt");
   
  return 0;

}