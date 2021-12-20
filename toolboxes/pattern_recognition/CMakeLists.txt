if (WIN32)
  add_definitions(-D__BUILD_GADGETRON_PR__)
endif ()


set(pr_header_fiels pr_export.h 
                    pr_kmeans.h )

set(pr_src_fiels pr_kmeans.cpp )

add_library(gadgetron_toolbox_pr OBJECT 
            ${pr_header_fiels} 
            ${pr_src_fiels} )

set_target_properties(gadgetron_toolbox_pr PROPERTIES VERSION ${GADGETRON_VERSION_STRING} SOVERSION ${GADGETRON_SOVERSION})

target_link_libraries(gadgetron_toolbox_pr
        	  ISMRMRD::ISMRMRD
            gadgetron_toolbox_log
)
target_include_directories(gadgetron_toolbox_pr
        PUBLIC
        $<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

install(TARGETS gadgetron_toolbox_pr
		EXPORT gadgetron-export
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	COMPONENT main
)


install(FILES ${pr_header_fiels} 
      DESTINATION ${GADGETRON_INSTALL_INCLUDE_PATH} COMPONENT main)

set(GADGETRON_BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR};${GADGETRON_BUILD_RPATH}" PARENT_SCOPE)