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
#                       Dec 13, 2022 / Tue

use strict;
use warnings;

use lib ".";
use CheckerGenerator;

# *** SCRIPT ***
my $flag_print_checker_dict;

# $flag_print_checker_dict = 0;
$flag_print_checker_dict = 1;

if ( $flag_print_checker_dict )
{
  my $checker_obj = CheckerGenerator->new;
  $checker_obj->print_checker;
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

  # Get reference of pregenerated hash.
  my $checker_ref = CheckerGenerator->new->checker;
  
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
      = $checker_ref->{ $item . '_' . $rem };
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
