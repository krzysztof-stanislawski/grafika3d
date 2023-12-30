# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "K:/studia/grafika3d/out/build/x64-Debug/_deps/spdlog-src"
  "K:/studia/grafika3d/out/build/x64-Debug/_deps/spdlog-build"
  "K:/studia/grafika3d/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix"
  "K:/studia/grafika3d/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/tmp"
  "K:/studia/grafika3d/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp"
  "K:/studia/grafika3d/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src"
  "K:/studia/grafika3d/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "K:/studia/grafika3d/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "K:/studia/grafika3d/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
