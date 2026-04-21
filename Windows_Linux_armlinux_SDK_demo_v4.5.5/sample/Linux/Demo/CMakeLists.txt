add_executable(RecoDemo RecoDemo.cpp rgb2bmp.cpp)
# include_directories(../ffmpeg/include)
# target_include_directories(RecoDemo PRIVATE ./ ../Interface ../OS ../AICamera
#                                         ../ffmpeg/lib/linux64_16)
target_link_libraries(
    RecoDemo
  PRIVATE pthread
  AICameraModule
            avutil
            avcodec
            swscale
            avformat
            avdevice
            swresample
            avfilter)
