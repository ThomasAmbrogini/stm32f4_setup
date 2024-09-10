set(DEBUG_OPTIONS -g)
add_library(debug_options INTERFACE)
target_compile_options(debug_options INTERFACE ${DEBUG_OPTIONS})

