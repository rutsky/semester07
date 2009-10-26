#!/usr/bin/R --slave -f 

gcd <- function(a, b) {
  c <- b
  while (a > 0) {
    c <- a
    a <- b %% a
    b <- c
  }
  b
}

print(gcd(42, 56))
