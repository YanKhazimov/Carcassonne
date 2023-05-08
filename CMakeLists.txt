cmake_minimum_required(VERSION 3.14)

project(Carcassonne VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

set(PROJECT_SOURCES
        DataTypes.h
        DataTypes.cpp
        TileData.h
        TileData.cpp
        ObjectManager.h
        ObjectManager.cpp
        MapObjectData.h
        MapObjectData.cpp
        Tile.h
        Tile.cpp
        QmlPresenter.h
        QmlPresenter.cpp
        TilesModel.h
        TilesModel.cpp
        DataRoles.h
        MapModel.h
        MapModel.cpp
        Player.h
        Player.cpp
        PlayersModel.h
        PlayersModel.cpp
        DeckBuilder.h
        DeckBuilder.cpp
        RemainingTilesModel.h
        RemainingTilesModel.cpp
        ShuffledDeck.h
        ShuffledDeck.cpp
        main.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Carcassonne
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Carcassonne APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Carcassonne SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Carcassonne
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(Carcassonne
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Carcassonne
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

set_target_properties(Carcassonne PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(Carcassonne)
    qt_finalize_executable(Carcassonne)
endif()
