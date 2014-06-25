@ECHO off
set /P aFileName="Enter first file name: "

set /P operation="Enter operation [+ - * / %%]: "

set /P bFileName="Enter second file name: "

set /P resFileName="Enter result file name: "

set /P binaryFile="Enter binary or not binary file (-b): "

@ECHO on
BI_2 "%aFileName%" "%operation%" "%bFileName%" "%resFileName%" "%binaryFile%"
pause