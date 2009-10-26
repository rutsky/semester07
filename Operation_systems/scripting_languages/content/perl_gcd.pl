#!/usr/bin/perl -wl

sub GCD {
  my ($a, $b) = @_;
  while ($a > 0)
  {
    $c = $a;
    $a = $b % $a;
    $b = $c;
  }
  return $b;
}
print GCD(42, 56);
