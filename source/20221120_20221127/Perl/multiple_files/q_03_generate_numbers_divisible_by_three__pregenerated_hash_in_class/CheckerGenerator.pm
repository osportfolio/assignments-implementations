#!/usr/bin/perl

# CheckerGenerator class definition in separate
# pm file.

# Worked on this code on
#                       Dec 13, 2022 / Tue

use warnings;
use strict;

package CheckerGenerator;
use Carp; 

sub new
{
  my ($class, @args) = @_;
  my $self = bless {}, $class;
  return $self->_init(@args);
}

sub _init
{
  my ($self, @args) = @_;
  $self->id ( 'CheckerGenerator' );
  $self->_generate;
  return $self;
}

# '_generate' indirectly called during construction
sub _generate
{
  my ($self, @args) = @_;
  
  my @checker_all
    = ( -12, -9, -6, -3, 0, 3, 6, 9, 12 );
  my @range_of_int
    = ( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 );
    
  my %range_of_int__hash
    = map { $_ => 1 } @range_of_int;
    
  my %checker;
  
  foreach my $rem ( ( 0 , 1 , 2 ) )
  {
    foreach my $item (@range_of_int)
    {
      my @checker_current = ();
      foreach my $n (@checker_all)
      {
        push @checker_current , $n+$item+(3-$rem) ;
      }
      # Form @checker_current in raw. Two stages of
      # pruning necessary.
      
      my @checker_current__temp = ();
      for my $k (@checker_current)
      {
        if ( exists $range_of_int__hash{$k} )
        {
          push @checker_current__temp , $k;
        }
      }
      @checker_current
        = @checker_current__temp;
      undef @checker_current__temp;
      # For computing those of the modified integers
      # that fall within the accepted range from 0 to 9
      # for a single digit.
      
      @checker_current__temp = ();
      for my $k (@checker_current)
      {
        if ( $k != $item )
        {
          push @checker_current__temp , $k;
        }
      }
      @checker_current
        = @checker_current__temp;
      undef @checker_current__temp;
      # Getting rid of the original digit if it is
      # actually within the resulting array.
      
      my $key = $item . "_" . $rem;
      # Stringification for hash key.
      
      $checker{$key} = [ sort(@checker_current) ];
      # Array reference stored as the value corresponding
      # to $key.
    } # foreach $item
  } # foreach $rem

  #$self->checker( {%checker} );
  # Copying %checker and assigning an anonymous reference
  # to the new copy. Setting the 'checker' member variable
  # as the stated reference.
  
  $self->checker( \%checker );
  # Copy effected through {} is unnecessary. Just copy
  # the reference; '\%checker' yields the reference to
  # the hash, with the backslash. Reference counting
  # mechanism takes care of garbage collection.
} # sub _generate

sub print_checker
{
  my ($self, @args) = @_;
  
  print "\n" , "Checker Hash :" , "\n\n";
  my $checker_ref = $self->checker;
  
  # Dereferencing the hash reference with %{}
  foreach my $key ( sort(keys %{$checker_ref}) )
  {
    print 
      "  " , "( " , 
      join( " , " , split( "_" , $key ) ) , 
      " )" , "  ->  " ,
      "[ " , join( " , " , @{$checker_ref->{$key}} ) , " ]" ,
      "\n";
  }
} # sub print_checker

sub id
{
  $_[0]->{id} = $_[1] if defined $_[1];
  $_[0]->{id}
}

sub checker
{
  $_[0]->{checker} = $_[1] if defined $_[1];
  $_[0]->{checker}
}


1;