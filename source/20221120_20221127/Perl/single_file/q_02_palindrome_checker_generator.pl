#!/usr/bin/perl

# The function 'solution' tries to generate
# a palindrome out of the string 'S' given
# as an input argument, replacing the '?'
# characters by what is required, and returns
# the palindrome or the string 'NO', the
# latter being the error identifier in case
# no palindrome construction is possible.

# Worked on this code on
#                       Nov 24, 2022 / Thu

use strict;
use warnings;

# Array of string inputs
my @s_inputs =
  (
    '?' ,
    'ba?' ,
    'ab' ,
    'a?b' ,
    'bac?b' ,
    '?acab' ,
  );

# Report the returned strings in response
# to the inputs.
foreach my $item (@s_inputs)
{
  print 
    "Response to \"" , $item , "\" :\n" ,
    "  " , solution($item) , "\n";
} # foreach


# The function used as the palindrome checker
# and generator
sub solution
{
  # Obtain the string input '$S' from the
  # default array '@_'.
  my ($S, @arg_other) = @_;
  # Split the input array into characters.
  my @s_list = split //, $S;
  
  # Declare first as in C and C++; this is
  # not the same as it would be in Python or
  # MATLAB/Octave. Variables in Perl die
  # out of the scope they are defined in.

  # Below, the variables 'index_right',
  # 'index_left', and 'n_max' have to be
  # calculated separately for an odd and
  # an even number of characters within
  # the original string. 
  # 
  # 'n_max' is the number of characters
  # to the right and left of the character
  # in the middle position (if there are an
  # odd number of characters) or in the 
  # position between the characters in the
  # middle (if there are even number of
  # characters).
  #     
  # 'index_right' and 'index_left' are the
  # starting values of the indices calculated
  # through integer offsets from the middle 
  # position (as explained above for the number 
  # of characters being odd or even) for the
  # characters to the right and to the left,
  # respectively, of the indicated position.
  my ( $index_right, $index_left, $n_max );
  
  # '$#s_list' is the index of the last entry
  # in the array '@s_list', with the indices 
  # starting at zero. '1 + $#s_list' then is 
  # the number of elements in the stated array.
  if ( (1 + $#s_list) % 2 == 1 )
  {
    my $index_middle 
         = int( (1+$#s_list - 1) / 2);
    if ( $s_list[$index_middle] eq '?' )
    {
      $s_list[$index_middle] = 'a';
    }
    # For a string with an odd number of
    # characters, the character in the middle
    # has to be set, if it has not already been
    # set.
    
    $index_right = $index_middle + 1;
    $index_left  = $index_middle - 1;
    $n_max = int( (1+$#s_list - 1) / 2);
  } # if
  else
  {
    $index_right = int( (1+$#s_list) / 2);
    $index_left  = int( (1+$#s_list) / 2 - 1);
    $n_max = int( (1+$#s_list) / 2);
  } # else
  
  for ( my $kk=0 ; $kk<$n_max ; ++$kk )
  {
    my $index_right_c = $index_right + $kk;
    my $index_left_c  = $index_left  - $kk;
    # Calculate the current indices through
    # the update 'kk' upon the initial values
    # for the indices of the entries to the
    # right and left of the entry in the middle.
    # The odd and even cases have already been
    # taken care of, so the codes above and
    # below within the scope of this for loop
    # apply to both cases.
    
    if ( ( $s_list[$index_right_c] ne '?' ) &&
         ( $s_list[$index_left_c]  ne '?' ) )
    {
      if ( $s_list[$index_right_c] ne $s_list[$index_left_c] )
      {
        return 'NO';
      }
    }
    # If the entries at the same distance to the 
    # right and left of the middle position are 
    # already set and are not the same, then
    # the string cannot be a palindrome.
    
    if ( ( $s_list[$index_right_c] eq '?' ) &&
         ( $s_list[$index_left_c]  eq '?' ) )
    {
      $s_list[$index_right_c] = 'a';
      $s_list[$index_left_c]  = 'a';
    }
    # If the entries of interest to the right and
    # left have not already been set, then set them
    # as the same character.
    
    if ( ( $s_list[$index_right_c] ne '?' ) &&
         ( $s_list[$index_left_c]  eq '?' ) )
    {
      $s_list[$index_left_c] = $s_list[$index_right_c];
    }
    # If the entry of interest to the right has
    # been set but that to the left not so, then
    # set the entry to the left to continue
    # in the path to obtaining a palindrome at
    # the end.
    
    if ( ( $s_list[$index_right_c] eq '?' ) &&
         ( $s_list[$index_left_c]  ne '?' ) )
    {
      $s_list[$index_right_c] = $s_list[$index_left_c];
    }
    # If the entry of interest to the left has
    # been set but that to the right not so, then
    # set the entry to the right to continue
    # in the path to obtaining a palindrome at
    # the end.
  } # for
  
  return join( '' , @s_list );
  # Join the resulting characters into a string,
  # and return this string.
} # solution