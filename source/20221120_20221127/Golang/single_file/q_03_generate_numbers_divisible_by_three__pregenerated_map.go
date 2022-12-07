/*
 * Given a string of digits each in the range from
 * 0 to 9, generates all the strings that correspond
 * to numbers that are divisible by three, which
 * are allowed to be devised only through modifications
 * on each of the digits in the original string.
 * Returns the total number of such strings; naturally
 * the original string is not included in the count
 * even if its corresponding number is divisible by three.
 * */

/*
  Worked on this code on
                        Dec 7, 2022 / Wed
*/

package main

import (
  "fmt" 
  "sort"
  "strings"
)

type DigitComputerFunctionType func(int, int, int) int

func returns_checker_map() (map[string] []int) {
  checker_all  := [9]  int {
    -12, -9, -6, -3, 0, +3, +6, +9, +12 }
  range_of_int := [10] int {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
  range_of_remainders := [3]  int {
    0, 1, 2 }
    
  checker := make( map[string] []int )
  
  var fh DigitComputerFunctionType = func (n int, item int, rem int) int {
    return  n + item + (3-rem)
  }
  
  for _, rem := range range_of_remainders {
    for _, item := range range_of_int {
      
      var checker_current [] int
      for _, n := range checker_all {
        checker_current = append(
          checker_current, fh(n, item, rem) )
      } // for n
      /*
       * Computed checker_current in raw form.
       * */
      
      var checker_current_temp [] int
      hash := make( map[int] int )
      for _, v := range checker_current {
        hash[v] = 1
      }
      for _, v := range range_of_int {
        if _, key_in_hash := hash[v]; key_in_hash {
          checker_current_temp = append(checker_current_temp, v)
        }
      }
      checker_current = checker_current_temp
      checker_current_temp = nil
      /*
       * Computed intersection set of checker_current and
       * range_of_int.
       * 
       * Reference:
       *   https://github.com/juliangruber/go-intersect/blob/master/intersect.go
       * */
      
      for _, v := range checker_current {
        if v != item {
          checker_current_temp = append(checker_current_temp, v)
        }
      }
      checker_current = checker_current_temp
      checker_current_temp = nil
      /*
       * Eliminated item from checker_current_temp.
       * */
      
      sort.Ints( checker_current )
      key := fmt.Sprintf("%d_%d", item, rem)
//       fmt.Println( key )
      
      checker[key] = checker_current
    } // for item
  } // for rem
  
  return checker
}

func solution(s_input string) int {
  s_list := [] rune(s_input)
  num := make( [] int, len(s_list) )
  i := 0
  for _, v := range s_list {
    num[i] = int(v - '0')
//     fmt.Println( num[i] )
    i++
  }
  /*
   * Converted characters into integer counterparts.
   * 
   * Reference:
   *   https://stackoverflow.com/questions/21322173/convert-rune-to-int
   * */
  
  checker := returns_checker_map()
  
  sum_of_num := 0
  for _, v := range num {
    sum_of_num += v
  }
  rem := sum_of_num % 3
  
  cnt := 0
  res := make( [] string , 0 )
  total := 0
  
  for _, item := range num {
    checker_current := checker[ 
      fmt.Sprintf( "%d_%d" , item , rem ) ]
    total += len(checker_current)
    
    for _, n := range checker_current {
      num_current := make( [] int , len(num) )
      copy( num_current , num )
      
      num_current[cnt] = n
      tba := strings.Trim(
        strings.Join(
          strings.Fields( fmt.Sprint( num_current ) ), ""), "[]" )
//       fmt.Println( tba )
      
      res = append(res, tba)
    } // for n
    
    cnt += 1
  } // for item
  
  hash := make( map[string] int )
  for _, v := range res {
    hash[v] = 1
  }
  res = nil
  
  for str := range hash {
    res = append( res , str )
  }
  sort.Strings( res )
  /*
   * Removed duplicates if any.
   * */
  
  fmt.Println(  )
  fmt.Println( fmt.Sprintf( "Generated Strings with the Input \"%s\" :" , s_input ) )
  fmt.Println( " " , strings.Join( res , " " ) )
  
  return total
}

func main() {
  var flag_print_checker_map bool
  flag_print_checker_map = true
//   flag_print_checker_map = false
  
  if flag_print_checker_map {
    checker := returns_checker_map()
    
    keys := make([]string, len(checker))
    i := 0
    for str := range checker {
//       fmt.Println( str )
      keys[i] = str
      i++
    }
    sort.Strings( keys )
    /*
     * Get keys of a map into an array.
     * 
     * Reference:
     *   https://stackoverflow.com/questions/21362950/getting-a-slice-of-keys-from-a-map
     * */
    
    fmt.Println( "\nChecker Map :\n" )
    for _, str := range keys {
      fmt.Println( 
        "  (" ,
        strings.Join( strings.Split( str , "_" ) , " , " ) , ")    [" , 
        strings.Trim(strings.Join(strings.Fields(fmt.Sprint(checker[str])), " , "), "[]") ,
        "]" )
      /*
       * Joined an array of integers into a string, with a delimiter
       * specified.
       * 
       * Reference:
       *   https://stackoverflow.com/questions/37532255/one-liner-to-transform-int-into-string
       * */
    }
  } // if flag_print_checker_map
  
  
  s_inputs := [] string {
    "0081" , "23" , "22454" }
//   s_inputs := [] string {
//     "23" }

//   var kk int
  
  for _, str := range s_inputs {
    s_out := solution( str )
    fmt.Println( 
      fmt.Sprintf( "Response to \"%s\" :" , str ) )
    fmt.Println( " " , s_out )
  }
}