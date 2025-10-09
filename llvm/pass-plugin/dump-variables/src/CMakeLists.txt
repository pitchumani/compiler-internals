add_library(dumpVariables MODULE
    DumpVariables.cpp
)

set_target_properties(dumpVariables PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

target_link_libraries(dumpVariables PRIVATE ${llvm_libs})

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(dumpVariables PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)

message(STATUS "dumpVariablesPass will be built as shared object")

