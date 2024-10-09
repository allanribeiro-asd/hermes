idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS ".")
target_compile_options(${lib} PRIVATE -Wno-error=format)
