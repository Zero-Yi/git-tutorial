# Merge Conflicts

When merging two branches there are sometimes changes that Git cannot automatically resolve. Git prefers then to flag the conflict as something it cannot resolve instead of intervening and potentially causing even larger errors. Errors that require human intervention usually result from changes to the same file, for example two people modify the same line of a file. Git would then require the person merging the files to decide which one it should keep.

It is important to note that during a merge process if you choose the wrong line or mess up the merge you can revert the merge. Meaning you must only commit the merge once you are happy that everything has been merged properly. At any time you can use the `git reset --hard HEAD` command to reset your HEAD to the last commit before the merge (if you didn't pick up on what this is then read [this](http://www.gitguys.com/topics/head-where-are-we-where-were-we/)).

## Resolving a conflict

Hello and welcome to this Git tutorial. I am to help you get some savvy Git skills whilst also using the C compilation process and a C project as a means to provide a reasoning behind the power and necessity of Git. The C projects will also demonstrate how a state machine works and a basic way of implementing one.

Please note that if you're reading these instruction whilst doing the tutorial they may dissapear if you change branch or do some git trickery that causes them to move/change. As such, while you get to grips with Git I would reccomend moving these README.md files, as they become available, somewhere outside of the current Git repo while you complete the challenge.

## Git

So what is Git?

I hope you all already know the answer to this. Git is a version control software that is now more or less the gold standard in code version control used around the world. As such, knowing Git is a very important skill in today's workplace for anyone that has anything to do with the development of code, regardless of the code type. It can be useful not just code projects but for the version control of any sort of project based around non-binary files, such as PCB designs.

So without writing a big blurb on Git, I say we just get into it and learn by doing.

## What is Forking?

So you will of now forked my repo from GitHub. What this means is that you have more or less copied (not cloned) my repo. It is a complete copy, including the Git histroy, Git objects etc. The key point is that it now belongs to you and you can do as you wish with it, without disturbing my original repo. It is a handy feature that is implemented by the Git server systems (such as GitLab and GitHub), it is not intrinsically a part of Git. It allows for developers to essentially snapshot someone's project, modify it and then, if they want, they can send the changes back to the original developer who can decide if they want to merge their changes into the original code. Forking is popular in the open source community where people are not always directly included in someone's project.

Throughout this tutorial we will do two things, we will set up a new repository for you to use throughout the semester to manage your code and we will undertake some little challenges in this repository to help further your Git and C abilities.

## Basics

Now the very basics of Git. Git works using repositories (previously mentioned repos). Repos are essentially a mini filesystem (locally seen as a folder) in which all changes, that happen within that folder, are (or can be) tracked. Git monitors changes to files and stores snapshots of the files at specified points. By snapshotting the file system, Git gives each point point in the repo's history a unique value. Enabling a developer to revert changes, go back and look at previous, or parallel, version as well as lots of other cool stuff we will cover a bit more later.

Without going into it too much now, we know that a Git repo will give us a folder, whose content will be tracked. So now let's set up the repo that you will use throughout semester.

For anyone doing this that is not one of my students you will have to just ignore the specifics aimed at my students.

You can either use the LRZ GitLab or a **private** GitHub repo for this, the functionality is identical. Do not use a public GitHub as other students will be able to view your code and you might be involved in some nasty business if duplicate code is found in another student's project.

So now you will need to create a new project. This will require you to do the following:

1. Create a new project/repository in the web GUI
2. Either follow the given instructions to clone the new repository or copy the clone link so you can clone the repository to your machine which I will explain now.

  There are two types of links always available, one via SSH and the other via HTTPS. SSH allows you to upload your public SSH key to the server and use it to authenticate yourself when interacting with the server, meaning you do not have to constantly enter your username and password when interacting with the server. In contrast HTTPS requires you to enter your username and password in the terminal every time you interact with the server when authentication is required.

  I recommend uploading a SSH key and using the SSH link. Google how to do this, its not hard.

  Then to clone the repository you simply have to run the `git clone` command. Looking at the manual page for the clone command (`man git clone`) we can see that the command takes the form of `git clone <options> <repository> <directory>`. For us we will just use the basic command to clone our newly created repository into a folder called "ESPL_code". From the folder where you would like to have your `ESPL_code` folder stored run

  ``` bash
  git clone <SSH or HTTPS URL> ESPL_code
  ```

  Now we will have the Git repo on our local machines. Next we will look into the basics of creating and storing code in our repository. Please note that after the basics of the "ESPL_code" repository are set up we will do the rest of this tutorial in the tutorial repository, I am just wanting to make sure you have a Git repo set up and ready for the rest of semester so that you USE IT!

# How Git Tracks Your Changes

Git works slightly differently to other version control software in that is uses a staging area to which a user adds files that he/she wishes to be tracked (changes recorded). As such Git does not automatically track all changes in a repository. It is up to the user to make sure that the files that they are interested in are added to the staging area, there are ways to wildcard add things but this can lead to very messy and unprofessional repos.

As such the workflow follows the flow of:

1. Working directory

  Here a developer can modify/create/delete files in their project, just do your thing....write your code etc.

2. Staging area

  Here are the files that the user has told Git are important and should be tracked. If a file is not here then Git will not care for the changes made to that file. Files are added to the staging area using the `git add` command. Use `man git add` for a more detailed overview. It's quite straight forward.

3. Repository

  Once files have been added to the staging area, using `git add`(`git commit`perhaps?), they can then be committed to the repository. A commit represents a snapshot in the repo's file system. The difference between two commits as seen as a set of changes to a set of files, also synonymous to a patch (funnily enough a lot of modern patches come straight from Git commits). Also note that that your changes and repository are local and not automatically sent to your Git server, this must be done manually. As such one must commit changes to your repository and then push the commits to the remote server, but we will get to this a little later.

The benefit of having a staging area is that a user can create separate commits for different chunks of work. If you modified two separate files you could add each file to the staging area individually, commit the changes, thus creating a psudo patch for that file then add and commit the second file creating a separate patch for the second file. While this functionality will most likely not be that useful for you in ESPL, it is an important concept to grasp, especially for industry work where the generation of patches is very important. As you should not have random files contained within your patches, such as debug files, knowing how to control the contents of a commit is very important.

Storing changes to file in the staging area are done using the `git commit` command. See `man git commit` for details. We will see how this is done in practice shortly and it should become clear if it's not making complete sense at the moment.

## What is a Commit?

Now that we know the rough workflow of Git, I feel that it will help to make the entire process of Git and tracking changes clearer if what a commit is is outlined.

A commit holds the state of the repository at the moment when the commit was created. This state is just a node in a linked list of the repository's previous states, with the commit node's parent(s) being the commits that came before it during the development within the Git repository. Git does not store the delta of each file like other versioning control software but instead creates copies of changed files, unchanged files are thus able to be simply referenced, such that that unnecessary copies of unchanged file are not made. This allows the user to navigate through this linked list of commits to look at the repository's snapshots at different points in time. As such, Git is more or less a mini filesystem that has some powerful tooling to achieve some pretty nifty tricks.

## Lets Commit!

Now let's put this into practice. Git repositories almost always contain a README.md file. The README is responsible for giving an overview of and/or instructions for the project on the GitHub/GitLab page when one views the repository in the web interface, as you are probably doing now.

The README usually contains useful information outlining the project, how to build it, developer's contact information etc. As such, we will create and add one to our newly created ESPL repository. Please then create, in your ESPL repository, a `README.md` file. The `.md` signifys that it is a markdown fil, allowing for markdown formatting of the text. Markdown formatting information can be found [here](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet#links).

Please add your name and a quick description to the README then we will go through and add it.

``` bash
echo "# Your name here" > README.md
echo "A quick description" >> README.md
```

This will create the file and add your name and a description to the file, with your name being a H1 title.

Every time you make a change to the contents of your Git repository you can see the status of the repository using the command `git status`.

Running that now will show us a few things

```
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	README.md

nothing added to commit but untracked files present (use "git add" to track)
```

We can see that we are on our Master branch (we will cover branches a little later) and that we have the file `README.md` as an untracked file, meaning it is not in the staging area and would not be included in any commits.

Let's for testing purposes try and commit our README without adding it to the staging area. Looking at the manual for the `git commit` command (running `man git commit`). We can see the commands which can be used to add and remove files from the staging area (read the description section). Now a commit always requires a commit message, given using the `-m` option. Commit messages should always be precise and describe what changes have been implemented in this commit. Think of the commit message as a title/description for the patch that would be generated from the commit. As such to "attempt" to commit our README without adding it to the staging area we would run

``` bash
git commit -m "Added README"
```

We will now see that Git complains that nothing was added to the commit, meaning the staging area was empty. As we should all know by now, we need to add the `README.md` to the staging area. To do this we can either add the individual file or add all files in the repository. I would recommend avoiding adding all file where possible as you tend to include a lot of junk. We will cover how to avoid this a little later on.

For now add your README using

``` bash
git add README.md
```

Now attempting to commit should result in the output

```
[master (root-commit) 3c2b284] Added README
 1 file changed, 2 insertions(+)
 create mode 100644 README.md
```

Showing us a few things. It shows us our branch `master`, the beginning of the commit hash `3c2b284`, the commit message `Added README`, the changes made as well as the files added, in this case the `README.md`. To find out what the mode is read [here](https://stackoverflow.com/questions/737673/how-to-read-the-mode-field-of-git-ls-trees-output/8347325#8347325).

We have now successfully created a commit in our repository. Running `git log` we can see that the commit now appears in the repository's logs. In the log you can also see the entire commit hash which is used to identify that specific commit within your repo.

In a repo you will create many commits as you implement features and commit them, the commits will not be automatically visible to others who also have the repository on their machines or are looking through the web interface. Git does not automatically sync changes as it is designed to be usable offline, only syncing when told to. To then send your commits to the remote repository, stored on a Git server, you must `git push`. To understand what we are doing exactly when we are pushing we need to know a couple of things.

To push our code to the Git server we us the command `git push origin master`.

Breaking this command down we have:

 * `git push`, this is the command the tells Git to send all of the commits saved locally on your machine to the remote server.
 * `origin`, is the alias given to the remote server where our repository is stored. If you look into the `.git/config` file in your repositories root directory you will see something similar to the following

  ```
  ...                                                 
  [remote "origin"]                                                                
    url = git@git.alxhoff.com:alxhoff/espl-test.git                              
    fetch = +refs/heads/*:refs/remotes/origin/*                                   
  ...
  ```

  This is telling us that when we use `origin` we will be sending our commits to the server specified by that alias. It is possible to send to multiple servers at once, for instance a backup server, or to send to both a private and public server.

* `master`, tells Git which branch's commits we are wanting to send. We will cover branches soon.

Running `git push origin master` will show us the following

```
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Writing objects: 100% (3/3), 253 bytes | 253.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0)
To git.alxhoff.com:alxhoff/espl-test.git
 * [new branch]      master -> master
```

which should be quick self-explanatory.

Now that we have covered how to add, commit and push we will stop using the ESPL repository and focus purely on this tutorial repository that you forked. The ESPL repository is there for you to use over the semester, read the exercise and project descriptions to see how your use of Git will be assessed. Using Git is required as part of the grading in this course, USE IT!

# Branching

Inside this repository there are a couple small programming challenge that we will get to soon. Through them where you will learn about some more advanced features of Git, the basics of building a C project and also do some very basic programming exercises. The first step will be to start our C project. To do this you will need to get and merge the CMake project to your master branch, to do this we need to learn about branches and merging. First step it branching.

A Git branch essentially takes a copy of the current state of your git repository and allows you to change it seperate to the branch from which you branch. Confused?
As the same implied, branching allows your to diverge your code base into a seperate "copy" that can be modified and later merged back into "core" of your repository.
Git uses branches to allow for parallel development of code without interfering with the code on other peoples machines or without breaking your stable code base whilst you hack around some changes. How exactly branches are used is a personal preference or the preference of your company, but there are some good ideas to employ when using your Git branches.

We have already come across the master branch, as the name implies this is the root branch of the repository and it usually the most sacred of all branches. Good practice is to not develop directly on the master branch as the master branch should always have a stable version of your code that builds and runs, while it might not have all the latest features, it should be able to be demo'd at any moment in time (except maybe exactly during a merge). You should as such never push to master, only merge to master. Be prepared for impromptu requests to see your code running, it should thus be able to be run from your master branch always even if it lacks all the latest features.

As master is this stable branch that must never break, you might of guessed that all development should be done on other branches. This is correct. When working in large groups or on a project where you are swapping between implementing multiple features at the same time, each person or feature should be a branch. I would recommend towards having a branch for a feature as multiple people might work on a feature over the duration of a project. To understand the next concept we need to have a basic understanding of what merging is, while we will look at merging in practice shortly, a theoretical understanding is needed.

Merging, as the name implies, is the task of merging the code (the changes) from one branch into another. If you have a branch to implement a certain feature, you would then merge this feature into your master branch once the feature is stable and completed. The merge process can become quite complex and involved but for now you should understand what merging aims to achieve. As you can imagine, merging large complex changes can become quite involved, while Git does a great job at handling most changes automatically it does not always manage on its own. As such, merging your changes into master can sometimes lead master to becoming unstable whilst the merge is handled. As such, you can imagine that employing a merge branch to handle the merging of complicated code changes into one single delta can act as a good intermediary between your feature branches and the master branch.

Therefore it can be good practice to have a branch structure similar to the following

```
master ----- merging ----- feature A
                     |---- feature B
```

Thus any complicated merge conflicts will be contained to the merging branch and can be resolved there before being merged (via a less complex merge, as the complex problems have now been resolved) into the master branch. We will cover merge errors and the likes later as your perform your own merges.

Let us now go to the merging branch. To check the branches that exist in the repository one can use the `git branch` command. A new repository might not show all of the branches as Git does not download all information when not required, to try and minimize the data required locally. `man git fetch` will detail how Git fetch can be used.

When no remote is specified the default `origin` is used. Run `git fetch` to thus retrieve all the branches and tags on the origin remote. Now run `git branch --all` to list all of the branches on the origin. We want a branch called `merging` where we will perform our merges before merging to master. To do this we need to first create a branch and then swap to this branch. To create a new branch simply use

``` bash
git branch merging
```
now if we list our branches using `git branch` you should now see that there is a `merging` branch. We now need to change to this branch so our modifications that we perform are done there. It should be noted that the new branch is a copy of this current branch, although if we were to continue modifying master then the merging branch would fall behind and would need to be brought back up to speed with master. But for now just checkout `merging` using the checkout command.

``` bash
Unmerged paths:
(use "git add <file>..." to mark resolution)

    both modified:   src/main.c
```

Inside each conflict file Git places markers that indicate the area of conflict. Let's take the simple example where two changes affected the same line of code in a file. This means that Git needs you to decide which change to keep. You will manually need to edit the code to integrate both solutions into your project. Choosing how to fix your code will be up to your discretion.

Now in this example I have branched my original code, then on the new branch **and** on my current branch created commits that modify the same line of code. On the current branch I added "Result:" to a `printf` statement while on the branch I added "Output:".

``` bash
Original code (shared commit) ------ + "Result:"
                              |----- + "Output:"
```

This has caused a merge conflict as the commit which they both share now has two different diffs when compared with the HEAD of both branches.

Looking into the file `src/main.c`, as shown by `git status`, we would see the following around the line of interest.

``` C
<<<<<<< HEAD
        printf("Result: %s", tmp);
=======
        printf("Output: %s", tmp);
>>>>>>> bar
```

This tells use that on our current branch (our current HEAD) the line containing "Result", where as on the branch we wish to merge into our current branch (bar) the line contains "Output". Git does not know which one we wish to use and as such we must decide. Let's say that we wish the have the line contain output and not result, then we must manually delete the markers from Git as well as the line. Using our new patch knowledge we can see the what needs to be done below.

``` bash
--- src/main.c  2019-03-20 11:47:22.947753390 +0100
+++ src/main.c  2019-03-20 11:47:34.777753931 +0100
@@ -8,11 +8,7 @@
    char *tmp = NULL;
    tmp = num_to_words(123);
    if (tmp)
-<<<<<<< HEAD
-        printf("Result: %s", tmp);
-=======
         printf("Output: %s", tmp);
->>>>>>> bar
    else
         return 1;
    return 0;
```

Once you have resolved the merge conflict you can then add the resolved file and finalize the merge with a normal commit. The commit message should summarize the changes during the merge.

# Coding Challenge III

Now that you has seen the basic ideas of how merging works, lets see if you can handle some more complex merge problem yourself. You will find a branch called `unknown_features` which has diverged from this current branch at the previous commit. Meaning that the HEAD of this branch and `unknown_features` have a shared previous commit....conflicts are looking likely!

Your job now is to merge `unknown_features` branch into this current branch and resolve the conflicts that appear (find files affected using `git status`). You will need to apply you C knowledge and CMake knowledge to merge the files correctly to get the project building properly. Please note that there are other tricks and errors hidden in the code. The code should not compile with warnings, as warnings should almost always be treated as errors. Warnings will be cause for deducted marks throughout this course.

The program you are building is a POSIX thread (`pthread`) based state machine that counts, using random intermediate values, to a number specified in the programs options. See the `--help` of the compiled binary to see how to use the program. An example usage of the program that counts up to the value 2 would be

``` bash
./state_machine 2
```

If the code has been compiled sucessfully the output should be something similar to

``` bash
Count until = 2
Verbose = no
Tick = 100ms
State 0 probed
State 1 probed
State 2 probed

### Starting State Machine ###

Count up once
Total count: 1
In state 1, state count: 1
---------
Count down once
Total count: 0
In state 3, state count: -1
---------
Entering 2
Count up twice
Total count: 2
In state 2, state count: 2
---------
Finshed
```

Once your binary performs this then you have the project merged and building correctly. Merge the project into `merging` and finally into `master`, if both projects are stable and working as expected. This code should replace the code that it in master from the 2nd coding challenge. Finally create another tag with the annotation "Coding Challenge 3".

If all of that is done then you have completed this tutorial. Please be wary that the use of Git is a requirement in this course and will be part of the project's assessment. Inform yourself on proper use of Git commit messages and make sure that you and your team partner establish a Git workflow that you will use throughout the course. A fun tool to use to make sure your workflow has been used properly is `git log --graph --all` which will give you a graphical representation of your repo's logs.

# Future Reading

There are a number of other features in Git that are useful to know. If you are motivated then I would recommend reading up on these features so that during semester you are able to overcome some problems you will no doubt encounter.

* `git stash`
* `git pull`
* `git show`
* `git revert`
* `git clean`
