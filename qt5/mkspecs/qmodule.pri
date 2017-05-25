host_build {
    QT_CPU_FEATURES.x86_64 = cx16 mmx sse sse2 sse3 ssse3
} else {
    QT_CPU_FEATURES.arm = neon
}
QT.global_private.enabled_features = dbus gui network posix_fallocate qml-debug reduce_exports sql system-zlib testlib widgets xml
QT.global_private.disabled_features = android-style-assets sse2 dbus-linked private_tests libudev reduce_relocations release_tools
PKG_CONFIG_EXECUTABLE = /usr/local/bin/pkg-config
QT_COORD_TYPE = double
QMAKE_LIBS_ZLIB = -lz
CONFIG += cross_compile enable_new_dtags largefile neon precompile_header
QT_BUILD_PARTS += libs tools
QT_HOST_CFLAGS_DBUS += 
