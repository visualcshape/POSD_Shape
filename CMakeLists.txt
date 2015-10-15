cmake_minimum_required(VERSION 3.3.0)

set(PROJECT_NAME "HW2")
set(LIBRARY_CHOICE "CC")

project(${PROJECT_NAME})

link_directories("cppunitlite")
set(SOURCE_FILES mainTest.cpp BoundingBox.h BoundingBox.cpp Circle.h Circle.cpp CompositeGraphics.h CompositeGraphics.cpp Graphics.h Graphic.cpp Line.h Line.cpp Point.h Point.cpp Rectangle.h Rectangle.cpp shape.h shape.cpp SimpleGraphics.h SimpleGraphic.cpp Square.h Square.cpp GraphicVisitor.cpp GraphicVisitor.h CompositeGraphicVisitor.cpp CompositeGraphicVisitor.h SimpleGraphicVisitor.cpp SimpleGraphicVisitor.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if(LIBRARY_CHOICE STREQUAL "MINGW")
    target_link_libraries(${PROJECT_NAME} libCppUnitLiteMinGW.a)
else()
    target_link_libraries(${PROJECT_NAME} CppUnitLite.a)
endif()