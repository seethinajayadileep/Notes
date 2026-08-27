# Git and GitHub Notes for CCT

---

## Table of Contents

1. [Git Cherry Pick](#git-cherry-pick)
2. [Git Stash](#git-stash)
3. [Linear and Non-Linear Git History](#linear-and-non-linear-git-history)
4. [Merge Strategies](#merge-strategies)
   - [Fast-Forward Merge](#fast-forward-merge)
   - [No Fast-Forward Merge](#no-fast-forward-merge)
   - [Squash Merge](#squash-merge)
   - [Merge Commit](#merge-commit)
5. [Rebase Strategies](#rebase-strategies)
   - [Rebase + Fast-Forward](#rebase--fast-forward)
   - [Rebase + No Fast-Forward](#rebase--no-fast-forward)
6. [GitHub Pull Request Merge Options](#github-pull-request-merge-options)
   - [Create a Merge Commit](#create-a-merge-commit)
   - [Squash and Merge](#squash-and-merge)
   - [Rebase and Merge](#rebase-and-merge)
7. [Other Important Git/GitHub Commands](#other-important-gitgithub-commands)
8. [Common Git Problems and Fixes](#common-git-problems-and-fixes)
9. [Best Practices from Senior Engineers](#best-practices-from-senior-engineers)
10. [Recommended Git Workflow for Students](#recommended-git-workflow-for-students)
11. [Quick Revision Cheat Sheet](#quick-revision-cheat-sheet)

---

## Git Cherry Pick

### Simple Meaning
`git cherry-pick` copies **one specific commit** from another branch onto your current branch.
You don't merge the whole branch — you just pick the single commit you need.

### Why We Use It
Suppose a teammate fixed a critical bug on the `develop` branch, but the same fix is urgently needed on the `release` branch right now.
You cannot wait for the full `develop` branch to be merged, so you cherry-pick just that one fix commit.

### Command
```bash
git switch release
git cherry-pick a1b2c3d
```

### Example Scenario
Your production app has a login bug. The fix already exists on `develop` as commit `a1b2c3d`. Production runs from `release`. You hop onto `release` and cherry-pick that one commit so users get the fix immediately, without dragging in unfinished `develop` work.

### Output / History Example
```text
develop:   A --- B --- C(a1b2c3d) --- D
                        |
                        | cherry-pick C
                        v
release:   X --- Y --- C'      <- copy of C with a new hash
```

### Senior Engineer Tip
Use `git cherry-pick -x a1b2c3d` — the `-x` flag automatically records which original commit it came from, so future-you knows where it originated.

### Common Mistake
Students cherry-pick a commit that secretly depends on earlier commits, then get confused when the code breaks. Pick **small, self-contained** commits only.

---

## Git Stash

### Simple Meaning
`git stash` temporarily saves your uncommitted changes and gives you a clean working directory.
It's perfect when your work isn't ready to commit but you need to switch branches quickly.

### Why We Use It
Suppose you are working on the `payment-feature` branch and suddenly your senior asks you to fix a bug on `main`.
Your current changes aren't committed, so Git won't let you switch safely. You stash your changes, fix the bug, then bring your work back.

### Command
```bash
# Save current changes
git stash

# Save with a message (older syntax)
git stash save "WIP payment form"

# Save with a message (modern preferred syntax)
git stash push -m "WIP payment form"

# See all stashes
git stash list

# Bring back the latest stash AND remove it from the list
git stash pop

# Delete a stash without applying it
git stash drop stash@{0}
```

### Example Scenario
You're half-done building a checkout form. A production bug appears. You run `git stash push -m "WIP checkout"`, switch to `main`, fix the bug, switch back, and run `git stash pop` to continue exactly where you left off — no commit needed, no lost work.

### Output / History Example
```text
Working directory (messy)  --->  git stash  --->  Working directory (clean)
        |                                                   |
        | changes saved into stash@{0}                      |
        |                                                   |
        +-------------------- git stash pop ----------------+
                     (changes return, stash removed)
```

### Stash Pop vs Stash Apply

| Command | Brings changes back? | Keeps the stash in the list? |
|---|---|---|
| `git stash apply` | ✅ Yes | ✅ Yes (stash stays) |
| `git stash pop` | ✅ Yes | ❌ No (stash is deleted) |

**Simple rule:** use `apply` if you might want the same stash again on another branch; use `pop` when you're done with it.

### Senior Engineer Tip
Always stash **with a message** (`git stash push -m "..."`). A stash list full of unnamed `WIP on main` entries is useless when you have five of them.

### Common Mistake
Students forget that `pop` deletes the stash. If a conflict happens during `pop`, they panic thinking the stash is lost — it isn't, but get into the habit of checking `git stash list`.

---

## Linear and Non-Linear Git History

### Simple Meaning
**Linear history** is one straight line of commits with no merge commits.
**Non-linear history** shows the real branching and merging, including merge commits.

### Why We Use It
Teams care about history shape because it affects readability. Linear history is easy to read and debug months later; non-linear history is an honest record of how work actually split and rejoined.

### Command
```bash
# See a linear, compact history
git log --oneline

# See the true branch shape (non-linear)
git log --oneline --graph --all
```

### Example Scenario
Your team keeps `main` **linear** by rebasing feature branches before merging, so the commit log reads like a clean changelog. Another team prefers **non-linear** history so auditors can see exactly when each feature branch was integrated.

### Output / History Example
```text
LINEAR HISTORY (clean, straight line):
A --- B --- C --- D --- E   (main)

NON-LINEAR HISTORY (shows branching + merge):
A --- B --------- M --- F   (main)
       \         /
        C --- D            (feature)
```

| | Linear | Non-Linear |
|---|---|---|
| Looks like | Straight line | Branches with merge points |
| Made by | Rebase / fast-forward | Merge commits |
| Advantage | Easy to read and debug | Honest, full traceability |
| Disadvantage | Rewrites history (risky if shared) | Log can get messy |

### Senior Engineer Tip
Aim for a clean `main` history, but get there safely — never rewrite a branch other people are already using just to make the log prettier.

### Common Mistake
Students rebase a shared branch trying to "clean up" history and end up breaking everyone else's copy. Clean history is good; achieving it recklessly is not.

---

## Merge Strategies

Merging brings changes from one branch into another. The result can take different "shapes" depending on the strategy.

---

### Fast-Forward Merge

#### Simple Meaning
When the target branch hasn't moved since you branched off, Git simply slides its pointer forward.
No new merge commit is created — the history stays a straight line.

#### Why We Use It
It's the cleanest possible merge for simple cases like a small fix on a solo project, where you don't need a record that a separate branch ever existed.

#### Command
```bash
git switch main
git merge feature        # fast-forwards when possible
```

#### Example Scenario
You created `hotfix` from `main`, made one commit, and `main` hasn't changed since. Merging just moves `main` forward to your commit — clean and simple.

#### Output / History Example
```text
Before:                  After fast-forward:
main:    A --- B         main:    A --- B --- C --- D
                \
feature:         C --- D
```

#### Senior Engineer Tip
Fast-forward is great for tiny changes, but for real features prefer a merge commit so history shows the feature existed.

#### Common Mistake
Students assume every merge fast-forwards. The moment `main` has new commits, a fast-forward becomes impossible and Git creates a merge commit instead.

---

### No Fast-Forward Merge

#### Simple Meaning
`--no-ff` forces Git to create a merge commit **even when** a fast-forward was possible.
This leaves a permanent marker in history showing that a feature branch existed.

#### Why We Use It
Teams use it so every feature has a clear integration point in the history — useful for tracing "when exactly did this feature land?"

#### Command
```bash
git switch main
git merge --no-ff feature
```

#### Example Scenario
Your company requires a traceable record of every merged feature for audits. You always merge with `--no-ff` so each feature branch leaves a visible merge commit on `main`.

#### Output / History Example
```text
main:    A --- B --------- M   <- merge commit M (kept on purpose)
                \         /
feature:         C --- D
```

#### Senior Engineer Tip
`--no-ff` is a common team default because it keeps feature boundaries visible without forcing everyone to rebase.

#### Common Mistake
Students think `--no-ff` changes the code somehow. It doesn't — it only changes the **history shape** by adding a merge commit.

---

### Squash Merge

#### Simple Meaning
A squash merge combines **all the commits** from a feature branch into **one single commit** on the target branch.
The messy individual commits don't appear on `main`.

#### Why We Use It
Feature branches often have ugly WIP commits like "fix typo," "oops," "try again." Squashing turns them into one clean, meaningful commit.

#### Command
```bash
git switch main
git merge --squash feature
git commit -m "Add shopping cart feature"
```

#### Example Scenario
Your `feature-cart` branch has 12 messy commits. Before merging into `main`, you squash them into a single commit titled "Add shopping cart feature" so the `main` log stays readable.

#### Output / History Example
```text
feature:  C --- D --- E   (3 messy commits)

After squash into main:
main:     A --- B --- S    <- S = one clean commit (C+D+E combined)
```

#### Senior Engineer Tip
Squash is the favorite of small teams and open-source projects because each feature becomes exactly one tidy commit — the log reads like release notes.

#### Common Mistake
Students expect to still see their individual feature commits on `main` after squashing. They're gone — only the combined commit remains.

---

### Merge Commit

#### Simple Meaning
A merge commit is a special commit with **two parents** that ties two branches together.
It's what you get with `--no-ff` or when branches have genuinely diverged.

#### Why We Use It
It preserves the full, honest history of how two lines of work came together — nothing is rewritten or hidden.

#### Command
```bash
git switch main
git merge feature        # creates a merge commit if branches diverged
```

#### Example Scenario
Two developers worked on `main` and `feature` at the same time, so both branches have new commits. Merging creates a merge commit that joins both histories.

#### Output / History Example
```text
main:    A --- B --------- M   <- M has TWO parents (B and D)
                \         /
feature:         C --- D
```

#### Senior Engineer Tip
Merge commits are best for long-lived branches that genuinely diverged and where full history matters more than a clean straight line.

#### Common Mistake
Students delete merge commits with `reset` to "tidy up," accidentally losing the record of integrated work. Use `revert` instead if you need to undo a merge safely.

---

## Rebase Strategies

### Simple Meaning
`git rebase` moves your commits so they sit **on top of** the latest version of another branch.
Instead of merging, you replay your commits onto a new base — giving a clean, linear history.

### Why We Use It
Rebase keeps history neat and easy to follow. It's the best way to update your feature branch with the latest `main` without creating an ugly merge commit.

### Command
```bash
git switch feature
git rebase main
```

### Example Scenario
Your `feature` branch is three days old and `main` has moved ahead. Before opening a pull request, you rebase onto `main` so your commits replay on top of the newest code — making the eventual merge clean and conflict-free.

### Output / History Example
```text
Before rebase:                After  git rebase main:
main:    A --- B --- C        main:    A --- B --- C
               \                                     \
feature:        D --- E       feature:                D' --- E'
                                       (D & E replayed as new commits)
```

### Merge vs Rebase

| | Merge | Rebase |
|---|---|---|
| What it does | Joins branches with a merge commit | Replays commits onto a new base |
| History shape | Non-linear (shows branching) | Linear (straight line) |
| Changes commit hashes? | No | Yes (creates new commits) |
| Safe on shared branches? | ✅ Yes | ⚠️ Dangerous |
| Best for | Integrating shared work | Cleaning up your own local branch |

### Senior Engineer Tip
🏆 **Golden rule:** rebase your *own local* commits freely, but **never rebase a shared/public branch** unless the whole team agrees. Rebasing rewrites history and forces everyone else to clean up the mess.

### Common Mistake
Students rebase a branch that's already pushed and shared, then force-push it — instantly breaking their teammates' copies. Rebase before sharing, not after.

---

### Rebase + Fast-Forward

#### Simple Meaning
After rebasing your feature onto `main`, your branch sits directly on top of `main`.
Now merging becomes a clean fast-forward, giving a perfectly linear history.

#### Why We Use It
This combo produces the cleanest possible result: one straight line with no merge commits at all.

#### Command
```bash
git switch feature
git rebase main          # replay feature on top of main
git switch main
git merge feature        # fast-forward, no merge commit
```

#### Example Scenario
You want `main` to stay a perfectly straight line. You rebase `feature` onto `main`, then fast-forward merge — the result looks like all the work happened in sequence.

#### Output / History Example
```text
After rebase + fast-forward:
main:    A --- B --- C --- D' --- E'   (one clean line)
```

#### Senior Engineer Tip
This is the go-to pattern for teams that insist on a strictly linear `main` history.

#### Common Mistake
Students forget the rebase step and wonder why a merge commit appeared. Fast-forward only works when the branch is directly ahead of `main`.

---

### Rebase + No Fast-Forward

#### Simple Meaning
You rebase first for a clean base, then merge with `--no-ff` so a merge commit still marks where the feature was integrated.
You get mostly-linear history **plus** a clear integration point.

#### Why We Use It
It balances readability with traceability: your commits are clean and on top of `main`, but the merge commit still shows where the feature landed.

#### Command
```bash
git switch feature
git rebase main
git switch main
git merge --no-ff feature   # keep a merge commit as a marker
```

#### Example Scenario
Your team wants clean commits but also wants to see feature boundaries for code reviews and audits. You rebase, then merge with `--no-ff` to get both.

#### Output / History Example
```text
After rebase + no fast-forward:
main:    A --- B --- C ------------ M
                       \           /
feature(rebased):       D' --- E'
```

#### Senior Engineer Tip
This hybrid is popular in mid-to-large teams: clean linear commits, but you never lose the "this was a feature" marker.

#### Common Mistake
Students mix up the order. Always rebase **first**, then merge — rebasing after merging defeats the purpose.

---

## GitHub Pull Request Merge Options

When you click the merge button on a GitHub pull request, you get three choices. Here's what each one does.

---

### Create a Merge Commit

#### Simple Meaning
GitHub keeps **all your individual commits** and adds one merge commit on top.
The result is a non-linear history that shows the full story.

#### Why We Use It
Large teams use it for complete traceability — every commit and the exact merge point is preserved.

#### Command
```text
On GitHub PR page → click the dropdown → "Create a merge commit"
```

#### Example Scenario
An enterprise team needs an audit trail. They choose "Create a merge commit" so every PR leaves a permanent record of when and how it was merged.

#### Output / History Example
```text
main:    A --- B --------- M
                \         /
PR commits:      C --- D --- E
```

#### Senior Engineer Tip
Best when history accuracy and traceability matter more than a clean log.

#### Common Mistake
Students use this for tiny PRs and end up flooding `main` with dozens of trivial "fix typo" commits.

---

### Squash and Merge

#### Simple Meaning
GitHub combines **all PR commits into one** and adds that single commit to `main`.
Your messy commits disappear into one clean commit.

#### Why We Use It
It keeps `main` tidy. Each PR becomes exactly one commit, so the history reads like a changelog.

#### Command
```text
On GitHub PR page → click the dropdown → "Squash and merge"
```

#### Example Scenario
A small startup uses "Squash and merge" on every PR. Their `main` log shows clean entries like "Add login," "Fix cart bug," "Update pricing page."

#### Output / History Example
```text
PR commits:   C --- D --- E   (messy)

After squash and merge:
main:    A --- B --- S         <- one clean commit
```

#### Senior Engineer Tip
This is the most popular choice for small teams and open-source projects — it keeps the public history professional.

#### Common Mistake
Students expect their detailed commit history to survive. After squashing, only the single combined commit remains on `main`.

---

### Rebase and Merge

#### Simple Meaning
GitHub replays each of your commits individually on top of `main`, with no merge commit.
You get a linear history that still keeps every commit.

#### Why We Use It
It's for teams that want a straight-line history **and** want to preserve individual commits instead of squashing them.

#### Command
```text
On GitHub PR page → click the dropdown → "Rebase and merge"
```

#### Example Scenario
A team values both clean linear history and the ability to see each logical step. They choose "Rebase and merge" so commits stay separate but the line stays straight.

#### Output / History Example
```text
After rebase and merge:
main:    A --- B --- C' --- D' --- E'   (linear, commits kept)
```

#### Senior Engineer Tip
Only use this when your individual commits are meaningful. If they're messy WIP commits, squash instead.

#### Common Mistake
Students pick "Rebase and merge" for a branch full of "oops" commits, leaving `main` cluttered with useless individual commits.

---

### Which Option Is Best?

| Project Type | Recommended Option | Why |
|---|---|---|
| **Small team** | Squash and merge | Clean `main`, one commit per feature |
| **Large team** | Create a merge commit | Full traceability and audit trail |
| **Open-source** | Squash and merge | Keeps public history tidy and professional |

---

## Other Important Git/GitHub Commands

### Simple Meaning
These are the everyday commands you'll use constantly — setting up repos, saving work, syncing, and inspecting history.

### Why We Use It
You can't get through a single workday without most of these. They are the foundation everything else builds on.

### Command
```bash
git init                      # start a new repository
git clone <url>               # copy a remote repository
git status                    # see what changed (your dashboard)
git add .                     # stage changes for commit
git commit -m "message"       # save a snapshot
git log --oneline --graph     # view history
git branch                    # list branches
git switch -c feature-x       # create AND switch to a branch
git checkout main             # switch branch (older command)
git pull origin main          # fetch + merge remote changes
git push -u origin feature-x  # upload your branch
git fetch origin              # download remote changes, no merge
git remote -v                 # show connected remotes
git reset --soft HEAD~1       # undo last commit, keep changes
git revert <hash>             # safely undo a commit (new commit)
git diff                      # see line-by-line changes
git tag v1.0.0                # mark a release point
git blame file.js             # see who changed each line
```

### Example Scenario
You join a new project: you `git clone` it, create a branch with `git switch -c`, make changes, check `git status`, `git add` and `git commit`, then `git push`. That's a normal day in five commands.

### Output / History Example
```text
git init    -->  empty repo
git add     -->  changes staged
git commit  -->  A           (first commit)
git commit  -->  A --- B     (second commit)
git push    -->  A --- B     (now on GitHub too)
```

### Senior Engineer Tip
Run `git status` constantly. It's free, it never breaks anything, and it tells you exactly where you stand before every action.

### Common Mistake
Students blindly run `git add .` and accidentally commit secrets, debug logs, or unrelated files. Always review with `git status` and `git diff` first.

---

## Common Git Problems and Fixes

### Simple Meaning
Real problems every developer hits — merge conflicts, wrong-branch commits, accidental deletions — and the calm way to fix each one.

### Why We Use It
Knowing these fixes turns Git from "scary tool that destroys my work" into "tool I'm confident with." Most problems are easily reversible.

### Command
```bash
# 1. Merge conflict — fix the marked files, then:
git add conflicted-file.js
git commit

# 2. Divergent branches (cleaner option):
git pull --rebase origin main

# 3. Committed to wrong branch:
git branch feature-correct      # save commit onto correct branch
git switch main
git reset --hard HEAD~1         # remove it from main
git switch feature-correct

# 4. Undo last commit (keep changes):
git reset --soft HEAD~1

# 5. Restore a deleted file:
git restore path/to/file.txt

# 6. Remove a file from staging:
git restore --staged file.txt

# 7. Pull without losing local changes:
git stash
git pull origin main
git stash pop
```

### Example Scenario
You accidentally committed to `main` instead of your feature branch. You create `feature-correct` (which now holds your commit), reset `main` back one commit, and switch to `feature-correct`. Your work is safe and `main` is clean.

### Output / History Example
```text
A merge conflict in a file looks like this:

<<<<<<< HEAD
your version of the line
=======
their version of the line
>>>>>>> branch-name

Edit it to the correct final version, remove the markers, then add + commit.
```

### Senior Engineer Tip
Prefer `git revert` over `git reset --hard` on shared branches. `revert` creates a safe new commit; `reset --hard` rewrites history and can lose work.

### Common Mistake
Students panic during a merge conflict and run random commands. Stay calm: open the file, pick the correct lines, remove the `<<<`, `===`, `>>>` markers, then `git add` and commit.

---

## Best Practices from Senior Engineers

### Simple Meaning
A short list of habits that separate a tidy, trusted developer from one whose pull requests everyone dreads reviewing.

### Why We Use It
Good Git habits prevent conflicts, make code reviews fast, and keep the whole team's history clean and understandable.

### Command
```bash
# Good commit message (specific, present tense)
git commit -m "Fix null pointer crash on empty cart"

# Always pull before pushing
git pull origin main
git push origin feature-x

# Work on feature branches, never directly on main
git switch -c feature-login

# If you ever must force push, use the safer version
git push --force-with-lease
```

### Example Scenario
Before pushing, you `git pull` to grab teammates' latest work, resolve anything locally, then push. Your push is accepted on the first try and you avoid the dreaded "rejected — non-fast-forward" error.

### Output / History Example
```text
GOOD habits           -->   clean, readable history
small PRs             -->   fast reviews
meaningful messages   -->   easy debugging months later
no force on shared    -->   no broken teammate branches
```

### Senior Engineer Tip
Keep PRs **small**. A 50-line PR gets reviewed in minutes; a 2,000-line PR sits ignored for days and hides bugs.

### Common Mistake
Students write commit messages like `"fix"`, `"update"`, or `"changes"`. Six months later nobody — including them — knows what changed. Be specific.

---

## Recommended Git Workflow for Students

### Simple Meaning
A simple, safe step-by-step flow you can follow for almost any project or assignment, from cloning to merging.

### Why We Use It
Following one consistent workflow keeps your work organized, avoids conflicts, and matches how real engineering teams operate.

### Command
```bash
# 1. Clone the repository
git clone https://github.com/user/project.git
cd project

# 2. Create and switch to a feature branch
git switch -c feature-login

# 3. Do your changes (edit files in your editor)

# 4. Check what changed
git status

# 5. Stage your files
git add .

# 6. Commit with a clear message
git commit -m "Add login form with validation"

# 7. Pull the latest changes to stay up to date
git switch main
git pull origin main
git switch feature-login
git rebase main          # optional: replay your work on top of latest main

# 8. Push your branch
git push -u origin feature-login

# 9. Create a pull request on GitHub
#    Click "Compare & pull request" → describe your work

# 10. Merge using your project's rule:
#     - "Squash and merge" for clean history, OR
#     - No-fast-forward merge to keep a feature marker
```

### Example Scenario
For a class project, you clone the repo, branch off as `feature-login`, build the feature, commit it, pull the latest `main`, push your branch, open a PR, and squash-merge it. Your teammate reviews exactly one clean commit.

### Output / History Example
```text
Clone → Branch → Change → Status → Add → Commit → Pull → Push → PR → Merge

main:        A --- B --------------------- S   <- your feature, squashed in
                    \                      /
feature-login:       C --- D --- E (your work)
```

### Senior Engineer Tip
When in doubt, run `git status`. It tells you exactly where you stand and never changes anything.

### Common Mistake
Students work directly on `main` instead of a feature branch, then struggle to separate their work or recover when something breaks. Always branch first.

---

## Quick Revision Cheat Sheet

```bash
# --- SETUP ---
git init                          # start a new repo
git clone <url>                   # copy a remote repo

# --- DAILY BASICS ---
git status                        # what changed?
git add .                         # stage everything
git commit -m "message"           # save a snapshot
git log --oneline --graph         # view history

# --- BRANCHING ---
git branch                        # list branches
git switch -c feature-x           # create + switch
git switch main                   # switch back

# --- SYNCING ---
git pull origin main              # fetch + merge
git pull --rebase origin main     # fetch + rebase
git fetch origin                  # download only, no merge
git push -u origin feature-x      # upload branch

# --- COMBINING WORK ---
git merge feature                 # standard merge
git merge --no-ff feature         # force a merge commit
git merge --squash feature        # squash into one commit
git rebase main                   # replay commits on main
git cherry-pick <hash>            # copy one commit

# --- SAVING WORK TEMPORARILY ---
git stash push -m "wip"           # set work aside
git stash list                    # see stashes
git stash pop                     # bring back + remove
git stash apply                   # bring back + keep
git stash drop stash@{0}          # delete a stash

# --- UNDOING THINGS ---
git restore file.txt              # discard file changes
git restore --staged file.txt     # unstage a file
git reset --soft HEAD~1           # undo commit, keep changes
git revert <hash>                 # safe undo (new commit)

# --- INSPECTING ---
git diff                          # see unstaged changes
git blame file.js                 # who changed each line
git remote -v                     # show remotes
git tag v1.0.0                    # mark a release
```

### One-Line Memory Hooks

| Concept | Remember This |
|---|---|
| Cherry-pick | Copy ONE commit to another branch |
| Stash | Temporarily save unfinished work |
| Pop vs Apply | Pop removes the stash, apply keeps it |
| Linear history | Straight line (rebase / fast-forward) |
| Non-linear history | Branches + merge commits |
| Fast-forward | Pointer slides forward, no merge commit |
| No fast-forward | Forces a merge commit marker |
| Squash | Many commits → one clean commit |
| Rebase | Replay commits on a new base (linear) |
| Golden rule | Never rebase shared branches without team agreement |

---

