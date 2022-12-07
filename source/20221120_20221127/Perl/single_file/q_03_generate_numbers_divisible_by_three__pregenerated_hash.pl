#!/usr/bin/perl

# Given a string of digits each in the range from
# 0 to 9, generates all the strings that correspond
# to numbers that are divisible by three, which
# are allowed to be devised only through modifications
# on each of the digits in the original string.
# Returns the total number of such strings; naturally
# the original string is not included in the count
# even if its corresponding number is divisible by three.

# Worked on this code on
#                       Dec 7, 2022 / Wed

use strict;
use warnings;

my $flag_print_checker_dict;

# $flag_print_checker_dict = 0;
$flag_print_checker_dict = 1;

if ( $flag_print_checker_dict )
{
  print "\n" , "Checker Dictionary :" , "\n\n";
  my %checker = returns_checker_hash();
  foreach my $key ( sort(keys %checker) )
  {
    print 
      "  " , "( " , 
      join( " , " , split( "_" , $key ) ) , 
      " )" , "    " ,
      "[ " , join( " , " , @{$checker{$key}} ) , " ]" ,
      "\n";
  }
}

# Array of string inputs
my @s_inputs =
  (
    '0081' ,
    '23' ,
    '22454' ,
  );

# Report the returned strings in response
# to the inputs.
foreach my $item (@s_inputs)
{
  print "\n";
  print 
    "Response to \"" , $item , "\" :\n" ,
    "  " , solution($item) , "\n";
} # foreach


sub solution
{
  # Obtain the string input '$S' from the
  # default array '@_'.
  my ($S, @arg_other) = @_;
  # Split the input array into characters.
  my @s_list = split //, $S;

  # Get pregenerated hash.
  my %checker = returns_checker_hash();
  
  my @num;
  my $sum_of_num = 0;
  foreach my $item (@s_list)
  {
    push @num , int($item);
    $sum_of_num += $num[$#num];
  }
  # Converts characters into integers and computes
  # the sum.
  
  my $rem = $sum_of_num % 3;
  # If the digits in a number total up to
  # a number divisible by 3, then the number
  # itself is divisible by three.
  
  my $cnt = 0;
  my @res = ();
  
  my $total = 0;
  # Variables that record the results.
  
  foreach my $item (@num)
  {
    my $checker_current_ref 
      = $checker{ $item . '_' . $rem };
    # Get the reference for the array from the hash.
      
    $total += 1 + $#{$checker_current_ref};
    # The number of possibilities that count for
    # the digit in question is the number of digits
    # calculated and contained within '$checker_current',
    # indirectly accessed through a reference.
    
    foreach my $n (@{$checker_current_ref})
    {
      my @num_current = @num;
      # For an array of native types, assignment
      # means value copy in Perl, not reference copy
      # as in Python.
        
      $num_current[$cnt] = $n;
      # Set the new value for the digit.
        
      my @num_current_str;
      foreach my $s (@num_current)
      {
        push @num_current_str , "".$s;
      }
      # Convert integers to characters.
        
      my $tba = join( '' , @num_current_str );
      # Obtain the resulting string for the number.
        
      push @res , $tba;
      # Append the string to the resulting array res.
    } # foreach $n
      
    ++$cnt;
  } # foreach $item
  
  
  my %res__hash = map { $_ => 1 } @res;
  my @res_reduced = sort( keys %res__hash );
  print 
    "Generated Strings with the Input \"$S\" :\n  " ,
    join( ' ' , @res_reduced ) , "\n";
  # Rule out duplicates if any through a hash,

#   return ( 1 + $#res_reduced );
  # Return the number of keys for the hash.
  
  return $total;
  # '$total' already holds the requested number.
} # sub solution


sub returns_checker_hash
{
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
  
  return %checker;
} # sub