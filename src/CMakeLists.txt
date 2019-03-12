cmake_minimum_required(VERSION 2.8) 

PROJECT(AudioSocket)
 
INCLUDE_DIRECTORIES(../include) 

AUX_SOURCE_DIRECTORY(. AudioSocket)

ADD_LIBRARY (AudioSocket SHARED ${AudioSocket})
