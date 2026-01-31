set(srcs "main.c"
        "nimble.c"
        "misc.c"
        "trg.c")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS ".")
