include(../RibiLibraries/ConsoleApplicationNoWeffcpp.pri)

include(../RibiLibraries/Boost.pri)
include(../RibiClasses/CppAbout/CppAbout.pri)
include(../RibiClasses/CppFileIo/CppFileIo.pri)
include(../RibiClasses/CppHelp/CppHelp.pri)
include(../RibiClasses/CppMenuDialog/CppMenuDialog.pri)
include(../RibiClasses/CppTrace/CppTrace.pri)

#Specific, console
include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../DotMatrix/DotMatrix.pri)
include(../RibiClasses/CppRibiRandom/CppRibiRandom.pri)
include(../RibiClasses/CppTextCanvas/CppTextCanvas.pri)
include(../Maziak/MaziakConsole.pri)

SOURCES += main.cpp

# Prevents this error:
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
QMAKE_CXXFLAGS += -fext-numeric-literals
