qt4_wrap_cpp (MOC dispatchthread.h)

ADD_LIBRARY(wtwithqt STATIC
  wqapplication.cpp
  dispatchthread.cpp
  ${MOC}
)

target_link_libraries(wtwithqt ${Wt_LIBRARIES} ${Boost_LIBRARIES})

#
# If you have Wt installed somehwere, you should use the
# installed Wt header files for your own Wt projects.
# e.g. INCLUDE_DIRECTORIES(/usr/local/wt/include)
# instead of the following:
#
# INCLUDE_DIRECTORIES(
#   ${WT_SOURCE_DIR}/src/wt
#   ${QT_QTCORE_INCLUDE_DIR} ${QT_INCLUDE_DIR}
# )
