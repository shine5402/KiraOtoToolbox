EXTRA_INCLUDEPATH += C:\\openssl\\include C:\\Utils\\my_sql\\mysql-5.7.25-winx64\\include C:\\Utils\\postgresql\\pgsql\\include
EXTRA_LIBDIR += C:\\openssl\\lib C:\\Utils\\my_sql\\mysql-5.7.25-winx64\\lib C:\\Utils\\postgresql\\pgsql\\lib
!host_build|!cross_compile {
    QMAKE_LFLAGS_APP+=-s
}
QT_CPU_FEATURES.x86_64 = cx16 mmx sse sse2 sse3
QT.global_private.enabled_features = sse2 alloca_malloc_h alloca dbus gui network relocatable sql testlib widgets xml
QT.global_private.disabled_features = alloca_h android-style-assets avx2 private_tests dbus-linked dlopen gc_binaries intelcet libudev posix_fallocate reduce_exports reduce_relocations release_tools stack-protector-strong system-zlib zstd
QT_COORD_TYPE = double
CONFIG += sse2 aesni sse3 ssse3 sse4_1 sse4_2 compile_examples force_debug_info largefile precompile_header rdrnd shani x86SimdAlways
QT_BUILD_PARTS += libs tools
QT_HOST_CFLAGS_DBUS += 
