cmake_minimum_required(VERSION 3.0)
include(../../common.cmake)
project(Boost)

# Folders
# -------------------------------------------------------------------------------------------------
set(BOOST_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

globrecurse_c_cpp_sources(BOOST_SRC_FILES ${BOOST_ROOT_DIR}/boost)
group_sources(${BOOST_ROOT_DIR}/boost ${BOOST_SRC_FILES})

# Target to build
# -------------------------------------------------------------------------------------------------
#add_library(boost SHARED ${BOOST_SRC_FILES})
#target_include_directories(boost
#       PUBLIC ${BOOST_ROOT_DIR})

		