#  ========================================================================
#  $File: CMakeLists.txt $
#  $Date: 2017-04-12 10:56:14 $
#  $Revision: $
#  $Creator: Jen-Chieh Shen $
#  $Notice: See LICENSE.txt for modification and distribution information
#					 Copyright (c) 2017 by Shen, Jen-Chieh $
#  ========================================================================


# project settings
PROJECT(JCSNetP_Test)

SET(${PROJECT_NAME}_headers *.h)
SET(${PROJECT_NAME}_sources *.cpp)

# include directories
INCLUDE_DIRECTORIES(../JCSNetP_Src)

# link
# ------------------------
TARGET_LINK_LIBRARIES(${PROJECT_NAME} JCSNetP)

# create binaries
# ------------------------
ADD_EXECUTABLE(${PROJECT_NAME} ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

#configure install
INSTALL(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/static)
