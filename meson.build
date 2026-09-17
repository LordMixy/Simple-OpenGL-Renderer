project(
	'4P',
	['c', 'cpp']
)

# 'warning_level=everything'
# default_options: ['cpp_std=c++17', 'warning_level=everything']
# default_options: ['cpp_std=c++20', 'optimization=3']

deps = [dependency('glfw3'), dependency('glew'), dependency('assimp')]

source = []
includes = include_directories('include')

subdir('src')

executable('4P', source, include_directories: includes, dependencies: deps)
