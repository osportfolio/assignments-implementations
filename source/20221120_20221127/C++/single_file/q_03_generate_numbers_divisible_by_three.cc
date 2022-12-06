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

// worked on this code 
//        from  Nov 22, 2022 / Tue
//        to    Nov 24, 2022 / Thu

#include <vector>
#include <tuple>
#include <set>
#include <string>
#include <algorithm>
#include <memory>
#include <iostream>

namespace os_types
{
  using set_of_int_type =
    std::set<int>;
} // namespace os_types

namespace os_core
{

/*
 * Function to generate a vector of integers, with the
 * consecutive ones separated by a specified increment
 * value.
 * */
std::vector<int>
range_of_integers
(
  int  i_start ,
  int  i_end ,
  int  i_increment
)
{
  std::vector<int>  v;
  for ( int kk=i_start ; kk<i_end ; kk+=i_increment )
    v.push_back( kk );
  return v;
}

std::vector<char>
string_to_vector_of_characters
(
  std::string  s_in
)
{
  auto & A = s_in;
  std::vector<char>  s_list;
  
  s_list.reserve( A.length() );
  
  const auto * c_ptr = A.c_str();
  for ( unsigned int kk = 0 ; kk < A.length() ; ++kk )
    s_list.push_back( *(c_ptr++) );
  
  return s_list;
} // string_to_vector_of_characters

std::string
vector_of_characters_to_string
(
  std::vector<char>  v_in
)
{
  std::string  res( v_in.begin() , v_in.end() );
  return res;
} // vector

template
< typename Container >
void
print_container_of_items
(
  Container    c_input ,
  std::string  identifier = "unspecified"
)
{
  using namespace std;
  cout 
    << "Printing items (of " 
    << identifier
    << "):" 
    << endl << "  ";
  
  for ( auto item : c_input )
    cout << item << " ";
  cout << endl;
} // print_container_of_items


/*
 * Base or parent class definition for the solution.
 * This one only counts the occurrences of the
 * strings with the integer forms that are divisible
 * by 3. The subclass will be the one that also
 * generates the list of such strings.
 * */
class DivisibleByThreeGeneratorBase
{
// typedefs
public:
  using LocalClassType =
    DivisibleByThreeGeneratorBase;
#define  LocalClassTypeName  \
    DivisibleByThreeGeneratorBase
/*
 * The typedef and preprocessor definition above
 * help one to forget about the actual name of
 * the class for the member functions to be
 * coded inside the actual body of the class 
 * definition. For member function bodies that
 * are to be outside the class definition, this
 * technique does not have much utility.
 * */

// static member variables
public:
  static
  bool  flag_debug;
/*
 * Debugging is done through characters redirected to
 * stdout. If this flag is reset to false, no such debug
 * strings will be printed. Making this variable static
 * ensures a class-specific instance for the member variable,
 * not class instance-specific. This static member variable
 * will also be accessible by the subclasses of the parent
 * class. A subclass will not have its own static variable
 * instance (for it to possess such an instance, one would
 * have to make use of CRTP (Curiously Recurring Template
 * Pattern)).
 * */
  
// static member variables
protected:
  static
  std::vector<int>
    checker_, range_of_int_;
/*
 * These are to be precalculated and then used by every
 * class instance.
 * */
  
// member variables
protected:
  // input string
  std::string
    s_input_;
  
  // internal vector of integers
  std::vector<int>
    num_;
    
  // sum of the integers in the vector above
  int
    sum_of_num_;
    
  // remainder of the sum when divided by 3
  int
    rem_;
  
  /*
   * Counts the total number of strings that can
   * be generated and that in integer form are
   * divisible by 3, as obtained through digit
   * modifications.
   * */
  int 
    total_;
    
// ctor dtor  
public:
  
