# Worked on this code on
#   Jan  7, 2023 / Sat

name_script_python := create_analyze_hierarchy_in_Python.py
name_script_perl   := create_analyze_hierarchy_in_Perl.pl
dname_content := text_files

path_impl_cpp := \
  ../../C++/q_04_counts_total_number_of_lines/_ignore_obj

exe_name_cpp__with_threads := \
  line_count_report__with_threads.cc.elf
exe_name_cpp__with_OpenMP  := \
  line_count_report__with_OpenMP.cc.elf
  
default :  create  force_look

create :  create_python  force_look
	@true;

analyze :  analyze_python  force_look
	@true;

create_python : force_look
	@./$(name_script_python)  create

create_perl : force_look
	@./$(name_script_perl)    create

analyze_python : force_look
	@./$(name_script_python)  analyze

analyze_perl : force_look
	@./$(name_script_perl)    analyze

analyze_cpp__with_threads : force_look
	@$(path_impl_cpp)/$(exe_name_cpp__with_threads)  ./$(dname_content)
	
analyze_cpp__with_OpenMP  : force_look
	@$(path_impl_cpp)/$(exe_name_cpp__with_OpenMP)   ./$(dname_content)

clean : force_look
	@mkdir -p $(dname_content) && rm -rf $(dname_content)

help : force_look
	@echo ""
	@echo "RECIPES"
	@echo ""
	@echo "  default                   :    creates random directory hierarchy"
	@echo "  create                    :    creates random directory hierarchy (with Python)"
	@echo "  analyze                   :    analyzes directory hierarchy (with Python)"
	@echo "  create_python             :    creates  with Python script"
	@echo "  create_perl               :    creates  with Perl   script"
	@echo "  analyze_python            :    analyzes with Python script"
	@echo "  analyze_perl              :    analyzes with Perl   script"
	@echo "  analyze_cpp__with_threads :    analyzes with C++ (std::thread)"
	@echo "  analyze_cpp__with_OpenMP  :    analyzes with C++ (OpenMP)"
	@echo "  clean                     :    removes directory"
	@echo "  help                      :    prints this help"

force_look :
	@true;