# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tadeusz/Desktop/ntru

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tadeusz/Desktop/ntru

# Include any dependencies generated for this target.
include CMakeFiles/ntrulib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ntrulib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ntrulib.dir/flags.make

CMakeFiles/ntrulib.dir/src/debug.c.o: CMakeFiles/ntrulib.dir/flags.make
CMakeFiles/ntrulib.dir/src/debug.c.o: src/debug.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tadeusz/Desktop/ntru/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ntrulib.dir/src/debug.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ntrulib.dir/src/debug.c.o   -c /home/tadeusz/Desktop/ntru/src/debug.c

CMakeFiles/ntrulib.dir/src/debug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ntrulib.dir/src/debug.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tadeusz/Desktop/ntru/src/debug.c > CMakeFiles/ntrulib.dir/src/debug.c.i

CMakeFiles/ntrulib.dir/src/debug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ntrulib.dir/src/debug.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tadeusz/Desktop/ntru/src/debug.c -o CMakeFiles/ntrulib.dir/src/debug.c.s

CMakeFiles/ntrulib.dir/src/debug.c.o.requires:

.PHONY : CMakeFiles/ntrulib.dir/src/debug.c.o.requires

CMakeFiles/ntrulib.dir/src/debug.c.o.provides: CMakeFiles/ntrulib.dir/src/debug.c.o.requires
	$(MAKE) -f CMakeFiles/ntrulib.dir/build.make CMakeFiles/ntrulib.dir/src/debug.c.o.provides.build
.PHONY : CMakeFiles/ntrulib.dir/src/debug.c.o.provides

CMakeFiles/ntrulib.dir/src/debug.c.o.provides.build: CMakeFiles/ntrulib.dir/src/debug.c.o


CMakeFiles/ntrulib.dir/src/hashtable.c.o: CMakeFiles/ntrulib.dir/flags.make
CMakeFiles/ntrulib.dir/src/hashtable.c.o: src/hashtable.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tadeusz/Desktop/ntru/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ntrulib.dir/src/hashtable.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ntrulib.dir/src/hashtable.c.o   -c /home/tadeusz/Desktop/ntru/src/hashtable.c

CMakeFiles/ntrulib.dir/src/hashtable.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ntrulib.dir/src/hashtable.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tadeusz/Desktop/ntru/src/hashtable.c > CMakeFiles/ntrulib.dir/src/hashtable.c.i

CMakeFiles/ntrulib.dir/src/hashtable.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ntrulib.dir/src/hashtable.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tadeusz/Desktop/ntru/src/hashtable.c -o CMakeFiles/ntrulib.dir/src/hashtable.c.s

CMakeFiles/ntrulib.dir/src/hashtable.c.o.requires:

.PHONY : CMakeFiles/ntrulib.dir/src/hashtable.c.o.requires

CMakeFiles/ntrulib.dir/src/hashtable.c.o.provides: CMakeFiles/ntrulib.dir/src/hashtable.c.o.requires
	$(MAKE) -f CMakeFiles/ntrulib.dir/build.make CMakeFiles/ntrulib.dir/src/hashtable.c.o.provides.build
.PHONY : CMakeFiles/ntrulib.dir/src/hashtable.c.o.provides

CMakeFiles/ntrulib.dir/src/hashtable.c.o.provides.build: CMakeFiles/ntrulib.dir/src/hashtable.c.o


CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o: CMakeFiles/ntrulib.dir/flags.make
CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o: src/integer_arithmetic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tadeusz/Desktop/ntru/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o   -c /home/tadeusz/Desktop/ntru/src/integer_arithmetic.c

CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tadeusz/Desktop/ntru/src/integer_arithmetic.c > CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.i

CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tadeusz/Desktop/ntru/src/integer_arithmetic.c -o CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.s

CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o.requires:

.PHONY : CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o.requires

CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o.provides: CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o.requires
	$(MAKE) -f CMakeFiles/ntrulib.dir/build.make CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o.provides.build
.PHONY : CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o.provides

CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o.provides.build: CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o


CMakeFiles/ntrulib.dir/src/main.c.o: CMakeFiles/ntrulib.dir/flags.make
CMakeFiles/ntrulib.dir/src/main.c.o: src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tadeusz/Desktop/ntru/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ntrulib.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ntrulib.dir/src/main.c.o   -c /home/tadeusz/Desktop/ntru/src/main.c

CMakeFiles/ntrulib.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ntrulib.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tadeusz/Desktop/ntru/src/main.c > CMakeFiles/ntrulib.dir/src/main.c.i

CMakeFiles/ntrulib.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ntrulib.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tadeusz/Desktop/ntru/src/main.c -o CMakeFiles/ntrulib.dir/src/main.c.s

CMakeFiles/ntrulib.dir/src/main.c.o.requires:

.PHONY : CMakeFiles/ntrulib.dir/src/main.c.o.requires

CMakeFiles/ntrulib.dir/src/main.c.o.provides: CMakeFiles/ntrulib.dir/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/ntrulib.dir/build.make CMakeFiles/ntrulib.dir/src/main.c.o.provides.build
.PHONY : CMakeFiles/ntrulib.dir/src/main.c.o.provides

CMakeFiles/ntrulib.dir/src/main.c.o.provides.build: CMakeFiles/ntrulib.dir/src/main.c.o


CMakeFiles/ntrulib.dir/src/memory.c.o: CMakeFiles/ntrulib.dir/flags.make
CMakeFiles/ntrulib.dir/src/memory.c.o: src/memory.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tadeusz/Desktop/ntru/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/ntrulib.dir/src/memory.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ntrulib.dir/src/memory.c.o   -c /home/tadeusz/Desktop/ntru/src/memory.c

CMakeFiles/ntrulib.dir/src/memory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ntrulib.dir/src/memory.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tadeusz/Desktop/ntru/src/memory.c > CMakeFiles/ntrulib.dir/src/memory.c.i

CMakeFiles/ntrulib.dir/src/memory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ntrulib.dir/src/memory.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tadeusz/Desktop/ntru/src/memory.c -o CMakeFiles/ntrulib.dir/src/memory.c.s

CMakeFiles/ntrulib.dir/src/memory.c.o.requires:

.PHONY : CMakeFiles/ntrulib.dir/src/memory.c.o.requires

CMakeFiles/ntrulib.dir/src/memory.c.o.provides: CMakeFiles/ntrulib.dir/src/memory.c.o.requires
	$(MAKE) -f CMakeFiles/ntrulib.dir/build.make CMakeFiles/ntrulib.dir/src/memory.c.o.provides.build
.PHONY : CMakeFiles/ntrulib.dir/src/memory.c.o.provides

CMakeFiles/ntrulib.dir/src/memory.c.o.provides.build: CMakeFiles/ntrulib.dir/src/memory.c.o


CMakeFiles/ntrulib.dir/src/polynomial.c.o: CMakeFiles/ntrulib.dir/flags.make
CMakeFiles/ntrulib.dir/src/polynomial.c.o: src/polynomial.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tadeusz/Desktop/ntru/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/ntrulib.dir/src/polynomial.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ntrulib.dir/src/polynomial.c.o   -c /home/tadeusz/Desktop/ntru/src/polynomial.c

CMakeFiles/ntrulib.dir/src/polynomial.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ntrulib.dir/src/polynomial.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tadeusz/Desktop/ntru/src/polynomial.c > CMakeFiles/ntrulib.dir/src/polynomial.c.i

CMakeFiles/ntrulib.dir/src/polynomial.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ntrulib.dir/src/polynomial.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tadeusz/Desktop/ntru/src/polynomial.c -o CMakeFiles/ntrulib.dir/src/polynomial.c.s

CMakeFiles/ntrulib.dir/src/polynomial.c.o.requires:

.PHONY : CMakeFiles/ntrulib.dir/src/polynomial.c.o.requires

