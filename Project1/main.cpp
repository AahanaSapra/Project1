#include "VacationAccount.h"
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

    return 0;
}
