/*
 * Member function definitions.
 * */

/*
 * Worked on this code on
 *   Dec 26, 2022 / Mon
 * */

#include "dir_info.hh"

#include <dirent.h>
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace os_core
{
namespace dir_utils
{

  /*
   * See an answer at
   *   https://stackoverflow.com/questions/5043403/listing-only-folders-in-directory
   * */
  FilesDirsExtractor &
  FilesDirsExtractor
    ::assess_directory_
  ()
  {
    using namespace std;
    
    dirs_vec_ .clear();
    files_vec_.clear();
    
    DIR * dir = 
      opendir( path_dir_.c_str() );
      
    if ( ! dir )
      throw  Dir_IO_Exception( path_dir_ );

    struct dirent * entry = 
      readdir( dir );
    
    while ( entry != NULL )
    {
      /*
      std::string item_type
        = ( entry->d_type == DT_DIR ) ? "dir" : "other" ;
      
      cout
        << "  " << setw(6) << item_type
        << "  " << entry->d_name
        << endl;
      */
      
      switch( entry->d_type )
      {
        case DT_DIR:
          {
            if ( 
                 ( std::string(entry->d_name) != std::string(".") ) 
                 && 
                 ( std::string(entry->d_name) != std::string("..") ) 
               )
              dirs_vec_.push_back( entry->d_name );
            break;
          }
        default:
          {
            files_vec_.push_back( entry->d_name );
            break;
          }
      } // switch - entry->d_type
      
      entry = readdir(dir);
    } // while entry

    closedir(dir);
    
    /*
     * Sort vectors.
     * */
    std::sort( dirs_vec_ .begin() , dirs_vec_ .end() );
    std::sort( files_vec_.begin() , files_vec_.end() );
    
    return *this;
  } // function - assess_directory_
  
  FilesDirsExtractor &
  FilesDirsExtractor
    ::print
  ()
  {
    using namespace std;
    
    cout << endl << "Directories :" << endl;
    for ( const auto & str : dirs_vec_ )
      cout << "  " << str << endl;
    
    cout << endl << "Files :" << endl;
    for ( const auto & str : files_vec_ )
      cout << "  " << str << endl;
    
    return *this;
  } // function - print

} // namespace dir_utils
} // namespace os_core