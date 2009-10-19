#!/usr/bin/perl -w

package Animal;
sub new {
  my $class=shift;
  my $self={name=>shift, sound=>shift};
  return bless $self, $class;
}

sub whoAmI {
  my $self=shift;
  print "Здравствуйте, я $self->{name}. ";
}

sub say {
  my $self=shift;
  print "$self->{sound}!\n";
}

package main;
my $cow=new Animal 'Корова', 'Муу';
my $cat=new Animal 'Кошка', 'Мяу';
my $dog=new Animal 'Собака', 'Гав';
$cow->whoAmI; $cow->say;
$cat->whoAmI; $cat->say;
$dog->whoAmI; $dog->say;
