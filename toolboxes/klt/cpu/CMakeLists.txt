if (WIN32)
  add_definitions(-D__BUILD_GADGETRON_CPUKLT__)
endif ()
add_library(gadgetron_toolbox_cpuklt OBJECT 
  cpuklt_export.h 
  hoNDKLT.h
  hoNDKLT.cpp
  )

set_target_properties(gadgetron_toolbox_cpuklt PROPERTIES VERSION ${GADGETRON_VERSION_STRING} SOVERSION ${GADGETRON_SOVERSION})

target_include_directories(
        gadgetron_toolbox_cpuklt
        PUBLIC
        $<INSTALL_INTERFACE:include/gadgetron>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>

)

install(TARGETS gadgetron_toolbox_cpuklt
	EXPORT gadgetron-export
		LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	COMPONENT main
)


install(FILES
  cpuklt_export.h 
  hoNDKLT.h
  DESTINATION ${GADGETRON_INSTALL_INCLUDE_PATH} COMPONENT main)

set(GADGETRON_BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR};${GADGETRON_BUILD_RPATH}" PARENT_SCOPE)
