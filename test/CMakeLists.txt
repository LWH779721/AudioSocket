cmake_minimum_required(VERSION 2.8) 

PROJECT(AudioSocketTest)

INCLUDE_DIRECTORIES(../include) 

ADD_EXECUTABLE(AudioEncoder AudioEncoder_test.c)  
TARGET_LINK_LIBRARIES(AudioEncoder AudioSocket m)

ADD_EXECUTABLE(AudioDecoder AudioDecoder_test.c)  
TARGET_LINK_LIBRARIES(AudioDecoder AudioSocket m asound)

ADD_EXECUTABLE(AudioDecoder_file AudioDecoder_file_test.c)  
TARGET_LINK_LIBRARIES(AudioDecoder_file AudioSocket m)
