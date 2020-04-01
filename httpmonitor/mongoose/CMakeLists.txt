PROJECT(mongoose C)
aux_source_directory(. MON_SRCS)
add_library(mongoose ${MON_SRCS})