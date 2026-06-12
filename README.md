# Traffic Management System

## 📌 Overview

Traffic Management System is a console-based **C++** application engineered to streamline vehicle registration and automate traffic violation tracking. The system provides an interactive menu-driven interface allowing operators to manage vehicle ownership records, issue or resolve fines, and perform multi-attribute lookups efficiently.

To bridge the gap between volatile memory and persistent data layers, the system incorporates robust **file handling (I/O)** workflows. This ensures all vehicle assets and penalization history remain intact across application lifecycles.

---

## 🚀 Features

### 🚘 Vehicle Management
* **Secure Registration:** Registers new vehicles while ensuring global uniqueness constraints on license plate formats.
* **Indexed Lookups:** Rapidly searches vehicle records using individual registration numbers.
* **Owner-Centric Aggregation:** Groups and resolves multiple vehicles mapped to a single owner's name.

### 🧾 Challan & Fine Management
* **Violation Issuance:** Generates structured traffic tickets (challans) tied directly to a vehicle's unique profile.
* **Ticket Clearance:** Erases or clears existing penalty points/fines upon resolution.
* **Multi-Tier Search Engine:** Queries violation databases filtered by either registration codes or individual owner details.
* **Violation Analytics:** Computes real-time metric counters tracking active offenses per vehicle asset.

### 💾 Data Persistence
* **Buffered Bootstrapping:** Reads structural vehicle datasets and offense maps out of persistent stores during initialization.
* **Transactional Syncing:** Automatically synchronizes and updates underlying flat-file structures upon addition or removal sequences.

---

## 🛠️ Technologies Used

* **Language:** C++
* **Paradigm:** Object-Oriented Programming (Abstraction, Data Encapsulation, Relationships)
* **File I/O Engine:** Standard stream controllers (`fstream`) for file system persistence
* **Interface Architecture:** Interactive Terminal-Based Menu Matrix

---

## 📊 Data Structures

The system leverages specialized **C++ Standard Template Library (STL)** containers to establish optimized search-and-retrieval complexities:

| Structure | Data Model Mapping | Technical Purpose |
| :--- | :--- | :--- |
| `std::map` | `Registration_No ➔ Vehicle_Obj` | Guarantees efficient unique lookups and prevents duplicate registrations. |
| `std::multimap` | `Owner_Name ➔ Vehicle_Obj` | Accommodates one-to-many relationships allowing an owner to hold multiple titles. |
| `std::multiset` | `Challan_Records` | Maintains chronologically ordered or structural sorting constraints for ticket lists. |
| `std::fstream` | `Disk 📁 Memory` | Serializes data representations into physical disk storage tracks. |

---

## 📂 File Structure

The localized database relies on plain text records split into clear schemas:

### 📄 `vehicles.txt`
Maintains structural vehicle definitions mapped line-by-line:
```text
[Registration_Number] [Owner_Name]
```

### 📄 `challans.txt`
Maintains relational traffic violation logs:
```text
[Registration_Number] [Violation_Reason] [Date_Issued] [Fine_Amount]
```

---

## 🎮 System Functionalities

1. **Register New Vehicle:** Appends valid profiles to active memory structures and writes down to storage tracks.
2. **Search Vehicle Profiles:** Scans the relational binary tree map using explicit registration tags.
3. **Issue Traffic Challans:** Builds violation objects, indexes them against specific vehicles, and increments structural fine counters.
4. **Revoke/Clear Challans:** Removes penalty objects dynamically, reorganizing target multisets.
5. **View Historical Logs:** Loops through stored collections to extract complete structural audit logs.
6. **Query Owner Portfolios:** Performs lookups over ownership mappings.
7. **Maintain Structural Persistence:** Updates transactional files safely upon exiting state operations.

---

## 📘 Learning Outcomes

This project demonstrates and reinforces key software engineering foundations:
* **Object-Oriented Design:** Translating real-world relational infrastructure into safe class definitions.
* **STL Architecture Mastery:** Aligning memory requirements with target algorithmic efficiencies (`map` vs `multiset`).
* **Persistent File Serialization:** Parsing strings, flattening runtime objects, and handling I/O streams safely.
* **Record Relational Frameworks:** Mimicking database primary/foreign keys using relational index mappings.

---

## 🧑‍💻 Author

**RISHI GOUTHAM** C++ | Object-Oriented Design | Computer Science Student  

*Developed as a C++ Object-Oriented Programming and File Handling project for simulating a real-world traffic record management system.*

---

## 📄 License

This project is created for educational and academic training purposes under the data structures and software systems curriculum.
```
