project('plates', 'cpp',
  version : '0.1',
  default_options : ['cpp_std=c++11']  # Set C++ standard
)

# Detect if we're cross-compiling for Windows
is_windows = host_machine.system() == 'windows'

# Define the source files
src_files = [
  'codegen.cpp',
  'cpiatti.cpp',
  'main.cpp',
]

# Define the headers files
head_files = [
    'cpiatti.hpp',
]
# Include directory for headers
inc_dir = include_directories(head_files)

# Set any Windows-specific compiler arguments
if is_windows
  add_project_arguments('-DWIN32', language : 'cpp')
endif

# Set executable name based on system
if is_windows
  exe_name = 'plates.exe'
else
  exe_name = 'plates.elf'
endif

# Create the executable
executable(exe_name,
  src_files,
  include_directories : inc_dir,
)