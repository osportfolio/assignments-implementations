# Worked on this makefile on
#                           Dec 2, 2022 / Fri

# variable definition, indeed path of the driver script
path_script := ./driver.py

# 'default' rule and its recipe calls the driver script.
default : force_look
	@$(path_script)

# There is only one cleaning job to be done by 'clean'.
clean : clean_pycache  force_look

# This recipe finds the directories called '__pycache__'
# and deletes them. These are those under the present
# working directory.
clean_pycache : force_look
	@find . -name "__pycache__" -type d -prune -exec rm -r "{}" \;

# Forces execution.
force_look :
	@true
