# CMakeLists.txt of XXX component

# Source files directories
set(XXX_SRC_DIRS
    "."
)

# Head files directories
set(XXX_INC_DIRS
    "."
)

# Public component requirement
set(XXX_REQUIRES
)

# Private component requirement
set(XXX_PRIV_REQUIRES
)

# Register component
idf_component_register(SRC_DIRS ${XXX_SRC_DIRS}
                  INCLUDE_DIRS ${XXX_INC_DIRS}
                  REQUIRES ${XXX_REQUIRES}
                  PRIV_REQUIRES ${XXX_PRIV_REQUIRES}
)