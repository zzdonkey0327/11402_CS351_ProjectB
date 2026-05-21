# Acceptance Tests

## 1. Purpose

This document defines the acceptance tests for the CSV Mini Database & Query Engine. These tests verify that the implemented features satisfy the user stories and acceptance criteria for the first version of the system.[web:92][web:95][web:98]

## 2. Scope

The acceptance tests in this document cover the following features:

- Startup help message
- `LOAD` command
- `SELECT` command
- `INSERT` command
- Basic error handling

## 3. Entry Criteria

Acceptance testing may begin when the following conditions are met:

- The source code builds successfully.
- Core command handling is implemented.
- Test CSV files are prepared.
- The test environment is ready.
- Relevant requirements and acceptance criteria have been documented.[web:92][web:97]

## 4. Exit Criteria

Acceptance testing is complete when:

- All defined acceptance tests have been executed.
- Critical failures have been fixed or documented.
- The implemented features satisfy the acceptance criteria for version 1.[web:91][web:92]

## 5. Test Environment

- Local machine
- Command-line terminal
- Compiled program executable
- Test CSV files stored locally

## 6. Test Data

### 6.1 Valid CSV File: `students.csv`

```csv
id,name,score
1,Alice,90
2,Bob,75
3,Carol,88
```

### 6.2 Malformed CSV File: `students_malformed.csv`

```csv
id,name,score
1,Alice
2,Bob,75,extra
```

## 7. Acceptance Test Cases

### TC-START-01 Startup Help Message

**Related Requirement:** FR-01  
**Related Story:** System Startup

**Precondition:** The program executable is available.

**Steps:**
1. Run the program.
2. Observe the startup output.

**Expected Result:**
- The system prints a welcome message.
- The system displays the supported commands.
- The system shows example syntax for `LOAD`, `SELECT`, and `INSERT`.

---

### TC-LOAD-01 Load Valid CSV File

**Related Requirement:** FR-02  
**Related Story:** PX11402-10 LOAD Command

**Precondition:** `students.csv` exists and is readable.

**Steps:**
1. Start the program.
2. Enter `LOAD students.csv`.

**Expected Result:**
- The system opens the file successfully.
- The system parses the header row as column names.
- The system stores the table in memory.
- The system displays a success message.

---

### TC-LOAD-02 Load Missing File

**Related Requirement:** FR-02, FR-05  
**Related Story:** PX11402-10 LOAD Command

**Precondition:** The specified file does not exist.

**Steps:**
1. Start the program.
2. Enter `LOAD missing.csv`.

**Expected Result:**
- The system does not crash.
- The system displays an error message indicating that the file cannot be opened.

---

### TC-LOAD-03 Load Malformed CSV File

**Related Requirement:** FR-02, FR-05  
**Related Story:** PX11402-10 LOAD Command

**Precondition:** `students_malformed.csv` exists.

**Steps:**
1. Start the program.
2. Enter `LOAD students_malformed.csv`.

**Expected Result:**
- The system detects malformed CSV content or inconsistent row structure.
- The system displays an error message or rejects invalid rows according to implementation rules.
- The program remains usable after the error.

---

### TC-SELECT-01 Select All Columns

**Related Requirement:** FR-03  
**Related Story:** PX11402-15 SELECT Command

**Precondition:** `students.csv` has been loaded successfully.

**Steps:**
1. Enter `SELECT * FROM students`.

**Expected Result:**
- The system displays all columns: `id`, `name`, and `score`.
- The system prints all available rows from the loaded table.

---

### TC-SELECT-02 Select Specific Columns

**Related Requirement:** FR-03  
**Related Story:** PX11402-15 SELECT Command

**Precondition:** `students.csv` has been loaded successfully.

**Steps:**
1. Enter `SELECT name, score FROM students`.

**Expected Result:**
- The system displays only the `name` and `score` columns.
- The system prints the correct values for all rows.

---

### TC-SELECT-03 Select Non-Existing Column

**Related Requirement:** FR-03, FR-05  
**Related Story:** PX11402-15 SELECT Command

**Precondition:** `students.csv` has been loaded successfully.

**Steps:**
1. Enter `SELECT age FROM students`.

**Expected Result:**
- The system does not execute the query.
- The system displays an error message indicating that the column does not exist.

---

### TC-SELECT-04 Select Before Load

**Related Requirement:** FR-03, FR-05  
**Related Story:** PX11402-15 SELECT Command

**Precondition:** No CSV file has been loaded.

