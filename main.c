#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h> 

#define MAXLEN 32

void getPassword(char *inputBuffer, int bufferLength){ 
    //questa funzione prende in input la password ed evita overflows (se inserisco una password con len maggiore
	// di bufferLenght allora la password viene tagliata fino alla bufferLength lettera
	int ch;
	while ((getchar()) != '\n'); //per pulire il buffer da qualsiasi cosa ci sia
	printf("\nInserisci password: ");
    fgets(inputBuffer, bufferLength, stdin);
	
    if (inputBuffer[strlen(inputBuffer) -1] != '\n')
    {
        while ((ch = getchar()) != '\n' && ch != EOF); 
    }
    else
    {
        inputBuffer[strlen(inputBuffer) -1] = '\0'; 
    }
}

void RowAndColumnsFinder(int *row, int *column, char value){ 
   //trova row e column del carattere, li inserisce nei due puntatori e ritorna
   int i, j;
   
   char const CrypterAlphabet[10][10] = {
      // 0       1      2      3      4      5      6      7      8      9
        'a',    'b',   'c',   'd',   'e',   'f',   'g',   'h',   'i',   'j', // 0
        'k',    'l',   'm',   'n',   'o',   'p',   'q',   'r',   's',   't', // 1
        'u',    'v',   'w',   'x',   'y',   'z',   'A',   'B',   'C',   'D', // 2
        'E',    'F',   'G',   'H',   'I',   'J',   'K',   'L',   'M',   'N', // 3
        'O',    'P',   'Q',   'R',   'S',   'T',   'U',   'V',   'W',   'X', // 4
        'Y',    'Z',   '0',   '1',   '2',   '3',   '4',   '5',   '6',   '7', // 5
        '8',    '9',   ',',   ';',   '.',   ':',   '-',   '_',   '@',   '#', // 6
        '(',    ')',   '[',   ']',   '{',   '}',   '+',   '*',   '/',   '^', // 7
        '?',    '=',   '&',   '!',   '%',   '$',   '<',   '>',  '\0',  '\0', // 8
        '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0'  // 9
    };
   
   for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
      if(CrypterAlphabet[i][j] == value){
      	*row = i;
      	*column = j;
        return;
      }
    }
  }
}

void DecimalToBinaryConverter(int *rowBinary, int *columnBinary, int row, int column){ 
    //converte row e column in binari (inseriti in due array inizializzati a 0)
	int i = 3;
	 while (row > 0) {
        rowBinary[i] = row % 2;
        row = row / 2;
        i--;
    }
    i=3;
    while (column > 0) {
        columnBinary[i] = column % 2;
        column = column / 2;
        i--;  
    } 
}

void arrayMerger(int *finalBinary, int *rowBinary, int *columnBinary){ 
    //unisce i due binari separati in uno solo
	int i = 0, j;
	
	for(j = 0; j<4; j++){
		finalBinary[i] = rowBinary[j];
		i++;
	}
	for(j = 0; j<4; j++){
		finalBinary[i] = columnBinary[j];
		i++;
	}
}

void addFinalBinaryToCryptedPassword(int *finalBinary, int *cryptedPassword, int * z){
    int i = *z, j;	
	for(j = 0; j<8; j++){
		cryptedPassword[i] = finalBinary[j];
		i++;
	}
    *z = i;
}

void PasswordCrypter(char *password, int *zn, int *cryptedPassword){
	int row, column, i, j;
	int rowBinary[4], columnBinary[4];
	int finalBinary[8], z=0;
	
	for(i = 0; i<strlen(password); i++){
		
		for(j = 0; j<4; j++)
			rowBinary[j] = columnBinary[j] = 0;	
		
		RowAndColumnsFinder(&row, &column, password[i]);

		DecimalToBinaryConverter(rowBinary, columnBinary, row, column);
		
		arrayMerger(finalBinary, rowBinary, columnBinary);
		
        addFinalBinaryToCryptedPassword(finalBinary, cryptedPassword, &z);
        /*
		printf("Binari separati: ");
		for(j = 0; j<4; j++){
			printf("%d", rowBinary[j]);
		}
		printf(" - ");
		for(j = 0; j<4; j++){
			printf("%d", columnBinary[j]);
		}
		printf("\nBinario finale: ");
		for(j = 0; j<8; j++){
			printf("%d", finalBinary[j]);
		}
        printf("\ncryptedPassword: ");
        for(j = 0; j < z; j++){
            if (j%8==0 && j!=0) printf("-");
            printf("%d",cryptedPassword[j]);
        }
		printf("\n");
        */
	}
    
    *zn = z;
}



void removeCryptedPasswordToFinalBinary(char *cryptedPassword, int *z, int *finalBinary){
    int i = *z,j;	
	for(j = 0; j<8; j++){
		finalBinary[j] = (int)(cryptedPassword[i])-48;
		i++;
	}
    *z = i;
}

