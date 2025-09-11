# Description
- This tests verifies that the Mock Data Testing data is identical between the EmotiBit SD card and a generated expected output.
- The data is verified with the bash script, comparing the SD card output with the outputed test.csv file from the executable
- Instructions to run this test can be found in the EmotiBit Test Protocols Document under Mock Data Testing

The following table shows commands for choosing the test type. A typical workflow will consist of:
1. Going into debug mode
2. Setting sendTestData to true
3. Choosing the Sawtooth test '#'
4. Pressing record in the oscilliscope and waiting for the test to finish
5. Comparing the SD card result with the bash script, specifying the extension

| Command | Details |
|--------|--------|
| < | Sets "sendTestData" to true|
| > | Sets "sendTestData" to false|
| # | Sets test data to Sawtooth (this is also the default)| 