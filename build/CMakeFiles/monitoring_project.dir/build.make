# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/build

# Include any dependencies generated for this target.
include CMakeFiles/monitoring_project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/monitoring_project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/monitoring_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/monitoring_project.dir/flags.make

CMakeFiles/monitoring_project.dir/src/main.c.o: CMakeFiles/monitoring_project.dir/flags.make
CMakeFiles/monitoring_project.dir/src/main.c.o: /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/main.c
CMakeFiles/monitoring_project.dir/src/main.c.o: CMakeFiles/monitoring_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/monitoring_project.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/monitoring_project.dir/src/main.c.o -MF CMakeFiles/monitoring_project.dir/src/main.c.o.d -o CMakeFiles/monitoring_project.dir/src/main.c.o -c /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/main.c

CMakeFiles/monitoring_project.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/monitoring_project.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/main.c > CMakeFiles/monitoring_project.dir/src/main.c.i

CMakeFiles/monitoring_project.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/monitoring_project.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/main.c -o CMakeFiles/monitoring_project.dir/src/main.c.s

CMakeFiles/monitoring_project.dir/src/metrics.c.o: CMakeFiles/monitoring_project.dir/flags.make
CMakeFiles/monitoring_project.dir/src/metrics.c.o: /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/metrics.c
CMakeFiles/monitoring_project.dir/src/metrics.c.o: CMakeFiles/monitoring_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/monitoring_project.dir/src/metrics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/monitoring_project.dir/src/metrics.c.o -MF CMakeFiles/monitoring_project.dir/src/metrics.c.o.d -o CMakeFiles/monitoring_project.dir/src/metrics.c.o -c /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/metrics.c

CMakeFiles/monitoring_project.dir/src/metrics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/monitoring_project.dir/src/metrics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/metrics.c > CMakeFiles/monitoring_project.dir/src/metrics.c.i

CMakeFiles/monitoring_project.dir/src/metrics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/monitoring_project.dir/src/metrics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/metrics.c -o CMakeFiles/monitoring_project.dir/src/metrics.c.s

CMakeFiles/monitoring_project.dir/src/expose_metrics.c.o: CMakeFiles/monitoring_project.dir/flags.make
CMakeFiles/monitoring_project.dir/src/expose_metrics.c.o: /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/expose_metrics.c
CMakeFiles/monitoring_project.dir/src/expose_metrics.c.o: CMakeFiles/monitoring_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/monitoring_project.dir/src/expose_metrics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/monitoring_project.dir/src/expose_metrics.c.o -MF CMakeFiles/monitoring_project.dir/src/expose_metrics.c.o.d -o CMakeFiles/monitoring_project.dir/src/expose_metrics.c.o -c /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/expose_metrics.c

CMakeFiles/monitoring_project.dir/src/expose_metrics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/monitoring_project.dir/src/expose_metrics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/expose_metrics.c > CMakeFiles/monitoring_project.dir/src/expose_metrics.c.i

CMakeFiles/monitoring_project.dir/src/expose_metrics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/monitoring_project.dir/src/expose_metrics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/src/expose_metrics.c -o CMakeFiles/monitoring_project.dir/src/expose_metrics.c.s

# Object files for target monitoring_project
monitoring_project_OBJECTS = \
"CMakeFiles/monitoring_project.dir/src/main.c.o" \
"CMakeFiles/monitoring_project.dir/src/metrics.c.o" \
"CMakeFiles/monitoring_project.dir/src/expose_metrics.c.o"

# External object files for target monitoring_project
monitoring_project_EXTERNAL_OBJECTS =

monitoring_project: CMakeFiles/monitoring_project.dir/src/main.c.o
monitoring_project: CMakeFiles/monitoring_project.dir/src/metrics.c.o
monitoring_project: CMakeFiles/monitoring_project.dir/src/expose_metrics.c.o
monitoring_project: CMakeFiles/monitoring_project.dir/build.make
monitoring_project: /usr/local/lib/libprom.so
monitoring_project: /usr/local/lib/libpromhttp.so
monitoring_project: CMakeFiles/monitoring_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable monitoring_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/monitoring_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/monitoring_project.dir/build: monitoring_project
.PHONY : CMakeFiles/monitoring_project.dir/build

CMakeFiles/monitoring_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/monitoring_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/monitoring_project.dir/clean

CMakeFiles/monitoring_project.dir/depend:
	cd /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/build /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/build /home/juan/Documentos/so-i-24-chp2-JuanSassi/monitor/build/CMakeFiles/monitoring_project.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/monitoring_project.dir/depend
