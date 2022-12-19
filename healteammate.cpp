void healtemmate ()
{
    if ( healthlevelc1 < 2  || healthlevelc2 < 2)
    {
    srand(time(0));
     // Generate a random number between 0 and 1
    int randNum = rand() % 2;

    // Return true if the random number is 1, false if it is 0
  if (randNum == 1) {
    if heathlevelc1 > healthlevelc2 
    {
        healthlevelc2++;
        healthlevelc1--;
    } else 
    {
        healthlevelc1++;
        healthlevelc2--;
    }
     return 0;
    }

    }
}