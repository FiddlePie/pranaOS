set(SOURCES
    Buffer.cpp
    ClientConnection.cpp
    Loader.cpp
    WavLoader.cpp
    WavWriter.cpp
)

set(GENERATED_SOURCES
    ../../Services/AudioServer/AudioClientEndpoint.h
    ../../Services/AudioServer/AudioServerEndpoint.h
)

pranaos_lib(LibAudio audio)
target_link_libraries(LibAudio LibCore LibIPC)
