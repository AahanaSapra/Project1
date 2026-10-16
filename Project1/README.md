# CS 32 — Project 1
Blood Donation and Vacation Credit Management System — Student Starter

This starter intentionally provides only interfaces, completed support code, and minimal stubs so that you implement the core logic.

- Files are in the root (no subfolders). Submit a ZIP with the required files in the root.
- Do not rename the required `.h` and `.cpp` files.
- No STL containers (`vector`, `list`, `map`, etc.). Use raw pointers and manual dynamic arrays.
- No console printing in the final submission (remove all `cout`/`printf`).
- Rule of 3 required for `VacationAccount` (destructor, copy constructor, copy assignment). Rule of 5 is not required.
- C++17 will be used for grading.

## Important Starter Design Notes

- `Date` is a plain struct. Do not add a constructor or member functions to it.
- Required date operations are free functions in the `DateUtil` namespace.
- `parseISO()` and `sameDay()` are already implemented.
- You must implement `DateUtil::isValid()` and `DateUtil::daysBetween()`.
- Helpers for leap years, month lengths, or serial-day conversion are implementation details. If you use them, define them in `Date.cpp`; they do not need to be added to `Date.h`.
- You may assume the ID used to construct a `VacationAccount` is a valid 6-digit employee ID.
- For `TOO_SOON`, donations may be assumed to arrive in chronological order. Compare against the most recently accepted donation. Exactly 180 days is allowed.

## How Grading Works

- The autograder uses 15 grading tests.
- Functional score = `(number of grading tests passed) × (100 / 15)`.
- During grading, the autograder replaces your submitted `main.cpp` with the instructor testing program.
- You must still submit your own `main.cpp` with at least 15 assertions to verify your implementation locally.
- Additional deductions may apply as described in the assignment specification.

## Build

```text
g++ Date.cpp BloodDonation.cpp VacationAccount.cpp main.cpp -o proj1 -std=c++17
```

## Your Tasks

- Implement all TODOs in `Date.cpp`, `BloodDonation.cpp`, and `VacationAccount.cpp`.
- Enforce exact result codes: `OK`, `BAD_ID`, `BAD_AGE`, `BAD_WEIGHT`, `BAD_DATE`, `SAME_DAY`, `TOO_SOON`.
- Add at least 15 assertions in `main.cpp` covering success, rejection, boundary, and copy-semantics cases.
- Write the short report specified in the assignment.
