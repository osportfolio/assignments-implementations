name_script   := create_analyze_hierarchy_in_Python.py
dname_content := text_files

path_impl_cpp := \
  ../../C++/q_04_counts_total_number_of_lines/_ignore_obj

exe_name_cpp__with_threads := \
  line_count_report__with_threads.cc.elf
exe_name_cpp__with_OpenMP  := \
  line_count_report__with_OpenMP.cc.elf
  
default :  create  force_look

create : force_look
	@./$(name_script)  create

analyze : force_look
	@./$(name_script)  analyze
	
analyze_cpp__with_threads : force_look
	@$(path_impl_cpp)/$(exe_name_cpp__with_threads)  ./$(dname_content)
	
analyze_cpp__with_OpenMP  : force_look
	@$(path_impl_cpp)/$(exe_name_cpp__with_OpenMP)   ./$(dname_content)

clean : force_look
	@mkdir -p $(dname_content) && rm -rf $(dname_content)

force_look :
	@true;