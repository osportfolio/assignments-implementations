#!/usr/bin/perl

# This script with the function 'solution' given
# a string input computes the length of the shortest 
# substring that only accommodates both small and capital
# versions of all the letters included in the indicated
# substring.

# Worked on this code on
#                       Nov 27, 2022 / Sun

use strict;
use warnings;

# Array of string inputs
my @s_inputs
  = (
      'aACCCxA' ,
      'CCzzcZazAxAZ' ,
      'CCzzcybzAxAZ'
    );
    
# Report the returned integers in response
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
  
  my @smalls   = ('a'..'z');
  my @capitals = ('A'..'Z');
  # Perl has a built-in facility for 
  # computing separately the ranges for the small
  # and capital letters. These are now available
  # as arrays.
  
  my %mp_small;
  my %mp_cap;
  
  for ( my $kk=0 ; $kk < 1+$#smalls ; ++$kk )
  {
    $mp_small{$smalls[$kk]}   = $capitals[$kk];
    $mp_cap  {$capitals[$kk]} = $smalls[$kk];
  } # for
  # Set up hashes to map each of the small
  # letters to the corresponding capital letter,
  # and vice versa. Hashes will save us time through
  # the virtually constant-time access facility.
  
  for ( my $s_length=2 ; $s_length<2+$#s_list ; ++$s_length )
  {
    for ( 
          my $s_index_start = 0 ; 
             $s_index_start < (1 + $#s_list) - $s_length + 1 ;
           ++$s_index_start 
        )
    {
      #  A useful substring has a length starting from 2
      #  and extending to the length of the whole string.
      #  
      #  The starting index for the substring in question
      #  has to have a range as indicated by the statement
      #  defining the iteration index for the inner 'for'
      #  loop.
      #  
      #  Since '$s_length' is iteratively set starting
      #  from the lowest length possible, the first
      #  success to be encountered during the search
      #  will mark the time to draw the function to
      #  an end, having found the shortest string that
      #  accommodates nothing other than some characters
      #  in both small and capital forms.

      my $s_index_end = $s_index_start + $s_length - 1;
      my @temp 
        = @s_list[$s_index_start..$s_index_end];
      # The list of characters for the current substring in
      # question.
        
      my %hash_from_array = map { $_ => 1 } @temp;
      # Generated a hash from the characters within the
      # substring. Keys have no duplicates. Will be
      # making use of the other hashes to check if a 
      # character together with its small or capital 
      # form is included within the substring in question.
      
      my $flag_found = 1;
      # If the flag above remains true after the 'for' loop
      # below, then it will be time to return and yield
      # the result.
      foreach my $item (keys %hash_from_array)
      {
        if
          (
            ( 
              (exists $mp_small{$item}) 
              && 
              (exists $hash_from_array{ $mp_small{$item} }) 
            ) 
            ||
            ( 
              (exists $mp_cap{$item}) 
              && 
              (exists $hash_from_array{ $mp_cap{$item} }) 
            )
          )
          # Making use of the hashes (and drawing
          # benefits through the constant-time access)
          # to check if a character together with its
          # corresponding small or capital form exists
          # within the current substring.
        {}
        else
        {
          $flag_found = 0;
          last;
          # If the condition above is not satisfied even for
          # a single character, then we should break out of the
          # for loop since there is no need to lose time
          # checking the remaining characters. Setting the
          # flag to false will prevent the remaining 'if'
          # conditional from terminating the function.
        }
      } # foreach $item
      
      if ( $flag_found )
      {
        print
          "String found in \'$S\' :\n  " , 
          join( '' , @temp ) , "\n";
        return $s_length;
      }
      # The first success to be encountered has the function
      # return the length of the string in question.
      
    } # for $s_index_start
  } # for $s_length
  
  return -1;
  # No possible success meaning there is no substring within
  # the original string accommodating both small and capital
  # forms of some letters, and nothing else.
} # sub solution