  LocalClassTypeName
  (
    std::string  S
  )
  :
  s_input_( S )
  // initialization list in ctor
  {
    using namespace std;
    
    auto s_list = 
      string_to_vector_of_characters( S );
    // Obtain vector of characters.
      
    // Pre-allocation of memory inside the vector.
    num_.reserve( s_list.size() );
    
    /*
     * Computes the integer equivalent of each
     * character in the given string, and pushes
     * these integers into the vector 'num_'.
     * A lambda expression is very handy in here.
     * Alternatives are a function pointer and
     * a functor; out of these alternatives, a
     * functor can be designed to have an internal
     * state, but a function, on the other hand,
     * can possess a state only through a static
     * variable in its scope, which can be set
     * through the input arguments of the function
     * in question.
     * 
     * In cases where an internal state is necessary
     * and also where the functionality is possibly
     * to be of use only once, a lambda expression
     * is the most convenient utility. For the task
     * below, no internal state is needed, so we have
     * empty space between the square brackets []
     * in the definition for the lambda expression.
     * 
     * 'back_inserter' provides an iterator for the
     * push back operation into 'num_'. An in-place
     * construction oriented 'back_emplacer' functionality
     * is not provided by the C++ standard, at least in
     * C++11; stackoverflow provides implementations
     * for 'back_emplacer'. We do not need 'back_emplacer'
     * below; integer is a native type, not a class.
     * */
    std::transform
      (
        s_list.begin() ,
        s_list.end() ,
        std::back_inserter(num_) ,
        [] (const char  item) -> int
          { // lambda
            return item - '0';
          } // lambda
      );
      
    /*
     * Compute the sum and remainder that will be necessary
     * within the relevant computation. In prototyping platforms
     * and vector-based computation libraries, sum is a
     * standard operation, but making use of only the C++ standard 
     * library in here, we need to compute the sum, possibly as 
     * shown below.
     * 
     * The lambda expression does not capture 'this' automatically.
     * Pointer copying for capture is very convenient. With the
     * 'this' pointer, the lambda expression gains access to
     * every member variable of the class instance.
     * */
    sum_of_num_ = 0;
    std::for_each
      (
        num_.begin() ,
        num_.end() ,
        [this] (const int  item)
          { // lambda
            this->sum_of_num_ += item;
          } // lambda
      );
    rem_ = sum_of_num_ % 3;
      
    total_ = 0;
    // Initialize 'total_'.
      
    if (flag_debug)
    {
      print_container_of_items
        (S    , "vector of characters" );
      print_container_of_items
        (num_ , "vector of digits" );
    }
    // Characters directed to stdout for debugging purposes.
  } // ctor
  
  /*
   * The destructor is identified as 'virtual'. In cases where
   * inheritance and polymorphic pointers are used in the code,
   * the destructor of the subclass instance can be called through 
   * the polymorphic pointer of the base class instance if the
   * destructor is made 'virtual'. Otherwise, the compiler
   * behavior is undefined.
   * */
  virtual
  ~LocalClassTypeName
  () = default;
  
  
public:
  
