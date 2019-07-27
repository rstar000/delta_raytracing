set (SOURCES
    "main.cpp"
    "image.cpp"
    "geom.cpp"
    "object.hpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(delta_raytracing PRIVATE OpenMP::OpenMP_CXX)
