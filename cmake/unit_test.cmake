macro(add_unit_test_lib target)

  find_package(Git REQUIRED)

  Include(FetchContent)

  FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG        v3.7.0
  )

  FetchContent_MakeAvailable(Catch2)

  add_dependencies(${target} Catch2)
  # set(CATCH_MODULE_DIR ${source_dir}/contrib CACHE INTERNAL "Path to include CMake Catch2 integration")
endmacro()