  /*
   * 'solve' computes the number of strings with integer forms
   * that are divisible by 3. Auxiliary member functions are
   * inteded to help compute also the list of the stated strings.
   * These auxiliaries are non-functional in this base class,
   * but they are defined as virtual to allow for polymorphism.
   * 
   * 'solve' itself is not virtual, and it is not going to be
   * overridden in a subclass.
   * 
   * For non-static member functions, when such a function
   * itself is not required to return anything useful, it is
   * recommended to have the function return a reference to
   * the class instance. This approach allows calls such as the
   * following:
   * 
   *    class_instance
   *      .member_function( parameters )
   *      .another_member_function( other_parameters );
   * */
  LocalClassType &
  solve
  ()
  {
    using local_set_type =
      os_types::set_of_int_type;
    // Set the local type.
    
    local_set_type  range_of_int__set
      ( range_of_int_.begin() , range_of_int_.end() );
    /*
     * 'range_of_int_' is static, and it has been computed
     * a priori, before any instantiation of the class.
     * The set 'range_of_int__set' is initialized through
     * an iterator-based ctor.
     * */
      
    int cnt = 0;
    /*
     * To be updated and sent as argument to virtual member
     * function auxiliaries. Signifies digit position.
     * */
    
    // Range-based 'for' to iterate through the digits.
    for ( auto item : num_ )
    {
      decltype(checker_)
        checker_current;
      checker_current.reserve( checker_.size() );
      /*
       * 'checker_' is static, and it has been computed
       * a priori. 'checker_current' will be a modified
       * form of 'checker_'. 'decltype' allows us to not
       * recall the actual declaration type.
       * */
      
      /*
       * The statement below and especially the lambda
       * expression compute the raw form for the
       * array of modified values for the digit in
       * question that will render the whole number
       * divisible by 3. The remainder 'rem_' and
       * the actual unmodified digit 'item' are used
       * in this computation.
       * 
       * Some pruning on 'checker_current' will be
       * necessary, and that is why I call it raw.
       * */
      std::transform
        (
          checker_.begin() ,
          checker_.end() ,
          std::back_inserter(checker_current) ,
          [this, item] (const int  n)
            { // lambda
              return n + item + ( 3 - this->rem_ );
            } // lambda
        );
        
      /*
       * Declaration and initialization to compute
       * the set of numbers within the vector
       * 'checker_current'. A set rules out duplicates.
       * */
      local_set_type  checker_current__set
        ( checker_current.begin() , checker_current.end() );
        
      /*
       * Will be computing the intersection of the sets
       * 'checker_current__set' and 'range_of_int__set',
       * i.e., the integers within 'checker_current__set'
       * that fall within the range from 0 to 9. 'checker_temp'
       * as a vector will hold the members of the intersection
       * set. A very conservative decision is to initialize
       * 'checker_temp' as a vector of zeros with the size
       * that is the sum of the number of elements in the
       * two sets.
       **/  
      std::vector<int>  checker_temp
        ( 
            checker_current__set.size() 
          + range_of_int__set.size()
        );
        
      /*
       * After 'set_intersection' executes its task,
       * an iterator pointing to the entry just after
       * the last element inserted is returned.
       * */
      auto  it =
        std::set_intersection
          ( 
            checker_current__set.begin() ,
            checker_current__set.end() ,
            range_of_int__set.begin() ,
            range_of_int__set.end() ,
            checker_temp.begin()
          );
      /*
       * The iterator 'it' tells us how many entries
       * with the value zero have to be eliminated
       * in resizing 'checker_temp'. The minus (-)
       * operator is overloaded for iterators.
       * */
      checker_temp.resize( it - checker_temp.begin() );
      
      if (flag_debug)
      {
        print_container_of_items
          ( checker_temp , 
            "vector from set of digits (after intersection)" );
      } // if
      
      /*
       * Done with the first pruning operation. Get the
       * digits in checker_temp into checker_current.
       * Vector assignment means value copying.
       * */
      checker_current = checker_temp;
      
      /*
       * Get rid of all the elements in 'checker_current__set'.
       * Reconstruct a set out of the elements in the now
       * pruned 'checker_current' through iterator-based
       * 'insert'.
       * */
      checker_current__set.clear();
      checker_current__set.insert
        ( checker_current.begin() , checker_current.end() );
        
      /*
       * Make ready for the second pruning operation.
       * If the original value for the digit as 'item' is
       * included in 'checker_current__set', it has to be
       * eliminated. Therefore initializing 'single_element__set'
       * through an initializer list.
       * */
      local_set_type  single_element__set = { item };
      
      /*
       * 'checker_temp' to hold the resulting digits of the
       * 'set_difference' operation is only a temporary.
       * Clear and reinitialize with zeros, again by a
       * conservative choice for the size. Past declaration,
       * reinitialize through 'resize'.
       * */
      checker_temp.clear();
      checker_temp.resize
        (
            checker_current__set.size()
          + single_element__set.size() ,
          0
        );
      
      /*
       * 'set_difference' API is similar to that of 'set_intersection'
       * explained above. Make use the iterator 'it' to resize,
       * i.e., to get rid of the elements in excess.
       * */
      it = 
        std::set_difference
          (
            checker_current__set.begin() ,
            checker_current__set.end() ,
            single_element__set.begin() ,
            single_element__set.end() ,
            checker_temp.begin()
          );
      checker_temp.resize( it - checker_temp.begin() );
      
      if (flag_debug)
      {
        print_container_of_items
          ( checker_temp , 
            "vector from set of digits (after difference)" );
      } // if
      
      /*
       * Obtain the necessary digits after the second pruning
       * operation.
       * */
      checker_current = checker_temp;
      
      // Clear temporary data.
      checker_temp.clear();
      checker_current__set.clear();
      single_element__set.clear();
      
      /*
       * Update 'total_'. The base class is only responsible for
       * calculating the total number of strings with integer
       * forms that are divisible by 3.
       * */
      total_ += checker_current.size();
      
      /*
       * Call virtual function (the function body definition
       * in the subclass through a polymorphic pointer or
       * reference). The virtual function within the base class
       * does nothing, when the pointer to the base class instance
       * is not polymorphic.
       * */
      append_to_set_of_generated_strings
        (cnt, checker_current);
      
      ++cnt;
    } // for
    
    if ( flag_debug )
    {
      std::cout
        << "Total Number of Generated Strings:"
        << std::endl
        << "  " << total_
        << std::endl;
    } // if
    
    /*
     * Call virtual function (the function body definition
     * in the subclass through a polymorphic pointer or
     * reference). The virtual function within the base class
     * does nothing, when the pointer to the base class instance
     * is not polymorphic.
     * */
    compute_list_of_generated_strings();
    
    /*
     * This member function is not required to return anything
     * useful. So just return a reference to the current
     * class instance.
     * */
    return *this;
  } // solve
  
