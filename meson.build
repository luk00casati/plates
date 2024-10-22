project('plates', 'cpp',
  version : '0.1',
  default_options : [
    'cpp_std=c++11', # Set C++ standard
    'warning_level=3', # warming
    'buildtype=debugoptimized', # Set optimizer
  ]
)

# Detect if we're cross-compiling for Windows
is_windows = host_machine.system() == 'windows'

if not is_windows
  add_project_link_arguments(
    '-static',
    '-static-libgcc',
    '-static-libstdc++',
    language : 'cpp'
  )
endif

# Define the source files
src_files = [
  'src/codegen.cpp',
  'src/cpiatti.cpp',
  'src/main.cpp',
]

# Include directory for headers
inc_dir = include_directories('inc')

# Set executable name based on system
if is_windows
  exe_name = 'plates'
else
  exe_name = 'plates.elf'
endif

# Create the executable
executable(exe_name,
  src_files,
  include_directories : inc_dir,
)
