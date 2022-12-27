name_script   := create_analyze_hierarchy_in_Python.py
dname_content := text_files

default :  create  force_look

create : force_look
	@./$(name_script)  create

analyze : force_look
	@./$(name_script)  analyze

clean : force_look
	@mkdir -p $(dname_content) && rm -rf $(dname_content)

force_look :
	@true;