  /*
   * Getter; does not modify the member variables of the
   * class instance, hence 'const'.
   * */
  int
  get_total_number_of_generated_strings
  ()
  const
  {
    return  total_;
  }
  
  // Getter; again 'const'.
  std::string
  get_original_string
  ()
  const
  {
    return  s_input_;
  }
  
protected:
/*
 * 'virtual', but not 'purely virtual' member
 * functions. These are to be overridden by the
 * function definitions in the subclass to be
 * defined through public inheritance. These
 * functions are not defined as 'purely virtual'
 * in order to make the base class instantiable
 * itself.
 * 
 * These functions are intended for computing
 * the actual list of strings, with integer
 * forms divisible by 3. They are called by the
 * member function 'solve'. In this base class,
 * the functions below do not need to do anything;
 * therefore, they only return a reference to the
 * class instance.
 * */
  
  virtual
  LocalClassType &
  append_to_set_of_generated_strings
  (
    int 
      cnt ,
    const std::vector<int> & 
      checker_current
  )
  {
    return *this;
  }
  
  virtual
  LocalClassType &
  compute_list_of_generated_strings
  ()
  {
    return *this;
  }
  
#undef  LocalClassTypeName  
/*
 * Preprocessor directive for undefining the
 * type name. The definition does not have
 * utility outside the class scope.
 * */
}; // class DivisibleByThreeGeneratorBase


/*
 * Static member variable initializations outside
 * the class definition body.
 * */
bool
DivisibleByThreeGeneratorBase::flag_debug = true;

std::vector<int>
DivisibleByThreeGeneratorBase::checker_
  = std::move( range_of_integers(-12, +13, +3) );
std::vector<int>
DivisibleByThreeGeneratorBase::range_of_int_
  = std::move( range_of_integers(0, 10, 1) );


/*
 * Subclass obtained through public inheritance.
 * Inherits the functionality of the base class,
 * implements string list computation on top of it
 * through virtual member functions. Technically,
 * the string list is not a list (linked list),
 * but a vector.
 * */
class DivisibleByThreeGeneratorWithListComputer
:
public
DivisibleByThreeGeneratorBase
{
// typedefs
public:
  using LocalClassType =
    DivisibleByThreeGeneratorWithListComputer;
#define  LocalClassTypeName  \
    DivisibleByThreeGeneratorWithListComputer

// member variables
protected:
  /*
   * Member variables related to the strings
   * to be computed.
   * */
  std::set<std::string>  
    generated_strings__set_;
  std::vector<std::string>
    generated_strings_;
    
// ctor dtor
public:

  LocalClassTypeName
  (
    std::string  S
  )
  :
  DivisibleByThreeGeneratorBase(S)
  /*
   * Initialization list directly calls the ctor
   * of the base class.
   * */
  {
    // Not necessary, but clearing the containers.
    generated_strings__set_.clear();
    generated_strings_.clear();
  } // ctor
  
  /*
   * Even without the keyword itself, the destructor
   * is declared as 'virtual'.
   * */
  virtual
  ~LocalClassTypeName
  () {}
  
// getters
public:
  
  /*
   * Getter returning reference to const type of
   * variable, for read-only operation in the scope
   * of the caller. The function is 'const', not
   * modifying member variables of the instance.
   * */
  const std::vector<std::string> &
  get_list_of_generated_strings
  ()
  const
  {
    return  generated_strings_;
  }
  
// computing member functions
protected:
  virtual
  LocalClassType &
  append_to_set_of_generated_strings
  (
    int 
      cnt ,
    const std::vector<int> &
      checker_current
  )
  {
    /*
     * 'checker_current' is obtained in read-only fashion.
     * Iterating through its elements in the range-based 'for' 
     * loop.
     * */
    for ( auto n : checker_current )
    {
      /*
       * Obtain a copy of the digits in the originally
       * input number, served initially as a string.
       * */
      auto  num_current = num_;
      
      /*
       * 'cnt' is the index of the entry to be modified.
       * 'n' is the modified value for the digit in
       * question.
       * */
      num_current[cnt] = n;
      
      /*
       * Computes the character corresponding to each digit
       * in 'num_current', now holding the modified digit
       * at the correct index. 'num_current_str' is the vector
       * of characters that will be converted to a string
       * */
      std::vector<char>
        num_current_str;
      num_current_str.reserve
        ( num_current.size() );
      std::transform
        (
          num_current.begin() ,
          num_current.end() ,
          std::back_inserter( num_current_str ) ,
          [] ( int item ) -> char
          {
            /*
             * Lambda expression body returning the corresponding
             * character.
             * */
            return ('0' + item);
          }
        );
      
      /*
       * Compute the string out of the vector of characters.
       * */
      auto  tba =
        vector_of_characters_to_string
          ( num_current_str );
      /*
       * Insert the string into the set.
       * */
      generated_strings__set_.insert
        ( tba );
    } // for n
    
    /*
     * Returns a reference to the subclass instance.
     * */
    return *this;
  }
  
  /*
   * Fill in the vector 'generated_strings_' with the entries
   * obtained from the set 'generated_strings__set_'.
   * */
  virtual
  LocalClassType &
  compute_list_of_generated_strings
  ()
  {
    generated_strings_.insert
      (
        generated_strings_.begin() ,
        generated_strings__set_.begin() ,
        generated_strings__set_.end()
      );
      
    if ( flag_debug )
      print_container_of_items
        (
          generated_strings_ ,
          "vector of generated strings"
        );
    
    /*
     * Returns a reference to the subclass instance.
     * */
    return *this;
  }
  
#undef  LocalClassTypeName
};
  
} // namespace os_core

