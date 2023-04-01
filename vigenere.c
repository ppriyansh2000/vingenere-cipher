// Priyansh Patel
// Assignment: Vigenere Cipher

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARRAY_SIZE 512

// ignores everything other than alphabets and turns them to lowercase
char* lowercase(char* text)
{
  int len;
  int count = 0;
  char* lowercase = malloc(sizeof(char) * (ARRAY_SIZE + 1));

  len = strlen(text);

  // coverts text to only lowercase alphabets
  for (int i = 0; i < len; i++)
  {
    if (isalpha(text[i]))
    {
      if (isupper(text[i]))
      {
        lowercase[count] = tolower(text[i]);
      }
      else
      {
        lowercase[count] = text[i];
      }
      count++;
    }
  }

  return lowercase;
}

// pads plaintext file with 'x'
char* plaintext_padding(char* text)
{
  int len = strlen(text);
  int counter = 0;

  for (int i = len; i < ARRAY_SIZE; i++)
  {
    text[i] = 'x';
    counter++;
  }

  return text;
}

// performs the encryption
char* vigenere_cipher(char* key, char* plaintext)
{
  char* cipher = malloc(sizeof(char) * (ARRAY_SIZE + 1));
  int counter = 0;
  int key_length = strlen(key);

  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    // go back to the begining key character
    if (key_length == counter)
    {
      counter = 0;
    }

    // cipher calculations
    cipher[i] = ((key[counter] - 'a' + plaintext[i] - 'a') % 26) + 'a';
    counter++;
  }

  return cipher;
}

// prints output 80 charcters per line
void print_lines(char* text)
{
  int length = strlen(text);

  for (int i = 0; i < length; i++)
  {
    if ((i % 80) == 0)
    {
      printf("\n");
    }
    printf("%c", text[i]);
  }

  return;
}

// print the output
void print_output(char* key, char* plaintext, char* cipher)
{
  printf("\n\n");
  printf("Vigenere Key:\n");
  print_lines(key);
  printf("\n\n\n");

  printf("Plaintext:\n");
  print_lines(plaintext);
  printf("\n\n\n");

  printf("Ciphertext:\n");
  print_lines(cipher);
  printf("\n");

  return;
}

int main(int argc, char** argv)
{
  // variables and pointers
  int count = 0;
  char* tmp = malloc(sizeof(char) * (ARRAY_SIZE + 1));
  char* key = malloc(sizeof(char) * (ARRAY_SIZE + 1));
  char* plaintext = malloc(sizeof(char) * (ARRAY_SIZE + 1));
  char* cipher = malloc(sizeof(char) * (ARRAY_SIZE + 1));

  FILE* key_file = NULL;
  FILE* plaintext_file = NULL;

  // check number of command line arguements
  if (argc != 3)
  {
    printf("incorrect number of arguements\n");
    return 1;
  }

  // open files for reading
  key_file = fopen(argv[1], "r");
  plaintext_file = fopen(argv[2], "r");

  // check if files opened properly
  if (key_file == NULL)
  {
    printf("key_file did not open\n");
    return 1;
  }

  if (plaintext_file == NULL)
  {
    printf("plaintext_file did not open\n");
    return 1;
  }

  // read in charaters from the file for key
  while (fgets(tmp, (ARRAY_SIZE + 1), key_file) != NULL)
  {
    count++;

    if (count == 1)
    {
      // tmp now contains lowercase alphabets
      tmp = lowercase(tmp);
      strcpy(key, tmp);
    }
    else
    {
      tmp = lowercase(tmp);
      strcat(key, tmp);
    }

  }

  // reset tmp string and counter
  tmp[0] = '\0';
  count = 0;

  // read in charaters from the file for plaintext
  while (fgets(tmp, (ARRAY_SIZE + 1), plaintext_file) != NULL)
  {
    count++;

    if (count == 1)
    {
      tmp = lowercase(tmp);
      strcpy(plaintext, tmp);
    }
    else
    {
      tmp = lowercase(tmp);
      strcat(plaintext, tmp);
    }

  }

  // close the files
  fclose(key_file);
  fclose(plaintext_file);

  // checks to keep the string length to 512 characters
  if (strlen(key) > (ARRAY_SIZE + 1))
  {
    key[ARRAY_SIZE] = '\0';
  }

  // pad with 'x' if string length is below 512 characters
  if (strlen(plaintext) > (ARRAY_SIZE + 1))
  {
    plaintext[ARRAY_SIZE] = '\0';
  }
  else
  {
    plaintext = plaintext_padding(plaintext);
  }

  // perform the cipher encryption
  cipher = vigenere_cipher(key, plaintext);

  if (strlen(cipher) > (ARRAY_SIZE + 1))
  {
    cipher[ARRAY_SIZE] = '\0';
  }

  // print output
  print_output(key, plaintext, cipher);

  // free dynamically allocated memory
  free(tmp);
  free(key);
  free(plaintext);
  free(cipher);

  return 0;
}
