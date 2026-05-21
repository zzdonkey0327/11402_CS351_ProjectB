# Project Plan

## Project Goal

The goal of this project is to build a mini database engine for CSV files that supports basic SQL-like interaction in a command-line interface. The first version will implement `LOAD`, `SELECT`, and `INSERT` as the core features.[web:79][web:82]

## Development Approach

The project will be implemented incrementally. Each core feature will be developed as a separate Jira story and verified with defined test cases. Requirements should remain traceable to design, implementation, and testing artifacts.[web:62][web:78]

## Milestones

### Milestone 1: Project Setup
- Create repository structure
- Prepare documentation files
- Set up source, header, and test folders

### Milestone 2: Startup Interface
- Print welcome message
- Print supported commands
- Enter command loop

### Milestone 3: LOAD Feature (PX11402-10)
- PX11402-11: Implement file input parser
- PX11402-12: Parse CSV header
- PX11402-13: Parse CSV data rows
- PX11402-14: Display load confirmation

### Milestone 4: SELECT Feature (PX11402-15)
- PX11402-16: Implement SELECT parser
- PX11402-17: Validate column names
- PX11402-18: Retrieve data from memory
- PX11402-19: Format and print results

### Milestone 5: INSERT Feature (PX11402-20)
- PX11402-21: Implement INSERT parser
- PX11402-22: Validate INSERT input
- PX11402-23: Create new row in memory
- PX11402-24: (Optional) Save to CSV file

### Milestone 6: Testing and Refinement
- Execute unit and functional tests
- Verify acceptance tests
- Fix defects and document known issues

## Stories

### PX11402-10: LOAD Command
As a user, I want to load a CSV file so that I can query its data.

**Acceptance Criteria:**
- User inputs `LOAD students.csv`
- System parses CSV and stores data in memory
- System displays "Load successful" message
- Error shown if file not found

### PX11402-15: SELECT Command
As a user, I want to retrieve data from the loaded table so that I can inspect the contents.

**Acceptance Criteria:**
- User can run `SELECT * FROM students`
- User can run `SELECT name, score FROM students`
- System prints results in table format
- Error shown if column does not exist

### PX11402-20: INSERT Command
As a user, I want to add a new row to the loaded table so that I can update the database.

**Acceptance Criteria:**
- User inputs `INSERT INTO students (id, name, score) VALUES (5, Amy, 90)`
- System validates column names and value count
- System adds new row to memory
- System reports success

## Risks

- Invalid or malformed CSV input
- Incorrect query parsing
- Inconsistent handling of column names and values
- Data loss if CSV writing is not implemented carefully

## Deliverables

- Source code for the mini database engine
- Header files and modular implementation
- Test files
- Project documentation
- Traceability matrix