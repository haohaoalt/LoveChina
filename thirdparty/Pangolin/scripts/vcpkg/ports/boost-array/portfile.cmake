# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/array
    REF boost-1.81.0
    SHA512 1ed3ede8b8d7bb4921c11c26ac20588054e9bc21d59900eb713057227753343bc07c7fd8f6b62b6695b10a421528eccc68539a74d78a2402ec4656a25937e39d
    HEAD_REF master
)

include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})