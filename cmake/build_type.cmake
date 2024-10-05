if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if(isMultiConfig)
        # Do something for the multi config
    else()
        set(allowedBuildTypes Debug Release RelWithDebInfo)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
            STRINGS "${allowedBuildTypes}"
        )
        if(NOT CMAKE_BUILD_TYPE)
            set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
        elseif(NOT CMAKE_BUILD_TYPE IN_LIST allowedBuildTypes)
            message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
        endif()
    endif()

    set(CMAKE_C_FLAGS_DEBUG "-g -O0")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-g -O0")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "-g -O0")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "-g -O0")

    set(CMAKE_C_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-O3")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-O3")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "-O3")

    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g -O3")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3")
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "-g -O3")
    set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "-g -O3")
    set(CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO "")
    set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO "-g -O3")
endif()

