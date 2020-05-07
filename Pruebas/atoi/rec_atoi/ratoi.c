int
ratoi(int acc, char *e)
{
  unsigned int i;

  if (! *e ){
      return acc;
  }
  else {
      /* go recursive */
      i =  *e - '0';
      return ratoi( acc * 10 + i, e + 1);
  }
}

