add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE image)
target_link_libraries(${PROJECT_NAME} PRIVATE parser)
target_link_libraries(${PROJECT_NAME} PRIVATE sandpile)
target_link_libraries(${PROJECT_NAME} PRIVATE utility)
target_link_libraries(${PROJECT_NAME} INTERFACE vector)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})