!host_build {
    QMAKE_CFLAGS    += --sysroot=$$[QT_SYSROOT]
    QMAKE_CXXFLAGS  += --sysroot=$$[QT_SYSROOT]
    QMAKE_LFLAGS    += --sysroot=$$[QT_SYSROOT]
}
host_build {
    QT_ARCH = x86_64
    QT_TARGET_ARCH = arm
} else {
    QT_ARCH = arm
}
QT.global.enabled_features = accessibility c++11 c++14 c++1z concurrent static
QT.global.disabled_features = framework shared rpath debug_and_release simulator_and_device build_all pkg-config force_asserts separate_debug_info
CONFIG += cross_compile release static
QT_CONFIG += accessibility release c++11 c++14 c++1z concurrent dbus no-pkg-config mremap reduce_exports release_tools static stl
QT_VERSION = 5.8.1
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 8
QT_PATCH_VERSION = 1
QT_EDITION = OpenSource
