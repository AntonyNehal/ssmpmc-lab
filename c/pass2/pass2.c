#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
    FILE *l, *i, *o, *s, *as, *ob;
    int kandu = 0; 
    char opcode1[100], value[100], symbol1[100], symbvalue[100];
    char label[100], opcode[100], pgname[100], operand[100], address[100], length[100], size[100];

    // Open files
    l = fopen("length.txt", "r");
    i = fopen("intermediate.txt", "r");
    as = fopen("assem.txt", "w");
    ob = fopen("object.txt", "w");

    fscanf(i, "%s%s%s%s", address, pgname, opcode, operand);
    fscanf(l, "%s%s", length, size);

    if (strcmp(opcode, "START") == 0) {
        fprintf(as, "%s\t\t%s\t\t%s\t\t%s  **\n", address, pgname, opcode, operand); // List assembly listing (start,address)
        fprintf(ob, "H^%s^%06d^%06d\n", pgname, atoi(operand), atoi(length)); // Write header record
        fprintf(ob, "T^%06d^%02d", atoi(operand), atoi(size)); // Initialize text record
        fscanf(i, "%s%s%s%s", address, label, opcode, operand); // Read next line
    }

    while (strcmp(opcode, "END") != 0) {
        kandu = 0;
        o = fopen("optab.txt", "r");
        
        // Search for opcode in optab
        while (fscanf(o, "%s", opcode1) != EOF) {
            fscanf(o, "%s", value);
            if (strcmp(opcode, opcode1) == 0) {
                kandu = 1;
                break;
            }
        }
        fclose(o);

        if (kandu == 1) { // If opcode found
            strcpy(symbvalue, "0000");
            s = fopen("symtab.txt", "r");

            // Search for symbol value in symtab
            while (fscanf(s, "%s", symbol1) != EOF) {
                fscanf(s, "%s", symbvalue);
                if (strcmp(symbol1, operand) == 0) {
                    break;
                }
            }
            fclose(s);

            if (strcmp(operand, "") != 0) { // If operand field is not empty
                fprintf(ob, "^%s%s", value, symbvalue); // Write to object program
                fprintf(as, "%s\t%s\t%s\t%s\t%s%s\n", address, label, opcode, operand, value, symbvalue); // Write assembly listing
            } else { // If operand field is empty
                fprintf(ob, "^%s%s", symbvalue, value); // Write object code with 4 0's appended
                fprintf(as, "%s\t%s\t%s\t%s\t%s%s\n", address, label, opcode, operand, symbvalue, value); // Write assembly listing
            }
        } 
        else if (strcmp(opcode, "WORD") == 0 || strcmp(opcode, "BYTE") == 0) {
            if (strcmp(opcode, "WORD") == 0) { // If opcode is WORD
                fprintf(ob, "^%06x", atoi(operand)); // Convert integer to hex and format as 6-digit
                fprintf(as, "%s\t%s\t%s\t%s\t%06x\n", address, label, opcode, operand, atoi(operand)); // Write to assembly listing
            } else if (strcmp(opcode, "BYTE") == 0) { // If opcode is BYTE
                fprintf(as, "%s\t%s\t%s\t%s\t", address, label, opcode, operand); // Write to assembly listing

                fprintf(ob, "^");
                if (operand[0] == 'X') { // For hexadecimal constant
                    fprintf(as, "%s", operand);
                    fprintf(ob, "%s", operand);
                } else { // For character constant
                    for (size_t j = 2; j < strlen(operand) - 1; j++) { // Skip C' and closing '
                        fprintf(ob, "%x", operand[j]); // Write ASCII in hex code
                        fprintf(as, "%x", operand[j]); // Write to assembly listing
                    }
                }
                fprintf(as, "\n"); // New line in assembly listing
            }
        }

        if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "RESW") == 0) {
            fprintf(as, "%s\t%s\t%s\t%s     **\n", address, label, opcode, operand); // Write assembly listing with no object code
        }
        
        fscanf(i, "%s%s%s%s", address, label, opcode, operand); // Read next intermediate line
    }

    fprintf(as, "%s\t\t\t%s\t\t%s\t\t\t%s\t\t**", address, label, opcode, operand); // Write last assembly listing
    unsigned int integer;
    sscanf(operand, "%x", &integer); // Convert hex string to integer
    fprintf(ob, "\nE^%06x", integer); // Write end record

    // Close all files
    fclose(l);
    fclose(ob);
    fclose(as);
    fclose(i);

    return 0;
}
