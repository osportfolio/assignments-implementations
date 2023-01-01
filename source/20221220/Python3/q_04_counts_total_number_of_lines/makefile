name_script   := create_analyze_hierarchy_in_Python.py
dname_content := text_files

path_impl_cpp := \
  ../../C++/q_04_counts_total_number_of_lines/_ignore_obj/line_count_report__with_threads.cc.elf
path_analyzed := \
  ./text_files
  
default :  create  force_look

create : force_look
	@./$(name_script)  create

analyze : force_look
	@./$(name_script)  analyze
	
analyze_cpp : force_look
	@$(path_impl_cpp)  $(path_analyzed)

clean : force_look
	@mkdir -p $(dname_content) && rm -rf $(dname_content)

force_look :
	@true;