#!/usr/bin/perl -wl

sub GCD {
  my ($a, $b) = @_;
  my $c = $b;
  while ($a > 0)
  {
    $c = $a;
    $a = $b % $a;
    $b = $c;
  }
  return $c;
}
print GCD(42, 56);
