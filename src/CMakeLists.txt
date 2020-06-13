add_executable(VT_Systems_PCAP_Parcer main.cpp uniquemacstat.cpp package.cpp ../test/test.cpp)

get_directory_property(DEFS COMPILE_DEFINITIONS)

if(DEFS MATCHES "TEST_APP")
    target_link_libraries(VT_Systems_PCAP_Parcer pcap gtest gtest_main)
else()
    target_link_libraries(VT_Systems_PCAP_Parcer pcap)
endif()
