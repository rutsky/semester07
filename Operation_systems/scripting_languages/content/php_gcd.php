#!/usr/bin/env php
<?php

function gcd( $a, $b ) {
  $c = $b;
  while ($a > 0)
  {
    $c = $a;
    $a = $b % $a;
    $b = $c;
  }
  return $b;
}

echo gcd(42, 56) . "\n";
?>
