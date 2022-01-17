#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

#define TOTAL_CELLS 3001
#define MAX_INSTRUCTIONS 10000
#define MAX_INSTRUCTION_SIZE 40

char* instruction1="આગળ\n";
char* instruction2="પાછળ\n";
char* instruction3="વધારો\n";
char* instruction4="ઘટાડો\n";
char* instruction5="તપાસો\n";
char* instruction6="છાપો\n";
char* instruction7="સંપૂર્ણ છાપો\n";	
char* instruction8="ઇનપુટ\n";	
char* instruction9="ડબલ\n";	
char* sad_emote="     .-\"\"\"\"\"\"-.\n   .\'          \'.\n  /   O      O   \\\n :                :\n |                |\n :    .------.    :\n  \\  \'        \'  /\n   \'.          .\'\n     \'-......-\'";

struct Cell{
	int value;
	int index;
	int type;
};

char instructions[MAX_INSTRUCTIONS][MAX_INSTRUCTION_SIZE];
struct Cell cells[TOTAL_CELLS];


int interpret(FILE* file){
	int line_count=0;
	for (char c = getc(file); c != EOF; c = getc(file))
		if (c == '\n') // Increment line_count if this character is newline
			line_count = line_count + 1;
	// printf("%d\n",line_count);
	rewind(file);
	if (line_count>MAX_INSTRUCTIONS)
	{
		fprintf(stderr,"Too long program, cant have more than %d instructions sorry\n\n%s",MAX_INSTRUCTIONS,sad_emote);
		exit(1);
	}
	for (int i = 0; i <= line_count; ++i)
	{
		fgets(instructions[i],MAX_INSTRUCTION_SIZE,file);
		// printf("%s",instructions[i]);
	}
	int current_cell=0;
	int current_instruction=0;
	while(current_instruction<=line_count){
		if (strcmp(instructions[current_instruction],instruction1)==0)
		{
			current_cell=(current_cell+1)%TOTAL_CELLS;
		}else if (strcmp(instructions[current_instruction],instruction2)==0)
		{
			current_cell=(current_cell+TOTAL_CELLS-1)%TOTAL_CELLS;
		}else if (strcmp(instructions[current_instruction],instruction3)==0)
		{
			++cells[current_cell].value;
		}else if (strcmp(instructions[current_instruction],instruction4)==0)
		{
			--cells[current_cell].value;
		}else if (strcmp(instructions[current_instruction],instruction5)==0)
		{
			if (cells[current_cell].value==0)
			{
				current_instruction=cells[0].value;
			}else{
				current_instruction=cells[1].value;
			}
			continue;
		}else if (strcmp(instructions[current_instruction],instruction6)==0)
		{
			printf("%c",cells[current_cell].value);
		}else if (strcmp(instructions[current_instruction],instruction7)==0)
		{
			for (int i = 0; i < TOTAL_CELLS; ++i)
			{
				if (cells[i].value!=0)
				{
					printf("%c",cells[i].value);
				}
			}
		}else if (strcmp(instructions[current_instruction],instruction8)==0)
		{
			scanf("%d",&cells[current_cell].value);
		}else if (strcmp(instructions[current_instruction],instruction9)==0)
		{
			cells[current_cell].value*=2;
		}
		++current_instruction;
	}
}

int main(int argc, char** argv){
	if (argc!=2){
		fprintf(stderr, "incorrect number of arguments\n\n%s",sad_emote);
		exit(1);
	}
	FILE* source=fopen(argv[1],"r");
	if(!source){
		fprintf(stderr,"Could not open source file %s\n\n%s",argv[1],sad_emote);
		exit(1);
	}
	for (int i = 0; i < TOTAL_CELLS; ++i)
	{
		cells[i].value=0;
		cells[i].index=i;
		cells[i].type=2;
	}
	cells[0].type=0;
	cells[1].type=1;
	interpret(source);
	return 0;
}
