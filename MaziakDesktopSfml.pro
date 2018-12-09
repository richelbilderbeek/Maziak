# Builds the entire project

################################################################################
# Files
################################################################################
# Source code of the project
include(MaziakDesktopSfml.pri)
include(MaziakConsole.pri)

# Entry point for this project
SOURCES += main_sfml.cpp

################################################################################
# Compiling, linking and tools
################################################################################
# C++14
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

# High warning levels
# SFML goes bad with -Weffc++
QMAKE_CXXFLAGS += -Wall -Wextra -Wnon-virtual-dtor -pedantic -Werror

!macx{
  QMAKE_CXXFLAGS += -Wshadow
}

unix:!macx {
  # Fix error: unrecognized option '--push-state--no-as-needed'
  QMAKE_LFLAGS += -fuse-ld=gold
}

# Debug and release settings
CONFIG += debug_and_release
CONFIG(release, debug|release) {

  DEFINES += NDEBUG

  # GNU/Linux
  unix:!macx {
    # gprof
    QMAKE_CXXFLAGS += -pg
    QMAKE_LFLAGS += -pg
  }
}

CONFIG(debug, debug|release) {

  # GNU/Linux
  unix:!macx {
    # gcov
    QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
    LIBS += -lgcov

    # helgrind, for helgrind and memcheck
    QMAKE_LFLAGS += -pthread -Wl,--no-as-needed

    # UBSAN
    QMAKE_CXXFLAGS += -fsanitize=undefined
    QMAKE_LFLAGS += -fsanitize=undefined
    LIBS += -lubsan
  }
}

################################################################################
# GSL
################################################################################
include(gsl.pri)

################################################################################
# Qt5
################################################################################
QT += core gui

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable

# Fixes
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
!mac{
  QMAKE_CXXFLAGS += -fext-numeric-literals
}

# Prevent Qt for failing with this error:
# qrc_[*].cpp:400:44: error: ‘qInitResources_[*]__init_variable__’ defined but not used
# [*]: the resource filename
QMAKE_CXXFLAGS += -Wno-unused-variable

################################################################################
# RibiClasses
################################################################################

include(../RibiClasses/CppAbout/CppAbout.pri)
include(../RibiClasses/CppHelp/CppHelp.pri)
include(../RibiClasses/CppMenuDialog/CppMenuDialog.pri)
include(../RibiClasses/CppStopwatch/CppStopwatch.pri)

################################################################################
# SFML
################################################################################
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