CMakeFiles/ntrulib.dir/src/polynomial.c.o.provides: CMakeFiles/ntrulib.dir/src/polynomial.c.o.requires
	$(MAKE) -f CMakeFiles/ntrulib.dir/build.make CMakeFiles/ntrulib.dir/src/polynomial.c.o.provides.build
.PHONY : CMakeFiles/ntrulib.dir/src/polynomial.c.o.provides

CMakeFiles/ntrulib.dir/src/polynomial.c.o.provides.build: CMakeFiles/ntrulib.dir/src/polynomial.c.o


CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o: CMakeFiles/ntrulib.dir/flags.make
CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o: src/quotient_polynomial_ring.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tadeusz/Desktop/ntru/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o   -c /home/tadeusz/Desktop/ntru/src/quotient_polynomial_ring.c

CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tadeusz/Desktop/ntru/src/quotient_polynomial_ring.c > CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.i

CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tadeusz/Desktop/ntru/src/quotient_polynomial_ring.c -o CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.s

CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o.requires:

.PHONY : CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o.requires

CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o.provides: CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o.requires
	$(MAKE) -f CMakeFiles/ntrulib.dir/build.make CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o.provides.build
.PHONY : CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o.provides

CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o.provides.build: CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o


# Object files for target ntrulib
ntrulib_OBJECTS = \
"CMakeFiles/ntrulib.dir/src/debug.c.o" \
"CMakeFiles/ntrulib.dir/src/hashtable.c.o" \
"CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o" \
"CMakeFiles/ntrulib.dir/src/main.c.o" \
"CMakeFiles/ntrulib.dir/src/memory.c.o" \
"CMakeFiles/ntrulib.dir/src/polynomial.c.o" \
"CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o"

# External object files for target ntrulib
ntrulib_EXTERNAL_OBJECTS =

libntrulib.a: CMakeFiles/ntrulib.dir/src/debug.c.o
libntrulib.a: CMakeFiles/ntrulib.dir/src/hashtable.c.o
libntrulib.a: CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o
libntrulib.a: CMakeFiles/ntrulib.dir/src/main.c.o
libntrulib.a: CMakeFiles/ntrulib.dir/src/memory.c.o
libntrulib.a: CMakeFiles/ntrulib.dir/src/polynomial.c.o
libntrulib.a: CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o
libntrulib.a: CMakeFiles/ntrulib.dir/build.make
libntrulib.a: CMakeFiles/ntrulib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tadeusz/Desktop/ntru/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C static library libntrulib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/ntrulib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ntrulib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ntrulib.dir/build: libntrulib.a

.PHONY : CMakeFiles/ntrulib.dir/build

CMakeFiles/ntrulib.dir/requires: CMakeFiles/ntrulib.dir/src/debug.c.o.requires
CMakeFiles/ntrulib.dir/requires: CMakeFiles/ntrulib.dir/src/hashtable.c.o.requires
CMakeFiles/ntrulib.dir/requires: CMakeFiles/ntrulib.dir/src/integer_arithmetic.c.o.requires
CMakeFiles/ntrulib.dir/requires: CMakeFiles/ntrulib.dir/src/main.c.o.requires
CMakeFiles/ntrulib.dir/requires: CMakeFiles/ntrulib.dir/src/memory.c.o.requires
CMakeFiles/ntrulib.dir/requires: CMakeFiles/ntrulib.dir/src/polynomial.c.o.requires
CMakeFiles/ntrulib.dir/requires: CMakeFiles/ntrulib.dir/src/quotient_polynomial_ring.c.o.requires

.PHONY : CMakeFiles/ntrulib.dir/requires

CMakeFiles/ntrulib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ntrulib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ntrulib.dir/clean

CMakeFiles/ntrulib.dir/depend:
	cd /home/tadeusz/Desktop/ntru && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tadeusz/Desktop/ntru /home/tadeusz/Desktop/ntru /home/tadeusz/Desktop/ntru /home/tadeusz/Desktop/ntru /home/tadeusz/Desktop/ntru/CMakeFiles/ntrulib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ntrulib.dir/depend

