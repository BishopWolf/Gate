# Install script for directory: /home/alex/Gate/git/source/externals/itk-mhd/MetaIO

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/alex/Gate/git/build/itk-mhd/MetaIO/libMetaIO.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaTypes.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaLine.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaForm.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaTubeGraph.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaMesh.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaImageTypes.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaArray.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaScene.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaLandmark.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaITKUtils.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaOutput.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaUtils.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaBlob.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaEllipse.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaContour.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaGroup.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaCommand.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaFEMObject.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaSurface.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/localMetaConfiguration.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaTransform.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaObject.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaDTITube.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaTube.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaArrow.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaVesselTube.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaImage.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaImageUtils.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaGaussian.h"
    "/home/alex/Gate/git/source/externals/itk-mhd/MetaIO/metaEvent.h"
    "/home/alex/Gate/git/build/itk-mhd/MetaIO/metaIOConfig.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")

