if (WIN32)
    add_definitions(-DTIXML_USE_STL)
endif ()


add_subdirectory(log)

add_subdirectory(operators)
add_subdirectory(solvers)

add_subdirectory(fft)
add_subdirectory(core)
add_subdirectory(mri_core)
add_subdirectory(mri)
add_subdirectory(cmr)

add_subdirectory(mri_image)

add_subdirectory(klt)
add_subdirectory(fatwater)
add_subdirectory(deblur)
add_subdirectory(nfft)
add_subdirectory(dwt)
add_subdirectory(registration)

add_subdirectory(ffd)
add_subdirectory(image)
add_subdirectory(pattern_recognition)
add_subdirectory(denoise)

add_subdirectory(image_io)
add_subdirectory(T1)
# Should we compile the python toolbox
if (BUILD_PYTHON_SUPPORT)
    message("Find python; build gadgetron toolbox python")
    add_subdirectory(python)
else ()
    message("Cannot find python; do not build gadgetron toolbox python")
endif ()

if (ARMADILLO_FOUND AND Boost_FOUND AND PLPLOT_FOUND)
    add_subdirectory(plplot)
endif ()

set(GADGETRON_BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR};${GADGETRON_BUILD_RPATH}" PARENT_SCOPE)

add_library(gadgetron_toolbox SHARED empty.cpp)

target_link_libraries(gadgetron_toolbox 
    gadgetron_toolbox_cmr
    gadgetron_toolbox_cpu_image
    gadgetron_toolbox_cpucore
    gadgetron_toolbox_cpudwt
    gadgetron_toolbox_cpufft
    gadgetron_toolbox_cpuklt
    gadgetron_toolbox_cpunfft
    gadgetron_toolbox_cpureg
    gadgetron_toolbox_cpusdc
    gadgetron_toolbox_deblur
    gadgetron_toolbox_denoise
    gadgetron_toolbox_fatwater
    gadgetron_toolbox_image_analyze_io
    gadgetron_toolbox_log
    gadgetron_toolbox_plplot
    gadgetron_toolbox_pr
    gadgetron_toolbox_python
    gadgetron_toolbox_spiral
    gadgetron_toolbox_t1
)

install(TARGETS gadgetron_toolbox
    EXPORT gadgetron-export
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    COMPONENT main
)

set_target_properties(gadgetron_toolbox PROPERTIES VERSION ${GADGETRON_VERSION_STRING} SOVERSION ${GADGETRON_SOVERSION})


if (CUDA_FOUND)
    cuda_add_library(gadgetron_toolbox_gpu SHARED empty.cpp)
    
    set_target_properties(gadgetron_toolbox_gpu PROPERTIES VERSION ${GADGETRON_VERSION_STRING} SOVERSION ${GADGETRON_SOVERSION})


    install(TARGETS gadgetron_toolbox_gpu
            EXPORT gadgetron-export
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            COMPONENT main
    )
endif ()

