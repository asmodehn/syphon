#
# Copyright (c) 2009, Asmodehn's Corp.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright notice,
#	    this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#		notice, this list of conditions and the following disclaimer in the
#	    documentation and/or other materials provided with the distribution.
#     * Neither the name of the Asmodehn's Corp. nor the names of its
#	    contributors may be used to endorse or promote products derived
#	    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
# THE POSSIBILITY OF SUCH DAMAGE.
#

#Using WkCMake, mandatory calls
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR )
INCLUDE ( CMake/WkCMake.cmake )
WkCMakeDir ( CMake )

#declaring the project
WkProject( syphon C )

# in case we are linked with a SHARED LIB
IF(MSVC)
ELSEIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	WkAddCXXFlags("-fPIC")
ENDIF()


add_subdirectory("depends/entityx")
include_directories( "depends/entityx")

#build rules for the project
#WkLibraryBuild( ProjectC1 STATIC "src/C1" )
#WkLibraryBuild( ProjectC2 SHARED "src/C2" )
#WkLibraryBuild( ProjectC3 MODULE "src/C3" )
WkLibraryBuild( syphon STATIC "src/syphon" )

WkExportConfig(syphon)

#TODO: command line tool

#Testing
#WkTestBuild( maintestC )
#WkTestRun( ProjectC maintestC )

