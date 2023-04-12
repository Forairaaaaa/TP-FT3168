# CMakeLists.txt of FT3168 component

# Source files directories
set(FT3168_SRC_DIRS
    "."
)

# Head files directories
set(FT3168_INC_DIRS
    "."
)

# Public component requirement
set(FT3168_REQUIRES
    "driver"
)

# Private component requirement
set(FT3168_PRIV_REQUIRES
)

# Register component
idf_component_register(SRC_DIRS ${FT3168_SRC_DIRS}
                  INCLUDE_DIRS ${FT3168_INC_DIRS}
                  REQUIRES ${FT3168_REQUIRES}
                  PRIV_REQUIRES ${FT3168_PRIV_REQUIRES}
)
