# SmartHire – 10-Phase Development Plan

**Purpose:** Split the whole project into 10 phases so that code is pushed to Git in small, tested, reviewable steps.
**Companion document:** `SmartHire_Documentation.md` (the specification). Every phase below refers to its sections.
**Roles:** **Owner** = decision maker and final reviewer. **Contributor** = your friend. Code may be generated with Antigravity, but the owner approves every merge.

---

## How to Use This Plan

### Rules for every phase

1. One phase = one Git branch = one Pull Request (PR) = one merge into `main`.
2. Start each phase with `git pull origin main`.
3. Build only what the phase lists. Do not start the next phase's work early.
4. Compile with zero warnings before pushing: `g++ -std=c++11 -Wall -Wextra -o smarthire src/main.cpp`.
5. Test the phase with a small throwaway test program that you do **not** commit (the project must stay at exactly 3 source files).
6. The owner reviews the PR using the checklist in Documentation section 17.4, then merges.
7. After merging, tag the milestone (`git tag phase-XX`) and push the tag.

### Standard push routine (same for every phase)

```bash
git checkout main
git pull origin main
git checkout -b phase-XX-short-name
# ... build, compile, test ...
git add <files of this phase>
git commit -m "Phase XX: <message from the phase>"
git push origin phase-XX-short-name
# open a Pull Request on GitHub, owner reviews and merges
git checkout main
git pull origin main
git tag phase-XX
git push origin phase-XX
```

### Overview

| Phase | Name | Assigned to | Main file(s) | Depends on |
|---|---|---|---|---|
| 1 | Project setup and repository | Owner | folders, README, `.gitignore` | – |
| 2 | Candidate record and Dynamic Array | Owner | `data_structures.h` | 1 |
| 3 | Hash Table | Owner | `data_structures.h` | 2 |
| 4 | BST (experience tree) | Contributor | `data_structures.h` | 3 merged |
| 5 | AVL Tree (ranking tree) | Contributor | `data_structures.h` | 4 |
| 6 | Max Heap (Top K) | Contributor | `data_structures.h` | 5 |
| 7 | Engine core: skills, scoring, add candidate, job | Owner | `smarthire_engine.h` | 2 to 6 |
| 8 | Engine advanced: rankings, status, files, report | Contributor (owner reviews) | `smarthire_engine.h` | 7 |
| 9 | Front end: helpers, screens, main menu | Owner (contributor helps with helpers) | `main.cpp` | 7, 8 |
| 10 | Integration, testing, cleanup and release | Both | all | 9 |

**Parallel work tip:** while the contributor does phases 4 to 6, the owner can prepare phase 7 on a separate branch, and the contributor can draft the input and table helpers for phase 9. Merge in numeric order to avoid conflicts, because phases 2 to 6 all edit `data_structures.h`.

---

## Phase 1 – Project Setup and Repository

| Item | Details |
|---|---|
| **Branch** | `phase-01-setup` |
| **Assigned to** | Owner |
| **Goal** | A clean repository with the agreed structure and empty source files |
| **Spec reference** | Documentation sections 7, 8, 14 |

**Tasks**
- [ ] Create the folder structure: `src/`, `data/`, `docs/`.
- [ ] Create empty `src/data_structures.h`, `src/smarthire_engine.h`, `src/main.cpp` (headers only contain include guards and their include lines).
- [ ] Create `data/candidates.txt` containing only `0`.
- [ ] Add `SmartHire_Documentation.md` as `README.md` and this phase plan to `docs/`.
- [ ] Add a `.gitignore` for compiled programs (`smarthire`, `smarthire.exe`, `*.o`) and `data/ranking_report.txt`.
- [ ] Fill in the Decision Log (Documentation section 14). **Owner decides every row.**
- [ ] Create the private GitHub repository and invite the contributor.
- [ ] Both team members install the compiler and confirm `g++ --version` works.

**Definition of done:** the project compiles (an empty `main` is enough), and both people have cloned the repository.
**Commit message:** `Phase 01: project structure, empty source files, documentation`
**Tag:** `phase-01`

---

## Phase 2 – Candidate Record and Dynamic Array

| Item | Details |
|---|---|
| **Branch** | `phase-02-candidate-array` |
| **Assigned to** | Owner |
| **File** | `src/data_structures.h` |
| **Spec reference** | Documentation 12.1 (Constants, `Candidate`, `CandidateArray`) |

**Tasks**
- [ ] Add constants: maximum name length, hash table size, status codes (Pending, Shortlisted, Rejected, Hired).
- [ ] Add the `Candidate` record (ID, name, experience years, skill bitmask, match score, hiring status).
- [ ] Build `CandidateArray`: start capacity 4, `append` doubles capacity when full, `at`, `size`, destructor, copying disabled.

**Test (throwaway program):** append 10 candidates, read them back by position, confirm none are lost when the array grows from 4 to 8 to 16.
**Definition of done:** compiles with no warnings, growth test passes, no memory leak.
**Commit message:** `Phase 02: candidate record and dynamic array`
**Tag:** `phase-02`

---

## Phase 3 – Hash Table