void arraySplitter(int *finalBinary, int *rowBinary, int *columnBinary){
    int i = 0, j;
	
	for(j = 0; j<4; j++){
		rowBinary[j] = finalBinary[i];
		i++;
	}
	for(j = 0; j<4; j++){
		columnBinary[j] = finalBinary[i];
		i++;
	}
}

void BinarytoDecimalConverter(int *rowBinary, int *columnBinary, int *row, int *column){
    int a=0,i;*row=0;*column=0;
    for (i = 3; i >= 0; i--){
        if(rowBinary[i] != 0){
            *row += pow(2, a);}
        if(columnBinary[i] != 0){
            *column += pow(2, a);}
        a++;
    }
}

void RowAndColumnsToLetter(int row, int column, char *letter){
    int i,j;
    char const CrypterAlphabet[10][10] = {
      // 0       1      2      3      4      5      6      7      8      9
        'a',    'b',   'c',   'd',   'e',   'f',   'g',   'h',   'i',   'j', // 0
        'k',    'l',   'm',   'n',   'o',   'p',   'q',   'r',   's',   't', // 1
        'u',    'v',   'w',   'x',   'y',   'z',   'A',   'B',   'C',   'D', // 2
        'E',    'F',   'G',   'H',   'I',   'J',   'K',   'L',   'M',   'N', // 3
        'O',    'P',   'Q',   'R',   'S',   'T',   'U',   'V',   'W',   'X', // 4
        'Y',    'Z',   '0',   '1',   '2',   '3',   '4',   '5',   '6',   '7', // 5
        '8',    '9',   ',',   ';',   '.',   ':',   '-',   '_',   '@',   '#', // 6
        '(',    ')',   '[',   ']',   '{',   '}',   '+',   '*',   '/',   '^', // 7
        '?',    '=',   '&',   '!',   '%',   '$',   '<',   '>',  '\0',  '\0', // 8
        '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0'  // 9
    };
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            if(i == row && j == column){
                *letter = CrypterAlphabet[i][j];
            }
        }
    }
}

void PasswordDecrypt(char *cryptedPassword, char *password){
    int row=0, column=0, i, j;
	int rowBinary[4], columnBinary[4];
	int finalBinary[8], z=0;
    char letter;
    int pwLength=0;

    for(i = 0; i<strlen(cryptedPassword)/8; i++){
        removeCryptedPasswordToFinalBinary(cryptedPassword, &z, finalBinary);
        arraySplitter(finalBinary, rowBinary, columnBinary);
        BinarytoDecimalConverter(rowBinary, columnBinary, &row, &column);
        RowAndColumnsToLetter(row, column, &letter);
        *password = letter;
        password++;
        pwLength++;

        /*STAMPA
        {
        
            printf("\nBinari separati: ");
            for(j = 0; j<4; j++){
                printf("%d", rowBinary[j]);
            }
            printf(" - ");
            for(j = 0; j<4; j++){
                printf("%d", columnBinary[j]);
            }
            printf("\nBinario finale: ");
            for(j = 0; j<8; j++){
                printf("%d", finalBinary[j]);
            }
        
        }
        */
    }
    *password = '\0';

    // for (int j = 0; j < pwLength; j++){
    //         printf("%c",*(password-pwLength+j));
    //     }
    // printf("\n");
}


int passPhrase(const char *passphrase){
    char cpw[MAXLEN*8], pw[MAXLEN];
    FILE *file;

    if ((file = fopen("passphrase.txt","r")) == NULL){
        printf("Errore nell'apertura del file");
        return 1;
    }

    fgets(cpw, MAXLEN*8, file);

    if(fclose(file) != 0){
        printf("Errore nella chiusura del file");
        return 1;
    }

    PasswordDecrypt(cpw,pw);

    return strcmp(passphrase, pw);
}


void new() {
    char password[MAXLEN];
    int cryptedPassword[MAXLEN*8], cPlenght = 0, i;
    FILE *file;

    getPassword(password, MAXLEN);
    
    PasswordCrypter(password, &cPlenght, cryptedPassword);

    for (i = 0; i < cPlenght; i++){
        printf("%d", cryptedPassword[i]);
    }
    
    if ((file = fopen("XXX.txt","a")) == NULL){
        printf("Errore nell'apertura del file");
        return;
    }

    for (i = 0; i < cPlenght; i++){
        fprintf(file, "%d", cryptedPassword[i]);
    }
    fprintf(file, "%c", '\n');

    if(fclose(file) != 0){
        printf("Errore nella chiusura del file");
        return;
    }

    printf("\n- Scrittura avvenuta con successo. -\n\n");
}

