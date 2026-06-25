# Traffic Management System

## 📌 Overview

Traffic Management System is a console-based **C++** application engineered to streamline vehicle registration and automate traffic violation tracking. The system provides an interactive menu-driven interface allowing operators to manage vehicle ownership records, issue or resolve fines, and perform multi-attribute lookups efficiently.

To bridge the gap between volatile memory and persistent data layers, the system incorporates robust **file handling (I/O)** workflows. This ensures all vehicle assets and penalization history remain intact across application lifecycles.

---

## 🚀 Features

### 🚘 Vehicle Management
* **Secure Registration:** Registers new vehicles while ensuring global uniqueness constraints on license plate formats.
* **Indexed Lookups:** Rapidly searches vehicle records using individual registration numbers.
* **Owner-Centric Aggregation:** Groups and resolves multiple vehicles mapped to a single owner's name using pointer references.

### 🧾 Challan & Fine Management
* **Violation Issuance:** Generates structured traffic tickets (challans) tied directly to a vehicle's unique profile.
* **Ticket Clearance:** Erases existing penalty records upon resolution and deducts the fine from the vehicle's total.
* **Multi-Tier Search Engine:** Queries violation databases filtered by either registration codes or individual owner details.
* **Violation Analytics:** Computes real-time metric counters tracking total active fine amounts per vehicle asset.
* ### 💾 Data Persistence
* **Buffered Bootstrapping:** Reads structural vehicle datasets and offense maps out of persistent text files during initialization.
* **Real-Time Syncing:** Automatically synchronizes and updates underlying flat-file structures immediately upon addition.
* **Dynamic File Rewriting:** Uses a secure temporary-file replacement strategy to safely delete resolved challans from permanent storage.

---

## 🛠️ Technologies Used

* **Language:** C++
* **Paradigm:** Object-Oriented Programming (Abstraction, Data Encapsulation, Relationships)
* **File I/O Engine:** Standard stream controllers (`fstream`, `stringstream`) for file system persistence.
* **Interface Architecture:** Interactive Terminal-Based Menu Matrix.

---

## 📊 Data Structures

The system leverages specialized C++ Standard Template Library (STL) containers to establish optimized search-and-retrieval complexities:

* **`std::map`:** Maps `Registration_No` to the `Vehicle` object. Guarantees efficient unique lookups and prevents duplicate registrations.
* **`std::multimap`:** Maps `Owner_Name` to a `Vehicle` pointer. Accommodates one-to-many relationships allowing an owner to hold multiple titles without duplicating vehicle data in memory.
* **`std::multiset`:** Maintains chronologically/structurally sorted `Challan` records for each vehicle using a custom overloaded `<` operator.
* ---

## 📂 File Structure

The localized database relies on plain text records split into clear schemas:

**`vehicles.txt`**
Maintains structural vehicle definitions mapped line-by-line:
`[Registration_Number] [Owner_Name]`

**`challans.txt`**
Maintains relational traffic violation logs:
`[Registration_Number] [Violation_Reason] [Date_Issued] [Fine_Amount]`

---

## 🎮 System Functionalities

1. **Register New Vehicle:** Appends valid profiles to active memory structures and writes down to storage tracks.
2. **Search Vehicle Profiles:** Scans the relational binary tree map using explicit registration tags or owner names.
3. **Issue Traffic Challans:** Builds violation objects, indexes them against specific vehicles, and immediately appends to storage.
4. **Revoke/Clear Challans:** Removes penalty objects dynamically and rewrites the database to reflect the cleared record.
5. **View Historical Logs:** Loops through stored collections to extract complete structural audit logs.

---

## Author

**RISHI GOUTHAM**
*C++ | Object-Oriented Design | Computer Science Student*
Developed as a C++ Object-Oriented Programming and File Handling project for simulating a real-world traffic record management system.

---

## License

This project is created for educational and academic training purposes under the data structures and software systems curriculum.