| Item | Details |
|---|---|
| **Branch** | `phase-03-hash-table` |
| **Assigned to** | Owner |
| **File** | `src/data_structures.h` |
| **Spec reference** | Documentation 12.1 (`CandidateHashTable`) |

**Tasks**
- [ ] Build `CandidateHashTable` with 101 buckets and chaining.
- [ ] `insert` places a new node at the front of its chain.
- [ ] `find` returns the array position, or -1 when the ID does not exist.
- [ ] Destructor frees every node of every chain.

**Test:** insert IDs 1 and 102 (same bucket) and confirm both are found; search an ID that was never inserted and confirm -1.
**Definition of done:** collision test passes and no leaks.
**Commit message:** `Phase 03: hash table with chaining`
**Tag:** `phase-03`
**Hand-over:** after this PR is merged the contributor starts phase 4 from the updated `main`.

---

## Phase 4 – BST (Experience Tree)

| Item | Details |
|---|---|
| **Branch** | `phase-04-experience-bst` |
| **Assigned to** | Contributor |
| **File** | `src/data_structures.h` (add a new block below the hash table) |
| **Spec reference** | Documentation 12.1 (`ExperienceTree`) |

**Tasks**
- [ ] Build `ExperienceTree`: smaller years go left, equal or larger go right.
- [ ] `collectAtLeast(minimumYears)` returns array positions, most experienced first, and skips a left subtree once a node is below the minimum.
- [ ] Destructor frees all nodes.

**Test:** insert experiences 3, 5, 1, 5, 8 and ask for at least 5. Expected order is 8, 5, 5. Ask for at least 0 and confirm all 5 come out. Ask for at least 20 and confirm 0 results.
**Definition of done:** tests pass, no warnings, no leaks, owner has explained the pruning rule back to the contributor.
**Commit message:** `Phase 04: BST for experience filtering`
**Tag:** `phase-04`

---

## Phase 5 – AVL Tree (Ranking Tree)

| Item | Details |
|---|---|
| **Branch** | `phase-05-avl-ranking` |
| **Assigned to** | Contributor |
| **File** | `src/data_structures.h` |
| **Spec reference** | Documentation 12.1 (`RankingTree`), section 4 for the key |

**Tasks**
- [ ] Build `RankingTree` with node height, left rotation and right rotation.
- [ ] Insert like a BST, update heights, and rebalance with all four cases: LL, RR, LR, RL.
- [ ] `collectDescending` returns positions from the highest key to the lowest.
- [ ] `treeHeight` for testing.
- [ ] Destructor frees all nodes.

**Test:** insert keys in rising order (10, 20, 30, 40, 50, 60, 70) and confirm the tree height is 3, not 7. Test one insert order for each rotation case and confirm descending output stays correct.
**Definition of done:** all four rotation cases proven by tests, no leaks.
**Commit message:** `Phase 05: AVL tree with four rotation cases`
**Tag:** `phase-05`

---

## Phase 6 – Max Heap (Top K)

| Item | Details |
|---|---|
| **Branch** | `phase-06-max-heap` |
| **Assigned to** | Contributor |
| **File** | `src/data_structures.h` |
| **Spec reference** | Documentation 12.1 (`TopCandidateHeap`) |

**Tasks**
- [ ] Build `TopCandidateHeap` with fixed capacity.
- [ ] `push` adds at the end and moves up.
- [ ] `popBest` returns the highest score, moves the replacement down, and returns false when empty.
- [ ] `isEmpty`, destructor, copying disabled.

**Test:** push scores 40, 90, 10, 70, 55 and pop all. Expected order is 90, 70, 55, 40, 10. Pop from an empty heap and confirm it returns false.
**Definition of done:** order test passes, no leaks. **`data_structures.h` is now complete (File 1 finished).**
**Commit message:** `Phase 06: max heap for top candidates`
**Tag:** `phase-06`

---

## Phase 7 – Engine Core (Skills, Scoring, Add Candidate, Job)

| Item | Details |
|---|---|
| **Branch** | `phase-07-engine-core` |
| **Assigned to** | Owner |
| **File** | `src/smarthire_engine.h` |
| **Spec reference** | Documentation 12.2, section 4 |

**Tasks**
- [ ] Add the 12-skill catalogue, limits, weights and file path constants.
- [ ] Add helper functions: count set bits, safe text copy, status code to text.
- [ ] Create the `SmartHireEngine` class owning the array, hash table, BST, job title, required skill mask, required skill count and "job defined" flag.
- [ ] Add candidate: reject IDs outside 1 to 99999 and duplicates, replace pipe characters in names, register in array, hash table and BST.
- [ ] Define job and recalculate scores using the formula (70 for skills, 3 per year of experience up to 30).
- [ ] Simple getters (candidate count, candidate at position, job title, job defined).

**Test:** a candidate with 2 of 3 required skills and 3 years must score 55 (46 + 9). A candidate with all skills and 10 or more years must score 100. A duplicate ID must be refused.
**Definition of done:** scoring tests pass, duplicates refused, compiles clean.
**Commit message:** `Phase 07: engine core with scoring and candidate registration`
**Tag:** `phase-07`

---