void view(){
    char password[MAXLEN];
    char cryptedPassword[MAXLEN*8];
    int pwLength, n = 0;
    FILE *file;

    if ((file = fopen("XXX.txt","r")) == NULL){
        printf("Errore nell'apertura del file");
        return;
    }

    printf("\n");
    while(fgets(cryptedPassword, MAXLEN*8, file) != NULL){
        printf("%d)",n);
        printf("%s",cryptedPassword);
        PasswordDecrypt(cryptedPassword, password);
        printf("%s\n",password);
        printf("\n");
        n++;
    }

    if(fclose(file) != 0){
        printf("Errore nella chiusura del file");
        return;
    }
}

void delete(){
    char passwordTemp[MAXLEN], deletedPassword[MAXLEN], cryptedPassword[MAXLEN*8];
    int cPassword[MAXLEN*8],cPlenght = 0, numstr = 2, i;
    FILE *file;
    char **buffer = (char **)malloc(numstr*sizeof(char *));
    
    getPassword(deletedPassword, MAXLEN);

    if ((file = fopen("XXX.txt","r")) == NULL){
        printf("Errore nell'apertura del file");
        return;
    }
    for(i=0; i<numstr; i++){
        buffer[i] = malloc(MAXLEN * sizeof(char));
    }

    int lenBuffer = 0;
    while(fgets(cryptedPassword, MAXLEN*8, file) != NULL){
        PasswordDecrypt(cryptedPassword, passwordTemp);
        if (strcmp(passwordTemp, deletedPassword) == 0){
            printf("\n- eliminata -\n");
            continue;
        }
        if(lenBuffer < numstr){
            strcpy(buffer[lenBuffer], passwordTemp);
        }
        else{
            if (lenBuffer == numstr){
                buffer = realloc(buffer, (lenBuffer+1) * sizeof(*buffer));
                buffer[lenBuffer] = malloc(MAXLEN * sizeof(char));
            }
            else{            
                buffer = realloc(buffer, (lenBuffer) * sizeof(*buffer));
                buffer[lenBuffer] = malloc(MAXLEN * sizeof(char));
            }
            strcpy(buffer[lenBuffer], passwordTemp);
        }
        lenBuffer++;
    }

    if(fclose(file) != 0){
        printf("Errore nella chiusura del file");
        return;
    }

    if ((file = fopen("XXX.txt","w")) == NULL){
        printf("Errore nell'apertura del file");
        return;
    }

    for (i = 0; i < lenBuffer; i++){
        PasswordCrypter(buffer[i], &cPlenght, cPassword);
        for (int i = 0; i < cPlenght; i++){
            fprintf(file, "%d", cPassword[i]);
        }
        fprintf(file, "%c", '\n');
    }

    if(fclose(file) != 0){
        printf("Errore nella chiusura del file");
        return;
    }

    free(buffer);
}

void modify(){
    char password[MAXLEN];
    int cryptedPassword[MAXLEN*8],cPlenght;
    FILE *file;

    getPassword(password,MAXLEN);
    PasswordCrypter(password,&cPlenght,cryptedPassword);

    if ((file = fopen("passphrase.txt","w")) == NULL){
        printf("Errore nell'apertura del file");
        return;
    }

    for (int i = 0; i < cPlenght; i++){
        fprintf(file, "%d", cryptedPassword[i]);
    }
    fprintf(file, "%c", '\n');

    if(fclose(file) != 0){
        printf("Errore nella chiusura del file");
        return;
    }

    printf("\n- Scrittura avvenuta con successo. -\n\n");
}

int main(int argc, char const *argv[]){
    int scelta, check;
    
    if(passPhrase(argv[1])){
        printf("password errata");
        return -1;
    }
    
    printf("\nBenvenuto, questo e' un Password-Manager.\n");
    printf("   (password fino a 32 caratteri)        \n");
    printf("\npuoi eseguire le seguenti opzioni:\n\n");

    /* menu */
    do{
        printf("\n<1> Salva una nuova password\n");
        printf("<2> Visiona le password\n");
        printf("<3> Elimina una password\n");
        printf("<4> modifica la password di accesso\n");
        printf("<0> Termina il programma\n\n");
        printf("< >");
        printf("\033[2D");

        check = scanf("%d",&scelta);
        if (check != 1 || scelta == EOF || scelta < 0 || scelta > 4){
            printf("\nERRORE - inserito un valore non appartenente alle scelte disponibili\n");
            scelta = -1;
            fflush(stdin);
        }
        
        switch (scelta) {
            case -1: continue;
            case 1: new();break;
            case 2: view();break;
            case 3: delete();break;
            case 4: modify();
        }
    }while(scelta != 0);

    printf("\nGrazie di avermi utilizzatp ^_^ Ciaooo!\n");

    return 0;
}