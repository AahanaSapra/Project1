#include "VacationAccount.h"
#include <iostream>
#include <cassert>

int main() {
    // Minimal starter; you must add >= 15 assertions to cover all rules.
    // Suggested coverage: calendar/leap-year cases; validation boundaries;
    // successful donation; ID mismatch; SAME_DAY; TOO_SOON; exactly 180 days;
    // copy construction; copy assignment; and independent copies.

    // --- Example tests (uncomment after you implement the corresponding functions) ---
    
    /*
    VacationAccount acc("123456");
    BloodDonation good("123456", 30, 150.0, "2025-01-01");
    assert(good.validate() == Result::OK);               // field validation
    assert(acc.add(good) == Result::OK);                 // account-level acceptance
    assert(acc.size() == 1);                       // size increments
    assert(acc.balanceHours() == 4.0);             // +4 hours credit

    BloodDonation badIdFmt("12A456", 30, 150.0, "2025-01-02");
    assert(badIdFmt.validate() == Result::BAD_ID);       // invalid ID format

    BloodDonation mismatch("654321", 30, 150.0, "2025-07-01");
    assert(mismatch.validate() == Result::OK);
    assert(acc.add(mismatch) == Result::BAD_ID);         // account-level id mismatch

    BloodDonation sameDay("123456", 30, 150.0, "2025-01-01");
    assert(acc.add(sameDay) == Result::SAME_DAY);        // duplicate calendar date

    BloodDonation tooSoon("123456", 30, 150.0, "2025-06-29");
    assert(tooSoon.validate() == Result::OK);
    assert(acc.add(tooSoon) == Result::TOO_SOON);        // < 180 days since last accepted
    */

    std::cout << "Start Assertions" << std::endl;

    VacationAccount acc1("123456"); // Test account

    // --- Blood Donation Field Validations ---
    // Test 1: BAD_ID (< 6 Digits)
    BloodDonation shortId("12345", 30, 150.0, "2025-01-01");
    assert(shortId.validate() == Result::BAD_ID);

    // Test 2: BAD_ID (Contains Letter)
    BloodDonation letterId("12345A", 30, 150.0, "2025-01-01");
    assert(letterId.validate() == Result::BAD_ID);

    // Test 3: BAD_AGE (> 65)
    BloodDonation oldAge("123456", 66, 150.0, "2025-01-01");
    assert(oldAge.validate() == Result::BAD_AGE);

    // Test 4: BAD_WEIGHT (< 101.0)
    BloodDonation thinWeight("123456", 30, 100.9, "2025-01-01");
    assert(thinWeight.validate() == Result::BAD_WEIGHT);

    // Test 5: BAD_DATE (Leap Year Violation)
    BloodDonation badLeapDay("123456", 30, 150.0, "2025-02-29");
    assert(badLeapDay.validate() == Result::BAD_DATE);

    // Test 6: BAD_DATE (Century Rule)
    BloodDonation centuryDay("123456", 30, 150.0, "1900-02-29");
    assert(centuryDay.validate() == Result::BAD_DATE);


    // --- Vacation Acccount Validations --- 
    // Test 7: BAD_ID (Mismatch)
    BloodDonation mismatchId("654321", 30, 150.0, "2025-01-01");
    assert(acc1.add(mismatchId) == Result::BAD_ID);

    // VALID base donation
    BloodDonation baseDonation("123456", 30, 150.0, "2025-01-01");
    assert(acc1.add(baseDonation) == Result::OK);

    // Test 8: SAME_DAY
    BloodDonation sameDayDonation("123456", 30, 150.0, "2025-01-01");
    assert(acc1.add(sameDayDonation) == Result::SAME_DAY);

    // Test 9: TOO_SOON (179 Days)
    BloodDonation earlyDonation("123456", 30, 150.0, "2025-06-29");
    assert(acc1.add(earlyDonation) == Result::TOO_SOON);

    // Test 10: Valid Interval Boundary (180 Days)
    BloodDonation validIntervalDonation("123456", 30, 150.0, "2025-06-30");
    assert(acc1.add(validIntervalDonation) == Result::OK);

    // Test 11: State Accumulation Verification (Correct Size & Hours)
    assert(acc1.size() == 2);
    assert(acc1.balanceHours() == 8.0);


    // --- Memory Management & Rule of Three --- 
    // Test 12: Copy Constructor Verification
    VacationAccount acc2(acc1);
    assert(acc2.size() == 2);
    assert(acc2.balanceHours() == 8.0);

    // Test 13: Copy Assignment Operator Verification
    VacationAccount acc3("454545"); // Starts with different ID
    acc3 = acc1;
    assert(acc3.id() == "123456");
    assert(acc3.size() == 2);

    // Add 3rd item to acc1
    BloodDonation thirdDonation("123456", 30, 150.0, "2025-12-30");
    assert(acc1.add(thirdDonation) == Result::OK);

    // Test 14: Deep Copy Isolation (No Shallow Copy)
    assert(acc1.size() == 3);
    assert(acc2.size() == 2); // size should be unchanged

    // Test 15: Deep Copy Isolation (Different Memory Address)
    assert(acc1.at(0) != acc2.at(0));


    std::cout << "Assertions Passed!" << std::endl;

    return 0;
}