## Phase 8 – Engine Advanced (Rankings, Status, Files, Report)

| Item | Details |
|---|---|
| **Branch** | `phase-08-engine-features` |
| **Assigned to** | Contributor (owner reviews carefully) |
| **File** | `src/smarthire_engine.h` |
| **Spec reference** | Documentation 12.2, sections 9 and 10 |

**Tasks**
- [ ] Full ranking using a fresh AVL tree each time, key = score × 100000 + ID.
- [ ] Top K using a fresh max heap, stopping early when fewer candidates exist.
- [ ] Experience filter through the BST.
- [ ] `updateStatus`: the only function that stores a hiring decision.
- [ ] Save to `data/candidates.txt` (count on line 1, then `ID|name|years|mask|status` per line).
- [ ] Load from the same file and rebuild all structures.
- [ ] Export the ranking report with the advisory note.

**Test:** add 3 candidates, save, restart the test program, load, and confirm the same data. Check ranking order against hand-calculated scores. Check that Top K with K larger than the count returns everyone. Open the report file and read it.
**Definition of done:** all engine operations work without any screen code, no leaks, owner has explained save and load back to the contributor.
**Commit message:** `Phase 08: ranking, top K, filter, status update, file save/load, report`
**Tag:** `phase-08`

---

## Phase 9 – Front End (Helpers, Screens, Main Menu)

| Item | Details |
|---|---|
| **Branch** | `phase-09-front-end` |
| **Assigned to** | Owner (contributor may write the layout and input helpers on a sub-branch) |
| **File** | `src/main.cpp` |
| **Spec reference** | Documentation 11, 12.3, 12.4, 12.5 |

**Tasks**
- [ ] Layout helpers: divider line, padded text, padded number, banner.
- [ ] Input helpers: `readInteger` with range checking and recovery from wrong input, `readText` that refuses empty text.
- [ ] Skill catalogue display, skill name display, skill selection by number.
- [ ] Candidate table header and rows.
- [ ] Screens for options 1 to 9 with the exact messages from section 12.4.
- [ ] Confirmation step before any status change.
- [ ] Main loop with the status line, menu, and save on exit; load data at start-up.

**Test:** run every menu option once. Type letters where numbers are expected. Press Enter on an empty name. Restart the program and confirm data is loaded.
**Definition of done:** every menu option works, bad input never crashes the program, messages match the specification.
**Commit message:** `Phase 09: console front end and main menu`
**Tag:** `phase-09`

---

## Phase 10 – Integration, Testing, Cleanup and Release

| Item | Details |
|---|---|
| **Branch** | `phase-10-final` |
| **Assigned to** | Both |
| **Files** | all, plus `docs/` |
| **Spec reference** | Documentation 15, 16, 17.4, 18 |

**Tasks**
- [ ] Run the full test checklist (Documentation section 15) and record the result of every row.
- [ ] Test with more than 10 candidates, duplicate hash buckets, and a job with only one required skill.
- [ ] Memory check: every `new` has a `delete` (use a leak checker such as Valgrind on Linux if available).
- [ ] Style check against Documentation section 16: humanized names, a comment above every function, no blank lines, only the two allowed headers.
- [ ] Remove any feature not listed in the Sandbox rules (section 6).
- [ ] Take screenshots of every menu option and save them in `docs/`.
- [ ] Update `README.md` with the final compile and run instructions.
- [ ] Practice the viva questions in section 18. Each person explains the other's parts out loud.
- [ ] If your course requires it, add the AI-assistance declaration to the report.

**Definition of done:** all tests pass, zero warnings, both team members can explain the entire program.
**Commit message:** `Phase 10: integration testing, cleanup, final documentation`
**Tag:** `v1.0` (and `phase-10`)

---

## Progress Tracker

| Phase | Owner of the phase | Branch pushed | PR merged | Tag pushed | Reviewed by owner |
|---|---|---|---|---|---|
| 1 | Owner | ☐ | ☐ | ☐ | ☐ |
| 2 | Owner | ☐ | ☐ | ☐ | ☐ |
| 3 | Owner | ☐ | ☐ | ☐ | ☐ |
| 4 | Contributor | ☐ | ☐ | ☐ | ☐ |
| 5 | Contributor | ☐ | ☐ | ☐ | ☐ |
| 6 | Contributor | ☐ | ☐ | ☐ | ☐ |
| 7 | Owner | ☐ | ☐ | ☐ | ☐ |
| 8 | Contributor | ☐ | ☐ | ☐ | ☐ |
| 9 | Owner | ☐ | ☐ | ☐ | ☐ |
| 10 | Both | ☐ | ☐ | ☐ | ☐ |

## If Something Goes Wrong

- **Merge conflict in `data_structures.h`:** it happens when two phases edit the same file. Pull `main`, keep both blocks, make sure each class stays in its own block, compile again, then push.
- **A phase fails its test:** do not merge. Fix it on the same branch and push again; the PR updates automatically.
- **The agent added something extra:** reject that part, tell the agent to remove it, and re-check against the specification before committing.
- **A phase needs a design change:** stop, update `SmartHire_Documentation.md` first, get the owner's approval, then change the code.