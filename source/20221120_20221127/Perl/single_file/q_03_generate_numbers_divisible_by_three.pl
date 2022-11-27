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
#                       Nov 27, 2022 / Sun

use strict;
use warnings;

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

  my $flag_compute_list;
  $flag_compute_list = 1;
#   $flag_compute_list = 0;
  
  my @num;
  my $sum_of_num = 0;
  foreach my $item (@s_list)
  {
    push @num , int($item);
    $sum_of_num += $num[$#num];
  }
#   print "$sum_of_num\n";
  # Converts characters into integers and computes
  # the sum.
  
  my $rem = $sum_of_num % 3;
#   print "$rem\n";
  # If the digits in a number total up to
  # a number divisible by 3, then the number
  # itself is divisible by three.
  
  my @checker 
    = ( -12, -9, -6, -3, 0, 3, 6, 9, 12 );
  # Will be adding the integers in the array above
  # to modify single digits in a number. Indeed,
  # the range from -9 to +9 is enough.
  
  my @range_of_int
    = ( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 );
  # Range of digits from 0 to 9. Will be checking
  # through this array if certain integers exist
  # as items in this array.
  
  my %range_of_int__hash
    = map { $_ => 1 } @range_of_int;
  # Generate a hash out of the range of integers.
  
  my $cnt = 0;
  my @res = ();
  
  my $total = 0;
  # Variables that record the results.
  
  foreach my $item (@num)
  {
    my @checker_current = ();
    foreach my $n (@checker)
    {
      push @checker_current , $n+$item+(3-$rem) ;
    }
#     print @checker_current , "\n";
    # Compute the modified integer for 
    # a digit '$item' that will make
    # the whole number divisible by 3.
    
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
    
    if ( $flag_compute_list )
    {
      foreach my $n (@checker_current)
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
#         print $tba , "\n";
        # Obtain the resulting string for the number.
        
        push @res , $tba;
        # Append the string to the resulting array res.
      } # foreach $n
      
      ++$cnt;
#       print "\n";
    } # if
    else
    {
      $total += 1 + $#checker_current;
      # The number of possibilities that count for
      # the digit in question is the number of digits
      # calculated and contained within '$checker_current'.
    } #else
  } # foreach $item
  
  if ( $flag_compute_list )
  {
    my %res__hash = map { $_ => 1 } @res;
    my @res_reduced = sort( keys %res__hash );
    print 
      "Generated Strings with the Input \"$S\" :\n  " ,
      join( ' ' , @res_reduced ) , "\n";
    return ( 1 + $#res_reduced );
    # Rule out duplicates if any through a hash,
    # and return the number of keys for the hash.
  }
  else
  {
    return $total;
    # '$total' already holds the requested number.
  }
  # Return statements for either choice for the flag
  # differ.
} # sub solution