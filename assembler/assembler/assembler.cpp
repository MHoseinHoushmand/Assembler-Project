// <<In The Name of God>>
//simple assembler of miniature
//universiry of Isfahan
//by:Mohammad Hussein Houshmand (983613064)
//time complexity: (n)log(n)log(instructions number) or 4nlogn 
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

struct lable
{
	int dec_address;
	char *name;

};
struct instruction
{
	char* name;
	short oppcode;
	char type;
};


int row_input_size() {
	FILE *input;

	fopen_s(&input, "assmble_program.as.txt", "r");
	char str[50];
	int counter = 0;
	while (!feof(input)) {
		fgets(str, 50, (FILE*)input);
		counter++;
	}
	fclose(input);
	return counter;

}



void extract_file_input_in_row(int number, char**rinput) {
	FILE *input;
	fopen_s(&input, "assmble_program.as.txt", "r");
	int i = 0;
	while (!feof(input)) {
		fgets(rinput[i], 50, (FILE*)input);
		i++;
	}
	for (int i = 0; i<number - 1; i++)
		rinput[i][strlen(rinput[i]) - 1] = '\0';
}

void Merge(lable*array, int start, int end, int mid) {
	int i, j, k;
	int n1 = mid - start + 1;
	int n2 = end - mid;
	lable*left = (lable*)malloc(n1 * sizeof(lable));
	lable*right = (lable*)malloc(n2 * sizeof(lable));
	for (i = 0; i <= n1 - 1; i++)
		left[i] = array[start + i];
	for (i = 0; i <= n2 - 1; i++)
		right[i] = array[mid + 1 + i];
	i = 0;
	j = 0;
	for (k = start; k <= end; k++) {
		if (i < n1 && j < n2) {
			if (strcmp(left[i].name, right[j].name) != 1) {
				array[k] = left[i];
				i++;
			}
			else
				if (strcmp(left[i].name, right[j].name) == 1) {
					array[k] = right[j];
					j++;
				}
		}
		else {
			if (i == n1) {
				array[k] = right[j];
				j++;
			}
			else {
				if (j == n2) {
					array[k] = left[i];
					i++;
				}
			}			
		}
	}

	free(left);
	free(right);

}


void merge_sort(lable* array, int start, int end) {
	if (start<end) {
		int mid = ((start + end) / 2);
		merge_sort(array, start, mid);
		merge_sort(array, mid + 1, end);
		Merge(array, start, end, mid);



	}
}

