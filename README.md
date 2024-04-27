# NitroCppTest-SeanMcGoff

The goal of this project was to build a well-documented, properly tested application that can read in a JSON file of rectangles, and return the intersections between those rectangles.

## Building and this Project

This project uses CMake as a building toolkit. The target for the executable is "NitroCppTest_SeanMcGoff"

To run the executable after building, you need to specify a file containing a valid json:
```
./path/to/NitroCppTest_SeanMcGoff path/to/rectangles.json
```

## Testing this Project

Google Test was used to write the test-cases. The target for the test cases is "NitroCppTest_gtest"

**Note**: Two of the testcases (canReadJSONFile and JSONValidation) require JSON files provided in test/json in the same directory to run correctly.
This should not be too much of an issue as they are copied over by CMake on build of the testing target, but worth pointing out.