**Steps:**
1. Start the program.
2. Enter `SELECT * FROM students`.

**Expected Result:**
- The system displays an error message indicating that no table is currently loaded.
- The program continues running.

---

### TC-INSERT-01 Insert Valid Row

**Related Requirement:** FR-04  
**Related Story:** PX11402-20 INSERT Command

**Precondition:** `students.csv` has been loaded successfully.

**Steps:**
1. Enter `INSERT INTO students (id, name, score) VALUES (4, David, 92)`.
2. Enter `SELECT * FROM students`.

**Expected Result:**
- The system accepts the insert command.
- The new row is appended to the in-memory table.
- The `SELECT` result includes the new record `4, David, 92`.

---

### TC-INSERT-02 Insert With Mismatched Value Count

**Related Requirement:** FR-04, FR-05  
**Related Story:** PX11402-20 INSERT Command

**Precondition:** `students.csv` has been loaded successfully.

**Steps:**
1. Enter `INSERT INTO students (id, name, score) VALUES (5, Emma)`.

**Expected Result:**
- The system rejects the command.
- The system displays an error message indicating that the number of values does not match the number of columns.

---

### TC-INSERT-03 Insert With Invalid Column Name

**Related Requirement:** FR-04, FR-05  
**Related Story:** PX11402-20 INSERT Command

**Precondition:** `students.csv` has been loaded successfully.

**Steps:**
1. Enter `INSERT INTO students (id, fullname, score) VALUES (5, Emma, 81)`.

**Expected Result:**
- The system rejects the command.
- The system displays an error message indicating that one or more columns do not exist.

---

### TC-INSERT-04 Insert Before Load

**Related Requirement:** FR-04, FR-05  
**Related Story:** PX11402-20 INSERT Command

**Precondition:** No CSV file has been loaded.

**Steps:**
1. Start the program.
2. Enter `INSERT INTO students (id, name, score) VALUES (4, David, 92)`.

**Expected Result:**
- The system rejects the command.
- The system displays an error message indicating that no table is currently loaded.

---

### TC-ERR-01 Invalid Command Syntax

**Related Requirement:** FR-05  
**Related Story:** All Stories

**Precondition:** The program is running.

**Steps:**
1. Enter `SELCT * FROM students`.

**Expected Result:**
- The system identifies the command as invalid.
- The system displays a syntax error message.
- The program remains active.

---

### TC-ERR-02 Unsupported Command

**Related Requirement:** FR-05  
**Related Story:** All Stories

**Precondition:** The program is running.

**Steps:**
1. Enter `DELETE FROM students`.

**Expected Result:**
- The system rejects the unsupported command.
- The system displays a message indicating that the command is not supported in version 1.

## 8. Acceptance Test Summary Matrix

| Test ID | Feature | Requirement | Story | Priority |
|---|---|---|---|---|
| TC-START-01 | Startup Help | FR-01 | System Startup | High |
| TC-LOAD-01 | LOAD valid CSV | FR-02 | PX11402-10 | High |
| TC-LOAD-02 | LOAD missing file | FR-02, FR-05 | PX11402-10 | High |
| TC-LOAD-03 | LOAD malformed CSV | FR-02, FR-05 | PX11402-10 | Medium |
| TC-SELECT-01 | SELECT all columns | FR-03 | PX11402-15 | High |
| TC-SELECT-02 | SELECT specific columns | FR-03 | PX11402-15 | High |
| TC-SELECT-03 | SELECT invalid column | FR-03, FR-05 | PX11402-15 | High |
| TC-SELECT-04 | SELECT before load | FR-03, FR-05 | PX11402-15 | Medium |
| TC-INSERT-01 | INSERT valid row | FR-04 | PX11402-20 | High |
| TC-INSERT-02 | INSERT mismatched values | FR-04, FR-05 | PX11402-20 | High |
| TC-INSERT-03 | INSERT invalid column | FR-04, FR-05 | PX11402-20 | High |
| TC-INSERT-04 | INSERT before load | FR-04, FR-05 | PX11402-20 | Medium |
| TC-ERR-01 | Invalid syntax | FR-05 | All Stories | High |
| TC-ERR-02 | Unsupported command | FR-05 | All Stories | Medium |

## 9. Notes

- Acceptance tests are derived from user stories and acceptance criteria.[web:51][web:93][web:95]
- Acceptance criteria describe what must be true for a feature to be accepted, while acceptance tests define how those conditions are verified.[web:95][web:98][web:100]
- Both positive and negative scenarios are included to improve coverage.[web:54][web:90]