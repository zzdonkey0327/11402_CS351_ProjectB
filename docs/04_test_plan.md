# Test Plan

## 1. Purpose

This document defines the testing strategy for the CSV Mini Database & Query Engine. The purpose of testing is to verify that each supported feature works correctly and that invalid input is handled safely.[web:48][web:51]

## 2. Scope

The test plan covers:
- Startup help display
- `LOAD` command
- `SELECT` command
- `INSERT` command
- Error handling

## 3. Test Objectives

- Verify that valid commands execute successfully
- Verify that invalid commands produce clear error messages
- Verify that loaded data is stored correctly in memory
- Verify that inserted rows are added to the active table
- Verify that selected results match expected output

## 4. Test Types

### 4.1 Unit Testing
Test individual modules such as:
- parser
- CSV loader
- query executor
- insert validator

### 4.2 Integration Testing
Test the interaction between:
- parser and executor
- loader and storage
- insert logic and storage

### 4.3 Functional Testing
Test complete user scenarios from command input to console output.[web:48][web:51]

## 5. Test Environment

- Local development machine
- Command-line terminal
- Sample CSV files
- Debug and normal build modes

## 6. Test Data

Example files:
- `students_valid.csv`
- `students_missing_header.csv`
- `students_malformed.csv`

Example sample records:
- `1,Alice,90`
- `2,Bob,75`

## 7. Entry Criteria

Testing begins when:
- project structure is available
- core modules compile successfully
- sample CSV files are prepared

## 8. Exit Criteria

Testing is complete when:
- all core feature tests have been executed
- critical defects are resolved or documented
- acceptance tests for `LOAD`, `SELECT`, and `INSERT` pass

## 9. Pass/Fail Criteria

A test passes when actual behavior matches the expected result.  
A test fails when the system returns incorrect output, crashes, or accepts invalid input unexpectedly.

## 10. Main Test Areas

### LOAD
- valid CSV load
- missing file
- malformed CSV
- empty file

### SELECT
- `SELECT *`
- specific columns
- missing column
- query before load

### INSERT
- valid insert
- invalid column name
- mismatched values
- insert before load