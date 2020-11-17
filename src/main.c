#include <stdio.h>
#include <espl_lib.h>

int main()
{
   unsigned int num;
   char *result;
   char continue_char = 'y';

   while(continue_char == 'y')
   {
      printf("Now the Game is On. Give me your number:");
      scanf("%u", &num);

      result = num_to_words(num);

      printf("\nYour number means:%s", result);
      printf("\nContinue?");
      
      do
      {
         //scanf("%c", &continue_char);
         continue_char = getchar();
         if(continue_char!='y' && continue_char!='n')
            printf("please enter y or n:");
      } while (continue_char!='y' && continue_char!='n');

   }

   printf("Goodbye!");
   return 0;
}

