# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /opt/sphenix/utils/stow/cmake-3.4.1/bin/cmake

# The command to remove a file.
RM = /opt/sphenix/utils/stow/cmake-3.4.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build

# Include any dependencies generated for this target.
include CMakeFiles/exampleGarfield.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exampleGarfield.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exampleGarfield.dir/flags.make

CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o: CMakeFiles/exampleGarfield.dir/flags.make
CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o: ../exampleGarfield.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o"
	/opt/rh/devtoolset-2/root/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o -c /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield.cc

CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.i"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield.cc > CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.i

CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.s"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield.cc -o CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.s

CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o.requires:

.PHONY : CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o.requires

CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o.provides: CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleGarfield.dir/build.make CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o.provides.build
.PHONY : CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o.provides

CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o.provides.build: CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o


CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o: CMakeFiles/exampleGarfield.dir/flags.make
CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o: ../src/GarfieldMessenger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o"
	/opt/rh/devtoolset-2/root/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o -c /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldMessenger.cc

CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.i"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldMessenger.cc > CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.i

CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.s"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldMessenger.cc -o CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.s

CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o.requires:

.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o.requires

CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o.provides: CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleGarfield.dir/build.make CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o.provides.build
.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o.provides

CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o.provides.build: CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o


CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o: CMakeFiles/exampleGarfield.dir/flags.make
CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o: ../src/GarfieldRunAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o"
	/opt/rh/devtoolset-2/root/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o -c /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldRunAction.cc

CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.i"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldRunAction.cc > CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.i

CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.s"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldRunAction.cc -o CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.s

CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o.requires:

.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o.requires

CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o.provides: CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleGarfield.dir/build.make CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o.provides.build
.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o.provides

CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o.provides.build: CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o


CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o: CMakeFiles/exampleGarfield.dir/flags.make
CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o: ../src/GarfieldSteppingAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o"
	/opt/rh/devtoolset-2/root/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o -c /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldSteppingAction.cc

CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.i"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldSteppingAction.cc > CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.i

CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.s"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldSteppingAction.cc -o CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.s

CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o.requires:

.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o.requires

CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o.provides: CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleGarfield.dir/build.make CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o.provides.build
.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o.provides

CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o.provides.build: CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o


CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o: CMakeFiles/exampleGarfield.dir/flags.make
CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o: ../src/GarfieldPhysics.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o"
	/opt/rh/devtoolset-2/root/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o -c /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldPhysics.cc

CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.i"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldPhysics.cc > CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.i

CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.s"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldPhysics.cc -o CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.s

CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o.requires:

.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o.requires

CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o.provides: CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleGarfield.dir/build.make CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o.provides.build
.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o.provides

CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o.provides.build: CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o


CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o: CMakeFiles/exampleGarfield.dir/flags.make
CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o: ../src/GarfieldPhysicsList.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o"
	/opt/rh/devtoolset-2/root/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o -c /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldPhysicsList.cc

CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.i"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldPhysicsList.cc > CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.i

CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.s"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldPhysicsList.cc -o CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.s

CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o.requires:

.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o.requires

CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o.provides: CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleGarfield.dir/build.make CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o.provides.build
.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o.provides

CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o.provides.build: CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o


CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o: CMakeFiles/exampleGarfield.dir/flags.make
CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o: ../src/GarfieldPrimaryGeneratorAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o"
	/opt/rh/devtoolset-2/root/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o -c /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldPrimaryGeneratorAction.cc

CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.i"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldPrimaryGeneratorAction.cc > CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.i

CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.s"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldPrimaryGeneratorAction.cc -o CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.s

CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o.requires:

.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o.requires

CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o.provides: CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleGarfield.dir/build.make CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o.provides.build
.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o.provides

CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o.provides.build: CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o


CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o: CMakeFiles/exampleGarfield.dir/flags.make
CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o: ../src/GarfieldEventAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o"
	/opt/rh/devtoolset-2/root/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o -c /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldEventAction.cc

CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.i"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldEventAction.cc > CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.i

CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.s"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldEventAction.cc -o CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.s

CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o.requires:

.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o.requires

CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o.provides: CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleGarfield.dir/build.make CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o.provides.build
.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o.provides

CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o.provides.build: CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o


CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o: CMakeFiles/exampleGarfield.dir/flags.make
CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o: ../src/GarfieldG4FastSimulationModel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o"
	/opt/rh/devtoolset-2/root/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o -c /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldG4FastSimulationModel.cc

CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.i"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldG4FastSimulationModel.cc > CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.i

CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.s"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldG4FastSimulationModel.cc -o CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.s

CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o.requires:

.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o.requires

CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o.provides: CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleGarfield.dir/build.make CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o.provides.build
.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o.provides

CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o.provides.build: CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o


CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o: CMakeFiles/exampleGarfield.dir/flags.make
CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o: ../src/GarfieldDetectorConstruction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o"
	/opt/rh/devtoolset-2/root/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o -c /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldDetectorConstruction.cc

CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.i"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldDetectorConstruction.cc > CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.i

CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.s"
	/opt/rh/devtoolset-2/root/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/src/GarfieldDetectorConstruction.cc -o CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.s

CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o.requires:

.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o.requires

CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o.provides: CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleGarfield.dir/build.make CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o.provides.build
.PHONY : CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o.provides

CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o.provides.build: CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o


# Object files for target exampleGarfield
exampleGarfield_OBJECTS = \
"CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o" \
"CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o" \
"CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o" \
"CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o" \
"CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o" \
"CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o" \
"CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o" \
"CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o" \
"CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o" \
"CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o"

# External object files for target exampleGarfield
exampleGarfield_EXTERNAL_OBJECTS =

exampleGarfield: CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o
exampleGarfield: CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o
exampleGarfield: CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o
exampleGarfield: CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o
exampleGarfield: CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o
exampleGarfield: CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o
exampleGarfield: CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o
exampleGarfield: CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o
exampleGarfield: CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o
exampleGarfield: CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o
exampleGarfield: CMakeFiles/exampleGarfield.dir/build.make
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4Tree.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4GMocren.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4visHepRep.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4RayTracer.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4VRML.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4OpenGL.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4gl2ps.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4interfaces.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4persistency.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4analysis.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4error_propagation.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4readout.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4physicslists.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4parmodels.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libCore.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libRIO.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libNet.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libHist.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libGraf.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libGraf3d.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libGpad.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libTree.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libRint.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libPostscript.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libMatrix.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libPhysics.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libMathCore.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libThread.so
exampleGarfield: /opt/sphenix/core/root-6.06.02/lib/libMultiProc.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4FR.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4vis_management.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4modeling.so
exampleGarfield: /usr/lib64/libXm.so
exampleGarfield: /usr/lib64/libSM.so
exampleGarfield: /usr/lib64/libICE.so
exampleGarfield: /usr/lib64/libX11.so
exampleGarfield: /usr/lib64/libXext.so
exampleGarfield: /usr/lib64/libXmu.so
exampleGarfield: /usr/lib64/libGLU.so
exampleGarfield: /usr/lib64/libGL.so
exampleGarfield: /usr/lib64/libQtOpenGL_debug.so
exampleGarfield: /usr/lib64/libQtGui.so
exampleGarfield: /usr/lib64/libQtGui_debug.so
exampleGarfield: /usr/lib64/libQtCore.so
exampleGarfield: /usr/lib64/libQtCore_debug.so
exampleGarfield: /opt/sphenix/core/lib/libxerces-c.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4run.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4event.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4tracking.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4processes.so
exampleGarfield: /usr/lib64/libz.so
exampleGarfield: /usr/lib64/libexpat.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4digits_hits.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4track.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4particles.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4geometry.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4materials.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4graphics_reps.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4intercoms.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4global.so
exampleGarfield: /opt/sphenix/core/geant4/lib64/libG4clhep.so
exampleGarfield: CMakeFiles/exampleGarfield.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable exampleGarfield"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exampleGarfield.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exampleGarfield.dir/build: exampleGarfield

.PHONY : CMakeFiles/exampleGarfield.dir/build

CMakeFiles/exampleGarfield.dir/requires: CMakeFiles/exampleGarfield.dir/exampleGarfield.cc.o.requires
CMakeFiles/exampleGarfield.dir/requires: CMakeFiles/exampleGarfield.dir/src/GarfieldMessenger.cc.o.requires
CMakeFiles/exampleGarfield.dir/requires: CMakeFiles/exampleGarfield.dir/src/GarfieldRunAction.cc.o.requires
CMakeFiles/exampleGarfield.dir/requires: CMakeFiles/exampleGarfield.dir/src/GarfieldSteppingAction.cc.o.requires
CMakeFiles/exampleGarfield.dir/requires: CMakeFiles/exampleGarfield.dir/src/GarfieldPhysics.cc.o.requires
CMakeFiles/exampleGarfield.dir/requires: CMakeFiles/exampleGarfield.dir/src/GarfieldPhysicsList.cc.o.requires
CMakeFiles/exampleGarfield.dir/requires: CMakeFiles/exampleGarfield.dir/src/GarfieldPrimaryGeneratorAction.cc.o.requires
CMakeFiles/exampleGarfield.dir/requires: CMakeFiles/exampleGarfield.dir/src/GarfieldEventAction.cc.o.requires
CMakeFiles/exampleGarfield.dir/requires: CMakeFiles/exampleGarfield.dir/src/GarfieldG4FastSimulationModel.cc.o.requires
CMakeFiles/exampleGarfield.dir/requires: CMakeFiles/exampleGarfield.dir/src/GarfieldDetectorConstruction.cc.o.requires

.PHONY : CMakeFiles/exampleGarfield.dir/requires

CMakeFiles/exampleGarfield.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exampleGarfield.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exampleGarfield.dir/clean

CMakeFiles/exampleGarfield.dir/depend:
	cd /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build /home/sphenix/work/garfield/Examples/Geant4GarfieldInterface/exampleGarfield_build/CMakeFiles/exampleGarfield.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exampleGarfield.dir/depend

