include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(bundle src/main.cpp src/ORBMatching.cpp src/sphere2500.cpp)

# 与G2O和OpenCV链接
target_link_libraries(bundle
        g2o_core g2o_stuff g2o_cli
        GL GLU cholmod
        g2o_incremental g2o_interactive g2o_interface g2o_parser
        g2o_solver_cholmod g2o_solver_csparse g2o_solver_dense g2o_solver_pcg
        g2o_types_icp g2o_types_sba g2o_types_sim3 g2o_types_slam2d g2o_types_slam3d
        ${g2o_libs}
        ${OpenCV_LIBS}
        ${QT_LIBRARIES}
        ${QT_QTOPENGL_LIBRARY}
        ${GLUT_LIBRARY}
        ${OPENGL_LIBRARY}
)