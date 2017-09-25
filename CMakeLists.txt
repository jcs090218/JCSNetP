#  ========================================================================
#  $File: CMakeLists.txt $
#  $Date: 2017-04-12 10:56:14 $
#  $Revision: $
#  $Creator: Jen-Chieh Shen $
#  $Notice: See LICENSE.txt for modification and distribution information
#					 Copyright (c) 2017 by Shen, Jen-Chieh $
#  ========================================================================


CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# project settings
PROJECT(JCSNetP_Framework)
SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

#defines
ADD_DEFINITIONS(-DDEF_RET_YES)

# environment settings
ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

# include directories

# link directories

# subdir settings
ADD_SUBDIRECTORY(Libraries)
ADD_SUBDIRECTORY(JCSNetP_Src)
ADD_SUBDIRECTORY(JCSNetP_Test)
ADD_SUBDIRECTORY(JCSNetP_ClientExample)
ADD_SUBDIRECTORY(JCSNetP_ServerExample)
