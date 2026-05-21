# Requirements Traceability Matrix

## Purpose

This document maps requirements to Jira stories, design components, source modules, and test coverage. A requirements traceability matrix is used to confirm that each requirement is implemented and verified.[web:78][web:81][web:84]

## Traceability Matrix

| Requirement ID | Requirement Summary | Jira Story | Design Component | Source Module | Test Reference | Status |
|---|---|---|---|---|---|---|
| FR-01 | Print startup help and supported commands | Startup Help | CLI Module | `src/main.cpp` | TC-START-01 | Planned |
| FR-02 | Load CSV file into memory | PX11402-10 | CSV Loader Module | `src/loader.cpp` | TC-LOAD-01, TC-LOAD-02, TC-LOAD-03 | In Progress |
| FR-03 | Execute `SELECT *` and projection queries | PX11402-15 | Parser + Query Executor | `src/parser.cpp`, `src/query.cpp` | TC-SELECT-01, TC-SELECT-02, TC-SELECT-03 | In Progress |
| FR-04 | Insert a new row into the table | PX11402-20 | Parser + Insert Executor | `src/parser.cpp`, `src/insert.cpp` | TC-INSERT-01, TC-INSERT-02, TC-INSERT-03 | In Progress |
| FR-05 | Handle invalid syntax and execution errors | All Stories | Error Handling Module | `src/error.cpp` | TC-ERR-01, TC-ERR-02 | Planned |
| NFR-01 | Provide clear command syntax guidance | Startup Help | CLI Module | `src/main.cpp` | TC-START-01 | Planned |
| NFR-02 | Maintain modular source structure | All Stories | Modular Architecture | `src/`, `include/` | Design review | Planned |
| NFR-03 | Reject malformed commands safely | All Stories | Parser + Error Handler | `src/parser.cpp`, `src/error.cpp` | TC-ERR-01, TC-ERR-02 | Planned |
| NFR-04 | Handle coursework-scale CSV efficiently | PX11402-10, PX11402-15 | Storage + Query Executor | `src/storage.cpp`, `src/query.cpp` | Performance observation | Planned |

## Detailed Task Mapping

### PX11402-10 LOAD Command

| Task ID | Task Summary | Module | Test Coverage |
|---|---|---|---|
| PX11402-11 | Implement file input parser | `src/loader.cpp` | TC-LOAD-01 |
| PX11402-12 | Parse CSV header | `src/loader.cpp` | TC-LOAD-02 |
| PX11402-13 | Parse CSV data rows | `src/loader.cpp` | TC-LOAD-03 |
| PX11402-14 | Display load confirmation | `src/main.cpp` | TC-LOAD-01 |

### PX11402-15 SELECT Command

| Task ID | Task Summary | Module | Test Coverage |
|---|---|---|---|
| PX11402-16 | Implement SELECT parser | `src/parser.cpp` | TC-SELECT-01 |
| PX11402-17 | Validate column names | `src/query.cpp` | TC-SELECT-03 |
| PX11402-18 | Retrieve data from memory | `src/query.cpp` | TC-SELECT-01, TC-SELECT-02 |
| PX11402-19 | Format and print results | `src/output.cpp` | TC-SELECT-01 |

### PX11402-20 INSERT Command

| Task ID | Task Summary | Module | Test Coverage |
|---|---|---|---|
| PX11402-21 | Implement INSERT parser | `src/parser.cpp` | TC-INSERT-01 |
| PX11402-22 | Validate INSERT input | `src/insert.cpp` | TC-INSERT-02, TC-INSERT-03 |
| PX11402-23 | Create new row in memory | `src/insert.cpp` | TC-INSERT-01 |
| PX11402-24 | (Optional) Save to CSV file | `src/storage.cpp` | TC-INSERT-04 |

## Notes

- Jira story IDs should remain consistent with the project backlog.[web:35][web:81]
- Each task should be traceable to specific source files and test cases.[web:78][web:84]
- Update this matrix when implementation or test details change.[web:78]