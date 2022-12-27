/*
 * Class definition for 'FilesDirsExtractor',
 * designed to extract the files and subdirectories
 * in a directory.
 * */

/*
 * Worked on this code on
 *   Dec 26, 2022 / Mon
 * */

#pragma once

#include <vector>
#include <string>

namespace os_core
{
namespace dir_utils
{

class FilesDirsExtractor
{
// typedefs
public:
  using LocalClassType
    = FilesDirsExtractor;
#define LocalClassTypeName \
      FilesDirsExtractor
  
// member variables
private:
  
  std::string
    path_dir_;
  
  std::vector<std::string>
    dirs_vec_;
  std::vector<std::string>
    files_vec_;
  
// ctor dtor
public:
  
  LocalClassTypeName
  (
    std::string  path_dir
  )
  :
  path_dir_( path_dir )
  {
    assess_directory_();
  }
  
  ~LocalClassTypeName
  ()
  {}
  
// setters getters
public:
  
  std::vector<std::string> &
  get_subdirs_vec
  ()
  {
    return dirs_vec_;
  }
  
  std::vector<std::string> &
  get_files_vec
  ()
  {
    return files_vec_;
  }
  
  std::string
  get_dir
  ()
  const
  {
    return path_dir_;
  }

// member functions
public:
  
  LocalClassType &
  print
  ();

// member functions
private:
  
  LocalClassType &
  assess_directory_
  ();
  
#undef  LocalClassTypeName
};
  
} // namespace dir_utils
} // namespace os_core