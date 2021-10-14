#ifndef IS_PRIME
#define IS_PRIME
bool is_prime(int num) {
  if(num == 1){
    return false;
  }
  int i = 2;

  while (i*i <= num) {
    // Check if i divides x without leaving a remainder
    if (num % i == 0) {
        // This means that n has a factor in between 2 and sqrt(n)
        // So it is not a prime number
        return false;
    }
    i += 1;
  }
  // If we did not find any factor in the above loop,
  // then n is a prime number
  return true; 
}
#endif

#ifndef NEXT_PRIME
#define NEXT_PRIME
int next_prime(int startingPrime){
  int startingPrimeMutable = startingPrime * 2;
  while(is_prime(startingPrimeMutable) == false){
    startingPrimeMutable++;
  }
  return startingPrimeMutable;
}
#endif