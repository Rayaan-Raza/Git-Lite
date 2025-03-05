# Git-Lite: Repository System with Tree Structures

##  Overview
This project is a **version control system** designed for handling structured data efficiently using **AVL Trees, B-Trees, or Red-Black Trees**. Instead of relying on RAM-heavy storage, it **stores nodes as text files**, optimizing performance for large datasets. 

The system supports:
- **Version tracking** for structured data (CSV format)
- **Efficient branching and merging** using tree structures
- **SQL-like queries** for searching and deleting records
- **Disk-based storage**, reducing memory consumption

---

##  Key Features
**Optimized Search**: Tree-based indexing allows **O(log N) lookups** instead of full-file scans.  
**Disk-Based Storage**: Nodes are stored as text files, preventing high memory usage.  
**Incremental Updates**: Only modified paths are updated during balancing.  
**Query Support**: Search and delete records with SQL-like commands.  

---

## How It Works

### Repository Initialization
- The system reads a **CSV file** and selects a **key column** for indexing.  
- Each row is stored as a **separate text file**, containing:  
  - **Key value** (for ordering)  
  - **Row data**  
  - **Parent path & child paths**  

### Tree-Based Versioning
- **AVL, B-Trees, or Red-Black Trees** maintain sorted structure.  
- Trees are stored **partially in memory** but primarily on disk.  
- Balancing updates **only file paths**, not entire trees.  

### Querying Data
- **Search Example**:  
  SELECT * FROM R WHERE R.k BETWEEN 10 AND 25;
  
- **Delete Example**
DELETE FROM Students WHERE RollNumber BETWEEN '21i-0066' AND '21i-0226';

### Branching & Merging
- Supports **multiple versions of data** using tree snapshots.  
- Merging is **automated with tree traversal**, reducing conflicts.  

---

## Performance Considerations

| Feature               | Traditional Storage | Git-Lite             |
|-----------------------|--------------------|-----------------------|
| **Data Retrieval**    | O(N) (Full Scan)   | O(log N) (Tree Lookup)|
| **Commit Performance**| Full File Rewrite  | Incremental Updates   |
| **Memory Usage**      | High (In-Memory)   | Lower (File-Based)    |


## Contributions
Contributions are welcome! Feel free to submit pull requests or report issues.



