/*
# Given a string of digits each in the range from
# 0 to 9, generates all the strings that correspond
# to numbers that are divisible by three, which
# are allowed to be devised only through modifications
# on each of the digits in the original string.
# Returns the total number of such strings; naturally
# the original string is not included in the count
# even if its corresponding number is divisible by three.
*/

/*
# Worked on this code on
#                       Dec 19-20, 2022 / Mon-Tue
*/

import java.util.*;
import java.util.stream.IntStream;

class CheckerGenerator
{
  public final
  HashMap<String, List<Integer>> 
    checker;

  private static
  Integer
  checker_helper
  (
    Integer  n ,
    Integer  item ,
    Integer  remainder
  )
  {
    return n + item + (3-remainder);
  }
  
  public CheckerGenerator ()
  {
    this.checker = new HashMap<>();
      
    List<Integer> range_of_int
      = new ArrayList<> ();
    IntStream
      .range( 0, 10 )
      .forEach( range_of_int::add );

    List<Integer> checker_all
      = new ArrayList<> ();
    IntStream.iterate( -12, i -> i + 3 )
             .limit  (   9 )
             .forEach( checker_all::add );
    /*
    range_of_int
      .stream()
      .forEach( System.out::println );
      
    checker_all
      .stream()
      .forEach( System.out::println );
    */
    
    for ( 
          Integer 
            remainder = 0 ;
            remainder < 3 ;
          ++remainder
        )
    {
      for ( Integer item : range_of_int )
      {
        List<Integer> checker_current
          = new ArrayList<> ();
        for ( Integer n : checker_all )
          checker_current.add
            ( checker_helper(n, item, remainder) );
          
        checker_current.retainAll
          ( new HashSet<Integer>( range_of_int ) );
          
        Set<Integer> single_item__set 
          = new HashSet<Integer>();
        single_item__set.add( item );
        checker_current.removeAll( single_item__set );
          
        String key 
          = Integer.toString(item) + "_" 
          + Integer.toString(remainder);
        /*  
        System.out.printf( "  %s  ->  %s\n" , 
          key , checker_current.toString() );
        */
        
        this.checker.put( key , checker_current );
      } // for item
    } // for remainder
    
    // System.out.printf( "%s\n" , this.checker );
  } // ctor
} // class CheckerGenerator

public class DivisibleByThreeGenerator
{
  public static
  List<String>
  solution
  (
    String S
  )
  {
    char[] ch_array = S.toCharArray();
    List<Integer> num
      = new ArrayList<> ();
    for ( char ch : ch_array )
      num.add( Character.getNumericValue( ch ) );
    
    CheckerGenerator checker_obj = 
      new CheckerGenerator ();
      
    int sum_of_num = 0;
    for ( int n : num )
      sum_of_num += n;
    int remainder  = sum_of_num % 3;
    
    int cnt = 0;
    List<String> res = new ArrayList<>();
    int total = 0;
    
    for ( int item : num )
    {
      String key 
        = Integer.toString(item) + "_" 
        + Integer.toString(remainder);
      List<Integer> checker_current
        = checker_obj.checker.get( key );
      total 
        += checker_current.size();
        
      for ( int n : checker_current )
      {
        List<Integer> num_current
          = new ArrayList<>( num );
          
        num_current.set( cnt , n );
        
        StringBuilder sb = new StringBuilder();
        for ( int digit : num_current )
          sb.append( Character.forDigit(digit, 10) );
          
        res.add( sb.toString() );
      } // for n
      
      ++cnt;
    } // for item
    
    Set<String> res__set = new HashSet<>(res);
    res.clear();
    res.addAll(res__set);
    
    Collections.sort(res);
    
    return res;
  }
  
  public static void main(String[] args) 
  {
    List<String> list_of_strings 
      = Arrays.asList
          (
            "0081" , 
            "23" , 
            "22454"
          );
          
    for ( String item : list_of_strings )
    {
      System.out.printf ( "\n" );
      List<String> a_out = solution(item);
      System.out.printf (
        "Response to \'%s\' :\n  %s\n" , 
        item , String.join( " " , a_out ) );
      System.out.printf (
        "Number of Computed Strings :\n  %d\n" ,
        a_out.size() );
    }
  }
} // public class DivisibleByThreeGenerator