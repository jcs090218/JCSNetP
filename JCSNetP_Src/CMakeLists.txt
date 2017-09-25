#  ========================================================================
#  $File: CMakeLists.txt $
#  $Date: 2017-04-12 10:56:14 $
#  $Revision: $
#  $Creator: Jen-Chieh Shen $
#  $Notice: See LICENSE.txt for modification and distribution information
#					 Copyright (c) 2017 by Shen, Jen-Chieh $
#  ========================================================================


# project settings
PROJECT(JCSNetP_Src)

# add your header and source files here
FILE(GLOB_RECURSE ${PROJECT_NAME}_headers "*.h")
FILE(GLOB_RECURSE ${PROJECT_NAME}_sources "*.cpp")

# Create the library
# ----------------------
ADD_LIBRARY(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})
ADD_LIBRARY(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

# linker
# ----------------------

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/static)
  
# subdir settings
ADD_SUBDIRECTORY(Core)
ADD_SUBDIRECTORY(Support)
