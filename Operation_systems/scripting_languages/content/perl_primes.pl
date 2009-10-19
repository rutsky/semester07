#!/usr/bin/perl -wl

(1 x $_) !~ /^(11+)\1+$/ && print while ++ $_ < 100
