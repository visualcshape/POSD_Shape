cmake_minimum_required(VERSION 3.3.0)

set(PROJECT_NAME "HW2")
set(LIBRARY_CHOICE "C")

project(${PROJECT_NAME})

link_directories("cppunitlite")
set(SOURCE_FILES mainTest.cpp )
set(SHAPE_SOURCE_FILES BoundingBox.h BoundingBox.cpp Circle.h Circle.cpp CompositeGraphics.h CompositeGraphics.cpp Graphics.h Graphic.cpp Line.h Line.cpp Point.h Point.cpp Rectangle.h Rectangle.cpp shape.h shape.cpp SimpleGraphics.h SimpleGraphic.cpp Square.h Square.cpp)
set(VISITOR_SOURCE_FILES GraphicsVisitor.cpp GraphicsVisitor.h AreaVisitor.cpp AreaVisitor.h DescriptionVisitor.cpp DescriptionVisitor.h)
set(FACTORY_SOURCE_FILES GraphicFactory.cpp GraphicFactory.h SimpleGraphicFactory.cpp SimpleGraphicFactory.h CompositeGraphicFactory.cpp CompositeGraphicFactory.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${SHAPE_SOURCE_FILES} ${VISITOR_SOURCE_FILES} ${FACTORY_SOURCE_FILES})

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(${PROJECT_NAME} CppUnitLiteOSX.a)
else()
    if(LIBRARY_CHOICE STREQUAL "MINGW")
        target_link_libraries(${PROJECT_NAME} CppUnitLiteMinGW.a)
    else()
        target_link_libraries(${PROJECT_NAME} CppUnitLite.a)
    endif()
endif()