int main()
{
	int  row_size = row_input_size();
	int i;
	char* str;

	char** full_rows_folder = (char**)malloc(row_size * sizeof(char*));
	for (int i = 0; i < row_size; i++)
		full_rows_folder[i] = (char*)malloc(50 * sizeof(char));

	extract_file_input_in_row(row_size, full_rows_folder);
	for (int i = 0; i<row_size; i++) {
		str = full_rows_folder[i];
		printf("%s\n", full_rows_folder[i]);
	}
	////////////////////////////////////////set lable name & address decimal

	int lable_size = 0;
	for (i = 0; i<row_size; i++) {
		str = full_rows_folder[i];
		if (str[0] != ' ')
			lable_size++;
	}

	lable* symbol_table = (lable*)malloc(6 * sizeof(lable));
	int t = 0;
	for (i = 0; i < row_size; i++) {
		str = full_rows_folder[i];
		if (str[0] != ' ') {
			symbol_table[t].name = (char*)malloc(6 * sizeof(char));

			strncpy_s(symbol_table[t].name, 7, str, 6);
			symbol_table[t].dec_address = i;
			t++;
		}
	}
	merge_sort(symbol_table, 0, lable_size - 1);
	

	///////////////////////////////////////// instruction_table 
	instruction* instruction_table = (instruction*)malloc(15 * sizeof(instruction));
	for (i = 0; i < 15; i++) {
		instruction_table[i].name = (char*)malloc(7 * sizeof(char));
	}


	instruction_table[0].name = "add   ";
	instruction_table[0].oppcode = 0;
	instruction_table[0].type = 'R';
	////////
	instruction_table[1].name = "addi  ";
	instruction_table[1].oppcode = 5;
	instruction_table[1].type = 'I';
	////////
	instruction_table[2].name = "beq   ";
	instruction_table[2].oppcode = 11;
	instruction_table[2].type = 'I';
	////////
	instruction_table[3].name = "halt  ";
	instruction_table[3].oppcode = 14;
	instruction_table[3].type = 'J';
	////////
	instruction_table[4].name = "j     ";
	instruction_table[4].oppcode = 13;
	instruction_table[4].type = 'J';
	////////
	instruction_table[5].name = "jalr  ";
	instruction_table[5].oppcode = 12;
	instruction_table[5].type = 'I';
	////////
	instruction_table[6].name = "lui   ";
	instruction_table[6].oppcode = 8;
	instruction_table[6].type = 'I';
	////////
	instruction_table[7].name = "lw    ";
	instruction_table[7].oppcode = 9;
	instruction_table[7].type = 'I';
	////////
	instruction_table[8].name = "nand  ";
	instruction_table[8].oppcode = 4;
	instruction_table[8].type = 'R';
	////////
	instruction_table[9].name = "or    ";
	instruction_table[9].oppcode = 3;
	instruction_table[9].type = 'R';
	////////
	instruction_table[10].name = "ori   ";
	instruction_table[10].oppcode = 7;
	instruction_table[10].type = 'I';
	////////
	instruction_table[11].name = "slt   ";
	instruction_table[11].oppcode = 2;
	instruction_table[11].type = 'R';
	////////
	instruction_table[12].name = "slti  ";
	instruction_table[12].oppcode = 6;
	instruction_table[12].type = 'I';
	////////
	instruction_table[13].name = "sub   ";
	instruction_table[13].oppcode = 1;
	instruction_table[13].type = 'R';
	////////
	instruction_table[14].name = "sw    ";
	instruction_table[14].oppcode = 10;
	instruction_table[14].type = 'I';
	////////
	//Checking error(lable repetiation)
	for (i = 0; i < lable_size - 1; i++) {
		if (strcmp(symbol_table[i].name, symbol_table[i + 1].name) == 0) {
			printf("run: exit(1)\n");
			for (int i = 0; i < row_size; i++)
			{
				char* f = full_rows_folder[i];
				free(f);
			}

			free(instruction_table);
			return 0;
		}

	}

	/////////////////////////////////set line code
	FILE *output_f;
	int j;
	fopen_s(&output_f,"assemble_program.mc.txt", "w");

	short check;
	char type;
	long int output;
	char *op_str = (char*)malloc(7 * sizeof(char));
	//Check each line
	for (i = 0; i < row_size; i++) {
		short high = 14;
		short low = 0;
		short mid;
		char lable[7];
		for (j = 0; j < 6; j++) {
			if (full_rows_folder[i][j + 7] != '\0') {
				op_str[j] = full_rows_folder[i][j + 7];
			}
			else
				op_str[j] = ' ';
		}
		op_str[6] = '\0';
			//Search oppcode and calculate result in decimal output
			while (high >= low)
			{
				mid = (high + low) / 2;
				check = strcmp(op_str, instruction_table[mid].name);
				if (check == 0) {//found
					output = 0;
					int d_num = 0, s_num = 0, t_num = 0, op=0,imm=0;
					bool find_lable = false;

					type = instruction_table[mid].type;
                    short k = 16;
					//R output
					if (type == 'R') {						
						op = instruction_table[mid].oppcode;
						d_num = full_rows_folder[i][k] - '0';
						k++;
						if (full_rows_folder[i][k] != ',') {
							d_num = 10 * d_num + (full_rows_folder[i][k] - '0');
							k += 2;
						}
						else
							k++;
						s_num = full_rows_folder[i][k] - '0';
						k++;
						if (full_rows_folder[i][k] != ',') {
							s_num = 10 * s_num + (full_rows_folder[i][k] - '0');
							k += 2;
						}
						else
							k++;
						t_num = full_rows_folder[i][k] - '0';
						k++;
						if (full_rows_folder[i][k] != ' ' && full_rows_folder[i][k]!='\0' && full_rows_folder[i][k]!='#') {
							t_num = 10 * t_num + (full_rows_folder[i][k] - '0');
							k += 2;
						}
						else
							k++;
						output += d_num * 4096;
						output += t_num * 65536;
						output += s_num * 1048576;
						output += op * 16777216;
						fprintf(output_f, "%d\n", output);

					}
					///I_type
					if (type == 'I') {
						short sign = 1;
						op = instruction_table[mid].oppcode;
						if (instruction_table[mid].name == "addi  " || instruction_table[mid].name == "slti  " || instruction_table[mid].name == "ori   ") {
							t_num = full_rows_folder[i][k] - '0';
							k++;
							if (full_rows_folder[i][k] != ',') {
								t_num = 10 * t_num + (full_rows_folder[i][k] - '0');
								k += 2;
							}
							else
								k++;
							s_num = full_rows_folder[i][k] - '0';
							k++;
							if (full_rows_folder[i][k] != ',') {
								s_num = 10 * s_num + (full_rows_folder[i][k] - '0');
								k += 2;
							}
							else
								k++;
							if (full_rows_folder[i][k] == '-') {
								sign = -1;
								k++;
							}
							do {
								imm *= 10;
								imm += full_rows_folder[i][k] - '0';
								k++;
							} while (full_rows_folder[i][k] != ' ' && full_rows_folder[i][k] != '#' && full_rows_folder[i][k] != '\0');
							imm = sign*imm;
							if (sign == -1)
								imm = 65536 + imm;
							//Checking error(illegal offset or immediate)
							if ( imm > 65535 ) {
								
								printf("run: exit(1)\n");
								for (int i = 0; i < row_size; i++)
								{
									char* f = full_rows_folder[i];
									free(f);
								}
	
								free(instruction_table);
								free(op_str);
								return 0;


							}

							output += imm;
							output += t_num * 65536;
							output += s_num * 1048576;
							output += op * 16777216;
							fprintf(output_f, "%d\n", output);
						}
						///////
						if (instruction_table[mid].name == "lui   ") {
							t_num = full_rows_folder[i][k] - '0';
							k++;
							if (full_rows_folder[i][k] != ',') {
								t_num = 10 * t_num + (full_rows_folder[i][k] - '0');
								k += 2;
							}
							else
								k++;
							if (full_rows_folder[i][k] == '-') {
								sign = -1;
								k++;
							}
							do {
								imm *= 10;
								imm += full_rows_folder[i][k] - '0';
								k++;
							} while (full_rows_folder[i][k] != ' ' && full_rows_folder[i][k] != '#' && full_rows_folder[i][k] != '\0');
							imm = sign*imm;
							if (sign == -1)
								imm = 65536 + imm;
							//Checking error(illegal offset or immediate)
							if (imm > 65535) {

								printf("run: exit(1)\n");
								for (int i = 0; i < row_size; i++)
								{
									char* f = full_rows_folder[i];
									free(f);
								}
				
								free(instruction_table);
								free(op_str);
								return 0;


							}

							output += imm;
							output += t_num * 65536;
							output += op * 16777216;
							fprintf(output_f, "%d\n", output);
						}
						if (instruction_table[mid].name == "lw    " || instruction_table[mid].name == "sw    " || instruction_table[mid].name == "beq   ") {
							t_num = full_rows_folder[i][k] - '0';
							k++;
							if (full_rows_folder[i][k] != ',') {
								t_num = 10 * t_num + (full_rows_folder[i][k] - '0');
								k += 2;
							}
							else
								k++;
							s_num = full_rows_folder[i][k] - '0';
							k++;
							if (full_rows_folder[i][k] != ',') {
								s_num = 10 * s_num + (full_rows_folder[i][k] - '0');
								k += 2;
							}
							else
								k++;
							if (full_rows_folder[i][k] == '-') {
								sign = -1;
								k++;
							}

							if (full_rows_folder[i][k] >= 48 && full_rows_folder[i][k] <= 57) {
								do {
									imm *= 10;
									imm += full_rows_folder[i][k] - '0';
									k++;
								} while (full_rows_folder[i][k] != ' ' && full_rows_folder[i][k] != '#' && full_rows_folder[i][k] != '\0');
							}
							else {
								for (int t = 0; t < 6; t++) {
									if (full_rows_folder[i][k] != '\0')
										lable[t] = full_rows_folder[i][k];
									else
										lable[t] = ' ';
									k++;
								}
								
								lable[6] = '\0';
								//find lable
								int low1 = 0;
								int high1 = lable_size - 1;
								int mid1;
								while (high1>=low1)
								{
									mid1 = (high1 + low1) / 2;
									if (strcmp(lable, symbol_table[mid1].name) == 0) {
										imm += symbol_table[mid1].dec_address ;
										find_lable = true;
										break;
									}
									if (strcmp(lable, symbol_table[mid1].name) == 1)
										low1 = mid1 + 1;
									if (strcmp(lable, symbol_table[mid1].name) == -1)
										high1 = mid1 - 1;
								}
								//Checking error(usage of illegal lable)
								if (find_lable == false) {
									printf("run: exit(1)\n");
									for (int i = 0; i < row_size; i++)
									{
										char* f = full_rows_folder[i];
										free(f);
									}
	
									free(instruction_table);
									free(op_str);
									return 0;

								}


							}
							if (sign == -1)
								imm = 65536 + imm;
						    imm = sign*imm;
							if (instruction_table[mid].name == "beq   ")
								imm=imm-1-i;

	

							//Checking error(illegal offset or immediate)
							if (imm > 65535) {

								printf("run: exit(1)\n");
								for (int i = 0; i < row_size; i++)
								{
									char* f = full_rows_folder[i];
									free(f);
								}
								free(instruction_table);
								free(op_str);
								return 0;


							}

							output += imm;
							output += t_num * 65536;
							output += s_num * 1048576;
							output += op * 16777216;
							fprintf(output_f, "%d\n", output);
						}
						if (instruction_table[mid].name == "jalr  ") {
							t_num = full_rows_folder[i][k] - '0';
							k++;
							if (full_rows_folder[i][k] != ',') {
								t_num = 10 * t_num + (full_rows_folder[i][k] - '0');
								k += 2;
							}
							else
								k++;
							if (full_rows_folder[i][k] != ',') {
								s_num = 10 * s_num + (full_rows_folder[i][k] - '0');
								k += 2;
							}
							else
								k++;
							output += t_num * 65536;
							output += s_num * 1048576;
							output += op * 16777216;
							fprintf(output_f, "%d\n", output);
						}
					}

					///j_type
					if (type == 'J') {
						short sign=1;
						op = instruction_table[mid].oppcode;
						if (instruction_table[mid].name == "halt  ") {
							output += op * 16777216;
							fprintf(output_f, "%d\n", output);
						}
						if (instruction_table[mid].name == "j     ") {
							if (full_rows_folder[i][k] == '-') {
								sign = -1;
								k++;
							}
							if (full_rows_folder[i][k] >= 48 && full_rows_folder[i][k] <= 57) {
								do {
									imm *= 10;
									imm += full_rows_folder[i][k] - '0';
									k++;
								} while (full_rows_folder[i][k] != ' ' && full_rows_folder[i][k] != '#' && full_rows_folder[i][k] != '\0');
							}
							else {
								for (int t = 0; t < 6; t++) {
									if (full_rows_folder[i][k] != '\0')
										lable[t] = full_rows_folder[i][k];
									else
										lable[t] = ' ';
									k++;
								}

								lable[6] = '\0';

								int low1 = 0;
								int high1 = lable_size - 1;
								int mid1;
								while (high1 >= low1)
								{
									mid1 = (high1 + low1) / 2;
									if (strcmp(lable, symbol_table[mid1].name) == 0) {
										imm += symbol_table[mid1].dec_address;
										find_lable = true;
										break;
									}
									if (strcmp(lable, symbol_table[mid1].name) == 1)
										low1 = mid1 + 1;
									if (strcmp(lable, symbol_table[mid1].name) == -1)
										high1 = mid1 - 1;
								}
								//Checking error(usage of illegal lable)
								if (find_lable == false) {

									printf("run: exit(1)\n");
									for (int i = 0; i < row_size; i++)
									{
										char* f = full_rows_folder[i];
										free(f);
									}
									free(instruction_table);
									free(op_str);
									return 0;

								}

							}
							imm = sign*imm;
							if (sign == -1)
								imm = 65536 + imm;
							//Checking error(illegal offset or immediate)
							if (imm > 65535) {

								printf("run: exit(1)\n");
								for (int i = 0; i < row_size; i++)
								{
									char* f = full_rows_folder[i];
									free(f);
								}
								free(instruction_table);
								free(op_str);
								return 0;


							}
							output += imm;
							output += op * 16777216;
							fprintf(output_f, "%d\n", output);
						}
					}
					break;


				}

				if (check == 1)
					low = mid + 1;
				if (check == -1)
					high = mid - 1;


			}
			if (low > high) {
				bool find_lable = false;
				short k = 16;
				short sign = 1;
				int tot = 0;
				if (strcmp(op_str, ".fill ") == 0 || strcmp(op_str, ".space") == 0) {
					if (full_rows_folder[i][k] == '-') {
						sign = -1;
						k++;
					}
					if (!(full_rows_folder[i][k] >= 48 && full_rows_folder[i][k] <= 57)) {
						for (int t = 0; t < 6; t++) {
							if (full_rows_folder[i][k] != '\0')
								lable[t] = full_rows_folder[i][k];
							else
								lable[t] = ' ';
							k++;
						}
						lable[6] = '\0';
						int low1 = 0;
						int high1 = lable_size - 1;
						int mid1;
						while (high1 >= low1)
						{
							mid1 = (high1 + low1) / 2;
							if (strcmp(lable, symbol_table[mid1].name) == 0) {
								tot += symbol_table[mid1].dec_address;
								find_lable = true;
								break;
							}
							if (strcmp(lable, symbol_table[mid1].name) == 1)
								low1 = mid1 + 1;
							if (strcmp(lable, symbol_table[mid1].name) == -1)
								high1 = mid1 - 1;
						}
						//Checking error(usage of illegal lable)
						if (find_lable == false) {

							printf("run: exit(1)\n");
							for (int i = 0; i < row_size; i++)
							{
								char* f = full_rows_folder[i];
								free(f);
							}
							free(instruction_table);
							free(op_str);
							return 0;

						}


					}
					else {
						do {
							tot *= 10;
							tot += full_rows_folder[i][k] - '0';
							k++;
						} while (full_rows_folder[i][k] != ' ' && full_rows_folder[i][k] != '#' && full_rows_folder[i][k] != '\0');
                    tot *= sign;
					}
					fprintf(output_f, "%d\n", tot);
					
				}
				else {
					//Checking error(illegal oppcode)
					printf("run: exit(1)\n");
					for (int i = 0; i < row_size; i++)
					{
						char* f = full_rows_folder[i];
						free(f);
					}
					free(instruction_table);
					free(op_str);
					return 0;
				}
			}

	}
	printf("run: exit(0)\n");
	for (int i = 0; i < row_size; i++)
	{
		char* f = full_rows_folder[i];
		free(f);
	}
	free(instruction_table);
	free(op_str);
	return 0;
}
