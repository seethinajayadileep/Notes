# Azure DevOps YAML and Classic Release Pipeline Notes

> **Created by:** DevOps Learner  
> **Topic:** CI/CD Pipeline for .NET Web Application using Azure DevOps  
> **Date:** Today's DevOps Training Session  
> **Level:** Beginner-Friendly (written by a Senior DevOps Engineer)

---

## Table of Contents

1. [What I Did Today](#1-what-i-did-today)
2. [Overall Pipeline Flow](#2-overall-pipeline-flow)
3. [YAML File Explanation Line by Line](#3-yaml-file-explanation-line-by-line)
4. [Important Azure DevOps Variables](#4-important-azure-devops-variables)
5. [Lifecycle Hooks in Deployment Jobs](#5-lifecycle-hooks-in-deployment-jobs)
6. [Deployment Strategies](#6-deployment-strategies)
7. [Build Stage vs Deployment Stage](#7-build-stage-vs-deployment-stage)
8. [Dev and QA Environments](#8-dev-and-qa-environments)
9. [Classic Release Pipeline](#9-classic-release-pipeline)
10. [YAML Pipeline vs Classic Release Pipeline](#10-yaml-pipeline-vs-classic-release-pipeline)
11. [Common Mistakes I Should Remember](#11-common-mistakes-i-should-remember)
12. [Corrected and Improved YAML](#12-corrected-and-improved-yaml)
13. [Interview Explanation](#13-interview-explanation)
14. [Real-Time Project Explanation](#14-real-time-project-explanation)
15. [Final Summary](#15-final-summary)

---

## 1. What I Did Today

Today was a very productive DevOps session. Here is a simple summary of what I accomplished:

### CI Part (Continuous Integration — Build Stage)

- Wrote a **YAML pipeline** from scratch for a **.NET web application**
- Installed **NuGet tool** inside the pipeline to manage packages
- Ran **NuGet restore** to download all required dependencies for the project
- Used **VSBuild task** to compile the code and create a deployable `.zip` package
- Published the build output (the `.zip` file) as a **build artifact** named `drop`

### CD Part (Continuous Deployment — Release Stages)

- Created a **DevRelease stage** that downloads the artifact and deploys to the **Dev Azure App Service** (`hdfcloan`)
- Created a **QaRelease stage** that downloads the same artifact and deploys to the **QA Azure App Service** (`qahdfcloan`)
- Used **`runOnce` deployment strategy** for both Dev and QA
- Used **Azure Environments** (`Dev`, `Qa`) to track and control deployments

### Classic Release Pipeline

- Created a **Classic Release Pipeline** using the Azure DevOps web UI (point-and-click)
- Connected it to the build artifact
- Added an **Azure App Service Deploy** task
- Connected it to an **Azure subscription (service connection)**
- Created a release manually and deployed successfully

---

## 2. Overall Pipeline Flow

Here is the complete flow of what happens from code to deployment:

```
Developer pushes code to 'develop' branch
              ↓
YAML pipeline triggers automatically (trigger: - develop)
              ↓
┌─────────────────────────────────┐
│         BUILD STAGE             │
│  1. NuGetToolInstaller runs     │
│  2. NuGet packages restored     │
│  3. VSBuild compiles solution   │
│  4. Creates .zip package        │
│  5. Artifact published as 'drop'│
└─────────────────────────────────┘
              ↓
┌─────────────────────────────────┐
│       DevRelease STAGE          │
│  1. Downloads 'drop' artifact   │
│  2. Deploys to Dev App Service  │
│     (hdfcloan)                  │
└─────────────────────────────────┘
              ↓
┌─────────────────────────────────┐
│       QaRelease STAGE           │
│  1. Waits 60 seconds            │
│  2. Downloads 'drop' artifact   │
│  3. Deploys to QA App Service   │
│     (qahdfcloan)                │
└─────────────────────────────────┘
```

> **Important:** Both DevRelease and QaRelease depend on the **same Build stage** (using `dependsOn: Build`). They both use the **same artifact** (the `drop` artifact built once). This follows the principle of **"Build Once, Deploy Many Times."**

---

## 3. YAML File Explanation Line by Line

Let's go through every part of the YAML file step by step.

### `trigger`

```yaml
trigger:
- develop
```

This tells Azure DevOps: **"Automatically run this pipeline whenever someone pushes code to the `develop` branch."**

Think of it as a sensor — when the `develop` branch gets new code, the pipeline wakes up automatically.

---

### `variables`

```yaml
variables:
  solution: '**/*.slnx'
  buildPlatform: 'Any CPU'
  buildConfiguration: 'Release'
```

Variables are reusable values. Instead of typing the same value again and again, we define it once and use it with `$(variableName)`.

| Variable | Value | Purpose |
|---|---|---|
| `solution` | `**/*.slnx` | Finds the solution file anywhere in the repo |
| `buildPlatform` | `Any CPU` | Build for any CPU architecture |
| `buildConfiguration` | `Release` | Build in Release mode (not Debug) |

> `**/*.slnx` means "look in all folders (`**`) and find any file ending in `.slnx`."

---

### `stages`

```yaml
stages:
  - stage: Build
  - stage: DevRelease
  - stage: QaRelease
```

A pipeline is divided into **stages**. Think of stages like phases:
- **Stage 1 — Build:** Compile the code
- **Stage 2 — DevRelease:** Deploy to Dev
- **Stage 3 — QaRelease:** Deploy to QA

---

### Build Stage — `NuGetToolInstaller@1`

```yaml
- task: NuGetToolInstaller@1
```

This installs the latest NuGet tool on the build agent (the virtual machine doing the work). NuGet is the package manager for .NET — like `npm` for Node.js or `pip` for Python.

---

### Build Stage — `NuGetCommand@2` (Restore)

```yaml
- task: NuGetCommand@2
  inputs:
    restoreSolution: '$(solution)'
```

This runs `nuget restore` which downloads all the NuGet packages that the project depends on.

Think of it like running `npm install` — it downloads the libraries your app needs before building.

---

### Build Stage — `VSBuild@1`

```yaml
- task: VSBuild@1
  inputs:
    solution: '$(solution)'
    msbuildArgs: '/p:DeployOnBuild=true /p:WebPublishMethod=Package /p:PackageAsSingleFile=true /p:SkipInvalidConfigurations=true /p:PackageLocation="$(build.artifactStagingDirectory)"'
    platform: '$(buildPlatform)'
    configuration: '$(buildConfiguration)'
```

This is the actual **build step** — it compiles the .NET code using Visual Studio's build engine (MSBuild).

Let's break down `msbuildArgs`:

| Argument | What It Does |
|---|---|
| `/p:DeployOnBuild=true` | After building, also create a deployment package |
| `/p:WebPublishMethod=Package` | Create the package as a .zip file |
| `/p:PackageAsSingleFile=true` | Put everything into one single .zip |
| `/p:SkipInvalidConfigurations=true` | Don't fail if a config is not valid |
| `/p:PackageLocation="$(build.artifactStagingDirectory)"` | Save the .zip here |

> The `.zip` file is saved at `$(Build.ArtifactStagingDirectory)` — a temporary folder on the build agent.

---

### Build Stage — `PublishBuildArtifacts@1`

```yaml
- task: PublishBuildArtifacts@1
  inputs:
    PathtoPublish: '$(Build.ArtifactStagingDirectory)'
    ArtifactName: 'drop'
    publishLocation: 'Container'
```

This takes the `.zip` file from the build agent and **publishes it to Azure DevOps artifact storage** so that other stages can download it.

- `ArtifactName: 'drop'` — The artifact is named `drop`. This name will be used in the deployment stages.
- `publishLocation: 'Container'` — Stores it in Azure DevOps (not on an external server).

---

### Deployment Job — `deployment`

```yaml
jobs:
  - deployment: DeployDev
    displayName: Deploy to dev
    pool:
      vmImage: 'windows-latest'
    environment: Dev
    strategy:
      runOnce:
        deploy:
          steps:
```

A **deployment job** is special. Unlike a regular `job`, a deployment job:
- Tracks deployment history in Azure DevOps **Environments**
- Supports deployment strategies (runOnce, rolling, canary)
- Requires an `environment` name

---

### `environment`

```yaml
environment: Dev
```

This links the deployment to an Azure DevOps **Environment** called `Dev`. Environments help you:
- See which version is deployed where
- Add **approval gates** (e.g., a manager must approve before deploying to QA)
- Track deployment history

---

### `strategy: runOnce`

```yaml
strategy:
  runOnce:
    deploy:
      steps:
```

`runOnce` means: deploy once, to all servers at the same time. It's the simplest strategy. See Section 6 for all strategies.

---

### `download: current`

```yaml
- download: current
  artifact: drop
```

This downloads the artifact named `drop` from the **current pipeline run**. After downloading, the artifact is available at:

```
$(Pipeline.Workspace)/drop/
```

---

### `AzureRmWebAppDeployment@5`

```yaml
- task: AzureRmWebAppDeployment@5
  inputs:
    ConnectionType: 'AzureRM'
    azureSubscription: 'hdfc'
    appType: 'webApp'
    WebAppName: 'hdfcloan'
    packageForLinux: '$(Pipeline.Workspace)/drop/**/*.zip'
```

This is the actual deployment task. It:
1. Connects to Azure using the service connection named `hdfc`
2. Finds the App Service named `hdfcloan`
3. Uploads the `.zip` file from `$(Pipeline.Workspace)/drop/**/*.zip`
4. Deploys the application

> `**/*.zip` is a glob pattern meaning "find any `.zip` file in any subfolder."

---

## 4. Important Azure DevOps Variables

### `$(Build.ArtifactStagingDirectory)`

This is a **predefined variable** provided automatically by Azure DevOps.

It points to a **temporary folder on the build agent** where you store files you want to publish as artifacts.

**Example path on agent:**
```
C:\agent\_work\1\a
```

**When is it used?**

During the **Build Stage**, when VSBuild creates the `.zip` file, it saves it here:

```yaml
/p:PackageLocation="$(build.artifactStagingDirectory)"
```

Then `PublishBuildArtifacts` uploads this folder to Azure DevOps storage.

---

### `$(Pipeline.Workspace)`

This is used in **Deployment Stages** (not the Build Stage).

When you run `download: current`, Azure DevOps downloads the artifact and places it in the **Pipeline Workspace**:

```
$(Pipeline.Workspace)/drop/
```

**Example path:**
```
C:\agent\_work\1\
```

---

### Summary: Where does the artifact live?

```
BUILD STAGE
-----------
VSBuild creates .zip  →  $(Build.ArtifactStagingDirectory)
                                       ↓
PublishBuildArtifacts uploads it to Azure DevOps storage (named 'drop')

DEPLOYMENT STAGE
----------------
download: current artifact: drop
                                       ↓
Artifact downloaded to → $(Pipeline.Workspace)/drop/
                                       ↓
AzureRmWebAppDeployment reads → $(Pipeline.Workspace)/drop/**/*.zip
```

| Variable | Stage | Location |
|---|---|---|
| `$(Build.ArtifactStagingDirectory)` | Build Stage | Temp folder on build agent |
| `$(Pipeline.Workspace)` | Deployment Stage | Workspace folder on deploy agent |

---

## 5. Lifecycle Hooks in Deployment Jobs

When you use a **deployment job** with a strategy like `runOnce`, Azure DevOps gives you special hooks that run at different times during the deployment process.

Think of lifecycle hooks like the lifecycle of a surgery:
- **preDeploy** → prepare the operation room
- **deploy** → perform the surgery
- **routeTraffic** → move patient to recovery
- **postRouteTraffic** → monitor after surgery
- **on.failure** → emergency protocol if something goes wrong
- **on.success** → celebration when it works!

---

### All Lifecycle Hooks

```yaml
strategy:
  runOnce:
    preDeploy:          # Runs BEFORE deployment begins
      steps:
        - script: echo "Preparing environment..."

    deploy:             # Main deployment steps (THIS IS MANDATORY)
      steps:
        - download: current
          artifact: drop
        - task: AzureRmWebAppDeployment@5

    routeTraffic:       # Runs AFTER deploy — send traffic to new version
      steps:
        - script: echo "Routing traffic to new version..."

    postRouteTraffic:   # Runs AFTER traffic is routed — health checks
      steps:
        - script: echo "Checking if app is healthy..."

    on:
      failure:          # Runs if ANYTHING above fails
        steps:
          - script: echo "Deployment failed! Rolling back..."

      success:          # Runs if everything succeeds
        steps:
          - script: echo "Deployment succeeded! Sending notification..."
```

---

### What I Used in My YAML

In my pipeline, I only used the `deploy` hook:

```yaml
strategy:
  runOnce:
    deploy:
      steps:
        - download: current
          artifact: drop
        - task: AzureRmWebAppDeployment@5
```

The `deploy` hook is the **main and most important lifecycle hook**. It is where actual deployment happens. For simple projects (like Dev and QA App Service deployments), using only `deploy` is perfectly fine.

---

### When Would You Use Other Hooks?

| Hook | Real Example |
|---|---|
| `preDeploy` | Back up the database before deploying new version |
| `deploy` | Deploy the application (always used) |
| `routeTraffic` | Switch load balancer to new version |
| `postRouteTraffic` | Run smoke tests to check if new version works |
| `on.failure` | Send alert to Slack/Teams if deployment fails |
| `on.success` | Send release announcement email |

---

## 6. Deployment Strategies

Azure DevOps supports three main deployment strategies. Let's understand each one.

---

### Strategy 1: `runOnce`

**What it means:** Deploy once to ALL servers at the same time.

**When to use:** Simple projects with one server or one App Service. No need for gradual rollout.

**Real example:** You have one Dev App Service (`hdfcloan`). You want to deploy the new version immediately. Use `runOnce`.

```yaml
strategy:
  runOnce:
    deploy:
      steps:
        - task: AzureRmWebAppDeployment@5
```

**Risk level:** Medium — if the deployment fails, all users are affected.

---

### Strategy 2: `rolling`

**What it means:** Deploy gradually to servers in batches. Deploy to 2 servers first → check health → deploy to 2 more → check → continue.

**When to use:** You have multiple servers (e.g., 10 VMs in a server pool) and want to reduce risk.

**Real example:** You have 10 web servers. Deploy to 2 at a time. If it works, continue. If it fails, stop and roll back.

```yaml
strategy:
  rolling:
    maxParallel: 2       # Deploy to 2 servers at a time
    deploy:
      steps:
        - task: AzureRmWebAppDeployment@5
```

**Risk level:** Lower — only a small portion of users are affected if something goes wrong.

---

### Strategy 3: `canary`

**What it means:** First deploy to a small percentage of users (e.g., 10%), monitor, then roll out to everyone.

**When to use:** Production deployments where you want to test with a small audience before full release. Named after "canary in a coal mine" — the canary detects danger early.

**Real example:** Deploy to 10% of users first. If error rate increases, stop. If all is well, deploy to 100%.

```yaml
strategy:
  canary:
    increments: [10, 50]   # Deploy to 10%, then 50%, then 100%
    deploy:
      steps:
        - task: AzureRmWebAppDeployment@5
```

**Risk level:** Lowest — most users are not affected if something goes wrong.

---

### Why `runOnce` is Correct for My Pipeline

In my pipeline, I'm deploying to:
- **Dev App Service** — used only by developers (1 server)
- **QA App Service** — used only by testers (1 server)

There is no need for rolling or canary. `runOnce` is the perfect choice here because:
- There is only one App Service per environment
- Dev and QA environments are not production — risk is low
- Simpler strategy = easier to debug

---

## 7. Build Stage vs Deployment Stage

| Aspect | Build Stage | Deployment Stage |
|---|---|---|
| Job type | `job` | `deployment` |
| What it does | Compiles code, creates artifact | Downloads artifact, deploys to Azure |
| Runs on | Build agent | Deploy agent |
| Environment used | No | Yes (`environment: Dev`) |
| Artifact created | Yes (published as `drop`) | No (downloads `drop`) |
| Azure connection | No | Yes (service connection) |

### Build Stage Summary

```
Code → NuGet Restore → VSBuild → .zip file → Publish Artifact (drop)
```

The build stage is like a **factory** that takes raw materials (code) and produces a finished product (the `.zip` package). It knows nothing about Azure or environments.

### Deployment Stage Summary

```
Download artifact (drop) → Connect to Azure → Upload .zip to App Service
```

The deployment stage is like a **delivery truck** that picks up the finished product from the warehouse and delivers it to the destination (Azure App Service). It knows nothing about how the product was built.

This clean separation is important: **Build once, deploy many times to different environments.**

---

## 8. Dev and QA Environments

### What is the Dev Environment?

The **Dev (Development) environment** is where developers first test their code after it is built. It is the first stop in the deployment journey.

- **Purpose:** Developer self-testing, quick feedback
- **Users:** Developers only
- **Stability:** Can break — it's okay, that's expected
- **App Service name:** `hdfcloan`

### What is the QA Environment?

The **QA (Quality Assurance) environment** is where testers validate the application.

- **Purpose:** Functional testing, bug detection
- **Users:** QA/Testing team
- **Stability:** Should be more stable than Dev
- **App Service name:** `qahdfcloan`

### Why Deploy to Dev First?

If you deploy directly to QA without testing in Dev first, testers waste time on bugs that developers could have caught themselves. Dev is a safety net.

```
Developer writes code
       ↓
Deploy to Dev (developer checks it works)
       ↓
Deploy to QA (testers validate all features)
       ↓
(After QA approval) Deploy to Production
```

### How Azure DevOps Environments Help

Azure DevOps **Environments** (not to be confused with deployment environments) are a feature in Azure DevOps that:

1. **Track deployment history** — You can see when each version was deployed and by whom
2. **Support approval gates** — You can require a person to approve before deployment starts
3. **Show health of resources** — You can link Kubernetes namespaces or App Services
4. **Enforce policies** — E.g., only deploy to Production on weekdays

In my pipeline:
```yaml
environment: Dev    # Links to the 'Dev' environment in Azure DevOps
environment: Qa     # Links to the 'Qa' environment in Azure DevOps
```

You can add **approvals** to the `Qa` environment in Azure DevOps UI — so a QA lead must approve before deployment starts.

---

## 9. Classic Release Pipeline

### What I Did

I also created a **Classic Release Pipeline** using the Azure DevOps web interface (no YAML needed).

Here are the steps I followed:

1. Went to **Pipelines → Releases** in Azure DevOps
2. Clicked **New Pipeline**
3. Selected the **build artifact** (the `drop` from the YAML Build stage)
4. Added a **Stage** named `Dev`
5. Added the task: **Azure App Service Deploy**
6. Configured the task:
   - Selected **Azure subscription** (service connection)
   - Selected the **App Service name**
   - Set the **package path** to the `.zip` file
7. Saved the pipeline
8. Clicked **Create Release** manually
9. Deployment succeeded ✅

---

### Classic Pipeline vs YAML Pipeline

**Classic Release Pipeline** is like filling out a form in a web UI — you click, select, and configure.

**YAML Pipeline** is like writing the same form as code — stored in your Git repository, version-controlled, reviewable.

Both achieve the same result. They just work differently.

---

## 10. YAML Pipeline vs Classic Release Pipeline

| Feature | YAML Pipeline | Classic Release Pipeline |
|---|---|---|
| **Configuration style** | Code (YAML file) | UI-based (point and click) |
| **Stored in repo** | Yes — `azure-pipelines.yml` in Git | No — stored in Azure DevOps DB |
| **Version control** | Yes — tracked with Git history | No — no native version control |
| **UI-based editing** | No — edit the `.yml` file | Yes — full drag-and-drop UI |
| **Best for** | Real projects, teams, DevOps maturity | Beginners, quick setups |
| **Reusability** | High — templates, parameters, stages | Medium — can clone stages |
| **PR reviews** | Yes — changes go through pull requests | No |
| **Modern DevOps usage** | Recommended by Microsoft | Being deprecated gradually |
| **Learning curve** | Higher | Lower |
| **Approval gates** | Yes (via Environments) | Yes (via Stage gates) |
| **Audit trail** | Via Git + pipeline runs | Via pipeline run history |

---

## 11. Common Mistakes I Should Remember

These are real mistakes beginners make. Learn them so you don't repeat them.

---

**Mistake 1: Wrong YAML indentation**

YAML is very sensitive to indentation. One extra space breaks everything.

```yaml
# ❌ WRONG - steps is under deploy but wrong indent
strategy:
  runOnce:
    deploy:
    steps:          # Wrong! steps should be indented under deploy

# ✅ CORRECT
strategy:
  runOnce:
    deploy:
      steps:        # Correct indentation
```

---

**Mistake 2: Wrong variable case**

Azure DevOps variables are **case-sensitive**.

```yaml
# ❌ WRONG
$(pipeline.workspace)     # lowercase 'p' - won't work

# ✅ CORRECT
$(Pipeline.Workspace)     # correct case
```

---

**Mistake 3: Forgetting the deployment job name**

A `deployment` job must have a name. A regular `job` also needs a name. Don't confuse them.

```yaml
# ❌ WRONG
jobs:
  - deployment:          # Missing the job name!

# ✅ CORRECT
jobs:
  - deployment: DeployDev   # 'DeployDev' is the job name
```

---

**Mistake 4: Wrong artifact path in deployment**

If the artifact is named `drop`, the downloaded path is `$(Pipeline.Workspace)/drop/`.

```yaml
# ❌ WRONG
packageForLinux: '$(Build.ArtifactStagingDirectory)/**/*.zip'   # This is build stage variable

# ✅ CORRECT
packageForLinux: '$(Pipeline.Workspace)/drop/**/*.zip'          # Correct for deployment stage
```

---

**Mistake 5: Wrong App Service name**

A typo in the App Service name will cause deployment to fail with a "resource not found" error.

```yaml
# ❌ WRONG
WebAppName: 'hdcfloan'      # Typo!

# ✅ CORRECT
WebAppName: 'hdfcloan'
```

---

**Mistake 6: Wrong Azure service connection name**

The `azureSubscription` must match **exactly** the name of the service connection in Azure DevOps.

```yaml
# ❌ WRONG
azureSubscription: 'HDFC'     # Wrong case

# ✅ CORRECT
azureSubscription: 'hdfc'     # Must match service connection name exactly
```

---

**Mistake 7: `packageForLinux` for Windows App Service**

The input parameter is named `packageForLinux` but it works for Windows App Services too. This confuses beginners. Don't let the name mislead you — it's the package path input, not a Linux-specific setting. When `appType: 'webApp'` is set, it's a Windows App Service.

---

**Mistake 8: Not publishing artifact before deployment**

If you forget the `PublishBuildArtifacts` task in the Build stage, the deployment stage has nothing to download.

Always include:
```yaml
- task: PublishBuildArtifacts@1
  inputs:
    PathtoPublish: '$(Build.ArtifactStagingDirectory)'
    ArtifactName: 'drop'
    publishLocation: 'Container'
```

---

**Mistake 9: Not downloading artifact in deployment stage**

Similarly, forgetting `download: current` in the deployment stage means the `.zip` file won't be available.

```yaml
# Always include this in deployment stage:
- download: current
  artifact: drop
```

---

**Mistake 10: `.sln` vs `.slnx` mismatch**

Visual Studio 2022 introduced the new `.slnx` format. If your solution file is `.slnx`, use:

```yaml
solution: '**/*.slnx'
```

If it's the old format, use:

```yaml
solution: '**/*.sln'
```

Using the wrong extension means the pipeline won't find your solution file and will fail.

---

## 12. Corrected and Improved YAML

Below is the full YAML with proper formatting, correct indentation, and comments explaining each important section:

```yaml
# ============================================================
# Azure DevOps CI/CD Pipeline for .NET Web Application
# Trigger: Runs on every push to the 'develop' branch
# Stages: Build → DevRelease → QaRelease
# ============================================================

trigger:
- develop   # Automatically trigger pipeline on push to develop branch

# ============================================================
# VARIABLES
# Define reusable values so we don't repeat them
# ============================================================
variables:
  solution: '**/*.slnx'           # Finds the .slnx solution file in any folder
  buildPlatform: 'Any CPU'         # Build for any CPU type
  buildConfiguration: 'Release'    # Use Release mode (not Debug)

# ============================================================
# STAGES
# Three stages: Build → DevRelease → QaRelease
# ============================================================
stages:

  # ==========================================================
  # STAGE 1: BUILD
  # Compiles code and publishes build artifact
  # ==========================================================
  - stage: Build
    displayName: 'Build Stage'
    jobs:
      - job: BuildJob
        displayName: 'Build .NET Application'
        pool:
          vmImage: 'windows-latest'   # Use Windows agent for .NET builds
        steps:

          # Step 1: Install NuGet tool
          - task: NuGetToolInstaller@1
            displayName: 'Install NuGet Tool'

          # Step 2: Restore NuGet packages (like npm install)
          - task: NuGetCommand@2
            displayName: 'Restore NuGet Packages'
            inputs:
              restoreSolution: '$(solution)'

          # Step 3: Build the solution and create a deployment .zip
          - task: VSBuild@1
            displayName: 'Build Solution and Create Package'
            inputs:
              solution: '$(solution)'
              msbuildArgs: >-
                /p:DeployOnBuild=true
                /p:WebPublishMethod=Package
                /p:PackageAsSingleFile=true
                /p:SkipInvalidConfigurations=true
                /p:PackageLocation="$(Build.ArtifactStagingDirectory)"
              platform: '$(buildPlatform)'
              configuration: '$(buildConfiguration)'

          # Step 4: Publish artifact to Azure DevOps storage
          # Artifact name 'drop' will be used in deployment stages
          - task: PublishBuildArtifacts@1
            displayName: 'Publish Artifact: drop'
            inputs:
              PathtoPublish: '$(Build.ArtifactStagingDirectory)'
              ArtifactName: 'drop'
              publishLocation: 'Container'

  # ==========================================================
  # STAGE 2: DEV RELEASE
  # Downloads artifact and deploys to Dev Azure App Service
  # ==========================================================
  - stage: DevRelease
    displayName: 'Release to Dev'
    dependsOn: Build         # This stage runs AFTER Build stage completes
    jobs:
      - deployment: DeployDev
        displayName: 'Deploy to Dev App Service'
        pool:
          vmImage: 'windows-latest'
        environment: Dev     # Links to 'Dev' environment in Azure DevOps
        strategy:
          runOnce:           # Simple deploy-once strategy
            deploy:          # Main lifecycle hook — actual deployment happens here
              steps:

                # Step 1: Download the 'drop' artifact from Build stage
                # After download, artifact is at: $(Pipeline.Workspace)/drop/
                - download: current
                  artifact: drop
                  displayName: 'Download Build Artifact'

                # Step 2: Deploy to Dev Azure App Service
                - task: AzureRmWebAppDeployment@5
                  displayName: 'Deploy to Dev App Service (hdfcloan)'
                  inputs:
                    ConnectionType: 'AzureRM'
                    azureSubscription: 'hdfc'       # Service connection name in Azure DevOps
                    appType: 'webApp'               # Windows Web App
                    WebAppName: 'hdfcloan'          # Dev App Service name
                    packageForLinux: '$(Pipeline.Workspace)/drop/**/*.zip'

  # ==========================================================
  # STAGE 3: QA RELEASE
  # Downloads same artifact and deploys to QA Azure App Service
  # Adds a 60-second wait before deployment
  # ==========================================================
  - stage: QaRelease
    displayName: 'Release to QA'
    dependsOn: Build         # Also depends on Build (not DevRelease)
    jobs:
      - deployment: DeployQa
        displayName: 'Deploy to QA App Service'
        pool:
          vmImage: 'windows-latest'
        environment: Qa      # Links to 'Qa' environment in Azure DevOps
        strategy:
          runOnce:
            deploy:
              steps:

                # Step 1: Wait 60 seconds before starting QA deployment
                # Useful to let Dev stabilize first
                - script: sleep 60
                  displayName: 'Wait 60 Seconds Before QA Deploy'

                # Step 2: Download the 'drop' artifact (same artifact as Dev)
                - download: current
                  artifact: drop
                  displayName: 'Download Build Artifact'

                # Step 3: Deploy to QA Azure App Service
                - task: AzureRmWebAppDeployment@5
                  displayName: 'Deploy to QA App Service (qahdfcloan)'
                  inputs:
                    ConnectionType: 'AzureRM'
                    azureSubscription: 'hdfc'       # Same service connection
                    appType: 'webApp'               # Windows Web App
                    WebAppName: 'qahdfcloan'        # QA App Service name
                    packageForLinux: '$(Pipeline.Workspace)/drop/**/*.zip'
```

---

## 13. Interview Explanation

When asked "Tell me about a CI/CD pipeline you built," here is a professional and simple answer:

> *"I built an Azure DevOps CI/CD pipeline for a .NET web application. The pipeline is written in YAML and has three stages.*
>
> *The first stage is the Build stage. It restores NuGet packages, compiles the solution using VSBuild, creates a deployment package as a ZIP file, and publishes it as a build artifact named 'drop'.*
>
> *The second stage is the Dev Release, which is a deployment job that downloads the 'drop' artifact and deploys it to a Dev Azure App Service using the AzureRmWebAppDeployment task. I used the runOnce deployment strategy since it's a simple single-server environment.*
>
> *The third stage is the QA Release, which deploys the same artifact to the QA App Service — following the 'build once, deploy many times' principle. I also used Azure DevOps Environments to track deployment history and enable approval gates.*
>
> *In addition, I explored the Classic Release Pipeline, which offers the same functionality through a UI-based approach rather than code, making it easier for beginners to start with.*"

---

## 14. Real-Time Project Explanation

Let's put this pipeline in the context of a real software project — a loan application portal for HDFC Bank.

### The Project

The development team is building an **HDFC Loan Application** — a web application where customers can apply for loans. The team uses the `develop` branch for active development.

### The Pipeline's Role in This Project

**The `develop` branch** is where all developers merge their feature code. Every time a developer pushes code here, the pipeline runs automatically — no manual action needed.

**The Build Stage** acts like a quality gate. It compiles the code, restores all dependencies, and packages the application into a deployable `.zip`. If the code has compilation errors, the pipeline fails here and nothing is deployed.

**The Dev App Service (`hdfcloan`)** is the developer's testing environment. After code is compiled and packaged, it is automatically deployed here. Developers can open their browser, go to the Dev URL, and immediately see their changes live. This gives fast feedback — within minutes of pushing code.

**The QA App Service (`qahdfcloan`)** is where the testing team validates the application. The **same `.zip` artifact** that was deployed to Dev is deployed to QA. This is crucial — the same binary is tested in both environments. We don't build again for QA, because rebuilding could produce a slightly different output.

**The 60-second wait in QA** gives Dev deployment time to complete before QA starts. In a real project, this could be replaced with an approval gate — a QA manager reviews and approves the deployment manually.

### The "Build Once, Deploy Many Times" Principle

```
Code is compiled ONCE → ZIP is created ONCE
         ↓
ZIP is deployed to Dev   (artifact: drop)
         ↓
SAME ZIP deployed to QA  (artifact: drop)
         ↓
SAME ZIP deployed to Prod (in future stages)
```

This ensures what is tested in QA is exactly what goes to Production. No surprises.

---

## 15. Final Summary

Here is everything you learned today, summarized in simple bullets:

**YAML Pipeline**
- A pipeline written as code in a `.yml` file
- Stored inside your Git repository
- Version-controlled — every change is tracked
- Triggers automatically on push to `develop` branch
- Has three stages: Build, DevRelease, QaRelease

**Build Stage**
- Installs NuGet, restores packages, builds code, creates `.zip`
- Saves `.zip` to `$(Build.ArtifactStagingDirectory)`
- Publishes artifact to Azure DevOps as `drop`

**Deployment Stage**
- Downloads artifact from `$(Pipeline.Workspace)/drop/`
- Connects to Azure using a service connection
- Deploys `.zip` to Azure App Service

**Key Variables**
- `$(Build.ArtifactStagingDirectory)` → temp folder during build
- `$(Pipeline.Workspace)` → downloaded artifact location during deployment

**Lifecycle Hooks**
- `preDeploy`, `deploy`, `routeTraffic`, `postRouteTraffic`, `on.failure`, `on.success`
- I used only `deploy` — the main hook

**Deployment Strategies**
- `runOnce` — simple, deploy all at once (used in my pipeline)
- `rolling` — deploy in batches to multiple servers
- `canary` — deploy to a percentage of users first

**Classic Release Pipeline**
- UI-based, no YAML needed
- Good for beginners
- Less suited for version control and team collaboration

**Environments**
- `Dev` — for developer testing
- `Qa` — for tester validation
- Tracked in Azure DevOps with deployment history and approvals

**Golden Principle:** Build once → Deploy many times. The same artifact travels from Dev to QA to Production.

---

> **Well done on completing your first Azure DevOps CI/CD pipeline! 🎉**  
> Keep practising, and soon this will become second nature.

---

*End of Notes — `azure-devops-yaml-classic-release-pipeline-notes.md`*
