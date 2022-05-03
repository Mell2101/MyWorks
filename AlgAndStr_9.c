#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>


//������� ��������� �������� �� ������ ���������
int isUpper(char letter);

//������� ��������� �������� �� ����� ��������
int isLower(char letter);

//������� ���������� �������� ��������� ���� ������
char encryption(char letter, int key);


int main()
{
    char ch[10], text;
   // SetConsoleCP(1251);
  //  SetConsoleOutputCP(1251);
    char string[10];
    int key;
    printf("Enter string (without space end max 50 simb): ");
    gets(string);
    printf("Enter the key: ");
    scanf("%d",key);

    text = string[10];

    int i;
    for(i = 0; i < 50; i++){
        string[i] = encryption(string[i],key);
    }
    printf("\n Encrypted string: ");
    puts(string);

    printf("\n Do you want to do decryption? Yes/No \n");
    gets(ch);

    if(ch == "Yes"){
        printf("\nEnter string: %s", text);
        printf("\n");
    }
    else exit(0);

    return 0;
}

int isUpper(char letter){
    int result = 0;
    // ���� ������ ������ ���� ����� '�' � ������ ���� ����� '�' �� ������� 1
    if(letter >= 'A' && letter <= '�')
        result = 1;

        return result;
}



int isLower(char letter){
    int result = 0;
    //���� ������ ������ ���� ����� '�' � ������ ���� ����� '�' �� ������� 1
    if(letter >= '�' && letter <= '�')
        result = 1;
    return result;
}

char encryption(char letter, int key){
    if(isUpper(letter)){
        letter += key;
        if((int)letter > 90){
            key = letter - 90;
            letter = 65 + key - 1;
        }
    }
    if(isLower(letter)){
        letter += key;
        if((int)letter > 122){
            key = letter - 122;
            letter = 97 + key - 1;
        }
    }
    return letter;
}
