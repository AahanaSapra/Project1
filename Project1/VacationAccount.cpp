#include "VacationAccount.h"

namespace {
    const int MIN_INTERVAL_DAYS = 180;
    const double HOURS_PER_DONATION = 4.0;
}

VacationAccount::VacationAccount(const std::string& donorId)
    : m_id(donorId), m_items(nullptr), m_size(0), m_capacity(0), m_hours(0.0)
{
    // You may assume donorId is a valid 6-digit employee ID.
    // You do not need to validate it in this constructor.
    // add() will verify that each donation belongs to this account.
}

// Destructor
VacationAccount::~VacationAccount() {
    // TODO: delete owned BloodDonation pointers and array
    clear();
}

// Copy Constructor (new object from old object)
VacationAccount::VacationAccount(const VacationAccount& other)
    : m_id(""), m_items(nullptr), m_size(0), m_capacity(0), m_hours(0.0) { // default values to prevent redundancy
    // TODO: deep copy other's donations and hours
    
    deepCopyFrom(other);
}

// Assignment Operator (existing object from existing object)
VacationAccount& VacationAccount::operator=(const VacationAccount& other) {
    if (this != &other) { // Check for aliasing
        // TODO: release current resources and deep copy from other

        clear();

        deepCopyFrom(other);
    }
    return *this;
}

void VacationAccount::ensureCapacity(int need) {
    // TODO: ensure m_items has room for at least 'need' pointers.
    // m_size is the number of donations stored; m_capacity is the number
    // of pointer slots allocated. Any growth strategy that provides at
    // least 'need' slots is acceptable (simple +1 growth is acceptable).

    if (m_capacity >= need) { // Already have enough space
        return;
    }

    // Exact Need Strategy: grow by exact need
    int newCapacity = need;
    BloodDonation** newItems = new BloodDonation * [newCapacity]; // Allocation arr of ptrs
    // Transfer existing ptr to new arr
    for (int i = 0; i < m_size; i++) {
        newItems[i] = m_items[i];
    }

    // Initialize new ptr slots to nullptr
    for (int i = m_size; i < newCapacity; i++) {
        newItems[i] = nullptr;
    }

    delete[] m_items; // Delete outer arr but NOT individual ptr

    // Update attributes
    m_items = newItems;
    m_capacity = newCapacity;
}

void VacationAccount::clear() {
    // TODO: delete owned donations, delete array, reset fields
    
    // Check that m_items is a valid pointer
    if (m_items != nullptr) {
        // Delete individual BloodDonation ptrs
        for (int i = 0; i < m_size; i++) {
            delete m_items[i];
        }

        delete[] m_items; // Delete arr of ptrs

        m_items = nullptr; // Avoid dangling ptr
    }

    // Reset other attributes
    m_id = "";
    m_size = 0;
    m_capacity = 0;
    m_hours = 0.0;
}

void VacationAccount::deepCopyFrom(const VacationAccount& other) {
    // TODO: give this account its own independently allocated array and
    // independently allocated copies of each BloodDonation. Do not merely
    // copy the BloodDonation* pointer values.

    // Copy over non-ptr attributes
    m_id = other.m_id;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_hours = other.m_hours;

    // Allocate new memory and deep copy from other
    if ((other.m_capacity > 0) && (other.m_items != nullptr)) {
        m_items = new BloodDonation*[m_capacity]; // Allocate new arr of ptr

        // Deep copy existing objects
        for (int i = 0; i < m_size; i++) {
            if (other.m_items[i] != nullptr) {
                m_items[i] = new BloodDonation(*other.m_items[i]); // Call copy constructor to clone object
            }
            else {
                m_items[i] = nullptr;
            }
        }

        // Initialize remaining slots to nullptr
        for (int i = m_size; i < m_capacity; i++) {
            m_items[i] = nullptr;
        }
    }
    else {
        m_items = nullptr;
    }
}

const std::string& VacationAccount::id() const { return m_id; }
double VacationAccount::balanceHours() const { return m_hours; }
int VacationAccount::size() const { return m_size; }

const BloodDonation* VacationAccount::at(int index) const {
    if (index < 0 || index >= m_size) return nullptr;
    return m_items[index];
}

std::string VacationAccount::add(const BloodDonation& donation) {
    // TODO: Implement in this exact order:
    // 1) Independent validation (donation.validate()). If not OK, return that code.
    if (donation.validate() != Result::OK) {
        return donation.validate();
    }
    // 2) Account ID equality: if donation.id() != m_id, return Result::BAD_ID.
    if (donation.id() != m_id) {
        return Result::BAD_ID;
    }
    // 3) SAME_DAY: if any accepted donation has the same calendar date,
    //    return Result::SAME_DAY.
    for (int i = 0; i < m_size; i++) {
        if (DateUtil::sameDay(m_items[i]->date(), donation.date())) {
            return Result::SAME_DAY;
        }
    }
    // 4) TOO_SOON: compare with the most recently accepted donation
    //    (m_items[m_size - 1]). If daysBetween(...) < 180,
    //    return Result::TOO_SOON. Exactly 180 days is allowed.
    //    You may assume donations are submitted in chronological order.
    if (m_size > 0) {
        BloodDonation* lastDonation = m_items[m_size - 1];
        if (DateUtil::daysBetween(lastDonation->date(), donation.date()) < MIN_INTERVAL_DAYS) {
            return Result::TOO_SOON;
        }
    }
    // 5) On success: store an independent copy, append it to the array,
    //    increment hours by +4.0, and return Result::OK.

    // Update arr and state vars
    ensureCapacity(m_size + 1);
    m_items[m_size] = new BloodDonation(donation);
    m_size++;
    m_hours += HOURS_PER_DONATION;

    return Result::OK; 
}
