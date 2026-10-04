add_test([=[pointless_ass_test.test_equality]=]  [==[/home/serge/Code/C++/SPSC/build/spsc_tests]==] [==[--gtest_filter=pointless_ass_test.test_equality]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[pointless_ass_test.test_equality]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/serge/Code/C++/SPSC/test/tests.cpp:7]==]
    WORKING_DIRECTORY [==[/home/serge/Code/C++/SPSC/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(spsc_tests_TESTS [==[pointless_ass_test.test_equality]==])