namespace os_test
{
// Scope-limited namespace inclusion.
using namespace os_core;

/*
 * Test function for the designed classes.
 * */
void 
test_solution ()
{
  using namespace std;

  /*
   * Typedef aliases for readability.
   * */
  using local_base_type
    = DivisibleByThreeGeneratorBase;
  using local_derived_type
    = DivisibleByThreeGeneratorWithListComputer;
  
  /*
   * Toggling the static member value 'flag_debug'.
   * No instance necessary.
   * */
  local_base_type::flag_debug
//     = true;
    = false;
    
  /*
   * Vector of strings initialized through an initializer
   * list.
   * */
  std::vector<std::string> s_inputs = 
    {
      "0081" ,
      "23" ,
      "22454"
    };

  /*
   * Vector of shared pointers for managing the lifetime
   * of raw polymorphic or non-polymorphic pointers.
   * */
  std::vector< std::shared_ptr< local_base_type > >
    vec_of_sh_ptr;
    
  /*
   * Reporter redirects strings to stdout.
   * */
  cout << endl;
  /*
   * Iterate through the input strings vector by this 
   * range-based 'for' loop.
   * */
  for ( auto item : s_inputs )
  {
    /*
     * In-place construction of an element in the vector
     * 'vec_of_sh_ptr' through 'emplace_back'. 'make_shared'
     * makes use of variadic templates and perfect forwarding
     * to redirect the ctor argument 'item' to the ctor of
     * 'local_base_type'. 'make_shared' returns an rvalue,
     * 'emplace_back' itself makes use of variadic templates 
     * and perfect forwarding, and there is a ctor overload
     * of shared_ptr that accepts an rvalue. Therefore,
     * with the statement below, move construction of the
     * 'shared_ptr' as an entry within the vector, without
     * an unnecessary copy generation, is possible.
     * */
    vec_of_sh_ptr.emplace_back
      ( 
        std::make_shared<local_base_type> 
          ( item )
      );
      
    /*
     * 'back' returns a reference to the vector element
     * at the end, and '->' is an overloaded operator
     * for a 'shared_ptr'. Therefore the 'solve' member
     * function for the instance pointed to by the
     * raw pointer, which is in turn managed by a 'shared_ptr'
     * can be called as such.
     * */
    ( vec_of_sh_ptr.back() )->solve();
      
    /*
     * 'local_derived_type' instance construction with a raw
     * polymorphic pointer pointing to it, and this raw
     * pointer managed by a 'shared_ptr', which is now a recent
     * entry at the very end of the vector 'vec_of_sh_ptr'.
     * Calling 'solve' as a non-virtual member function,
     * but internally 'solve' itself calls virtual member
     * functions with their overriding definitions residing
     * within the definition of 'local_derived_type'.
     * Virtual member functions of the derived class are called
     * through the polymorphic pointer of the 'local_base_type'. 
     * */
    vec_of_sh_ptr.emplace_back
      ( 
        std::make_shared<local_derived_type> 
          ( item )
      );
    ( vec_of_sh_ptr.back() )->solve();
  } // for
  
  /*
   * Avoiding unnecessary 'shared_ptr' copies through the
   * type-detected 'auto &' in this range-based 'for' loop.
   * */
  for ( auto & obj : vec_of_sh_ptr )
  {
    /*
     * Requesting and printing the information that can
     * be returned by the 'local_base_type' instance,
     * before checking if the managed raw pointer is
     * polymorphic or not.
     * */
    cout 
      << "Original String for Object:" << endl
      << "  " << obj->get_original_string() << endl
      << "Total Number of Generated Strings:" << endl
      << "  " 
      << obj->get_total_number_of_generated_strings() << endl;
      
    /*
     * The check for polymorphism through 'dynamic_pointer_cast',
     * which works for smart pointers. For raw pointers, one
     * would use 'dynamic_cast'.
     * */
    auto  sh_ptr_for_derived =
      std::dynamic_pointer_cast<local_derived_type>(obj);
    /*
     * '!' is overloaded for 'shared_ptr', and it returns true
     * if the managed raw pointer is NULL, and then a second
     * '!' operates on the result for logical negation.
     * 
     * 'bool flag = shared_ptr_instance;' would not compile.
     * */
    bool flag_can_be_dynamically_cast
      = ! ( ! sh_ptr_for_derived );
    
    /*
     * Report status of polymorphism for the managed raw pointer,
     * making use of the ternary operator as well.
     * */
    cout
      << "Shared Pointer Can Be Dynamically Cast into That for Subclass:"
      << endl
      << "  " << ( flag_can_be_dynamically_cast ? "YES" : "NO" )
      << endl;
    
    if ( flag_can_be_dynamically_cast )
    {
      /*
       * Through the now non-polymorphic raw pointer for the
       * 'local_derived_type' instance, managed by 'sh_ptr_for_derived',
       * obtain and print the vector of generated strings, with
       * integer forms divisible by 3.
       * */
      print_container_of_items
        (
          sh_ptr_for_derived
            ->get_list_of_generated_strings() ,
          "vector of generated strings"
        );
    } // if
    
    cout << endl;
  } // for

} // test_solution

} // namespace os_test

int
main(void)
{
  using namespace os_test;
  
  test_solution();
  
  return 0;
}